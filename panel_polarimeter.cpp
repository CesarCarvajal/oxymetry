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
        }
        else
        {
            // Polarimeter Plot of Raw Signal
            curves_Pol.append(new QwtPlotCurve(ptrSpectrometers[SpectrometerNumber]->getSerialNumber()));
            curves_Pol[0]->setItemAttribute(QwtPlotItem::Legend, false);
        }

        // Polarimeter Plot of Raw Signal Color
        curves_Pol[0]->setPen(QPen(defaultColors[SpectrometerNumber % 5]));
        curves_Pol[0]->attach(ui->qwtPlot_Pol);

        // Polarimeter buttons and labels signal mapper
        connect(devices2[0]->ui->label_integrationTime, SIGNAL(clicked()), signalMapper, SLOT(map()));
        connect(devices2[0]->ui->label_numberOfAverages, SIGNAL(clicked()), signalMapper, SLOT(map()));
        connect(devices2[0]->ui->label_autoAdjust, SIGNAL(clicked()), signalMapper, SLOT(map()));

        // Polarimeter set mapping for buttons and labels
        signalMapper->setMapping(devices2[0]->ui->label_integrationTime, devices2[0]->ui->label_integrationTime);
        signalMapper->setMapping(devices2[0]->ui->label_numberOfAverages, devices2[0]->ui->label_numberOfAverages);
        signalMapper->setMapping(devices2[0]->ui->label_autoAdjust, devices2[0]->ui->label_autoAdjust);
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

    /* Connect buttons for saving purposes */
    connect(ui->checkBox_AutoSave_Pol, SIGNAL(clicked(bool)), this, SLOT(AutoSave_FFT()));
    connect(ui->checkBox_AutoSave_Pol_Raw, SIGNAL(clicked(bool)), this, SLOT(AutoSave_Raw()));

    /* Connect button for Configuration */
    connect(ui->button_Conf_Setup_Pol, SIGNAL(clicked()), this, SLOT(ConfSetup_Pol()));
    connect(ui->button_Pol_ConfigureMeasurement, SIGNAL(clicked()), this, SLOT(ConfSetup_Pol_Measurement()));

    /* Connect event handler */
    connect(qApp, SIGNAL(DataIsHere(int, int)), this, SLOT(ReceiveDataIsHerePol(int, int)));

    /* If there are spectrometers connected, allow Polarimetry Measurement */
    ui->button_Start_Meas_Pol->setDisabled((!m_NrDevices) ? true : false);
    ui->button_Start_Meas_Pol->setStyleSheet((!m_NrDevices) ? grayButton : greenButton);
    ui->checkBox_AutoSave_Pol->setDisabled((!m_NrDevices) ? true : false);
    ui->checkBox_AutoSave_Pol_Raw->setDisabled((!m_NrDevices) ? true : false);

    /* Set axis and title of Raw Signal plot for Polarimeter */
    ui->qwtPlot_Pol->setXAxisTitle("Wavelength in nm");
    ui->qwtPlot_Pol->setYAxisTitle("ADC counts");
    ui->qwtPlot_Pol->setYAxis(0.0, 65535.0);

    /* Set axis and title of Compensated Signal plot for Polarimeter */
    ui->qwtPlot_Pol_Compensation->setXAxisTitle("Wavelength in nm");
    ui->qwtPlot_Pol_Compensation->setYAxisTitle("Intensity");
    ui->qwtPlot_Pol_Compensation->setYAxis(0.0, 3);

    /* Set axis and title of w/2w plot for Polarimeter */
    ui->qwtPlot_Pol_w_2w->setXAxisTitle("Wavelength in nm");
    ui->qwtPlot_Pol_w_2w->setYAxisTitle("FFT Intesities");
    ui->qwtPlot_Pol_w_2w->setYAxis(0.0, 30000000);

    /* Set axis and title of Average over all Wavelenths plot for Polarimeter */
    ui->qwtPlot_Pol_Average->setXAxisTitle("Time in min");
    ui->qwtPlot_Pol_Average->setYAxisTitle("Intensity");
    ui->qwtPlot_Pol_Average->setYAxis(0.0, 5600000);
    ui->qwtPlot_Pol_Average->setXAxis(0.0, 60);

    /* Set axis and title of Prediction Curve, now in use to show the FFT */
    // ui->qwtPlot_Pol_Prediction->setXAxisTitle("Reference Concentration");
    ui->qwtPlot_Pol_Prediction->setXAxisTitle("Frequency in Hz");
    ui->qwtPlot_Pol_Prediction->setYAxisTitle("FFT Intensity");
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

    /* Which wavelentgth would you like to see the FFT? */
    signalMapper->setMapping(ui->waveToPlotFFT, ui->waveToPlotFFT);
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
                    ptrSpectrometers[SpectrometerNumber]->startMeasurement(-1);
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
                    ptrSpectrometers[SpectrometerNumber]->startMeasurement(-1);
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
}

