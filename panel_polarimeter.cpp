/*
 * Hemoxymetrie in non-hemolyzed human whole blood
 * Copyright (C) 2016-2017 Benjamin Redmer
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/*
 * External includes
 */

/* Qt libraries */
#include <QSettings>
#include <QDialog>
#include <QFileDialog>
#include <QMessageBox>
#include "qwt_plot_renderer.h"
#include <QTimer>
#include <QApplication>
#include <QSignalMapper>

/*
 * Internal includes
 */

/* Qt library */

/* General stuff */
#include "application.h"
#include "messages.h"
#include "timer.h"
#include "fft.h"
#include "math_helper.h"

/* Panel stuff */
#include "panel_change_averages.h"
#include "panel_change_time.h"
#include "panel_change_Wave_FFT.h"
#include "panel_item_polarimeter.h"
#include "ui_panel_item_pol.h"
#include "panel_polarimeter.h"
#include "ui_panel_polarimeter.h"
#include "panel.h"
#include "configure_Polarimeter_Measure.h"

/* Spectrometer control */
#include "spectrometer.h"

/*
 * Global variables
 */
extern QSettings *settings;
extern Spectrometer** ptrSpectrometers;
extern unsigned int m_NrDevices;

/* Colors for spectrometers */
extern QString defaultColors[];
double counts_average_time = 0;
double counts_average = 0;

QString greenButton = "color: rgb(0,128,0)", RedButton = "color: rgb(250,0,0)", grayButton = "color: rgb(211,211,211)";

/**
 * @brief Constructor of 'Polarimeter' class
 */
PanelPolarimeter::PanelPolarimeter(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PanelPolarimeter)
{
    /* Set up user interface */
    ui->setupUi(this);

    /* Create signal mapper for panel */
    signalMapper = new QSignalMapper(this);

    /* Set window flags */
    this->setWindowFlags(Qt::Window);

    /* Create new item in Polarimeter Spectrometer List */
    QListWidgetItem *item_Pol = new QListWidgetItem(0);

    /* If we have at least one device selected from the list or available */
    if (m_NrDevices > 0)
    {
        /* The purpose of this list is to inform which spectrometer is in use for the Polarimetry Tab. Be able to see
        its name and change its parameters as the Integration time, number of averages, name and set the Auto Adjust */

        /* By Default, use the First Device checked on the List of Spectrometers from Preview Tab */

        /* Which Spectrometer are we using from the Preview List? - Default the first (0) */
        SpectrometerNumber = 0;

        /* Does the first spectrometer already have a readable name assigned? */
        if (ptrSpectrometers[SpectrometerNumber]->hasReadableName())
        {
            /* Yes. Add the spectrometer to the list using the readable name. */
            devices2.append(new PanelItem_Pol(0, ptrSpectrometers[SpectrometerNumber]->getReadableName()));
        }
        else
        {
            /* No. Add the spectrometer to the list using the serial number. */
            devices2.append(new PanelItem_Pol(0, ptrSpectrometers[SpectrometerNumber]->getSerialNumber()));
        }

        /* Polarimeter Setup Device Initialization */
        devices2[0]->setIntegrationTime(ptrSpectrometers[SpectrometerNumber]->getIntegrationTime());
        devices2[0]->setNumberOfAverages(ptrSpectrometers[SpectrometerNumber]->getNumberOfAverages());
        devices2[0]->setIsSaturated(ptrSpectrometers[SpectrometerNumber]->isSaturated());
        devices2[0]->setIsEnabled(true);

        /* Don't allow resize of item */
        item_Pol->setSizeHint(devices2[0]->size());

        // Polarimeter List Item
        ui->list_devices_Pol->addItem(item_Pol);
        ui->list_devices_Pol->setItemWidget(item_Pol, devices2[0]);

        /* Does the first spectrometer already have a readable name assigned? */
        if (ptrSpectrometers[SpectrometerNumber]->hasReadableName())
        {
            // Polarimeter Plot of Raw Signal
            curves_Pol.append(new QwtPlotCurve(ptrSpectrometers[SpectrometerNumber]->getReadableName()));
            curves_Pol[0]->setItemAttribute(QwtPlotItem::Legend, false);
            curves_Pol.append(new QwtPlotCurve(ptrSpectrometers[SpectrometerNumber]->getReadableName()));
            curves_Pol[1]->setItemAttribute(QwtPlotItem::Legend, false);
        }
        else
        {
            // Polarimeter Plot of Raw Signal
            curves_Pol.append(new QwtPlotCurve(ptrSpectrometers[SpectrometerNumber]->getSerialNumber()));
            curves_Pol[0]->setItemAttribute(QwtPlotItem::Legend, false);
            curves_Pol.append(new QwtPlotCurve(ptrSpectrometers[SpectrometerNumber]->getSerialNumber()));
            curves_Pol[1]->setItemAttribute(QwtPlotItem::Legend, false);
        }

        // Polarimeter Plot of Raw Signal Color
        curves_Pol[0]->setPen(QPen(defaultColors[SpectrometerNumber % 5]));
        curves_Pol[0]->attach(ui->qwtPlot_Pol);

        curves_Pol[1]->setPen(QPen(defaultColors[SpectrometerNumber % 5]));
        curves_Pol[1]->attach(ui->qwtPlot_Pol_Average);

        // Polarimeter buttons and labels signal mapper
        connect(devices2[0]->ui->label_integrationTime, SIGNAL(clicked()), signalMapper, SLOT(map()));
        connect(devices2[0]->ui->label_numberOfAverages, SIGNAL(clicked()), signalMapper, SLOT(map()));
        connect(devices2[0]->ui->label_autoAdjust, SIGNAL(clicked()), signalMapper, SLOT(map()));
        connect(ui->checkBox_AutoSave_Pol_Raw, SIGNAL(clicked()), signalMapper, SLOT(map()));
        connect(ui->checkBox_AutoSave_Pol, SIGNAL(clicked()), signalMapper, SLOT(map()));

        // Polarimeter set mapping for buttons and labels
        signalMapper->setMapping(devices2[0]->ui->label_integrationTime, devices2[0]->ui->label_integrationTime);
        signalMapper->setMapping(devices2[0]->ui->label_numberOfAverages, devices2[0]->ui->label_numberOfAverages);
        signalMapper->setMapping(devices2[0]->ui->label_autoAdjust, devices2[0]->ui->label_autoAdjust);
        signalMapper->setMapping(ui->checkBox_AutoSave_Pol_Raw, ui->checkBox_AutoSave_Pol_Raw);
        signalMapper->setMapping(ui->checkBox_AutoSave_Pol, ui->checkBox_AutoSave_Pol);

        /* Connect event handler */
        connect(qApp, SIGNAL(DataPolIsHere(int, int)), this, SLOT(ReceiveDataIsHerePol(int, int)));

    }

    /* Connect signal mapper action */
    connect(signalMapper, SIGNAL(mapped(QWidget *)), this, SLOT(handleClickEvent(QWidget *)));

    /*
     * Connect and configure the Polarimeter Stuff
     */

    /* Connect buttons in Polarimeter Tab */
    connect(ui->button_Start_Meas_Pol, SIGNAL(clicked()), this, SLOT(toggle_Pol_Measurement()));
    ui->button_Start_Meas_Pol->setStyleSheet(greenButton);
    connect(ui->button_Load_FFTData, SIGNAL(clicked()), this, SLOT(LoadFromFFT()));
    connect(ui->button_AnalyzeRawPolData, SIGNAL(clicked()), this, SLOT(LoadFromRawData()));
    connect(ui->waveToPlotFFT, SIGNAL(clicked()), signalMapper, SLOT(map()));

    /* Connect buttons for saving graphs to pdf */
    connect(ui->Button_Save_Graphs_Pol, SIGNAL(clicked()), this, SLOT(saveGraph_Pol()));

    /* Connect button for Configuration */
    connect(ui->button_calibrate, SIGNAL(clicked()), this, SLOT(toggle_Pol_Calibration()));
    ui->button_Start_Meas_Pol->setStyleSheet("black");
    connect(ui->button_Pol_ConfigureMeasurement, SIGNAL(clicked()), this, SLOT(ConfSetup_Pol_Measurement()));

    /* If there are spectrometers connected, allow Polarimetry Measurement */
    ui->button_Start_Meas_Pol->setDisabled((!m_NrDevices) ? true : false);
    ui->button_Start_Meas_Pol->setStyleSheet((!m_NrDevices) ? grayButton : greenButton);
    ui->button_calibrate->setDisabled((!m_NrDevices) ? true : false);
    ui->button_calibrate->setStyleSheet((!m_NrDevices) ? grayButton : "black");
    ui->checkBox_AutoSave_Pol->setDisabled((!m_NrDevices) ? true : false);
    ui->checkBox_AutoSave_Pol_Raw->setDisabled((!m_NrDevices) ? true : false);

    /* Set axis and title of Raw Signal plot for Polarimeter */
    ui->qwtPlot_Pol->setXAxisTitle("Wavelength (nm)");
    ui->qwtPlot_Pol->setYAxisTitle("ADC counts");
    ui->qwtPlot_Pol->setYAxis(0.0, 65535.0);

    /* Set axis and title of Compensated Signal plot for Polarimeter */
    ui->qwtPlot_Pol_Compensation->setXAxisTitle("Wavelength (nm)");
    ui->qwtPlot_Pol_Compensation->setYAxisTitle("Intensity");
    ui->qwtPlot_Pol_Compensation->setYAxis(0.0, 3);

    /* Set axis and title of w/2w plot for Polarimeter */
    ui->qwtPlot_Pol_w_2w->setXAxisTitle("Wavelength (nm)");
    ui->qwtPlot_Pol_w_2w->setYAxisTitle("Intesity");
    ui->qwtPlot_Pol_w_2w->setYAxis(0.0, 30000000);

    /* Set axis and title of Average over all Wavelenths plot for Polarimeter */
    ui->qwtPlot_Pol_Average->setXAxisTitle("Time (sec)");
    ui->qwtPlot_Pol_Average->setYAxisTitle("Intensity");
    ui->qwtPlot_Pol_Average->setYAxis(0.0, 2000);
    ui->qwtPlot_Pol_Average->setXAxis(0.0, 100);

    /* Set axis and title of Prediction Curve, now in use to show the FFT */
    // ui->qwtPlot_Pol_Prediction->setXAxisTitle("Reference Concentration");
    ui->qwtPlot_Pol_Prediction->setXAxisTitle("Frequency (Hz)");
    ui->qwtPlot_Pol_Prediction->setYAxisTitle("Intensity");
    // ui->qwtPlot_Pol_Prediction->setXAxis(0.0, 100);
    ui->qwtPlot_Pol_Prediction->setXAxis(0.0, 6);
    ui->qwtPlot_Pol_Prediction->setYAxis(0.0, 30000000);

    /* Is there a measurement running? */
    PolMeasurementRunning = false;

    /* Defaults values for x-axis are 400 to 1000 nm */
    double minWavelength = 400.0, maxWavelength = 1000.0;

    unsigned int i = 0;

    /* Are there any spectrometers connected? */
    if (m_NrDevices > 0)
    {
        double startWavelengths[m_NrDevices], stopWavelengths[m_NrDevices];

        /* Loop through spectrometers */
        for (i = 0; i < m_NrDevices; i++)
        {
            /* Get start and stop wavelengths for current spectrometer */
            startWavelengths[i] = ptrSpectrometers[i]->getStartWavelength();
            stopWavelengths[i] = ptrSpectrometers[i]->getStopWavelength();
        }
        /* Find minimum and maximum wavelengths in array */
        minWavelength = getMinimum(startWavelengths, m_NrDevices);
        maxWavelength = getMaximum(stopWavelengths, m_NrDevices);
    }

    /* Update x-axis of graphs depending on Wavelengths */
    ui->qwtPlot_Pol->setXAxis(minWavelength, maxWavelength);
    ui->qwtPlot_Pol_Compensation->setXAxis(minWavelength, maxWavelength);
    ui->qwtPlot_Pol_w_2w->setXAxis(minWavelength, maxWavelength);

    if (m_NrDevices > 0)
    {
        /* Which wavelentgth would you like to see the FFT? */
        signalMapper->setMapping(ui->waveToPlotFFT, ui->waveToPlotFFT);

        /* Disable edition of Spectrometer Data until there is a calibration running */
        devices2[0]->ui->label_autoAdjust->setEnabled(false);
        devices2[0]->ui->label_integrationTime->setEnabled(false);
        devices2[0]->ui->label_numberOfAverages->setEnabled(false);

        averaged_Raw_Signal_Difference.append(0);

        /* Dc, W and 2w Averages */
        Average_DC_Signal = new QwtPlotCurve("DC");
        Average_DC_Signal->setPen(QPen("blue"));
        Average_DC_Signal->setItemAttribute(QwtPlotItem::Legend, false);

        Average_W_Signal = new QwtPlotCurve("W");
        Average_W_Signal->setPen(QPen("red"));
        Average_W_Signal->setItemAttribute(QwtPlotItem::Legend, false);

        Average_2W_Signal = new QwtPlotCurve("2W");
        Average_2W_Signal->setPen(QPen("green"));
        Average_2W_Signal->setItemAttribute(QwtPlotItem::Legend, false);

    }

    ui->tableInfoMeasure->setColumnWidth(0,70);
    ui->tableInfoMeasure->setColumnWidth(1,68);
    ui->tableInfoMeasure->setColumnWidth(2,90);
    ui->tableInfoMeasure->setColumnWidth(3,60);
}

