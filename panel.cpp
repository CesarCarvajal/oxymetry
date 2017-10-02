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

#define USE_POSTMESSAGE

/* External includes */
#include <QSettings>
#include <QDialog>
#include <QListWidget>
#include <QListWidgetItem>
#include <QSignalMapper>
#include <QApplication>
#include <QMessageBox>
#include <QFileInfo>
#include <QCheckBox>
#include <QIcon>
#include <QElapsedTimer>
#include <QDate>
#include <QTime>
#include <QFileDialog>
#include <QTimer>
#include <QThread>
#include <QStringRef>

/* Avantes AvaSpec library */
#include "avaspec.h"

/* Qwt library */
#include "qwt_plot_curve.h"

/* Internal includes */
#include "application.h"
#include "messages.h"
#include "timer.h"
#include "math_helper.h"
#include "spectrometer.h"
#include "panel_item_Pol.h"
#include "ui_panel_item_Pol.h"
#include "panel_item.h"
#include "ui_panel_item.h"
#include "panel_change_averages.h"
#include "panel_change_time.h"
#include "panel_about.h"
#include "panel_legend.h"
#include "iad_configure.h"
#include "iad_calibrate.h"
#include "iad_measure.h"
#include "panel_storetoram.h"
#include "ui_panel_storetoram.h"
#include "panel_timepattern.h"
#include "ui_panel_timepattern.h"
#include "spectrometer_config.h"
#include "ui_spectrometer_config.h"
#include "panel.h"
#include "ui_panel.h"
#include "fft.h"

/*
 * Global variables
 */
extern QSettings *settings;
extern Spectrometer** ptrSpectrometers;
extern unsigned int m_NrDevices;

/* Colors for spectrometers */
QString defaultColors[] = { "blue", "red", "green", "yellow", "cyan" };

/**
 * @brief Constructor of 'Panel' class
 */