/**
 * @brief Enable polarimeter: If there is a selected spectrometer, then it´s added to the list of Polarimeter Tab.
 */
void PanelPolarimeter::enable_Polarimeter_Measurement(bool activate)
{
    /* Enable measurements and get the information of the current selected spectrometer */
    ui->button_Start_Meas_Pol->setEnabled(activate);
    ui->button_Start_Meas_Pol->setStyleSheet(activate ? greenButton : grayButton);
    devices2[0]->ui->label_autoAdjust->setEnabled(activate);
    devices2[0]->ui->label_integrationTime->setEnabled(activate);
    devices2[0]->ui->label_numberOfAverages->setEnabled(activate);
    devices2[0]->ui->lineEdit_name->setEnabled(activate);
}

/**
 * @brief Load Data from the FFT, Polarimeter Setup
 */
void PanelPolarimeter::LoadFromFFT(void) {

    /* What kind of data are we loading? */
    isFFTData = true;

    /* Clean the plots for a new plotting */
    clearPlots();

    /* Load Data Path */
    QFileInfo fileInfo;
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
    if (fileInfo.completeBaseName().count(QLatin1Char('_')) != 4 || fileInfo.completeBaseName().at(fileInfo.completeBaseName().length()-1) !="T")
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
    if(FFTL.fft_DC != nullptr && isFFTData == false){

        /* File doens't exists. Did we ask the user to save the analyzed data from raw data? */
        if (QMessageBox::Yes == QMessageBox::question(this, "Save FFT File", "Do you want to save the FFT analysis from the Loaded Raw Data?",
                                                      QMessageBox::Yes | QMessageBox::No))
        {
            /* Button 'yes' pressed; Save the FFT data to the folder on Bin */
            FFTL.saveFFTtoFile();
        }
    }

    /* Clear all the plots for a new load of data */
    clearPlots();

    /* Load Data Path */
    QFileInfo fileInfo;
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

    /* Are we using a FFT file or a Raw Data file? */
    isFFTData = false;
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
    ui->qwtPlot_Pol_Prediction->setXAxis(0.0,  6*FFTL.f_w/10);
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
        /* No Pol Measurement running at the moment. Start it. */
        start_Pol_Measurement();
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

    /* Enable / Disable buttons from Preview */ //???  Read Benajamin File

    /* Enable / Disable buttons when measuring */
    ui->button_Load_FFTData->setEnabled(false);
    ui->button_AnalyzeRawPolData->setEnabled(false);
    ui->button_Start_Meas_Pol->setEnabled(false);
    ui->checkBox_AutoSave_Pol->setEnabled(false);
    ui->checkBox_AutoSave_Pol_Raw->setEnabled(false);
    ui->button_Conf_Setup_Pol->setEnabled(false);
    ui->button_Pol_ConfigureMeasurement->setEnabled(false);

    /* Is spectrometer enabled? */
    devices2[0]->setIsEnabled(false);

    /* Prepare for new measurement */
    if (ptrSpectrometers[SpectrometerNumber]->prepareMeasurement())
    {
        /* If successful, start measurement */
        ptrSpectrometers[SpectrometerNumber]->startMeasurement(-1);
    }

    /* Handle events and update UI */
    Application::processEvents();

    /* Remember Polarimeter Measurement is Running */
    PolMeasurementRunning = true;

    // Introduce here the routine for a Measurement.

    /* Update pol meas button */
    ui->button_Start_Meas_Pol->setText("Stop Measurement");
    ui->button_Start_Meas_Pol->setStyleSheet(RedButton);
    ui->button_Start_Meas_Pol->setEnabled(true);
}

/**
 * @brief Stop Measurments for the Polarimeter Setup
 */
