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

    /* Create new item in Polarimeter Spectrometer List */
    QListWidgetItem *item_Pol = new QListWidgetItem(0);

    if (m_NrDevices > 0)
    {

        /* The purpose of this list is to inform which spectrometer is in use for the Polarimetry Tab. Be able to see
        its name and change its parameters as the Integration time, number of averages, name and set the Auto Adjust */

        /* By Default, use the First Device checked on the List of Spectrometers */

        SpectrometerNumber = 0;

        /* Does the first spectrometer already have a readable name assigned? */
        if (ptrSpectrometers[0]->hasReadableName())
        {
            /* Yes. Add the spectrometer to the list using the readable name. */
            devices2.append(new PanelItem_Pol(0, ptrSpectrometers[0]->getReadableName())); // Polarimeter Setup Variable
        }
        else
        {
            /* No. Add the spectrometer to the list using the serial number. */
            devices2.append(new PanelItem_Pol(0, ptrSpectrometers[0]->getSerialNumber())); // Polarimeter Setup Variable
        }

        // Polarimeter Setup Device Initialization Start
        devices2[0]->setIntegrationTime(ptrSpectrometers[0]->getIntegrationTime());
        devices2[0]->setNumberOfAverages(ptrSpectrometers[0]->getNumberOfAverages());
        devices2[0]->setIsSaturated(ptrSpectrometers[0]->isSaturated());
        devices2[0]->setIsEnabled(true);

        /* Don't allow resize of item */
        item_Pol->setSizeHint(devices2[0]->size());  // Polarimeter Setup Variable

        // Polarimeter List Item
        ui->list_devices_Pol->addItem(item_Pol);
        ui->list_devices_Pol->setItemWidget(item_Pol, devices2[0]); // Polarimeter Setup Variable

        /* Does the first spectrometer already have a readable name assigned? */
        if (ptrSpectrometers[0]->hasReadableName())
        {
            // Polarimeter Plot of Raw Signal
            curves_Pol.append(new QwtPlotCurve(ptrSpectrometers[0]->getReadableName())); // Polarimeter Setup Variable
            curves_Pol[0]->setItemAttribute(QwtPlotItem::Legend, false); // Polarimeter Setup Variable
        }
        else
        {
            // Polarimeter Plot of Raw Signal
            curves_Pol.append(new QwtPlotCurve(ptrSpectrometers[0]->getSerialNumber())); // Polarimeter Setup Variable
            curves_Pol[0]->setItemAttribute(QwtPlotItem::Legend, false); // Polarimeter Setup Variable
        }

        // Polarimeter Plot of Raw Signal Color
        curves_Pol[0]->setPen(QPen(defaultColors[0 % 5])); // Polarimeter Setup Variable
        curves_Pol[0]->attach(ui->qwtPlot_Pol); // Polarimeter Setup Variable

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

    /* If there are spectrometers connected, allow Polarimetry Measurement */
    ui->button_Start_Meas_Pol->setDisabled((!m_NrDevices) ? true : false);
    ui->checkBox_AutoSave_Pol->setDisabled((!m_NrDevices) ? true : false);
    ui->checkBox_AutoSave_Pol_Raw->setDisabled((!m_NrDevices) ? true : false);

    /*
     * An item has been added to the list of polarimeter Tab. Now connect all other buttons and the event handler.
     */

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

    /* Set axis and title of Average over all Wavelenths plot for Polarimeter */
    // ui->qwtPlot_Pol_Prediction->setXAxisTitle("Reference Concentration");
    ui->qwtPlot_Pol_Prediction->setXAxisTitle("Frequency in Hz");
    ui->qwtPlot_Pol_Prediction->setYAxisTitle("FFT Intensity");
    // ui->qwtPlot_Pol_Prediction->setXAxis(0.0, 100);
    ui->qwtPlot_Pol_Prediction->setXAxis(0.0, 6);
    ui->qwtPlot_Pol_Prediction->setYAxis(0.0, 30000000);

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
    ui->qwtPlot_Pol->setXAxis(minWavelength, maxWavelength);   // Polarimeter Setup Variable
    ui->qwtPlot_Pol_Compensation->setXAxis(minWavelength, maxWavelength);    // Polarimeter Setup Variable
    ui->qwtPlot_Pol_w_2w->setXAxis(minWavelength, maxWavelength);     // Polarimeter Setup Variable

    /*
     * Connect and configure the Polarimeter Stuff
     */

    /* Connect buttons in Polarimeter Tab */
    connect(ui->button_Start_Meas_Pol, SIGNAL(clicked()), this, SLOT(toggle_Pol_Measurement()));
    connect(ui->button_Load_FFTData, SIGNAL(clicked()), this, SLOT(LoadFromFFT()));
    connect(ui->button_AnalyzeRawPolData, SIGNAL(clicked()), this, SLOT(LoadFromRawData()));
    connect(ui->waveToPlotFFT, SIGNAL(clicked()), signalMapper, SLOT(map()));


    /* Connect buttons for saving graphs to pdf */
    connect(ui->Button_Save_Graphs_Pol, SIGNAL(clicked()), this, SLOT(saveGraph_Pol()));

    /* Connect buttons for saving purposes Automatically */
    connect(ui->checkBox_AutoSave_Pol, SIGNAL(clicked(bool)), this, SLOT(AutoSave_FFT()));
    connect(ui->checkBox_AutoSave_Pol_Raw, SIGNAL(clicked(bool)), this, SLOT(AutoSave_Raw()));

    /* Connect button for Faraday Rotator and Syringe Pump Configuration */
    connect(ui->button_Conf_Setup_Pol, SIGNAL(clicked()), this, SLOT(ConfSetup_Pol()));
    connect(ui->button_Pol_Syringe, SIGNAL(clicked()), this, SLOT(ConfSetup_Pol_Pump()));

    signalMapper->setMapping(ui->waveToPlotFFT, ui->waveToPlotFFT);

}