Panel::Panel(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Panel)
{
    /* Set up user interface */
    ui->setupUi(this);

    /* Set window flags */
    this->setWindowFlags(Qt::Window);

    /* Create signal mapper for panel */
    signalMapper = new QSignalMapper(this);

    /*
     * For each detected spectrometer, an item should be added to the list
     * of spectrometers on the preview page. This item allows control of integration
     * time, number of averages, EEPROM and more configuration parameters.
     */

    unsigned int i = 0;

    /* Loop through devices */
    for (i = 0; i < m_NrDevices; i++)
    {
        /* Create new item in spectrometer list */
        QListWidgetItem *item = new QListWidgetItem(0);
        QListWidgetItem *item_Pol = new QListWidgetItem(0);

        /* Does the current spectrometer already have a readable name assigned? */
        if (ptrSpectrometers[i]->hasReadableName())
        {
            /* Yes. Add the spectrometer to the list using the readable name. */
            devices.append(new PanelItem(0, ptrSpectrometers[i]->getReadableName(), defaultColors[i % 5]));
            devices2.append(new PanelItem_Pol(0, ptrSpectrometers[i]->getReadableName(), defaultColors[i % 5]));
        }
        else
        {
            /* No. Add the spectrometer to the list using the serial number. */
            devices.append(new PanelItem(0, ptrSpectrometers[i]->getSerialNumber(), defaultColors[i % 5]));
            devices2.append(new PanelItem_Pol(0, ptrSpectrometers[i]->getSerialNumber(), defaultColors[i % 5]));
        }

        /* Set initial values */
        devices[i]->setIntegrationTime(ptrSpectrometers[i]->getIntegrationTime());
        devices[i]->setNumberOfAverages(ptrSpectrometers[i]->getNumberOfAverages());
        devices[i]->setIsSaturated(false);
        devices[i]->setProgress(100);
        devices[i]->setIsEnabled(true);
        devices[i]->setIsChecked(true);

        // Polarimeter Preview
        devices2[0]->setIntegrationTime(devices[i]->getIntegrationTime());
        devices2[0]->setNumberOfAverages(devices[i]->getNumberOfAverages());
        devices2[0]->setIsSaturated(devices[i]->getIsSaturated());
        devices2[0]->setIsEnabled(true);

        /* Set current spectrometer enabled */
        ptrSpectrometers[i]->setEnabled(true);

        /* Don't allow resize of item */
        item->setSizeHint(devices[i]->size());
        item_Pol->setSizeHint(devices2[0]->size());

        /* Add item to list and make it visible */
        ui->list_devices->addItem(item);
        ui->list_devices->setItemWidget(item, devices[i]);

        // Polarimeter Preview Item
        ui->list_devices_Pol->addItem(item_Pol);
        ui->list_devices_Pol->setItemWidget(item_Pol, devices2[0]);

        /* Does the current spectrometer already have a readable name assigned? */
        if (ptrSpectrometers[i]->hasReadableName())
        {
            /* Yes. Create new plot curve using the readable name */
            curves.append(new QwtPlotCurve(ptrSpectrometers[i]->getReadableName()));
            // Polarimeter Adds
            curves_Pol.append(new QwtPlotCurve(ptrSpectrometers[i]->getReadableName()));
            curves_Pol[i]->setItemAttribute(QwtPlotItem::Legend, false);
        }
        else
        {
            /* No. Create new plot curve using the serial number */
            curves.append(new QwtPlotCurve(ptrSpectrometers[i]->getSerialNumber()));
            // Polarimeter Adds
            curves_Pol.append(new QwtPlotCurve(ptrSpectrometers[i]->getSerialNumber()));
            curves_Pol[i]->setItemAttribute(QwtPlotItem::Legend, false);
        }

        /* Add a curve to preview plot for current spectrometer */
        curves[i]->setPen(QPen(defaultColors[i % 5]));
        curves[i]->attach(ui->qwtPlot);
        // Polarimeter Adds
        curves_Pol[i]->setPen(QPen(defaultColors[i % 5]));
        curves_Pol[i]->attach(ui->qwtPlot_Pol);

        /* Connect buttons and labels to signal mapper */
        connect(devices[i]->ui->lineEdit_name, SIGNAL(textChanged(const QString &)), signalMapper, SLOT(map()));
        connect(devices[i]->ui->button_config, SIGNAL(clicked()), signalMapper, SLOT(map()));
        connect(devices[i]->ui->button_eeprom, SIGNAL(clicked()), signalMapper, SLOT(map()));
        connect(devices[i]->ui->label_integrationTime, SIGNAL(clicked()), signalMapper, SLOT(map()));
        connect(devices[i]->ui->label_autoAdjust, SIGNAL(clicked()), signalMapper, SLOT(map()));
        connect(devices[i]->ui->label_numberOfAverages, SIGNAL(clicked()), signalMapper, SLOT(map()));
        connect(devices[i]->ui->checkBox_enabled, SIGNAL(clicked()), signalMapper, SLOT(map()));

        // Polarimeter buttons and labels signal mapper
        connect(devices2[0]->ui->label_integrationTime, SIGNAL(clicked()), signalMapper, SLOT(map()));
        connect(devices2[0]->ui->label_numberOfAverages, SIGNAL(clicked()), signalMapper, SLOT(map()));
        connect(devices2[0]->ui->label_autoAdjust, SIGNAL(clicked()), signalMapper, SLOT(map()));

        /* Set mapping for buttons and labels */
        signalMapper->setMapping(devices[i]->ui->lineEdit_name, devices[i]->ui->lineEdit_name);
        signalMapper->setMapping(devices[i]->ui->button_config, devices[i]->ui->button_config);
        signalMapper->setMapping(devices[i]->ui->button_eeprom, devices[i]->ui->button_eeprom);
        signalMapper->setMapping(devices[i]->ui->label_integrationTime, devices[i]->ui->label_integrationTime);
        signalMapper->setMapping(devices[i]->ui->label_autoAdjust, devices[i]->ui->label_autoAdjust);
        signalMapper->setMapping(devices[i]->ui->label_numberOfAverages, devices[i]->ui->label_numberOfAverages);
        signalMapper->setMapping(devices[i]->ui->checkBox_enabled, devices[i]->ui->checkBox_enabled);

        // Polarimeter set mapping for buttons and labels
        signalMapper->setMapping(devices2[0]->ui->label_integrationTime, devices2[0]->ui->label_integrationTime);
        signalMapper->setMapping(devices2[0]->ui->label_numberOfAverages, devices2[0]->ui->label_numberOfAverages);
        signalMapper->setMapping(devices2[0]->ui->label_autoAdjust, devices2[0]->ui->label_autoAdjust);
    }

    /* Connect signal mapper action */
    connect(signalMapper, SIGNAL(mapped(QWidget *)), this, SLOT(handleClickEvent(QWidget *)));

    /*
     * An item has been added to the list on the preview page for each detected
     * spectrometer. Now connect all other buttons and the event handler.
     */

    /* Connect 'general purpose' buttons */
    connect(ui->pushButton_preview, SIGNAL(clicked()), this, SLOT(togglePreview()));
    connect(ui->pushButton_storeToRam, SIGNAL(clicked()), this, SLOT(storeToRam()));
    connect(ui->pushButton_timePattern, SIGNAL(clicked()), this, SLOT(timePattern()));

    /* Connect buttons for graph saving and data export */
    connect(ui->pushButton_legend, SIGNAL(clicked()), this, SLOT(showLegend()));
    connect(ui->pushButton_saveGraph, SIGNAL(clicked()), this, SLOT(saveGraph()));
    connect(ui->pushButton_exportData, SIGNAL(clicked()), this, SLOT(exportData()));
    connect(ui->pushButton_about, SIGNAL(clicked()), this, SLOT(showAbout()));

    /* Connect event handler */
    connect(qApp, SIGNAL(DataIsHere(int, int)), this, SLOT(ReceiveDataIsHere(int, int)));

    /*
     * Configure the buttons and plot on the preview page
     */

    /* If there are spectrometers connected, allow preview */
    ui->pushButton_preview->setDisabled((!m_NrDevices) ? true : false);
    ui->pushButton_storeToRam->setDisabled((!m_NrDevices) ? true : false);
    ui->pushButton_timePattern->setDisabled((!m_NrDevices) ? true : false);
    ui->pushButton_legend->setDisabled((!m_NrDevices) ? true : false);
    ui->pushButton_exportData->setDisabled((!m_NrDevices) ? true : false);
    ui->pushButton_saveGraph->setDisabled((!m_NrDevices) ? true : false);

    /* There's no preview running */
    previewRunning = false;

    /* Set axis and title of preview plot */
    ui->qwtPlot->setXAxisTitle("Wavelength in nm");
    ui->qwtPlot->setYAxisTitle("ADC counts");
    ui->qwtPlot->setYAxis(0.0, 65535.0);

    /* Set axis and title of preview plot for Polarimeter */
    ui->qwtPlot_Pol->setXAxisTitle("Wavelength in nm");
    ui->qwtPlot_Pol->setYAxisTitle("ADC counts");
    ui->qwtPlot_Pol->setYAxis(0.0, 65535.0);

    /* Set axis and title of the normalized intensity plots */
    ui->qwtPlot_reflection->setXAxisTitle("Wavelength in nm");
    ui->qwtPlot_reflection->setYAxisTitle("Normalized intensity");
    ui->qwtPlot_reflection->setCaption("Normalized reflection");
    ui->qwtPlot_reflection->setYAxis(0.0, 1.0);
    ui->qwtPlot_transmission->setXAxisTitle("Wavelength in nm");
    ui->qwtPlot_transmission->setYAxisTitle("Normalized intensity");
    ui->qwtPlot_transmission->setCaption("Normalized transmission");
    ui->qwtPlot_transmission->setYAxis(0.0, 1.0);

    /* Set axis and title of Compensated Signal plot for Polarimeter */
    ui->qwtPlot_Pol_Compensation->setXAxisTitle("Wavelength in nm");
    ui->qwtPlot_Pol_Compensation->setYAxisTitle("Intensity");
    ui->qwtPlot_Pol_Compensation->setYAxis(0.0, 1);

    /* Set axis and title of w/2w plot for Polarimeter */
    ui->qwtPlot_Pol_w_2w->setXAxisTitle("Wavelength in nm");
    ui->qwtPlot_Pol_w_2w->setYAxisTitle("FFT Intesities");
    ui->qwtPlot_Pol_w_2w->setYAxis(0.0, 30000000);

    /* Set axis and title of Average over all Wavelenths plot for Polarimeter */
    ui->qwtPlot_Pol_Average->setXAxisTitle("Time in min");
    ui->qwtPlot_Pol_Average->setYAxisTitle("Intensity");
    ui->qwtPlot_Pol_Average->setYAxis(0.0, 1);
    ui->qwtPlot_Pol_Average->setXAxis(0.0, 100.0);

    /* Set axis and title of Average over all Wavelenths plot for Polarimeter */
   // ui->qwtPlot_Pol_Prediction->setXAxisTitle("Reference Concentration");
    ui->qwtPlot_Pol_Prediction->setXAxisTitle("Frequency in Hz");
    ui->qwtPlot_Pol_Prediction->setYAxisTitle("FFT Intensity");
   // ui->qwtPlot_Pol_Prediction->setXAxis(0.0, 100);
    ui->qwtPlot_Pol_Prediction->setXAxis(0.0, 6);
    ui->qwtPlot_Pol_Prediction->setYAxis(0.0, 30000000);

    /* Defaults values for x-axis are 400 to 1000 nm */
    double minWavelength = 400.0, maxWavelength = 1000.0;

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

    /* Update x-axis of graphs */
    ui->qwtPlot->setXAxis(minWavelength, maxWavelength);
    ui->qwtPlot_Pol->setXAxis(minWavelength, maxWavelength);
    ui->qwtPlot_reflection->setXAxis(minWavelength, maxWavelength);
    ui->qwtPlot_transmission->setXAxis(minWavelength, maxWavelength);

    ui->qwtPlot_Pol_Compensation->setXAxis(minWavelength, maxWavelength);
    ui->qwtPlot_Pol_w_2w->setXAxis(minWavelength, maxWavelength);

    /* ---------------------------------------- */

    /* To do */
    M_R = new QwtPlotCurve("Diffuse reflection");
    M_T = new QwtPlotCurve("Diffuse transmission");
    M_U = new QwtPlotCurve("Unscattered transmission");

    M_R->setPen(QPen("blue"));
    M_R->attach(ui->qwtPlot_reflection);
    M_T->setPen(QPen("red"));
    M_T->attach(ui->qwtPlot_transmission);
    M_U->setPen(QPen("green"));
    M_U->attach(ui->qwtPlot_transmission);

    /* ---------------------------------------- */

    /*
     * Connect and configure the Inverse Adding-Doubling stuff
     */

    /* Connect buttons in Inverse Adding-Doubling tab */
    connect(ui->button_iad_newConfiguration, SIGNAL(clicked()), this, SLOT(newConfigurationIAD()));
    connect(ui->button_iad_openConfiguration, SIGNAL(clicked()), this, SLOT(openConfigurationIAD()));
    connect(ui->button_iad_calibrate, SIGNAL(clicked()), this, SLOT(calibrateIAD()));
    connect(ui->button_iad_measure, SIGNAL(clicked()), this, SLOT(measureIAD()));
    connect(ui->checkBox_iad_liveView, SIGNAL(clicked(bool)), this, SLOT(liveViewIAD()));

    /* No configuration file loaded by default */
    ui->label_iad_configurationName->setText(QString("No configuration loaded"));
    ui->label_iad_configurationName->setStyleSheet("QLabel { color: red; text-decoration: none; }");
    ui->label_iad_configurationName->setCursor(QCursor(Qt::ArrowCursor));

    //ui->table_iad_measurements->setup();

    /*
     * Create timer for updating spectrometer progress bars
     */

    /* Create timer object */
    timer = new QTimer(this);

    /* If timer times out, things should be updated */
    connect(timer, SIGNAL(timeout()), this, SLOT(updateProgress()));

    /*
     * Connect and configure the Polarimeter stuff ****************************************************************************************************
     */

        /* Connect buttons in Polarimeter Tab */
         connect(ui->button_Start_Meas_Pol, SIGNAL(clicked()), this, SLOT(startMeasurement()));
         connect(ui->button_Stop_Meas_Pol, SIGNAL(clicked()), this, SLOT(stopMeasurement()));

         /* If there are spectrometers connected, allow the Measurements*/
       //  ui->button_Start_Meas_Pol->setDisabled((!m_NrDevices) ? true : false); *************----------------------------------
         ui->button_Stop_Meas_Pol->setDisabled(true);

         /* Connect buttons for saving purposes manually */
         connect(ui->button_Save_FFT_Pol, SIGNAL(clicked()), this, SLOT(saveManuallyFFT()));
         connect(ui->Button_Save_Graphs_Pol, SIGNAL(clicked()), this, SLOT(saveGraph_Pol()));
         connect(ui->checkBox_Save_Pol, SIGNAL(clicked(bool)), this, SLOT(Save_FFT()));
         connect(ui->checkBox_Save_Pol_Raw, SIGNAL(clicked(bool)), this, SLOT(Save_Raw()));

         /* Connect buttons for saving purposes Automatically */
         connect(ui->checkBox_AutoSave_Pol, SIGNAL(clicked(bool)), this, SLOT(AutoSave_FFT()));
         connect(ui->checkBox_AutoSave_Pol_Raw, SIGNAL(clicked(bool)), this, SLOT(AutoSave_Raw()));

         /* Connect button for Faraday Rotator and Syringe Pump Configuration */
         connect(ui->button_Conf_Setup_Pol, SIGNAL(clicked()), this, SLOT(ConfSetup_Pol()));
         connect(ui->button_Pol_Syringe, SIGNAL(clicked()), this, SLOT(ConfSetup_Pol_Pump()));
}