/**
 * @brief Called if a widget on a spectrometer item in list got clicked,
 *        e.g. Integration time label.
 * @param widget Widget which has been clicked
 */
void PanelPolarimeter::handleClickEvent(QWidget *widget)
{
    QLabel *label = qobject_cast<QLabel *>(widget);

    // Fix Bidirectional Update in Polarimeter/Preview Tab!  ?????? See ReadMe Benjamin File.

    /* The integration time label has been clicked */
    if (label == devices2[0]->ui->label_integrationTime)
    {
        PanelChangeTime changeDialog(this);

        /* Set integration time */
        changeDialog.setValue(devices2[0]->getIntegrationTime());

        /* User pressed 'ok' */
        if (QDialog::Accepted == changeDialog.exec())
        {
            /* Get new integration time */
            float intTime = changeDialog.getValue();

            /* Set panel item and device integration time */
            devices2[0]->setIntegrationTime(intTime);
            ptrSpectrometers[SpectrometerNumber]->setIntegrationTime(intTime);

            /* Is the device measuring? */
            if (ptrSpectrometers[SpectrometerNumber]->isMeasuring())
            {
                /* Stop running measurements */
                ptrSpectrometers[SpectrometerNumber]->stopMeasurement();

                /* Prepare for new measurement */
                if (ptrSpectrometers[SpectrometerNumber]->prepareMeasurement())
                {
                    /* If successful, start measurement */
                    ptrSpectrometers[SpectrometerNumber]->startMeasurement(-2);
                }
            }
        }
    }
    /* The auto-adjust label has been clicked */
    else if (label == devices2[0]->ui->label_autoAdjust)
    {
        /* Run automatic adjustment of integration time */
        adjustIntegrationTime();
    }
    /* The number of averages label has been clicked */
    else if (label == devices2[0]->ui->label_numberOfAverages)
    {
        PanelChangeAverages changeDialog(this);

        /* Set number of averages */
        changeDialog.setValue(devices2[0]->getNumberOfAverages());

        /* User pressed 'ok' */
        if (QDialog::Accepted == changeDialog.exec())
        {
            /* Get new number of averages */
            int numberOfAverages = changeDialog.getValue();

            /* Set panel item and device number of averages */
            devices2[0]->setNumberOfAverages(numberOfAverages);
            ptrSpectrometers[SpectrometerNumber]->setNumberOfAverages(numberOfAverages);

            /* Is the device measuring? */
            if (ptrSpectrometers[SpectrometerNumber]->isMeasuring())
            {
                /* Stop running measurements */
                ptrSpectrometers[SpectrometerNumber]->stopMeasurement();

                /* Prepare for new measurement */
                if (ptrSpectrometers[SpectrometerNumber]->prepareMeasurement())
                {
                    /* If successful, start measurement */
                    ptrSpectrometers[SpectrometerNumber]->startMeasurement(-2);
                }
            }
        }
        /* The wavelength to show the FFT label has been clicked */
    } else if(label == ui->waveToPlotFFT){

        PanelChangeWaveFFT changeDialog(this);

        /* Is there loaded information to be shown already? */
        if(FFT_DC != nullptr){
            for (int i =0; i<FFTL.NrWaves;i++){
                changeDialog.setValue(FFTL.wavelengths[i]);
            }
        }else{
            changeDialog.setValue(0);
        }

        /* If there is information to show, then ask for the wavelength to show the FFT */
        if (QDialog::Accepted == changeDialog.exec() && FFT_DC != nullptr)
        {
            /* Get the needed information at the frequencies DC, W and 2W */
            if(FFTL.wavelengths != nullptr){
                selectedWave = changeDialog.getValue();
                for ( int  i = 0; i < FFTL.NrSpectra/2; i++ )
                {
                    /* Other frequencies aren't of interest, then set to zero */
                    if (i != 0 || i != FFTL.f_w || i != 2*FFTL.f_w){
                        FFTL.fft_data[i] = 0;
                    }
                }

                FFTL.fft_data[0] = FFTL.fft_DC[selectedWave];
                FFTL.fft_data[FFTL.f_w] = FFTL.fft_W[selectedWave];
                FFTL.fft_data[2*FFTL.f_w] = FFTL.fft_2W[selectedWave];

                /* Show the selected wavelength of FFT */
                ui->waveToPlotFFT->setText(QString::number(FFTL.wavelengths[selectedWave]));

                /* Clean the layout to show the new selected FFT at the new wavelength */
                FFT_oneWave->detach();
                delete FFT_oneWave;
                FFT_oneWave= nullptr;
                ui->qwtPlot_Pol_Prediction->update();
                ui->qwtPlot_Pol_Prediction->updateLayout();

                /* Plot the FFT Signals */
                plotFFTatSelectedWave(FFTL.fft_data, FFTL.time);
            }
        }
    }

    if(!ui->checkBox_AutoSave_Pol->isChecked() && !ui->checkBox_AutoSave_Pol_Raw->isChecked()){
        /* Show message */
        showWarning("Data might not be saved during the Measurement, FFT Data will be selected by default!", "");
        ui->checkBox_AutoSave_Pol->setChecked(true);
        return;
    }

}