/**
 * @brief Called if a widget on a spectrometer item in list got clicked,
 *        e.g. the configuration button or integration time label.
 * @param widget Widget which has been clicked
 */
void PanelPolarimeter::handleClickEvent(QWidget *widget)
{
    QLabel *label = qobject_cast<QLabel *>(widget);

    // Fix Bidirectional Update in Polarimeter/Preview Tab!  ?????? See ReadMe Benjamin File.

    /* Loop through spectrometers */

    /* The integration time label has been clicked */ // Polarimeter Setup Involved
    if (label == devices2[0]->ui->label_integrationTime)
    {
        PanelChangeTime changeDialog(this);

        /* Set integration time */
        changeDialog.setValue(devices2[0]->getIntegrationTime()); // Polarimeter Setup Variable

        /* User pressed 'ok' */
        if (QDialog::Accepted == changeDialog.exec())
        {
            /* Get new integration time */
            float intTime = changeDialog.getValue();

            /* Set panel item and device integration time */
            devices2[0]->setIntegrationTime(intTime);  // Polarimeter Setup Variable
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
    /* The auto-adjust label has been clicked */ // Polarimeter Setup Involved
    else if (label == devices2[0]->ui->label_autoAdjust)
    {
        /* Run automatic adjustment of integration time */
        //            adjustIntegrationTime(i);
    }
    /* The number of averages label has been clicked */ // Polarimeter Setup Involved
    else if (label == devices2[0]->ui->label_numberOfAverages)
    {
        PanelChangeAverages changeDialog(this);

        /* Set number of averages */
        changeDialog.setValue(devices2[0]->getNumberOfAverages());  // Polarimeter Setup Variable

        /* User pressed 'ok' */
        if (QDialog::Accepted == changeDialog.exec())
        {
            /* Get new number of averages */
            int numberOfAverages = changeDialog.getValue();

            /* Set panel item and device number of averages */
            devices2[0]->setNumberOfAverages(numberOfAverages);  // Polarimeter Setup Variable
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
    } else if(label == ui->waveToPlotFFT){

        PanelChangeWaveFFT changeDialog(this);

        if(FFT_DC != nullptr){
            /* Set number of averages */
            for (int i =0; i<FFTL.NrWaves;i++){
                changeDialog.setValue(FFTL.wavelengths[i]);
            }
        }else{
            changeDialog.setValue(0);
        }

        /* User pressed 'ok' */
        if (QDialog::Accepted == changeDialog.exec() && FFT_DC != nullptr)
        {
            if(FFTL.wavelengths != nullptr){
                selectedWave = changeDialog.getValue();
                for ( int  i = 0; i < FFTL.NrSpectra/2; i++ )
                {
                    if (i != 0 || i != FFTL.f_w || i != 2*FFTL.f_w){
                        FFTL.fft_data[i] = 0;
                    }
                }

                FFTL.fft_data[0] = FFTL.fft_DC[selectedWave];
                FFTL.fft_data[FFTL.f_w] = FFTL.fft_W[selectedWave];
                FFTL.fft_data[2*FFTL.f_w] = FFTL.fft_2W[selectedWave];

                ui->waveToPlotFFT->setText(QString::number(FFTL.wavelengths[selectedWave]));
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

    /*
         * Furthermore, we have to check if there are any enabled spectrometers left.
         * If no, the polarimeter measurement is disabled or ask to select one from the preview list.
         */
}

/**
 * @brief POLARIMETER FUNCTIONS
 */

/**
 * @brief Disable polarimeter: If there is any spectrometer, then the list should be in blank and ask
 * the user to select one spectrometer from the Preview List.
 */
void PanelPolarimeter::disable_Polarimeter_Measurement(void)
{
    // Polarimeter Setup Interactions
    ui->button_Start_Meas_Pol->setEnabled(false);
    devices2[0]->ui->label_autoAdjust->setEnabled(false);
    devices2[0]->ui->label_integrationTime->setEnabled(false);
    devices2[0]->ui->label_numberOfAverages->setEnabled(false);
    devices2[0]->ui->lineEdit_name->setEnabled(false);
}

/**
 * @brief Enable polarimeter: If there is selected a spectrometer, then it´s added to the list of Polarimeter Tab.
 */
void PanelPolarimeter::enable_Polarimeter_Measurement(void)
{
    // Polarimeter Setup Interactions
    ui->button_Start_Meas_Pol->setEnabled(true);
    devices2[0]->ui->label_autoAdjust->setEnabled(true);
    devices2[0]->ui->label_integrationTime->setEnabled(true);
    devices2[0]->ui->label_numberOfAverages->setEnabled(true);
    devices2[0]->ui->lineEdit_name->setEnabled(true);
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

    /* Enable / Disable buttons from Preview */
    //    ui->pushButton_preview->setEnabled(false);
    //    ui->pushButton_storeToRam->setEnabled(false);
    //    ui->pushButton_timePattern->setEnabled(false);

    /* Enable / Disable buttons when measuring */
    ui->button_Load_FFTData->setEnabled(false);
    ui->button_AnalyzeRawPolData->setEnabled(false);
    ui->button_Start_Meas_Pol->setEnabled(false);
    ui->checkBox_AutoSave_Pol->setEnabled(false);
    ui->checkBox_AutoSave_Pol_Raw->setEnabled(false);
    ui->button_Conf_Setup_Pol->setEnabled(false);
    ui->button_Pol_Syringe->setEnabled(false);

    /* Is spectrometer enabled? */

    /*    if (devices2[0]->getIsEnabled())
    {

        // Prepare for new measurement
      if (ptrSpectrometers[0]->prepareMeasurement())
    {
            // If successful, start measurement
            ptrSpectrometers[0]->startMeasurement(-1);
        }

        // Handle events and update UI
        Application::processEvents();
    }
*/
    /* Remember preview or Pol Measurement is running */
    //    previewRunning = true;

    /* Start update timer */
    //    timer->start(1);


    // Introduce here the routine for a Measurement.

    /* Update pol meas button */
    ui->button_Start_Meas_Pol->setText("Stop Measurement");
    ui->button_Start_Meas_Pol->setEnabled(true);

    PolMeasurementRunning = true;

}

/**
 * @brief Stop Measurments for the Polarimeter Setup
 */
void PanelPolarimeter::stop_Pol_Measurement(void) {

    /* Disable preview button */
    //    ui->pushButton_preview->setEnabled(true);
    //    ui->button_Start_Meas_Pol->setEnabled(false);

    //    ui->pushButton_storeToRam->setEnabled(true);
    //    ui->pushButton_timePattern->setEnabled(true);

    ui->button_Load_FFTData->setEnabled(true);
    ui->button_AnalyzeRawPolData->setEnabled(true);

    /* Is spectrometer enabled? */
    //        if (devices2[0]->getIsEnabled())
    //        {
    /* Stop measurement */
    //            ptrSpectrometers[0]->stopMeasurement();
    //        }

    /* Handle events and update UI */
    //        Application::processEvents();

    /* No preview running anymore */

    //        previewRunning = false;

    /* Stop update timer */
    //    timer->stop();

    ui->checkBox_AutoSave_Pol->setEnabled(true);
    ui->checkBox_AutoSave_Pol_Raw->setEnabled(true);
    ui->button_Conf_Setup_Pol->setEnabled(true);
    ui->button_Pol_Syringe->setEnabled(true);

    /* Update pol meas button */
    ui->button_Start_Meas_Pol->setText("Start Measurement");
    ui->button_Start_Meas_Pol->setEnabled(true);

    /*
if (PolMeasurementRunning){

}

*/

    PolMeasurementRunning = false;

}

/**
 * @brief Configuration of the Faraday Rotator for the Polarimeter Setup
 */
void PanelPolarimeter::ConfSetup_Pol(void) {

}

/**
 * @brief Configuration of the Syrynge Pump for the Polarimeter Setup
 */
void PanelPolarimeter::ConfSetup_Pol_Pump(void) {

}

/**
 * @brief Load Data from the FFT, Polarimeter Setup
 */
void PanelPolarimeter::LoadFromFFT(void) {

    isRawData = true;

    clearPlots();

    QFileInfo fileInfo;

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

    /* Data Analysis by FFT */
    FFTL.getFFTfromFFTData(fileInfo);

    /* Plot the FFT Signals */
    this->Plot_FFT_Graphs(FFTL.wavelengths, FFTL.time, FFTL.fft_data, FFTL.fft_DC, FFTL.fft_W, FFTL.fft_2W, FFTL.fft_Compensation_Signal);
    ui->waveToPlotFFT->setText(QString::number(FFTL.wavelengths[438]));

}

/**
 * @brief Load Data and Perform FFT from Raw Data, Polarimeter Setup
 */
void PanelPolarimeter::LoadFromRawData(void) {

    if(FFTL.fft_DC != nullptr && isRawData == false){

        /* File exists. Did we ask the user to save the analyzed data from raw data? */
        if (QMessageBox::Yes == QMessageBox::question(this, "Save FFT File", "Do you want to save the FFT analysis from the Loaded Raw Data?",
                                                      QMessageBox::Yes | QMessageBox::No))
        {
            /* Button 'yes' pressed; Save the FFT data to the folder on Bin */
            FFTL.saveFFTtoFile();

        }
    }

    clearPlots();

    QFileInfo fileInfo;

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

    /* Data Analysis by FFT */
    FFTL.getFFTfromRawData(fileInfo);

    /* Plot the FFT Signals */
    this->Plot_FFT_Graphs(FFTL.wavelengths, FFTL.time, FFTL.fft_data, FFTL.fft_DC, FFTL.fft_W, FFTL.fft_2W, FFTL.fft_Compensation_Signal);
    ui->waveToPlotFFT->setText(QString::number(FFTL.wavelengths[438]));

    isRawData = false;

}

/**
 * @brief Plot Only the FFT of the Selected Wavelength.
 */
void PanelPolarimeter::plotFFTatSelectedWave(double FFTLfft_data[], double FFTLtime[]){

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
 * @brief Receive the Data to be ploted on the FFT related Plots of the Polarimeter Tab Interface.
 */
void PanelPolarimeter::Plot_FFT_Graphs(double FFTLwavelengths[], double FFTLtime[], double FFTLfft_data[], double FFTLfft_DC[], double FFTLfft_W[], double FFTLfft_2W[], double FFTLfft_Compensation_Signal[]){

    /* Plot The FFT at a Determined Wavelength */
    plotFFTatSelectedWave(FFTLfft_data, FFTLtime);

    /* Plot the DC, W and 2W Signal */
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

                /* Save the which spectrometer are we using if it's not the first*/
                SpectrometerNumber = i;

                if (ptrSpectrometers[i]->hasReadableName())
                {
                    devices2[0]->setName(ptrSpectrometers[i]->getReadableName());
                }else{
                    devices2[0]->setName(ptrSpectrometers[i]->getSerialNumber());
                }

                break;
            }
        }
    }

    /* Update buttons */
    ui->button_Start_Meas_Pol->setEnabled(devicesEnabled ? true : false);  // Polarimeter Setup Variable
}

/**
 * @brief Remove all plots in the Interface before to load any other plots.
 */
void PanelPolarimeter::clearPlots(void) {

    if(FFT_DC!=nullptr)
    {
        FFT_DC->detach();
        FFT_W->detach();
        FFT_2W->detach();
        FFT_oneWave->detach();
        Compensation_Signal->detach();
    }

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

    QString url = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                    "",
                                                    QFileDialog::ShowDirsOnly
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