/**
 * @brief Called if a widget on a spectrometer item in list got clicked,
 *        e.g. the configuration button or integration time label.
 * @param widget Widget which has been clicked
 */
void Panel::handleClickEvent(QWidget *widget)
{
    QLineEdit *lineEdit = qobject_cast<QLineEdit *>(widget);
    QPushButton *pushButton = qobject_cast<QPushButton *>(widget);
    QLabel *label = qobject_cast<QLabel *>(widget);
    QCheckBox *checkBox = qobject_cast<QCheckBox *>(widget);

    unsigned int i = 0;

    /* Loop through spectrometers */
    for (i = 0; i < m_NrDevices; i++)
    {
        /* The readable name has been changed */
        if (lineEdit == devices[i]->ui->lineEdit_name)
        {
            /* Get current readable name */
            QString readableName = devices[i]->ui->lineEdit_name->text();

            /* Check length of readable name */
            if (!readableName.isEmpty())
            {
                /* If it's not empty, set text as new readable name */
                ptrSpectrometers[i]->setReadableName(readableName);
            }
        }
        /* The configuration button has been clicked */
        if (pushButton == devices[i]->ui->button_config)
        {
            SpectrometerConfig configDialog(this);

            /* Show configuration dialog */
            configDialog.assignSpectrometer(i);

            /* Execute dialog */
            configDialog.exec();

            /*
             * Spectrometer configuration might have changed. Changes are automatically
             * applied to the assigned spectrometer object, but the item in the devices
             * list needs to be updated, too.
             */

            /* Apply current integration time and number of averages */
            devices[i]->setIntegrationTime(ptrSpectrometers[i]->getIntegrationTime());
            devices[i]->setNumberOfAverages(ptrSpectrometers[i]->getNumberOfAverages());

            /*
             * If start or stop pixel change, the range of displayed wavelengths changes
             * too. We need to adjust the area of our graph which is visible to the user.
             */

            double startWavelengths[m_NrDevices], stopWavelengths[m_NrDevices];

            /* Loop through spectrometers */
            for (i = 0; i < m_NrDevices; i++)
            {
                /* Get start and stop wavelengths for current spectrometer */
                startWavelengths[i] = ptrSpectrometers[i]->getStartWavelength();
                stopWavelengths[i] = ptrSpectrometers[i]->getStopWavelength();
            }

            double minWavelength, maxWavelength;

            /* Find minimum and maximum wavelengths in arrays */
            minWavelength = getMinimum(startWavelengths, m_NrDevices);
            maxWavelength = getMaximum(stopWavelengths, m_NrDevices);

            /* Update x-axis of graphs */
            ui->qwtPlot->setXAxis(minWavelength, maxWavelength);
            ui->qwtPlot_reflection->setXAxis(minWavelength, maxWavelength);
            ui->qwtPlot_transmission->setXAxis(minWavelength, maxWavelength);
            ui->qwtPlot_Pol->setXAxis(minWavelength, maxWavelength);

        }
        /* The EEPROM button has been clicked */
        else if (pushButton == devices[i]->ui->button_eeprom)
        {
            /* Show EEPROM dialog for spectrometer */
            ptrSpectrometers[i]->showEEPROM();
        }
        /* The integration time label has been clicked */
        else if (label == devices[i]->ui->label_integrationTime || label == devices2[0]->ui->label_integrationTime)
        {
            PanelChangeTime changeDialog(this);

            /* Set integration time */
            changeDialog.setValue(devices[i]->getIntegrationTime());
            changeDialog.setValue(devices2[0]->getIntegrationTime());

            /* User pressed 'ok' */
            if (QDialog::Accepted == changeDialog.exec())
            {
                /* Get new integration time */
                float intTime = changeDialog.getValue();

                /* Set panel item and device integration time */
                devices[i]->setIntegrationTime(intTime);
                devices2[0]->setIntegrationTime(intTime);
                ptrSpectrometers[i]->setIntegrationTime(intTime);

                /* Is the device measuring? */
                if (ptrSpectrometers[i]->isMeasuring())
                {
                    /* Stop running measurements */
                    ptrSpectrometers[i]->stopMeasurement();

                    /* Prepare for new measurement */
                    if (ptrSpectrometers[i]->prepareMeasurement())
                    {
                        /* If successful, start measurement */
                        ptrSpectrometers[i]->startMeasurement(-1);
                    }
                }
            }
        }
        /* The auto-adjust label has been clicked */
        else if (label == devices[i]->ui->label_autoAdjust || label == devices2[0]->ui->label_autoAdjust)
        {
            /* Run automatic adjustment of integration time */
            adjustIntegrationTime(i);
        }
        /* The number of averages label has been clicked */
        else if (label == devices[i]->ui->label_numberOfAverages || label == devices2[0]->ui->label_numberOfAverages )
        {
            PanelChangeAverages changeDialog(this);

            /* Set number of averages */
            changeDialog.setValue(devices[i]->getNumberOfAverages());
            changeDialog.setValue(devices2[0]->getNumberOfAverages());

            /* User pressed 'ok' */
            if (QDialog::Accepted == changeDialog.exec())
            {
                /* Get new number of averages */
                int numberOfAverages = changeDialog.getValue();

                /* Set panel item and device number of averages */
                devices[i]->setNumberOfAverages(numberOfAverages);
                devices2[0]->setNumberOfAverages(numberOfAverages);
                ptrSpectrometers[i]->setNumberOfAverages(numberOfAverages);

                /* Is the device measuring? */
                if (ptrSpectrometers[i]->isMeasuring())
                {
                    /* Stop running measurements */
                    ptrSpectrometers[i]->stopMeasurement();

                    /* Prepare for new measurement */
                    if (ptrSpectrometers[i]->prepareMeasurement())
                    {
                        /* If successful, start measurement */
                        ptrSpectrometers[i]->startMeasurement(-1);
                    }
                }
            }
        }
        /* The device enabled checkbox has been clicked */
        else if (checkBox == devices[i]->ui->checkBox_enabled)
        {
            /* Is the given spectrometer in list enabled? */
            bool isChecked = devices[i]->getIsChecked();
            bool isChecked2 = devices[0]->getIsChecked();

            /* Disable or enable complete item */
            devices[i]->setIsEnabled(isChecked);
            devices[i]->setClickableLabelsEnabled(isChecked);
            devices2[0]->setIsEnabled(isChecked2);
            devices2[0]->setClickableLabelsEnabled(isChecked2);
            ptrSpectrometers[i]->setEnabled(isChecked);

            /*
             * Furthermore, we have to check if there are any enabled spectrometers left.
             * If no spectrometers are enabled anymore, preview has to be disabled.
             */

            bool devicesEnabled = false;

            unsigned int i = 0;

            /* Loop through devices */
            for (i = 0; i < m_NrDevices; i++)
            {
                devicesEnabled = devicesEnabled || devices[i]->getIsEnabled();
            }

            /* Update buttons */
            ui->pushButton_preview->setEnabled(devicesEnabled ? true : false);
            ui->pushButton_storeToRam->setEnabled(devicesEnabled ? true : false);
            ui->pushButton_timePattern->setEnabled(devicesEnabled ? true : false);
            ui->button_Start_Meas_Pol->setEnabled(devicesEnabled ? true : false);

        }
    }
}