/**
 * @brief Enable polarimeter: If there is a selected spectrometer, then it´s added to the list of Polarimeter Tab.
 */
void PanelPolarimeter::enable_Polarimeter_Measurement(bool activate)
{
    /* Enable measurements and get the information of the current selected spectrometer */
    ui->button_Start_Meas_Pol->setEnabled(activate);
    ui->button_Start_Meas_Pol->setStyleSheet(activate ? greenButton : grayButton);
    ui->button_calibrate->setEnabled(activate);
    ui->button_calibrate->setStyleSheet(activate ? "black" : grayButton);
    devices2[0]->ui->label_autoAdjust->setEnabled(activate);
    devices2[0]->ui->label_integrationTime->setEnabled(activate);
    devices2[0]->ui->label_numberOfAverages->setEnabled(activate);
    devices2[0]->ui->lineEdit_name->setEnabled(activate);
}

/**
 * @brief Load Data from the FFT, Polarimeter Setup
 */
void PanelPolarimeter::LoadFromFFT(void) {

    /* Is there something already analyzed by FFT? */
    if(FFT_DC != nullptr && isFFTData == false){

        /* File doens't exists. Did we ask the user to save the analyzed data from raw data? */
        if (QMessageBox::Yes == QMessageBox::question(this, "Save FFT File", "Do you want to save the FFT analysis from the Loaded Raw Data?",
                                                      QMessageBox::Yes | QMessageBox::No))
        {
            /* Button 'yes' pressed; Save the FFT data to the folder on Bin */
            FFTL.saveFFTtoFile(fileInfo);
        }
    }

    /* What kind of data are we loading? */
    isFFTData = true;

    /* Clean the plots for a new plotting */
    clearPlots();

    /* Load Data Path */
    FFTDataPath = QFileDialog::getOpenFileName(this, QString("Open FFT Data file"), ".", QString("*.TXT"));

    /* File selected by user? */
    if (NULL == FFTDataPath)
    {
        /* No file selected. Dialog aborted. */
        return;
    }else{
        fileInfo = FFTDataPath;
    }

    /* Check format of file; we need at least 4 _ in name */
    if (fileInfo.completeBaseName().count(QLatin1Char('_')) != 5 || fileInfo.completeBaseName().at(fileInfo.completeBaseName().length()-1) !="T")
    {
        /* Show message */
        showWarning("Non valid File for FFT Analysis Loading! \n\n Please check Name and Content of the FFT File", "");
        return;
    }

    /* Show the analyzed data from FFT */
    FFTL.getFFTfromFFTData(fileInfo);

    /* Plot the FFT Signals */
    this->Plot_FFT_Graphs(FFTL.wavelengths, FFTL.time, FFTL.fft_data, FFTL.fft_DC, FFTL.fft_W, FFTL.fft_2W, FFTL.fft_Compensation_Signal);

    /* By default show the wavelength 537,57 nm */
    ui->waveToPlotFFT->setText(QString::number(FFTL.wavelengths[438]));
}

/**
 * @brief Load Data and Perform FFT from Raw Data, Polarimeter Setup
 */
void PanelPolarimeter::LoadFromRawData(void) {

    /* Is there something already analyzed by FFT? */
    if(FFT_DC != nullptr && isFFTData == false){

        /* File doens't exists. Did we ask the user to save the analyzed data from raw data? */
        if (QMessageBox::Yes == QMessageBox::question(this, "Save FFT File", "Do you want to save the FFT analysis from the Loaded Raw Data?",
                                                      QMessageBox::Yes | QMessageBox::No))
        {
            /* Button 'yes' pressed; Save the FFT data to the folder on Bin */
            FFTL.saveFFTtoFile(fileInfo);
        }
    }

    isFFTData = false;

    /* Clear all the plots for a new load of data */
    clearPlots();

    /* Load Data Path */
    RawDataPath = QFileDialog::getOpenFileName(this, QString("Open Raw Data file"), ".", QString("*.CS;*.TXT"));

    /* File selected by user? */
    if (NULL == RawDataPath)
    {
        /* No file selected. Dialog aborted. */
        return;
    }else{
        fileInfo = RawDataPath;
    }

    /* Check format of file; we need at least 4 _ in name */
    if (fileInfo.completeBaseName().count(QLatin1Char('_')) != 4 || !fileInfo.completeBaseName().at(fileInfo.completeBaseName().length()-1).isNumber())
    {
        /* Show message */
        showWarning("Non valid File for Raw Data Analysis! \n\n Please check Name and Content of the Raw Data File", "");
        return;
    }

    /* Data Analysis by FFT */
    FFTL.getFFTfromRawData(fileInfo);

    /* Plot the FFT Signals */
    this->Plot_FFT_Graphs(FFTL.wavelengths, FFTL.time, FFTL.fft_data, FFTL.fft_DC, FFTL.fft_W, FFTL.fft_2W, FFTL.fft_Compensation_Signal);
    ui->waveToPlotFFT->setText(QString::number(FFTL.wavelengths[438]));
}

/**
 * @brief Plot Only the FFT of the Selected Wavelength.
 */
void PanelPolarimeter::plotFFTatSelectedWave(double FFTLfft_data[], double FFTLtime[]){

    /* We want to plot the FFT at the wavelength selected by the user */
    FFT_oneWave = new QwtPlotCurve("");
    FFT_oneWave->setPen(QPen("blue"));
    FFT_oneWave->setItemAttribute(QwtPlotItem::Legend, false);
    ui->waveToPlotFFT->setStyleSheet("QLabel { color: blue; }");
    ui->qwtPlot_Pol_Prediction->setXAxis(0.0,  6*FFTL.f_w/(FFTL.NrSpectra < 1000? 1 : 10));
    ui->qwtPlot_Pol_Prediction->setYAxis(0.0, getMaximum(FFTLfft_data,FFTL.NrSpectra/2)*1.2);
    FFT_oneWave->setSamples(FFTLtime , FFTLfft_data,FFTL.NrSpectra/2);
    FFT_oneWave->attach(ui->qwtPlot_Pol_Prediction);
    FFT_oneWave->show();
    ui->qwtPlot_Pol_Prediction->update();
    ui->qwtPlot_Pol_Prediction->updateLayout();
}

/**
 * @brief Receive the Data to be ploted on the Polarimeter Tab Interface.
 */