void PanelPolarimeter::stop_Pol_Measurement(void) {

    /* Disable preview button */ //???   Read Benjamin File

    ui->button_Load_FFTData->setEnabled(true);
    ui->button_AnalyzeRawPolData->setEnabled(true);

    /* Stop measurement */
    ptrSpectrometers[SpectrometerNumber]->stopMeasurement();

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
    ui->button_Conf_Setup_Pol->setEnabled(true);
    ui->button_Pol_ConfigureMeasurement->setEnabled(true);
}

/**
 * @brief Configuration of Measurments
 */
void PanelPolarimeter::ConfSetup_Pol_Measurement(void) {

    configurePolMeasure ConfigureMeasurement(this);
    ConfigureMeasurement.exec();

    /* Prevent user from resizing the header */
    ui->Table_Measurements_Pol->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);

    /* Left align column titles */
    ui->Table_Measurements_Pol->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);

    /* Prevent user from editing the cells */
    ui->Table_Measurements_Pol->setEditTriggers(QAbstractItemView::NoEditTriggers);

    /* Adjust table widget */
    ui->Table_Measurements_Pol->setColumnWidth(0, 30);
    ui->Table_Measurements_Pol->setColumnWidth(1, 80);
    ui->Table_Measurements_Pol->setColumnWidth(2, 190);

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
}

/**
 * @brief Updates the graph
 */
void PanelPolarimeter::updateGraph(void)
{
    /* Update the graph */
    ui->qwtPlot_Pol->update();
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
            }
        }

        /* Update curve data */
        curves_Pol[0]->setSamples(ptrSpectrometers[SpectrometerNumber]->getWavelengths(), ptrSpectrometers[SpectrometerNumber]->getCounts(),
                                  ptrSpectrometers[SpectrometerNumber]->getNumberOfPixels());

        /* Does the graph needs a update? */
        if (needUpdate)
        {
            /* Update the graph */
            ui->qwtPlot_Pol->update();
        }
    }
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
            if (!ptrSpectrometers[SpectrometerNumber]->startMeasurement(-1))
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
 * @brief Configuration of the Faraday Rotator for the Polarimeter Setup
 */
void PanelPolarimeter::ConfSetup_Pol(void) {
    // Development
}


/**
 * @brief Save the FFT Automatic from the Polarimeter Setup
 */
void PanelPolarimeter::AutoSave_FFT(void) {
    if (ui->checkBox_AutoSave_Pol->isChecked())
    {
        // AutoSave
    }
    else
    {
        // Stop AutoSave
    }
}

/**
 * @brief Save the Raw Data Automatic from the Polarimeter Setup
 */
void PanelPolarimeter::AutoSave_Raw(void) {
    if (ui->checkBox_AutoSave_Pol_Raw->isChecked())
    {
        // AutoSave
    }
    else
    {
        // Stop AutoSave
    }
}

/**
 * @brief Destructor of 'Polarimeter' class
 */
PanelPolarimeter::~PanelPolarimeter(void)
{
}

/*
    // Plot the Average Signal of DC, W and 2W vs time
    Average_DC_Signal = new QwtPlotCurve("DC");
    Average_DC_Signal->setPen(QPen("blue"));
    Average_DC_Signal->setSamples(FFTL.time , FFTL.fft_Average_DC_signal,100);
    Average_DC_Signal->attach(ui->qwtPlot_Pol_Average);
    Average_W_Signal = new QwtPlotCurve("W");
    Average_W_Signal->setPen(QPen("red"));
    Average_W_Signal->setSamples(FFTL.time , FFTL.fft_Average_W_signal,100);
    Average_W_Signal->attach(ui->qwtPlot_Pol_Average);
    Average_2W_Signal = new QwtPlotCurve("2W");
    Average_2W_Signal->setPen(QPen("green"));
    Average_2W_Signal->setSamples(FFTL.time , FFTL.fft_Average_2W_signal,100);
    Average_2W_Signal->attach(ui->qwtPlot_Pol_Average);
    ui->qwtPlot_Pol_Average->update();
    ui->qwtPlot_Pol_Average->updateLayout();


      Average_DC_Signal->detach();
      delete Average_DC_Signal;
      Average_DC_Signal= nullptr;

      Average_W_Signal->detach();
      delete Average_W_Signal;
      Average_W_Signal= nullptr;

      Average_2W_Signal->detach();
      delete Average_2W_Signal;
      Average_2W_Signal= nullptr;

   // ui->qwtPlot_Pol_Average->update();


  */