/**
 * @brief Starts StoreToRAM
 */
void Panel::storeToRam(void)
{
    /* Disable buttons */
    ui->pushButton_storeToRam->setEnabled(false);
    ui->pushButton_timePattern->setEnabled(false);
    ui->pushButton_preview->setEnabled(false);

    unsigned int i = 0;

    /* Loop through devices */
    for (i = 0; i < m_NrDevices; i++)
    {
        /* Is spectrometer enabled? */
        if (devices[i]->getIsChecked())
        {
            /* Disable GUI elements */
            devices[i]->setIsEnabled(false);
        }

        /* Disable checkboxes */
        devices[i]->ui->checkBox_enabled->setEnabled(false);
    }

    PanelStoreToRAM storeToRAM(this);

    /* Loop through devices */
    for (i = 0; i < m_NrDevices; i++)
    {
        /* Is spectrometer enabled? */
        if (devices[i]->getIsChecked())
        {
            /* Is the device enabled and measuring? */
            if (ptrSpectrometers[i]->isMeasuring())
            {
               /* Stop measurement on current device */
               ptrSpectrometers[i]->stopMeasurement();
            }

            /* Add device to list */
            storeToRAM.addSpectrometer(i);
        }
    }

    /* Execute StoreToRAM dialog */
    storeToRAM.exec();

    /* Loop through devices */
    for (i = 0; i < m_NrDevices; i++)
    {
        /* Is spectrometer enabled? */
        if (devices[i]->getIsChecked())
        {
            /* Enable GUI elements */
            devices[i]->setIsEnabled(true);
        }

        /* Disable checkboxes */
        devices[i]->ui->checkBox_enabled->setEnabled(true);
    }

    /* Enable buttons */
    ui->pushButton_preview->setEnabled(true);
    ui->pushButton_timePattern->setEnabled(true);
    ui->pushButton_storeToRam->setEnabled(true);
}

/**
 * @brief Allows measurements by specific time pattern
 */
void Panel::timePattern(void)
{
    /* Disable buttons */
    ui->pushButton_storeToRam->setEnabled(false);
    ui->pushButton_timePattern->setEnabled(false);
    ui->pushButton_preview->setEnabled(false);

    unsigned int i = 0;

    /* Loop through devices */
    for (i = 0; i < m_NrDevices; i++)
    {
        /* Is spectrometer enabled? */
        if (devices[i]->getIsChecked())
        {
            /* Disable GUI elements */
            devices[i]->setIsEnabled(false);
        }

        /* Disable checkboxes */
        devices[i]->ui->checkBox_enabled->setEnabled(false);
    }

    PanelTimePattern timePattern(this);

    /* Loop through devices */
    for (i = 0; i < m_NrDevices; i++)
    {
        /* Is spectrometer enabled? */
        if (devices[i]->getIsChecked())
        {
            /* Is the device enabled and measuring? */
            if (ptrSpectrometers[i]->isMeasuring())
            {
               /* Stop measurement on current device */
               ptrSpectrometers[i]->stopMeasurement();
            }
        }
    }

    /* Execute time pattern dialog */
    timePattern.exec();

    /* Loop through devices */
    for (i = 0; i < m_NrDevices; i++)
    {
        /* Is spectrometer enabled? */
        if (devices[i]->getIsChecked())
        {
            /* Disable GUI elements */
            devices[i]->setIsEnabled(true);
        }

        /* Active checkboxes again */
        devices[i]->ui->checkBox_enabled->setEnabled(true);
    }

    /* Enable buttons */
    ui->pushButton_preview->setEnabled(true);
    ui->pushButton_timePattern->setEnabled(true);
    ui->pushButton_storeToRam->setEnabled(true);
}

/**
 * @brief Toggles preview of spectrometer data
 */
void Panel::togglePreview(void)
{
    /* Preview running or not? */
    if (!previewRunning)
    {
        /* No preview running at the moment. Start preview. */
        startPreview();
    }
    else
    {
        /* Preview running at the moment. Stop preview. */
        stopPreview();
    }
}

/**
 * @brief Starts preview of spectrometer data
 */
void Panel::startPreview(void)
{
    /* Disable buttons */
    ui->pushButton_preview->setEnabled(false);
    ui->pushButton_storeToRam->setEnabled(false);
    ui->pushButton_timePattern->setEnabled(false);

    ui->button_Stop_Meas_Pol->setEnabled(true);
    ui->button_Start_Meas_Pol->setEnabled(false);

    unsigned int i = 0;

    /* Loop through devices */
    for (i = 0; i < m_NrDevices; i++)
    {
        /* Is spectrometer enabled? */
        if (devices[i]->getIsChecked())
        {
            /* Disable GUI elements */
            devices[i]->setIsEnabled(false);
        }

        /* Active checkboxes again */
        devices[i]->ui->checkBox_enabled->setEnabled(false);
    }

    /* Loop through devices */
    for (i = 0; i < m_NrDevices; i++)
    {
        /* Is spectrometer enabled? */
        if (devices[i]->getIsChecked())
        {
            /* Prepare for new measurement */
            if (ptrSpectrometers[i]->prepareMeasurement())
            {
                /* If successful, start measurement */
                ptrSpectrometers[i]->startMeasurement(-1);
            }

            /* Handle events and update UI */
            Application::processEvents();
        }
    }

    /* Remember preview is running */
    previewRunning = true;

    /* Start update timer */
    timer->start(1);

    /* Update preview button */
    ui->pushButton_preview->setText("Stop preview");
    ui->pushButton_preview->setEnabled(true);
}

/**
 * @brief Stops preview of spectrometer data
 */
void Panel::stopPreview(void)
{
    /* Disable preview button */
    ui->pushButton_preview->setEnabled(false);

    unsigned int i = 0;

    /* Loop through devices */
    for (i = 0; i < m_NrDevices; i++)
    {
        /* Is spectrometer enabled? */
        if (devices[i]->getIsChecked())
        {
            /* Stop measurement */
            ptrSpectrometers[i]->stopMeasurement();
        }

        /* Handle events and update UI */
        Application::processEvents();
    }

    /* Loop through devices */
    for (i = 0; i < m_NrDevices; i++)
    {
        /* Is spectrometer enabled? */
        if (devices[i]->getIsChecked())
        {
            /* Enable GUI elements */
            devices[i]->setIsEnabled(true);
        }

        /* Active checkboxes again */
        devices[i]->ui->checkBox_enabled->setEnabled(true);
    }

    /* No preview running anymore */
    previewRunning = false;

    /* Stop update timer */
    timer->stop();

    /* Update preview button */
    ui->pushButton_preview->setText("Start preview");
    ui->pushButton_preview->setEnabled(true);

    /* Enable buttons */
    ui->pushButton_storeToRam->setEnabled(true);
    ui->pushButton_timePattern->setEnabled(true);

    ui->button_Stop_Meas_Pol->setEnabled(false);
    ui->button_Start_Meas_Pol->setEnabled(true);
}

/**
 * @brief Show legend
 */
void Panel::showLegend(void)
{
    PanelLegend legend(this);

    /* Execute legend */
    legend.exec();
}

/**
 * @brief Saves the graph to disk
 */