void PanelPolarimeter::Plot_FFT_Graphs(double FFTLwavelengths[], double FFTLtime[], double FFTLfft_data[], double FFTLfft_DC[], double FFTLfft_W[]
                                       , double FFTLfft_2W[], double FFTLfft_Compensation_Signal[]){

    /* Plot The FFT at the default Wavelength first */
    plotFFTatSelectedWave(FFTLfft_data, FFTLtime);

    /* Plot the DC, W and 2W Signals */
    ui->qwtPlot_Pol_w_2w->setXAxis(FFTLwavelengths[0], FFTLwavelengths[FFTL.NrWaves-1]);
    ui->qwtPlot_Pol_w_2w->setYAxis(0.0, getMaximum(FFTLfft_DC,FFTL.NrWaves)*1.1);

    FFT_DC = new QwtPlotCurve("DC");
    FFT_W = new QwtPlotCurve("W");
    FFT_2W = new QwtPlotCurve("2W");
    FFT_DC->setPen(QPen("blue"));
    FFT_W->setPen(QPen("red"));
    FFT_2W->setPen(QPen("green"));

    FFT_DC->setSamples(FFTLwavelengths , FFTLfft_DC,FFTL.NrWaves);
    FFT_DC->attach(ui->qwtPlot_Pol_w_2w);
    FFT_W->setSamples(FFTLwavelengths , FFTLfft_W,FFTL.NrWaves);
    FFT_W->attach(ui->qwtPlot_Pol_w_2w);
    FFT_2W->setSamples(FFTLwavelengths , FFTLfft_2W,FFTL.NrWaves);
    FFT_2W->attach(ui->qwtPlot_Pol_w_2w);

    /* Plot the Compensation W/2W Signal */
    Compensation_Signal = new QwtPlotCurve("");
    Compensation_Signal->setPen(QPen("red"));
    ui->qwtPlot_Pol_Compensation->setXAxis(FFTLwavelengths[0], FFTLwavelengths[FFTL.NrWaves-1]);
    ui->qwtPlot_Pol_Compensation->setYAxis(0.0, getMaximum(FFTLfft_Compensation_Signal,FFTL.NrWaves)*1);
    Compensation_Signal->setSamples(FFTLwavelengths , FFTLfft_Compensation_Signal,FFTL.NrWaves);
    Compensation_Signal->setItemAttribute(QwtPlotItem::Legend, false);
    Compensation_Signal->attach(ui->qwtPlot_Pol_Compensation);

    /* Update the Plots and Labels */
    ui->qwtPlot_Pol_w_2w->update();
    ui->qwtPlot_Pol_Compensation->update();
    ui->qwtPlot_Pol_Compensation->updateLayout();
    ui->qwtPlot_Pol_w_2w->updateLayout();
}

/**
 * @brief Add to the List of Spectrometers in Polarimeter Tab the First Checked Spectrometer of the Preview List.
 * This function is called in Panel.cpp
 */
void PanelPolarimeter::SelectedSpectrometer_Polarimeter(void){

    bool devicesEnabled = false;

    unsigned int i = 0;

    /* Loop through devices */
    for (i = 0; i < m_NrDevices; i++)
    {
        devicesEnabled = devicesEnabled || ptrSpectrometers[i]->isEnabled();
    }

    if(devicesEnabled == false){
        /* Blank the List of spectrometers and ask to choose one from the preview list. */
        devices2[0]->setClickableLabelsEnabled(false);
        devices2[0]->setName("");

    }else{
        /* Loop through devices */
        for (i = 0; i < m_NrDevices; i++)
        {
            if( ptrSpectrometers[i]->isEnabled()){

                devices2[0]->setIsEnabled(true);
                devices2[0]->setClickableLabelsEnabled(true);
                devices2[0]->setIntegrationTime(ptrSpectrometers[i]->getIntegrationTime());
                devices2[0]->setNumberOfAverages(ptrSpectrometers[i]->getNumberOfAverages());

                /* Save the spectrometer that we are using if it's not the first*/
                SpectrometerNumber = i;

                if (ptrSpectrometers[i]->hasReadableName())
                {
                    devices2[0]->setName(ptrSpectrometers[i]->getReadableName());
                }else{
                    devices2[0]->setName(ptrSpectrometers[i]->getSerialNumber());
                }
                /* Just use the first spectrometer checked from the list */
                break;
            }
        }
    }

    /* Update buttons */
    ui->button_Start_Meas_Pol->setEnabled(devicesEnabled ? true : false);
    ui->button_Start_Meas_Pol->setStyleSheet(devicesEnabled ? greenButton : grayButton);
    ui->button_calibrate->setEnabled(devicesEnabled ? true : false);
    ui->button_calibrate->setStyleSheet(devicesEnabled ? "black" : grayButton);
}

/**
 * @brief Remove all plots of the Interface before to load any other plots.
 */
void PanelPolarimeter::clearPlots(void) {

    /* Is there any information ploted already? */
    if(FFT_DC!=nullptr)
    {
        FFT_DC->detach();
        FFT_W->detach();
        FFT_2W->detach();
        FFT_oneWave->detach();
        Compensation_Signal->detach();
    }

    /* Delete all the existing data ploted on the interface */
    delete FFT_DC;
    FFT_DC = nullptr;
    delete FFT_W;
    FFT_W = nullptr;
    delete FFT_2W;
    FFT_2W = nullptr;
    delete Compensation_Signal;
    Compensation_Signal  = nullptr;
    delete FFT_oneWave;
    FFT_oneWave= nullptr;

    ui->qwtPlot_Pol_w_2w->update();
    ui->qwtPlot_Pol_Compensation->update();
    ui->qwtPlot_Pol_Prediction->update();
    ui->qwtPlot_Pol_Prediction->updateLayout();
    ui->waveToPlotFFT->setText("");
}

/**
 * @brief Save All graphs from the Polarimeter Setup
 */
void PanelPolarimeter::saveGraph_Pol(void) {

    /* Get the folder to save the different PDF files with the plots */
    QString url = QFileDialog::getExistingDirectory(this, tr("Open Directory"), "", QFileDialog::ShowDirsOnly
                                                    | QFileDialog::DontResolveSymlinks);
    /* Check export path */
    if (!url.isEmpty())
    {
        QwtPlotRenderer renderer;
        /* Save to disk */
        renderer.renderDocument(ui->qwtPlot_Pol_w_2w, url + "/DC_W_2W.pdf" , "pdf",QSizeF(300, 200));
        renderer.renderDocument(ui->qwtPlot_Pol_Compensation, url + "/W_Over_2W.pdf" , "pdf",QSizeF(300, 200));
    }
}

/**
 * @brief Toggles Measurements of the Polarimeter
 */
void PanelPolarimeter::toggle_Pol_Measurement(void)
{
    /* Pol Measurement running or not? */
    if(!PolMeasurementRunning)
    {
        /* Is there a Profile Loaded? */
        if(measurement_Pol_profileLoaded){
            start_Pol_Measurement();
        }else{
            /* Show message */
            showCritical("Please Load a Measurement Profile to Start a Measurement", "");
            return;
        }
    }
    else
    {
        /* Pol Measurement running at the moment. Stop it. */
        stop_Pol_Measurement();
    }
}

/**
 * @brief Start Measurments for the Polarimeter Setup
 */