void Panel::saveGraph(void)
{
    QString exportPath;

    /* Get path for data export */
    exportPath = QFileDialog::getSaveFileName(this, QString("Save graph"), (!lastExportPath.length()) ? "." : lastExportPath, QString("Portable document format (*.pdf)"));

    /* Check export path */
    if (!exportPath.isEmpty())
    {
        /* Remember export path */
        lastExportPath = exportPath;

        /* Save graph to disk */
        ui->qwtPlot->save(exportPath);
    }
}

/**
 * @brief Exports data to text file
 */
void Panel::exportData(void)
{
    QString exportPath;

    /* Get path for data export */
    exportPath = QFileDialog::getSaveFileName(this, QString("Export data"), (!lastExportPath.length()) ? "." : lastExportPath, QString("Text file (*.txt)"));

    /* Check export path */
    if (!exportPath.isEmpty())
    {
        /* Remember export path */
        lastExportPath = exportPath;

        unsigned int i = 0, numDevicesEnabled = 0;

        /* Loop through devices */
        for (i = 0; i < m_NrDevices; i++)
        {
            /* Is current device enabled? */
            if (devices[i]->getIsChecked())
            {
                QString filePath;

                /* Append serial number to export filename */
                filePath = exportPath.left(exportPath.length() - 4) + "_" + ptrSpectrometers[i]->getSerialNumber() + ".txt";

                QFileInfo checkFile(filePath);

                /* Check if file exists */
                if (checkFile.exists() && checkFile.isFile())
                {
                    /* File exists. Did we ask the user whether files should be overwritten or not? */
                    if (QMessageBox::Yes == QMessageBox::question(this, "File already exists", "Do you really want to overwrite existing file data?",
                                                                  QMessageBox::Yes | QMessageBox::No))
                    {
                        /* Button 'yes' pressed; export data for current spectrometer */
                        ptrSpectrometers[i]->saveData(filePath);
                    }
                }
                else
                {
                    /* File doesn't exist; export data for current spectrometer */
                    ptrSpectrometers[i]->saveData(filePath);
                }

                /* Increase counter of enabled devices */
                numDevicesEnabled++;
            }
        }

        /* Check if at least one device was enabled */
        if (!numDevicesEnabled)
        {
            /* Show warning */
            showWarning(QString("No devices enabled"), QString(""));
        }
    }
}

/**
 * @brief Show 'about' dialog
 */
void Panel::showAbout(void)
{
    PanelAbout aboutDialog(this);

    /* Execute dialog */
    aboutDialog.exec();
}

/**
 * @brief Gets curve's visibility
 *
 * @param[in] i Index of curve
 * @return TRUE if curve is visible, else FALSE
 */
bool Panel::isCurveVisible(unsigned int i)
{
    return curves[i]->isVisible();
}

/**
 * @brief Sets curve's visibility
 *
 * @param[in] i Index of curve
 * @param[in] value TRUE if curve should be visible, else FALSE
 */
void Panel::setCurveVisible(unsigned int i, bool value)
{
    curves[i]->setVisible(value);
    curves_Pol[i]->setVisible(value);

}

/**
 * @brief Updates the graph
 */
void Panel::updateGraph(void)
{
    /* Update the graph */
    ui->qwtPlot->update();
    ui->qwtPlot_Pol->update();
}

/**
 * @brief Updates spectrometer progress bar
 */
void Panel::updateProgress(void)
{
    unsigned int i = 0;

    /* Loop through spectrometers */
    for (i = 0; i < m_NrDevices; i++)
    {
        /* Is current spectrometer activated and measuring? */
        if (devices[i]->getIsChecked() && ptrSpectrometers[i]->isMeasuring())
        {
            /* Get time elapsed since start of measurement */
            qint64 timeElapsed = ptrSpectrometers[i]->getTimeElapsed();

            /* More than 100 ms elapsed since last update? */
            if (timeElapsed >= 100)
            {
                /* Update progress bar */
                devices[i]->setProgress(timeElapsed / ptrSpectrometers[i]->getTimePerMeasurement() * 100);
            }
        }
    }
}

/**
 * @brief Automatic adjustment of integration time
 * @param[in] id Spectrometer ID
 */
void Panel::adjustIntegrationTime(unsigned int id)
{
    /* Remember whether the spectrometer is measuring or not */
    bool wasMeasuring = ptrSpectrometers[id]->isMeasuring();

    /* Is the spectrometer measuring? */
    if (wasMeasuring)
    {
        /* Yes, so stop the measurement */
        ptrSpectrometers[id]->stopMeasurement();

        /* Handle events and update UI */
        Application::processEvents();

        /* Wait 1 ms */
        Timer::msleep(1);
    }

    /*
     * We need a linear relationship between counts and integration time, so dynamic dark
     * correction has to be disabled. There's a linear relationship between counts and
     * integration time then. This is only valid for the signal part of the spectrum. The
     * background behaves different and have to be removed first to calculate a scale factor.
     */

    /* If high-resolution ADC is enabled, try to reach 60000 counts; else 15000 */
    double targetCounts = ptrSpectrometers[id]->getUseHighResADC() ? 60000.0 : 15000.0;

    /* Remember whether the spectrometer has dynamic dark correction enabled or not */
    bool hadDynamicDarkCorrection = ptrSpectrometers[id]->getDynamicDarkCorrection();

    /* Remember current number of averages */
    int numberOfAverages = ptrSpectrometers[id]->getNumberOfAverages();

    /* Enable dynamic dark correction */
    ptrSpectrometers[id]->setForgetPercentage(100);
    ptrSpectrometers[id]->setDynamicDarkCorrection(true);

    /* Reduce number of averages to minimum */
    ptrSpectrometers[id]->setNumberOfAverages(1);

    /* Maximum counts from last spectrum */
    double maxCounts = 0.0;

    /* Number of loops done for adjustment */
    unsigned char loopCounts = 0;

    do
    {
        /* Prepare measurement; only continue if successful */
        if (ptrSpectrometers[id]->prepareMeasurement())
        {
            /* Number of measurements done */
            unsigned long before = 0;

            /* Get current number of measurements done */
            before = ptrSpectrometers[id]->getMeasCount();

            /* Measure one spectra */
            if (ptrSpectrometers[id]->startMeasurement(1))
            {
                /* Wait until done; update event loop */
                do
                {
                    /* Handle events and update UI */
                    Application::processEvents();

                    /* Wait 1 ms */
                    Timer::msleep(1);
                }
                while (ptrSpectrometers[id]->getMeasCount() < before + 1);
            }
            else
            {
                /* Restore spectrometer settings */
                ptrSpectrometers[id]->setDynamicDarkCorrection(hadDynamicDarkCorrection);
                ptrSpectrometers[id]->setNumberOfAverages(numberOfAverages);

                /* Show warning */
                showWarning(QString("Unable to start measurement on spectrometer %1!").arg(ptrSpectrometers[id]->getSerialNumber()), QString(""));
                break;
            }
        }
        else
        {
            /* Restore spectrometer settings */
            ptrSpectrometers[id]->setDynamicDarkCorrection(hadDynamicDarkCorrection);
            ptrSpectrometers[id]->setNumberOfAverages(numberOfAverages);

            /* Show warning */
            showWarning(QString("Unable to prepare measurement on spectrometer %1!").arg(ptrSpectrometers[id]->getSerialNumber()), QString(""));
            break;
        }

        /* Get maximum counts from last spectrum */
        maxCounts = ptrSpectrometers[id]->getMaxCounts();

        /* Do we have more than 5% deviation from target? */
        if ((maxCounts > (targetCounts + (targetCounts * 5 / 100))) ||
            (maxCounts < (targetCounts - (targetCounts * 5 / 100))))
        {
            /* Get current integration time */
            float intTime = devices[id]->getIntegrationTime();

            double scaleFactor = 0.0;

            /* Is spectrometer saturated? */
            if (!ptrSpectrometers[id]->isSaturated())
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
                showWarning(QString("Integration time on spectrometer %1 is limited to 10 seconds!").arg(ptrSpectrometers[id]->getSerialNumber()), QString(""));
            }

            /* Integration time smaller than 1.05 ms? */
            if (intTime < 1.05f)
            {
                /* Limit to 1.05 ms */
                intTime = 1.05f;
            }

            /* Set panel item and device new integration time */
            devices[id]->setIntegrationTime(intTime);
            devices2[0]->setIntegrationTime(devices[id]->getIntegrationTime());
            ptrSpectrometers[id]->setIntegrationTime(intTime);
        }

        /* Increase loop counter */
        loopCounts++;

        /* Limit number of loops for adjustment to 10 */
        if (loopCounts >= 10)
        {
            /* Show warning */
            showWarning(QString("Unable to adjust integration time on spectrometer %1 within 10 iterations!").arg(ptrSpectrometers[id]->getSerialNumber()), QString(""));
            break;
        }
    }
    /* Leave loop if counts have less than 5% deviation from target */
    while ((maxCounts > (targetCounts + (targetCounts * 5 / 100))) ||
           (maxCounts < (targetCounts - (targetCounts * 5 / 100))));

    /* Restore spectrometer settings */
    ptrSpectrometers[id]->setDynamicDarkCorrection(hadDynamicDarkCorrection);
    ptrSpectrometers[id]->setNumberOfAverages(numberOfAverages);

    /* Was the spectrometer measuring before (e.g. preview)? */
    if (wasMeasuring)
    {
        /* Yes, so prepare the measurement */
        if (ptrSpectrometers[id]->prepareMeasurement())
        {
            /* Restart the measurement */
            if (!ptrSpectrometers[id]->startMeasurement(-1))
            {
                /* Show warning */
                showWarning(QString("Unable to start measurement on spectrometer %1!").arg(ptrSpectrometers[id]->getSerialNumber()), QString(""));
                return;
            }
        }
        else
        {
            /* Show warning */
            showWarning(QString("Unable to prepare measurement on spectrometer %1!").arg(ptrSpectrometers[id]->getSerialNumber()), QString(""));
            return;
        }
    }
}