void PanelPolarimeter::start_Pol_Measurement(void) {

    /* Enable / Disable buttons when measuring */
    ui->button_Load_FFTData->setEnabled(false);
    ui->button_AnalyzeRawPolData->setEnabled(false);
    ui->button_Start_Meas_Pol->setEnabled(false);
    ui->checkBox_AutoSave_Pol->setEnabled(false);
    ui->checkBox_AutoSave_Pol_Raw->setEnabled(false);
    ui->button_calibrate->setEnabled(false);
    ui->button_Pol_ConfigureMeasurement->setEnabled(false);

    /* Is spectrometer enabled? */
    devices2[0]->setIsEnabled(false);

    /* Prepare for new measurement */
    //if (ptrSpectrometers[SpectrometerNumber]->prepareMeasurement())
    // {
    /* If successful, start measurement */
    //     ptrSpectrometers[SpectrometerNumber]->startMeasurement(-2);
    // }

    /* Remember Polarimeter Measurement is Running */
    PolMeasurementRunning = true;

    /* Update pol meas button */
    ui->button_Start_Meas_Pol->setText("Stop Measurement");
    ui->button_Start_Meas_Pol->setStyleSheet(RedButton);
    ui->button_Start_Meas_Pol->setEnabled(true);

    /* Measurement Routine */
    ui->currentProgressBar_Pol->setValue(0);
    ui->TotalProgressBar_Pol->setValue(0);

    QElapsedTimer timer;

    /* Start timer */
    timer.start();

    unsigned int i = 0;

    do
    {
        /* Check if we have more entries to do */
        if (i < (unsigned int)ConfigureMeasurement.timePoint.length())
        {
            /* Next measurement starts now? */
            if (timer.elapsed() >= ConfigureMeasurement.timePoint[i])
            {
                /* Generate absolute path for StoreToRAM files */
                fileInfo = QFileInfo(ConfigureMeasurement.path);
                QString path(fileInfo.absoluteDir().path() + "/");
                path.append(ConfigureMeasurement.fileName[i] + ".CS");

                /* Check if spectrometer is still measuring */
                if (ptrSpectrometers[SpectrometerNumber]->isMeasuring())
                {
                    /* Show message */
                    showWarning("Spectrometer is still measuring! Too small time steps?", "");
                }
                else
                {
                    /* Configure spectrometer */
                    ptrSpectrometers[SpectrometerNumber]->setIntegrationTime(ConfigureMeasurement.integrationTime);
                    ptrSpectrometers[SpectrometerNumber]->setNumberOfAverages(ConfigureMeasurement.numberOfAverages);

                    /* Prepare StoreToRAM measurement */
                    ptrSpectrometers[SpectrometerNumber]->forceStoreToRAM(path, ConfigureMeasurement.numSpectra);
                    if (ptrSpectrometers[SpectrometerNumber]->prepareMeasurement())
                    {
                        /* Start measurement */
                        ptrSpectrometers[SpectrometerNumber]->startMeasurement(2);
                    }
                }

                /* Select the row that belongs to the measurement */
                ui->Table_Measurements_Pol->setSelectionBehavior(QAbstractItemView::SelectRows);
                ui->Table_Measurements_Pol->setSelectionMode(QAbstractItemView::SingleSelection);
                ui->Table_Measurements_Pol->selectRow(i);
                ui->Table_Measurements_Pol->setSelectionMode(QAbstractItemView::NoSelection);

                /* Go to next entry */
                i++;
            }
        }

        int progress = 0;

        /* Calculate progress for first entry? */
        if (i == 0)
        {
            progress = 100 - (ConfigureMeasurement.timePoint[0] - timer.elapsed()) / ConfigureMeasurement.timePoint[0] * 100;
        }
        /* Calculate progress for last entry? */
        else if (i >= (unsigned int)ConfigureMeasurement.timePoint.length())
        {
            /* Abort while loop if no measurement is running anymore */
            PolMeasurementRunning = ptrSpectrometers[SpectrometerNumber]->isMeasuring();

            /* Progress done */
            progress = 100;
        }
        /* Calculate progress for any other entry? */
        else
        {
            /* Current progress is calculated by the difference between actual time and next measurement */
            progress = 100 - (ConfigureMeasurement.timePoint[i] - timer.elapsed()) / (ConfigureMeasurement.timePoint[i] - ConfigureMeasurement.timePoint[i-1]) * 100;
        }

        /* Update progress bars */
        ui->currentProgressBar_Pol->setValue(progress);
        ui->TotalProgressBar_Pol->setValue((i) * 100 / ConfigureMeasurement.timePoint.count());

        /* Handle events and update UI */
        Application::processEvents();

        /* Wait 1 ms */
        Timer::msleep(1);

        if(timer.elapsed() % 1000 == 0){
            plotAverages(timer.elapsed()/1000);
        }
    }
    while (PolMeasurementRunning);

    /* Stop measurements */
    PolMeasurementRunning = false;


    /* Reset selected row */
    ui->Table_Measurements_Pol->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->Table_Measurements_Pol->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->Table_Measurements_Pol->selectRow(0);
    ui->Table_Measurements_Pol->setSelectionMode(QAbstractItemView::NoSelection);

    /* Set progress bars to 100 percent */
    ui->currentProgressBar_Pol->setValue(0);
    ui->TotalProgressBar_Pol->setValue(0);

    stop_Pol_Measurement();
}

/**
 * @brief Stop Measurments for the Polarimeter Setup
 */
void PanelPolarimeter::stop_Pol_Measurement(void) {

    /* Disable preview button */ //???   Read Benjamin File

    ui->button_Load_FFTData->setEnabled(true);
    ui->button_AnalyzeRawPolData->setEnabled(true);

    /* Stop measurement */
    //ptrSpectrometers[SpectrometerNumber]->stopMeasurement();

    devices2[0]->setIsEnabled(true);

    /* Handle events and update UI */
    Application::processEvents();

    /* No Polarimetric Measurement running anymore */
    PolMeasurementRunning = false;

    /* Update pol meas button */
    ui->button_Start_Meas_Pol->setText("Start Measurement");
    ui->button_Start_Meas_Pol->setStyleSheet(greenButton);
    ui->button_Start_Meas_Pol->setEnabled(true);

    ui->checkBox_AutoSave_Pol->setEnabled(true);
    ui->checkBox_AutoSave_Pol_Raw->setEnabled(true);
    ui->button_calibrate->setEnabled(true);
    ui->button_Pol_ConfigureMeasurement->setEnabled(true);
}

/**
 * @brief Configuration of Measurments
 */
void PanelPolarimeter::ConfSetup_Pol_Measurement(void) {

    ConfigureMeasurement.exec();

    if(ConfigureMeasurement.configured){

        measurement_Pol_profileLoaded = true;

        /* Prevent user from resizing the header */
        ui->Table_Measurements_Pol->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
        ui->tableInfoMeasure->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);

        /* Left align column titles */
        ui->Table_Measurements_Pol->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);
        ui->tableInfoMeasure->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);

        /* Prevent user from editing the cells */
        ui->Table_Measurements_Pol->setEditTriggers(QAbstractItemView::NoEditTriggers);
        ui->tableInfoMeasure->setEditTriggers(QAbstractItemView::NoEditTriggers);

        /* Adjust table widget */
        ui->Table_Measurements_Pol->setColumnWidth(0, 80);
        ui->Table_Measurements_Pol->setColumnWidth(1, 130);

        /* Zero row count */
        ui->Table_Measurements_Pol->setRowCount(0);

        unsigned int i = 0;

        /* Loop through elements */
        for (i = 0; i < (unsigned int) ConfigureMeasurement.timePoint.length(); i++)
        {

            /* At least second entry? */
            if (i > 0)
            {
                /* Calculate duration of entry before current entry */
                double duration =  ConfigureMeasurement.numSpectra *  ConfigureMeasurement.integrationTime *  ConfigureMeasurement.numberOfAverages;

                /* Check if there's a time overlap between last and current entry */
                if (( ConfigureMeasurement.timePoint[i - 1] + duration) >  ConfigureMeasurement.timePoint[i])
                {
                    /* Zero row count */
                    ui->Table_Measurements_Pol->setRowCount(0);
                    return;
                }
            }

            /* Increase current row count */
            ui->Table_Measurements_Pol->setRowCount(ui->Table_Measurements_Pol->rowCount() + 1);

            QLabel *nt2 = new QLabel();
            /* Create label for time point */
            nt2->setText(QString::number(ConfigureMeasurement.timePoint.at(i)));
            nt2->setStyleSheet("QLabel { margin-left: 2px; }");
            ui->Table_Measurements_Pol->setCellWidget(i, 0, nt2);

            QLabel *nt3 = new QLabel();
            /* Create label for file name */
            nt3->setText(ConfigureMeasurement.fileName.at(i));
            nt3->setStyleSheet("QLabel { margin-left: 2px; }");
            ui->Table_Measurements_Pol->setCellWidget(i, 1, nt3);

        }

        QLabel *nt4 = new QLabel();
        /* Create label for number of spectra */
        nt4->setText(QString::number(ConfigureMeasurement.numSpectra));
        nt4->setStyleSheet("QLabel { margin-left: 2px; }");
        ui->tableInfoMeasure->setCellWidget(0, 0, nt4);

        QLabel *nt7 = new QLabel();
        /* Create label for Frequency Measurement */
        nt7->setText(QString::number(ConfigureMeasurement.freqToMeasure));
        nt7->setStyleSheet("QLabel { margin-left: 2px; }");
        ui->tableInfoMeasure->setCellWidget(0, 1, nt7);

        QLabel *nt5 = new QLabel();
        /* Create label for integration time */
        nt5->setText(QString::number(ConfigureMeasurement.integrationTime));
        nt5->setStyleSheet("QLabel { margin-left: 2px; }");
        ui->tableInfoMeasure->setCellWidget(0, 2, nt5);

        QLabel *nt6 = new QLabel();
        /* Create label for number of averages */
        nt6->setText(QString::number(ConfigureMeasurement.numberOfAverages));
        nt6->setStyleSheet("QLabel { margin-left: 2px; }");
        ui->tableInfoMeasure->setCellWidget(0, 3, nt6);

        ptrSpectrometers[SpectrometerNumber]->setIntegrationTime(ConfigureMeasurement.integrationTime);
        devices2[0]->ui->label_integrationTime->setText(QString::number(ptrSpectrometers[SpectrometerNumber]->getIntegrationTime()));
        ptrSpectrometers[SpectrometerNumber]->setNumberOfAverages(ConfigureMeasurement.numberOfAverages);
        devices2[0]->ui->label_numberOfAverages->setText(QString::number(ptrSpectrometers[SpectrometerNumber]->getNumberOfAverages()));

        /* Select first row */
        ui->Table_Measurements_Pol->selectRow(0);
    }
}