/**
 * @brief Creates new configuration for IAD method
 */
void Panel::newConfigurationIAD(void)
{
    /*
     * Runs the IAD configuration assistant. No file name will be delivered, so all settings
     * are set to default values. Finally these settings are saved in a configuration file.
     */
    ConfigureIAD assistant(NULL);

    /* Checks if IAD configuration was successful */
    if (assistant.getIsConfigured())
    {
        /* Get path and name of configuration file */
        configPath = assistant.getConfigurationName();
        QFileInfo fileInfo = configPath;
        QString fileName = fileInfo.baseName();

        unsigned int i = 0;

        /* Loop through devices */
        for (i = 0; i < m_NrDevices; i++)
        {
            /* Update name in preview from serial number to readable name */
            devices[i]->setName(ptrSpectrometers[i]->getReadableName());
        }

        /* Process configuration data and update buttons */
        ui->label_iad_configurationName->setText(fileName);
        ui->label_iad_configurationName->setStyleSheet("QLabel { color: blue; text-decoration: underline; }");
        ui->label_iad_configurationName->setCursor(QCursor(Qt::PointingHandCursor));

        /* Enable IAD calibration */
        ui->button_iad_calibrate->setEnabled(true);
        ui->button_iad_measure->setEnabled(false);

        /* Mouse click on label should show IAD configuration */
        connect(ui->label_iad_configurationName, SIGNAL(clicked()), this, SLOT(showConfigurationIAD()));
    }
    else
    {
        /* Process configuration data and update buttons */
        ui->label_iad_configurationName->setText(QString("No configuration loaded"));
        ui->label_iad_configurationName->setStyleSheet("QLabel { color: red; text-decoration: none; }");
        ui->label_iad_configurationName->setCursor(QCursor(Qt::ArrowCursor));

        /* Disable IAD calibration */
        ui->button_iad_calibrate->setEnabled(false);
        ui->button_iad_measure->setEnabled(false);

        /* Mouse click on label should not result in any action */
        disconnect(ui->label_iad_configurationName, SIGNAL(clicked()), this, 0);
    }
}

/**
 * @brief Opens configuration for IAD method
 */
void Panel::openConfigurationIAD(void)
{
    /* Let the user choose the configuration file */
    configPath = QFileDialog::getOpenFileName(this, QString("Open configuration file"), "./config", QString("Configuration file (*.cfg)"));

    /* File selected by user? */
    if (NULL == configPath)
    {
        /* No file selected. Dialog aborted. */
        return;
    }

    /*
     * Runs the IAD configuration assistant. The file name of the selected configuration file
     * will be delivered; all settings are loaded from the configuration file. Any changes will
     * be saved into the configuration file.
     */
    ConfigureIAD assistant(configPath);

    /* Checks if IAD configuration was successful */
    if (assistant.getIsConfigured())
    {
        /* Get path and name of configuration file */
        QFileInfo fileInfo = configPath;
        QString fileName = fileInfo.baseName();

        unsigned int i = 0;

        /* Loop through devices */
        for (i = 0; i < m_NrDevices; i++)
        {
            /* Update name in preview from serial number to readable name */
            devices[i]->setName(ptrSpectrometers[i]->getReadableName());
        }

        /* Process configuration data and update buttons */
        ui->label_iad_configurationName->setText(fileName);
        ui->label_iad_configurationName->setStyleSheet("QLabel { color: blue; text-decoration: underline; }");
        ui->label_iad_configurationName->setCursor(QCursor(Qt::PointingHandCursor));

        /* Enable IAD calibration */
        ui->button_iad_calibrate->setEnabled(true);
        ui->button_iad_measure->setEnabled(false);

        /* Mouse click on label should show IAD configuration */
        connect(ui->label_iad_configurationName, SIGNAL(clicked()), this, SLOT(showConfigurationIAD()));
    }
    else
    {
        /* Process configuration data and update buttons */
        ui->label_iad_configurationName->setText(QString("No configuration loaded"));
        ui->label_iad_configurationName->setStyleSheet("QLabel { color: red; text-decoration: none; }");
        ui->label_iad_configurationName->setCursor(QCursor(Qt::ArrowCursor));

        /* Disable IAD calibration */
        ui->button_iad_calibrate->setEnabled(false);
        ui->button_iad_measure->setEnabled(false);

        /* Mouse click on label should not result in any action */
        disconnect(ui->label_iad_configurationName, SIGNAL(clicked()), this, 0);
    }
}

/**
 * @brief Shows configuration for IAD method
 */
void Panel::showConfigurationIAD(void)
{
    /*
     * Runs the IAD configuration assistant. The file name of the currently loaded configuration
     * file will be delivered; all settings are loaded from the configuration file. Any changes will
     * be saved into the configuration file.
     */
    ConfigureIAD assistant(configPath);
}

/**
 * @brief Do calibration for IAD method
 */
void Panel::calibrateIAD(void)
{
    /* Check if preview is running */
    if (previewRunning)
    {
        /* Stop preview */
        stopPreview();
    }

    /* Disable all buttons */
    ui->pushButton_preview->setDisabled(true);
    ui->pushButton_storeToRam->setDisabled(true);
    ui->pushButton_timePattern->setDisabled(true);
    ui->pushButton_exportData->setDisabled(true);
    ui->pushButton_saveGraph->setDisabled(true);
    ui->pushButton_about->setDisabled(true);

    CalibrateIAD assistant(Rd_factor, Td_factor, Tu_factor);

    /* Get status of calibration */
    bool isCalibrated = assistant.getIsCalibrated();

    /* Process assistant data and update buttons */
    ui->button_iad_measure->setEnabled(isCalibrated);
    ui->checkBox_iad_liveView->setEnabled(isCalibrated);
    ui->lineEdit_iad_name->setEnabled(isCalibrated);
    ui->plainTextEdit_iad_description->setEnabled(isCalibrated);

    /* Enable all buttons */
    ui->pushButton_preview->setEnabled(true);
    ui->pushButton_storeToRam->setEnabled(true);
    ui->pushButton_timePattern->setEnabled(true);
    ui->pushButton_exportData->setEnabled(true);
    ui->pushButton_saveGraph->setEnabled(true);
    ui->pushButton_about->setEnabled(true);
}

/**
 * @brief Do measurement for IAD method
 */