/**
 * @brief Toggles Calibration of the Polarimeter
 */
void PanelPolarimeter::toggle_Pol_Calibration(void)
{
    /* Pol Calibration running or not? */
    if(!PolMeasurementRunning)
    {
        /* No Pol Measurement running at the moment. Start it. */
        if(!measurement_Pol_profileLoaded){
            /* Show message */
            showWarning("If you don't load a Measurement Profile for Calibration, changes on Spectrometer Parameters here won't affect the measurements settings", "");
        }

        /* No Pol Calibration running at the moment. Start it. */
        Calibrate_Pol_Start();
        clearPlots();
    }
    else
    {
        /* Pol Calibration running at the moment. Stop it. */
        Calibrate_Pol_Stop();
    }
}


/**
 * @brief Start to Calibrate the Spectrometer Settings and the Polarimeter Setup
 */
void PanelPolarimeter::Calibrate_Pol_Start(void) {

    /* Enable edition of Spectrometer Data until there is no calibration running */
    devices2[0]->ui->label_autoAdjust->setEnabled(true);
    devices2[0]->ui->label_integrationTime->setEnabled(true);
    devices2[0]->ui->label_numberOfAverages->setEnabled(true);

    /* Enable / Disable buttons when measuring */
    ui->button_Load_FFTData->setEnabled(false);
    ui->button_AnalyzeRawPolData->setEnabled(false);
    ui->button_Start_Meas_Pol->setEnabled(false);
    ui->checkBox_AutoSave_Pol->setEnabled(false);
    ui->checkBox_AutoSave_Pol_Raw->setEnabled(false);
    ui->button_calibrate->setEnabled(false);
    ui->button_Pol_ConfigureMeasurement->setEnabled(false);

    /* Is spectrometer enabled? */
    devices2[0]->setIsEnabled(false);

    /* Prepare for new measurement */
    if (ptrSpectrometers[SpectrometerNumber]->prepareMeasurement())
    {
        /* If successful, start measurement */
        ptrSpectrometers[SpectrometerNumber]->startMeasurement(-2);
    }

    /* Handle events and update UI */
    Application::processEvents();

    /* Remember Polarimeter Measurement is Running */
    PolMeasurementRunning = true;

    /* Update pol meas button */
    ui->button_calibrate->setText("Stop Calibration");
    ui->button_calibrate->setStyleSheet(RedButton);
    ui->button_calibrate->setEnabled(true);
    ui->button_Start_Meas_Pol->setStyleSheet(grayButton);
}

/**
 * @brief Stop the Calibration of the Spectrometer Settings and the Polarimeter Setup
 */
void PanelPolarimeter::Calibrate_Pol_Stop(void) {

    /* Disable edition of Spectrometer Data until there is a calibration running */
    devices2[0]->ui->label_autoAdjust->setEnabled(false);
    devices2[0]->ui->label_integrationTime->setEnabled(false);
    devices2[0]->ui->label_numberOfAverages->setEnabled(false);

    ui->button_Load_FFTData->setEnabled(true);
    ui->button_AnalyzeRawPolData->setEnabled(true);
    ui->button_Start_Meas_Pol->setEnabled(true);

    /* Stop measurement */
    ptrSpectrometers[SpectrometerNumber]->stopMeasurement();

    devices2[0]->setIsEnabled(true);

    /* Handle events and update UI */
    Application::processEvents();

    /* No Polarimetric Measurement running anymore */
    PolMeasurementRunning = false;

    /* Update pol meas button */
    ui->button_calibrate->setText("Calibrate");
    ui->button_calibrate->setStyleSheet("black");
    ui->button_calibrate->setEnabled(true);

    ui->checkBox_AutoSave_Pol->setEnabled(true);
    ui->checkBox_AutoSave_Pol_Raw->setEnabled(true);
    ui->button_Pol_ConfigureMeasurement->setEnabled(true);
    ui->button_Start_Meas_Pol->setStyleSheet(greenButton);
}

/**
 * @brief Gets curve's visibility
 * @return TRUE if curve is visible, else FALSE
 */
bool PanelPolarimeter::isCurveVisible()
{
    return curves_Pol[0]->isVisible();
}

/**
 * @brief Sets curve's visibility
 * @param[in] value TRUE if curve should be visible, else FALSE
 */
void PanelPolarimeter::setCurveVisible(bool value)
{
    curves_Pol[0]->setVisible(value);
    curves_Pol[1]->setVisible(value);
}

/**
 * @brief Updates the graph
 */
void PanelPolarimeter::updateGraph(void)
{
    /* Update the graph */
    ui->qwtPlot_Pol->update();
    ui->qwtPlot_Pol_Average->update();
}

/**
 * @brief Data from spectrometer has arrived
 * @param WParam
 * @param LParam
 */