void Panel::measureIAD(void)
{
            /* Check for measurement name */
            if (ui->lineEdit_iad_name->text().isEmpty())
            {
                /* Show message */
                showWarning(QString("You have to enter a name for the measurement."), QString(""));
                return;
            }

            /* Disable 'Measure' button */
            ui->button_iad_measure->setEnabled(false);

            /* Check if preview is running */
            if (previewRunning)
            {
                /* Stop preview */
                stopPreview();
            }

        /* Disable all buttons */
        ui->pushButton_preview->setDisabled(true);
        ui->pushButton_storeToRam->setDisabled(true);
        ui->pushButton_timePattern->setDisabled(true);
        ui->pushButton_exportData->setDisabled(true);
        ui->pushButton_saveGraph->setDisabled(true);
        ui->pushButton_about->setDisabled(true);

        MeasureIAD assistant;

        /* Set measurement name and description */
        assistant.setName(ui->lineEdit_iad_name->text());
        assistant.setDescription(ui->plainTextEdit_iad_description->toPlainText());

        /* Run measurement */
        if (assistant.measure())
        {
            /* Measurement successful */
            assistant.save(NULL);

            /* Add current measurement to list of measurements */
            ui->table_iad_measurements->add(assistant.getName(), ui->lineEdit_iad_name->text(),
                                            assistant.getDate(), assistant.getTime());
        }

        /* Enable all buttons */
        ui->pushButton_preview->setEnabled(true);
        ui->pushButton_storeToRam->setEnabled(true);
        ui->pushButton_timePattern->setEnabled(true);
        ui->pushButton_exportData->setEnabled(true);
        ui->pushButton_saveGraph->setEnabled(true);
        ui->pushButton_about->setEnabled(true);
}

void Panel::liveViewIAD(void)
{
    if (ui->checkBox_iad_liveView->isChecked())
    {
        startPreview();
    }
    else
    {
        stopPreview();
    }
}

/**
 * @brief Data from spectrometer has arrived
 * @param WParam
 * @param LParam
 */
void Panel::ReceiveDataIsHere(int WParam, int LParam)
{
    /* Successful gained data */
    if (WParam >= ERR_SUCCESS)
    {
        /* Graph needs update? */
        bool needUpdate = false;

        unsigned int i = 0;

        /* Loop through spectrometers */
        for (i = 0; i < m_NrDevices; i++)
        {
            /* Did the current spectrometer sent the data? */
            if ((LParam == ptrSpectrometers[i]->getHandle()) && (ptrSpectrometers[i]->getNumberOfPixels() > 0))
            {
                /* Normal measurement? */
                if (ERR_SUCCESS == WParam)
                {
                    /* Handle event */
                    ptrSpectrometers[i]->handleEvent();

                    /* Update saturation status */
                    devices[i]->setIsSaturated(ptrSpectrometers[i]->isSaturated());
                    devices2[0]->setIsSaturated(ptrSpectrometers[0]->isSaturated());

                    /* Graph needs update */
                    needUpdate = true;
                }
                /* Start Store to RAM measurement */
                else
                {
                    /* Get StoreToRAM path */
                    QString path = ptrSpectrometers[i]->getStoreToRAMPath();

                    /* Show error if no path is choosen */
                    if (path.isEmpty())
                    {
                        /* Show critical error */
                        showCritical(QString("No path for StoreToRAM file specified!"), QString(""));
                        return;
                    }

                    /* Allocate memory for spectra (number of pixel elements multiplied with the number of measurements) */
                    double *a_pSpectrum = new double[ptrSpectrometers[i]->getNumberOfPixels() * (unsigned int)WParam];

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
                        if ((LParam == ptrSpectrometers[i]->getHandle()) && (ptrSpectrometers[i]->getNumberOfPixels() > 0))
                        {
                            /* Handle event */
                            ptrSpectrometers[i]->handleEvent();

                            /* Update saturation status */
                            devices[i]->setIsSaturated(ptrSpectrometers[i]->isSaturated());
                            devices2[0]->setIsSaturated(ptrSpectrometers[0]->isSaturated());

                            /* Save counts */
                            double *temp = ptrSpectrometers[i]->getCounts();

                            unsigned int k = 0;

                            /* Loop through pixel values */
                            for (k = 0; k < ptrSpectrometers[i]->getNumberOfPixels(); k++)
                            {
                                *(a_pSpectrum + (ptrSpectrometers[i]->getNumberOfPixels() * (j - 1)) + k) = *(temp + k);
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
                        showCritical(QString("Unable to create file '%1'.").arg(ptrSpectrometers[i]->getStoreToRAMPath()), QString(""));
                        return;
                    }

                    /* Write header */
                    fprintf(file, "Serial number: %s\n", ptrSpectrometers[i]->getSerialNumber().toLatin1().data());
                    if (ptrSpectrometers[i]->hasReadableName())
                    {
                        fprintf(file, "Readable name: %s\n", ptrSpectrometers[i]->getReadableName().toLatin1().data());
                    }
                    fprintf(file, "Integration time: %.2f ms\n", ptrSpectrometers[i]->getIntegrationTime());
                    fprintf(file, "Number of averages: %i\n\n", ptrSpectrometers[i]->getNumberOfAverages());

                    /* Save wavelength */
                    double *a_pWavelength = ptrSpectrometers[i]->getWavelengths();

                    /* Loop through pixel values */
                    for (j = 0; j < ptrSpectrometers[i]->getNumberOfPixels(); j++)
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
                            fprintf(file, "\t\t%.2f", *(a_pSpectrum + ptrSpectrometers[i]->getNumberOfPixels() * k + j));
                        }
                        fprintf(file, "\n");
                    }

                    /* Close file */
                    fclose(file);
                    file = nullptr;

                    /* Free memory */
                    delete[] a_pSpectrum;
                    a_pSpectrum = nullptr;

                    /* Spectrometer finished measurement */
                    ptrSpectrometers[i]->bMeasuring = false;

                    /* Enable GUI elements */
                    devices[i]->setIsEnabled(true);
                    devices[i]->ui->checkBox_enabled->setEnabled(true);
                }
            }

            /* Update curve data */
            curves[i]->setSamples(ptrSpectrometers[i]->getWavelengths(), ptrSpectrometers[i]->getCounts(), ptrSpectrometers[i]->getNumberOfPixels());
            curves_Pol[i]->setSamples(ptrSpectrometers[i]->getWavelengths(), ptrSpectrometers[i]->getCounts(), ptrSpectrometers[i]->getNumberOfPixels());

            /* ---------------------------------------- */

            /* To do */
            if ((nullptr != Rd_factor) && (nullptr != Td_factor) && (nullptr != Tu_factor))
            {
                unsigned int j = 0;

                double pixels[ptrSpectrometers[i]->getNumberOfPixels()];

                if (!QString::compare(ptrSpectrometers[i]->getReadableName(), QString("Diffuse reflection")))
                {
                    for (j = 0; j < ptrSpectrometers[i]->getNumberOfPixels(); j++)
                    {
                        pixels[j] = 1 * (ptrSpectrometers[i]->getCounts()[j] - 0/* Dark */) / Rd_factor[j];
                    }
                    M_R->setSamples(ptrSpectrometers[i]->getWavelengths(), pixels, ptrSpectrometers[i]->getNumberOfPixels());
                }
                else if (!QString::compare(ptrSpectrometers[i]->getReadableName(), QString("Diffuse transmission")))
                {
                    for (j = 0; j < ptrSpectrometers[i]->getNumberOfPixels(); j++)
                    {
                        pixels[j] = (ptrSpectrometers[i]->getCounts()[j] - 0/* Dark */) / Td_factor[j];
                    }
                    M_T->setSamples(ptrSpectrometers[i]->getWavelengths(), pixels, ptrSpectrometers[i]->getNumberOfPixels());
                }
                else if (!QString::compare(ptrSpectrometers[i]->getReadableName(), QString("Unscattered transmission")))
                {
                    for (j = 0; j < ptrSpectrometers[i]->getNumberOfPixels(); j++)
                    {
                        pixels[j] = (ptrSpectrometers[i]->getCounts()[j] - 0/* Dark */) / Tu_factor[j];
                    }
                    M_U->setSamples(ptrSpectrometers[i]->getWavelengths(), pixels, ptrSpectrometers[i]->getNumberOfPixels());
                }
            }

            /* ---------------------------------------- */
        }

        /* Does the graph needs a update? */
        if (needUpdate)
        {
            /* Update the graph */
            ui->qwtPlot->update();
            ui->qwtPlot_Pol->update();

        }
    }
}