void PanelPolarimeter::ReceiveDataIsHerePol(int WParam, int LParam)
{

    /* Successful gained data */
    if (WParam >= ERR_SUCCESS)
    {
        /* Graph needs update? */
        bool needUpdate = false;

        /* Did the current spectrometer sent the data? */
        if ((LParam == ptrSpectrometers[SpectrometerNumber]->getHandle()) && (ptrSpectrometers[SpectrometerNumber]->getNumberOfPixels() > 0))
        {
            /* Normal measurement? */
            if (ERR_SUCCESS == WParam)
            {
                /* Handle event */
                ptrSpectrometers[SpectrometerNumber]->handleEvent();

                /* Update saturation status */
                devices2[0]->setIsSaturated(ptrSpectrometers[SpectrometerNumber]->isSaturated());

                /* Graph needs update */
                needUpdate = true;
            }            /* Start Store to RAM measurement */
            else
            {
                /* Get StoreToRAM path */
                QString path = ptrSpectrometers[SpectrometerNumber]->getStoreToRAMPath();

                /* Show error if no path is choosen */
                if (path.isEmpty())
                {
                    /* Show critical error */
                    showCritical(QString("No path for StoreToRAM file specified!"), QString(""));
                    return;
                }

                /* Allocate memory for spectra (number of pixel elements multiplied with the number of measurements) */
                double *a_pSpectrum = new double[ptrSpectrometers[SpectrometerNumber]->getNumberOfPixels() * (unsigned int)WParam];

                /* Not able to allocate memory? */
                if (nullptr == a_pSpectrum)
                {
                    /* Show critical error */
                    showCritical(QString("Not enough memory for StoreToRAM data!"), QString(""));
                    return;
                }

                unsigned int j = 1;

                /* Loop through number of measurements */
                for (j = 1; j <= (unsigned int)WParam; j++)
                {
                    /* Did the current spectrometer sent the data? */
                    if ((LParam == ptrSpectrometers[SpectrometerNumber]->getHandle()) && (ptrSpectrometers[SpectrometerNumber]->getNumberOfPixels() > 0))
                    {
                        /* Handle event */
                        ptrSpectrometers[SpectrometerNumber]->handleEvent();

                        /* Update saturation status */
                        devices2[0]->setIsSaturated(ptrSpectrometers[SpectrometerNumber]->isSaturated());

                        /* Save counts */
                        double *temp = ptrSpectrometers[SpectrometerNumber]->getCounts();

                        unsigned int k = 0;

                        /* Loop through pixel values */
                        for (k = 0; k < ptrSpectrometers[SpectrometerNumber]->getNumberOfPixels(); k++)
                        {
                            *(a_pSpectrum + (ptrSpectrometers[SpectrometerNumber]->getNumberOfPixels() * (j - 1)) + k) = *(temp + k);
                        }
                    }
                }

                /* Graph needs update */
                needUpdate = true;

                /*
             * Got all StoreToRAM data, save it to disk now!
             */

                FILE *file = fopen(path.toLatin1().data(), "wt");

                /* Check file handle */
                if (nullptr == file)
                {
                    /* Free memory */
                    delete[] a_pSpectrum;
                    a_pSpectrum = nullptr;

                    /* Show message */
                    showCritical(QString("Unable to create file '%1'.").arg(ptrSpectrometers[SpectrometerNumber]->getStoreToRAMPath()), QString(""));
                    return;
                }

                /* Write header */
                writeToFile(file, a_pSpectrum, WParam);

                /* Close file */
                fclose(file);
                file = nullptr;
                /* Free memory */
                delete[] a_pSpectrum;
                a_pSpectrum = nullptr;

                /* Then Do FFT */

                isFFTData = false;

                /* Clear all the plots for a new load of data */
                clearPlots();

                fileInfo = QFileInfo(path);

                /* Data Analysis by FFT */
                FFTL.getFFTfromRawData(fileInfo);

                /* Plot the FFT Signals */
                this->Plot_FFT_Graphs(FFTL.wavelengths, FFTL.time, FFTL.fft_data, FFTL.fft_DC, FFTL.fft_W, FFTL.fft_2W, FFTL.fft_Compensation_Signal);
                ui->waveToPlotFFT->setText(QString::number(FFTL.wavelengths[438]));

                if(ui->checkBox_AutoSave_Pol->isChecked()){
                    FFTL.saveFFTtoFile(fileInfo);
                }

                if(!ui->checkBox_AutoSave_Pol_Raw->isChecked()){
                    remove(path.toLatin1().data());
                }

                /* Spectrometer finished measurement */
                ptrSpectrometers[SpectrometerNumber]->bMeasuring = false;
            }
        }

        /* Update curve data */
        curves_Pol[0]->setSamples(ptrSpectrometers[SpectrometerNumber]->getWavelengths(), ptrSpectrometers[SpectrometerNumber]->getCounts(),
                                  ptrSpectrometers[SpectrometerNumber]->getNumberOfPixels());

        liveFFTCalibration();

        /* Does the graph needs a update? */
        if (needUpdate)
        {
            /* Update the graph */
            ui->qwtPlot_Pol->update();
            ui->qwtPlot_Pol_Average->update();
        }
    }
}

/**
 * @brief Live Analysis and Plot of the Raw Signal
 */
void PanelPolarimeter::liveFFTCalibration()
{

    //int NrLiveSamples = 200;
    double *counts = new double[ptrSpectrometers[SpectrometerNumber]->getNumberOfPixels()];
    counts = ptrSpectrometers[SpectrometerNumber]->getCounts();

    /* Average Raw Signal */
    for(int j = 0; j < ptrSpectrometers[SpectrometerNumber]->getNumberOfPixels(); j++ ){
        counts_average = counts_average + counts[j];
    }

    counts_average = counts_average/ptrSpectrometers[SpectrometerNumber]->getNumberOfPixels();

    counts_average_time = counts_average_time + 1;

    if(counts_average_time > 1){
        averaged_Raw_Signal_Difference.append(abs(averaged_Raw_Signal - counts_average));
        averaged_Raw_Signal = counts_average;
    }else{
        averaged_Raw_Signal_Difference.append(0);
        averaged_Raw_Signal = counts_average;
    }

    averaged_Raw_Signal_time.append(counts_average_time);

    /* Plot in Average layout */

    double maxtime = *std::max_element(averaged_Raw_Signal_time.begin(), averaged_Raw_Signal_time.end());

    if(averaged_Raw_Signal_time.length() % 500 == 0){
        ui->qwtPlot_Pol_Average->setXAxis(maxtime, maxtime+500);
    }

    /* Raw Signal Restart */
    if(averaged_Raw_Signal_time.length() > 1000){
        averaged_Raw_Signal_Difference.resize(0);
        averaged_Raw_Signal_time.resize(0);
        AverageDC.resize(0);
        AverageW.resize(0);
        Average2W.resize(0);
        ui->qwtPlot_Pol_Average->setXAxis(maxtime, maxtime+500);
    }

    ui->qwtPlot_Pol_Average->setYAxis(0.0, *std::max_element(averaged_Raw_Signal_Difference.begin(), averaged_Raw_Signal_Difference.end())+500);

    curves_Pol[1]->setSamples(averaged_Raw_Signal_time, averaged_Raw_Signal_Difference);

    /*
    if(averaged_Raw_Signal_time.length() % NrLiveSamples == 0){
        //  FFTL.Calculate_Live_FFT(Raw_signal); Do we have to create a temporal file with the 200 data of the 1400 wavelength? how to solve this?
    }*/
}

/**
 * @brief Automatic adjustment of integration time
 */