/**
 * @brief POLARIMETER FUNCTIONS *********************************************************************************
 */

/**
 * @brief Start Measurments for the Polarimeter Setup
 */

void Panel::startMeasurement(void) {

    /* Enable / Disable buttons when measuring */
       ui->button_Stop_Meas_Pol->setEnabled(true);
       ui->button_Start_Meas_Pol->setEnabled(false);
       ui->button_Load_Graphs->setEnabled(false);

       ui->checkBox_AutoSave_Pol->setEnabled(false);
       ui->checkBox_AutoSave_Pol_Raw->setEnabled(false);
       ui->button_Conf_Setup_Pol->setEnabled(false);
       ui->button_Pol_Syringe->setEnabled(false);

       for (unsigned int i = 0; i < m_NrDevices; i++)
       {
           /* Is spectrometer enabled? */
           if (devices[i]->getIsChecked())
           {
               /* Disable GUI elements */
               devices[i]->setIsEnabled(false);
           }

           /* Active checkboxes again */
           devices[i]->ui->checkBox_enabled->setEnabled(false);
       }

           /* Is spectrometer enabled? */
           if (devices2[0]->getIsEnabled())
           {
               /* Prepare for new measurement */
               if (ptrSpectrometers[0]->prepareMeasurement())
               {
                   /* If successful, start measurement */
                   ptrSpectrometers[0]->startMeasurement(-1);
               }

               /* Handle events and update UI */
               Application::processEvents();
          }

       /* Remember preview is running */
       previewRunning = true;

       /* Start update timer */
       timer->start(1);

   // Start the Store to RAM with sequences of storage of Data!!!

   // Can we perform the FFT while measuring or we need to wait until everything is done?
       // if yes... do it every x time
       // else Add a Load data button or an auto load of the last file obtained from the spectrometer and then do FFT

    FFTL = new fft();

    FFTL->getFFT(1000); // 1000 is the number of samples obtained

    FFT_oneWave = new QwtPlotCurve("FFT for " + QString::number(FFTL->wavelengths[438]) + " nm");
    FFT_oneWave->setPen(QPen("blue"));

    FFT_oneWave->setSamples(FFTL->time , FFTL->fft_data,500);

    FFT_oneWave->attach(ui->qwtPlot_Pol_Prediction);

    FFT_DC = new QwtPlotCurve("DC");
    FFT_DC->setPen(QPen("blue"));
    FFT_DC->setSamples(FFTL->wavelengths , FFTL->fft_DC,1430);
    FFT_DC->attach(ui->qwtPlot_Pol_w_2w);

    FFT_W = new QwtPlotCurve("W");
    FFT_W->setPen(QPen("red"));
    FFT_W->setSamples(FFTL->wavelengths , FFTL->fft_W,1430);
    FFT_W->attach(ui->qwtPlot_Pol_w_2w);

    FFT_2W = new QwtPlotCurve("2W");
    FFT_2W->setPen(QPen("green"));
    FFT_2W->setSamples(FFTL->wavelengths , FFTL->fft_2W,1430);
    FFT_2W->attach(ui->qwtPlot_Pol_w_2w);

    }

/**
 * @brief Stop Measurments for the Polarimeter Setup
 */
void Panel::stopMeasurement(void) {

    ui->button_Stop_Meas_Pol->setEnabled(false);
    ui->button_Start_Meas_Pol->setEnabled(true);

    ui->button_Load_Graphs->setEnabled(true);

        /* Is spectrometer enabled? */
        if (devices2[0]->getIsEnabled())
        {
            /* Stop measurement */
            ptrSpectrometers[0]->stopMeasurement();
        }

        for (unsigned int i = 0; i < m_NrDevices; i++)
        {
            /* Is spectrometer enabled? */
            if (devices[i]->getIsChecked())
            {
                /* Enable GUI elements */
                devices[i]->setIsEnabled(true);
            }

            /* Active checkboxes again */
            devices[i]->ui->checkBox_enabled->setEnabled(true);
        }


        /* Handle events and update UI */
        Application::processEvents();

    /* No preview running anymore */
    previewRunning = false;

    /* Stop update timer */
    timer->stop();

    ui->checkBox_AutoSave_Pol->setEnabled(true);
    ui->checkBox_AutoSave_Pol_Raw->setEnabled(true);
    ui->button_Conf_Setup_Pol->setEnabled(true);
    ui->button_Pol_Syringe->setEnabled(true);

}

/**
 * @brief Save the FFT manually from the Polarimeter Setup
 */
void Panel::saveManuallyFFT(void) {

    QString exportPath_Pol;

    /* Get path for data export */
    exportPath_Pol = QFileDialog::getSaveFileName(this, QString("Save FFT"), (!lastExportPath.length()) ? "." : lastExportPath, QString("Text file (*.CS)"));

// ....

}

/**
 * @brief Save the FFT Manually from the Polarimeter Setup
 */
void Panel::Save_FFT(void) {
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
 * @brief Save the Raw Data Manually from the Polarimeter Setup
 */
void Panel::Save_Raw(void) {
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
 * @brief Save the FFT Automatic from the Polarimeter Setup
 */
void Panel::AutoSave_FFT(void) {
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
void Panel::AutoSave_Raw(void) {
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
 * @brief Save All graphs from the Polarimeter Setup
 */
void Panel::saveGraph_Pol(void) {
    QString exportPath_Graph_Pol;

    /* Get path for data export */
    exportPath_Graph_Pol = QFileDialog::getSaveFileName(this, QString("Save graphs"), (!lastExportPath.length()) ? "." : lastExportPath, QString("Portable document format (*.pdf)"));

    /* Check export path */
    if (!exportPath_Graph_Pol.isEmpty())
    {
        /* Remember export path */
        lastExportPath = exportPath_Graph_Pol;

        /* Save graph to disk */
        ui->qwtPlot->save(exportPath_Graph_Pol);
    }
}

/**
 * @brief Opens Previous Measurements of Polarimeter Setup
 */
void Panel::Load_Pol_Graphs(void)
{
    /* Let the user choose the configuration file */
    configPath = QFileDialog::getOpenFileName(this, QString("Open configuration file"), "./config", QString("Configuration file (*.CS)"));

}

/**
 * @brief Configuration of the Faraday Rotator for the Polarimeter Setup
 */
void Panel::ConfSetup_Pol(void) {

}

/**
 * @brief Configuration of the Syrynge Pump for the Polarimeter Setup
 */
void Panel::ConfSetup_Pol_Pump(void) {

}

/**
 * @brief Destructor of 'Panel' class
 */
Panel::~Panel(void)
{
    unsigned int i = 0;

    /* Loop through spectrometers */
    for (i = 0; i < m_NrDevices; i++)
    {
        /* Check handle */
        if (nullptr != curves[i])
        {
            /* Detach curve */
            curves[i]->detach();

            /* Free memory */
            delete curves[i];
            curves[i] = nullptr;
        }
    }

    /* ---------------------------------------- */

    /* To do */
    M_R->detach();
    delete M_R;
    M_R = nullptr;

    M_T->detach();
    delete M_T;
    M_T = nullptr;

    M_U->detach();
    delete M_U;
    M_U = nullptr;

    /* ---------------------------------------- */

    /* Loop through spectrometers */
    for (i = 0; i < m_NrDevices; i++)
    {
        /* Is current spectrometer still measuring? */
        if (ptrSpectrometers[i]->isMeasuring())
        {
            /* Stop current measurement */
            ptrSpectrometers[i]->stopMeasurement();
        }

        /* Free memory */
        delete ptrSpectrometers[i];
        ptrSpectrometers[i] = nullptr;
    }

    /* Check spectrometer array handle */
    if (nullptr != ptrSpectrometers)
    {
        /* Free memory */
        delete[] ptrSpectrometers;
        ptrSpectrometers = nullptr;
    }

    /* Close library */
    AVS_Done();

    /* Delete user interface */
    delete ui;
}