void PanelPolarimeter::adjustIntegrationTime()
{
    /* Remember whether the spectrometer is measuring or not */
    bool wasMeasuring = ptrSpectrometers[SpectrometerNumber]->isMeasuring();

    /* Is the spectrometer measuring? */
    if (wasMeasuring)
    {
        /* Yes, so stop the measurement */
        ptrSpectrometers[SpectrometerNumber]->stopMeasurement();

        /* Handle events and update UI */
        Application::processEvents();
    }

    /* If high-resolution ADC is enabled, try to reach 60000 counts; else 15000 */
    double targetCounts = ptrSpectrometers[SpectrometerNumber]->getUseHighResADC() ? 60000.0 : 15000.0;

    /* Remember whether the spectrometer has dynamic dark correction enabled or not */
    bool hadDynamicDarkCorrection = ptrSpectrometers[SpectrometerNumber]->getDynamicDarkCorrection();

    /* Remember current number of averages */
    int numberOfAverages = ptrSpectrometers[SpectrometerNumber]->getNumberOfAverages();

    /* Enable dynamic dark correction */
    ptrSpectrometers[SpectrometerNumber]->setForgetPercentage(100);
    ptrSpectrometers[SpectrometerNumber]->setDynamicDarkCorrection(true);

    /* Reduce number of averages to minimum */
    ptrSpectrometers[SpectrometerNumber]->setNumberOfAverages(1);

    /* Maximum counts from last spectrum */
    double maxCounts = 0.0;

    /* Number of loops done for adjustment */
    unsigned char loopCounts = 0;

    do
    {
        /* Prepare measurement; only continue if successful */
        if (ptrSpectrometers[SpectrometerNumber]->prepareMeasurement())
        {
            /* Number of measurements done */
            unsigned long before = 0;

            /* Get current number of measurements done */
            before = ptrSpectrometers[SpectrometerNumber]->getMeasCount();

            /* Measure one spectra */
            if (ptrSpectrometers[SpectrometerNumber]->startMeasurement(1))
            {
                /* Wait until done; update event loop */
                do
                {
                    /* Handle events and update UI */
                    Application::processEvents();
                }
                while (ptrSpectrometers[SpectrometerNumber]->getMeasCount() < before + 1);
            }
            else
            {
                /* Restore spectrometer settings */
                ptrSpectrometers[SpectrometerNumber]->setDynamicDarkCorrection(hadDynamicDarkCorrection);
                ptrSpectrometers[SpectrometerNumber]->setNumberOfAverages(numberOfAverages);

                /* Show warning */
                showWarning(QString("Unable to start measurement on spectrometer %1!").arg(ptrSpectrometers[SpectrometerNumber]->getSerialNumber()), QString(""));
                break;
            }
        }
        else
        {
            /* Restore spectrometer settings */
            ptrSpectrometers[SpectrometerNumber]->setDynamicDarkCorrection(hadDynamicDarkCorrection);
            ptrSpectrometers[SpectrometerNumber]->setNumberOfAverages(numberOfAverages);

            /* Show warning */
            showWarning(QString("Unable to prepare measurement on spectrometer %1!").arg(ptrSpectrometers[SpectrometerNumber]->getSerialNumber()), QString(""));
            break;
        }

        /* Get maximum counts from last spectrum */
        maxCounts = ptrSpectrometers[SpectrometerNumber]->getMaxCounts();

        /* Do we have more than 5% deviation from target? */
        if ((maxCounts > (targetCounts + (targetCounts * 5 / 100))) ||
                (maxCounts < (targetCounts - (targetCounts * 5 / 100))))
        {
            /* Get current integration time */
            float intTime = devices2[SpectrometerNumber]->getIntegrationTime();

            double scaleFactor = 0.0;

            /* Is spectrometer saturated? */
            if (!ptrSpectrometers[SpectrometerNumber]->isSaturated())
            {
                /* Spectrometer is not saturated, so calculate scale factor by maximum counts */
                scaleFactor = targetCounts / maxCounts;
            }
            else
            {
                /* Spectrometer is saturated, so divide integration time by two */
                scaleFactor = 0.5;
            }

            /* Scale integration time with calculated factor; limit number to 2 decimal places */
            intTime = (float)(((int)(intTime * scaleFactor * 100)) / 100.0);

            /* New integration time greater than 10 seconds? */
            if (intTime > 10000.0f)
            {
                /* Limit to 10 seconds */
                intTime = 10000.0f;

                /* Show warning */
                showWarning(QString("Integration time on spectrometer %1 is limited to 10 seconds!").arg(ptrSpectrometers[SpectrometerNumber]->getSerialNumber()), QString(""));
            }

            /* Integration time smaller than 1.05 ms? */
            if (intTime < 1.05f)
            {
                /* Limit to 1.05 ms */
                intTime = 1.05f;
            }

            /* Set panel item and device new integration time */
            devices2[0]->setIntegrationTime(intTime);
            ptrSpectrometers[SpectrometerNumber]->setIntegrationTime(intTime);
        }

        /* Increase loop counter */
        loopCounts++;

        /* Limit number of loops for adjustment to 10 */
        if (loopCounts >= 10)
        {
            /* Show warning */
            showWarning(QString("Unable to adjust integration time on spectrometer %1 within 10 iterations!").arg(ptrSpectrometers[SpectrometerNumber]->getSerialNumber()), QString(""));
            break;
        }
    }
    /* Leave loop if counts have less than 5% deviation from target */
    while ((maxCounts > (targetCounts + (targetCounts * 5 / 100))) ||
           (maxCounts < (targetCounts - (targetCounts * 5 / 100))));

    /* Restore spectrometer settings */
    ptrSpectrometers[SpectrometerNumber]->setDynamicDarkCorrection(hadDynamicDarkCorrection);
    ptrSpectrometers[SpectrometerNumber]->setNumberOfAverages(numberOfAverages);

    /* Was the spectrometer measuring before (e.g. preview)? */
    if (wasMeasuring)
    {
        /* Yes, so prepare the measurement */
        if (ptrSpectrometers[SpectrometerNumber]->prepareMeasurement())
        {
            /* Restart the measurement */
            if (!ptrSpectrometers[SpectrometerNumber]->startMeasurement(-2))
            {
                /* Show warning */
                showWarning(QString("Unable to start measurement on spectrometer %1!").arg(ptrSpectrometers[SpectrometerNumber]->getSerialNumber()), QString(""));
                return;
            }
        }
        else
        {
            /* Show warning */
            showWarning(QString("Unable to prepare measurement on spectrometer %1!").arg(ptrSpectrometers[SpectrometerNumber]->getSerialNumber()), QString(""));
            return;
        }
    }
}

/**
 * @brief Write the Raw Data to a File
 */
void PanelPolarimeter::writeToFile(FILE *file, double *a_pSpectrum, int WParam) {

    fprintf(file, "Serial number: %s\n", ptrSpectrometers[SpectrometerNumber]->getSerialNumber().toLatin1().data());
    // if (ptrSpectrometers[SpectrometerNumber]->hasReadableName())
    //{
    //   fprintf(file, "Readable name: %s\n", ptrSpectrometers[SpectrometerNumber]->getReadableName().toLatin1().data());
    //}
    fprintf(file, "Integration time: %.2f ms\n", ptrSpectrometers[SpectrometerNumber]->getIntegrationTime());
    fprintf(file, "Number of averages: %i\n", ptrSpectrometers[SpectrometerNumber]->getNumberOfAverages());
    fprintf(file, "Number of Spectra: %i\n\n", ConfigureMeasurement.numSpectra);


    /* Save wavelength */
    double *a_pWavelength = ptrSpectrometers[SpectrometerNumber]->getWavelengths();
    unsigned int j = 1;

    /* Loop through pixel values */
    for (j = 0; j < ptrSpectrometers[SpectrometerNumber]->getNumberOfPixels(); j++)
    {
        unsigned int k = 0;

        /* write counts header */
        if (j == 0)
        {
            fprintf(file, "Wavelength\t# 00001");

            /* Write number of spectrum */
            for (k = 2; k <= (unsigned int)WParam; k++)
            {
                fprintf(file, "\t\t# %05u", k);
            }
            fprintf(file, "\n");
        }

        /* Write wavelength and counts */
        fprintf(file, "%.2f", *(a_pWavelength+j));

        for (k = 0; k < (unsigned int)WParam; k++)
        {
            fprintf(file, "\t\t%.2f", *(a_pSpectrum + ptrSpectrometers[SpectrometerNumber]->getNumberOfPixels() * k + j));
        }
        fprintf(file, "\n");
    }
}

/**
 * @brief Plot W, DC and 2W averaged
 */
void PanelPolarimeter::plotAverages(double time){

    double average_DC=0, average_W=0, average_2W = 0;

    // Average the Analyzed Signals
    for ( int  i = 0; i < FFTL.NrWaves; i++ )
    {
        average_DC = average_DC + FFTL.fft_DC[i];
        average_W = average_W + FFTL.fft_W[i];
        average_2W = average_2W + FFTL.fft_2W[i];
    }

    if(FFTL.NrWaves== 0){
        AverageDC.append(0);
        AverageW.append(0);
        Average2W.append(0);
    }else{
        AverageDC.append(average_DC/FFTL.NrWaves);
        AverageW.append(average_W/FFTL.NrWaves);
        Average2W.append(average_2W/FFTL.NrWaves);
    }

    averaged_Raw_Signal_time.append(time);

    double maxtime = *std::max_element(averaged_Raw_Signal_time.begin(), averaged_Raw_Signal_time.end());

    if(averaged_Raw_Signal_time.length() % 100 == 0){
        ui->qwtPlot_Pol_Average->setXAxis(maxtime, maxtime+30);
    }

    /* DC, W and 2W plots */

    Average_DC_Signal->setSamples(averaged_Raw_Signal_time, AverageDC);
    Average_DC_Signal->attach(ui->qwtPlot_Pol_Average);

    Average_W_Signal->setSamples(averaged_Raw_Signal_time, AverageW);
    Average_W_Signal->attach(ui->qwtPlot_Pol_Average);

    Average_2W_Signal->setSamples(averaged_Raw_Signal_time, Average2W);
    Average_2W_Signal->attach(ui->qwtPlot_Pol_Average);

    /* Signal Restart */
    if(averaged_Raw_Signal_time.length() > 5000){
        averaged_Raw_Signal_time.resize(0);
        AverageDC.resize(0);
        AverageW.resize(0);
        Average2W.resize(0);
        ui->qwtPlot_Pol_Average->setXAxis(maxtime, maxtime+30);
    }

    ui->qwtPlot_Pol_Average->setYAxis(0.0, *std::max_element(AverageDC.begin(), AverageDC.end())+10000);

    ui->qwtPlot_Pol_Average->update();

}

/**
 * @brief Destructor of 'Polarimeter' class
 */
PanelPolarimeter::~PanelPolarimeter(void)
{
}

/*

      Average_DC_Signal->detach();
      delete Average_DC_Signal;
      Average_DC_Signal= nullptr;

      Average_W_Signal->detach();
      delete Average_W_Signal;
      Average_W_Signal= nullptr;

      Average_2W_Signal->detach();
      delete Average_2W_Signal;
      Average_2W_Signal= nullptr;


*/
