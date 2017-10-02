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

/* External includes */
#include <QWidget>
#include <QDialog>
#include <QString>

/* Internal includes */
#include "application.h"
#include "messages.h"
#include "timer.h"
#include "spectrometer.h"
#include "light_control.h"
#include "iad_calibrate_page02.h"
#include "ui_iad_calibrate_page02.h"

/*
 * Global variables
 */
extern Spectrometer** ptrSpectrometers;
extern unsigned int m_NrDevices;
extern ControlLight* lightSource;

/**
 * @brief Constructor of 'CalibrateIADPage02' class
 */
CalibrateIADPage02::CalibrateIADPage02(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CalibrateIADPage02)
{
    /* Set up user interface */
    ui->setupUi(this);

    /* Set window flags */
    this->setWindowFlags(Qt::Dialog | Qt::WindowTitleHint | Qt::WindowStaysOnTopHint);

    /* Disable resize of elements */
    this->setFixedSize(this->size());

    /* Call destructor on close event */
    this->setAttribute(Qt::WA_DeleteOnClose);

    /* Calibration ready */
    status = PROCESS_READY;

    /* Connect button signal handles */
    connect(ui->button_abort, SIGNAL(clicked(bool)), this, SLOT(abort()));
    connect(ui->button_next, SIGNAL(clicked(bool)), this, SLOT(next()));
}

/**
 * @brief Adjusts the pinhole for unscattered transmission measurement
 */
void CalibrateIADPage02::process(unsigned int idRd)
{
    /* Waiting for user pressing 'Begin' button */
    while (!(status & PROCESS_RUNNING))
    {
        /* User pressed 'Abort' button? */
        if (status & PROCESS_CLOSED)
        {
            /* Calibration failed */
            status |= PROCESS_FAILURE;
            return;
        }

        /* Handle events and update UI */
        Application::processEvents();

        /* Wait 1 ms */
        Timer::msleep(1);
    }

    /* Save spectrometer assignment */
    this->idRd = idRd;

    /* Set progress bar to zero */
    ui->progressBar->setValue(0);

    /*
     * -----------------------------------------------------------
     * Allocate memory for spectra without sample (full intensity)
     * -----------------------------------------------------------
     */

    /* Check if memory allocated */
    if (nullptr != diffuseReflection_counts)
    {
        /* Free memory */
        delete[] diffuseReflection_counts;
        diffuseReflection_counts = nullptr;
    }

    /* Allocate memory for diffuse reflection (no sample) counts */
    diffuseReflection_counts = new double[ptrSpectrometers[idRd]->getNumberOfPixels()];

    /* Check if memory allocated */
    if (nullptr == diffuseReflection_counts)
    {
        /* Calibration failed */
        status |= PROCESS_FAILURE;

        /* Create message box */
        showCritical(QString("Unable to allocate memory for diffuse reflection (no sample) on spectrometer %1. Calibration aborted.").
                       arg(ptrSpectrometers[idRd]->getSerialNumber()),
                     QString("File:\t%1\nFunction:\t%2\nLine:\t%3").
                       arg(__FILE__, __FUNCTION__, QString::number(__LINE__-3)));

        return;
    }

    /*
     * ---------------------------------------------------------
     * Capture the diffuse reflection spectrum at full intensity
     * ---------------------------------------------------------
     */

    /* Set start integration time and start number of averages */
    float integrationTime = CALIBRATION_RD_START_INTEGRATION_TIME;
    float numberOfAverages = CALIBRATION_RD_START_NUM_AVERAGES;

    /* Enable dynamic dark correction */
    ptrSpectrometers[idRd]->setForgetPercentage(100);
    ptrSpectrometers[idRd]->setDynamicDarkCorrection(true);

    /* Update GUI elements */
    ui->spinBox_diffuseReflection_counts->setValue(0);
    ui->doubleSpinBox_diffuseReflection_integrationTime->setValue(integrationTime);
    ui->spinBox_diffuseReflection_numberOfAverages->setValue(numberOfAverages);

    /* Open light source shutter */
    lightSource->openShutter();

    /* Wait 500 ms */
    Timer::msleep(500);

    /* Number of measurements done */
    unsigned long before = 0;

    /* Maximum counts from last spectrum */
    double maxCounts = 0.0;

    /* Not finished */
    bool done = false;

    do
    {
        /* Set new integration time and number of averages */
        ptrSpectrometers[idRd]->setIntegrationTime(integrationTime);
        ptrSpectrometers[idRd]->setNumberOfAverages(numberOfAverages);

        /* Prepare measurement; only continue if successful */
        if (ptrSpectrometers[idRd]->prepareMeasurement())
        {
            /* Get current number of measurements done */
            before = ptrSpectrometers[idRd]->getMeasCount();

            /* Measure one spectra */
            if (ptrSpectrometers[idRd]->startMeasurement(1))
            {
                /* Wait until done; update event loop */
                do
                {
                    /* Handle events and update UI */
                    Application::processEvents();

                    /* Wait 1 ms */
                    Timer::msleep(1);
                }
                while (ptrSpectrometers[idRd]->getMeasCount() < before + 1);

                /* Get maximum counts from last spectrum */
                maxCounts = ptrSpectrometers[idRd]->getMaxCounts();

                /* Update GUI elements */
                ui->spinBox_diffuseReflection_counts->setValue(maxCounts);
                ui->progressBar_diffuseReflection->setValue(maxCounts);
                ui->doubleSpinBox_diffuseReflection_integrationTime->setValue(integrationTime);
                ui->spinBox_diffuseReflection_numberOfAverages->setValue(numberOfAverages);

                /* Handle events and update UI */
                Application::processEvents();

                /* Counts should be between THRESHOLD_COUNTS_LOW and THRESHOLD_COUNTS_HIGH */
                if ((maxCounts >= THRESHOLD_COUNTS_LOW) && (maxCounts <= THRESHOLD_COUNTS_HIGH))
                {
                    /* Calculate maximum number of averages */
                    int maxNumberOfAverages = CALIBRATION_MAX_TIME_PER_SPECTRUM / integrationTime;

                    /* Done if current number of averages is equal to maximum number of averages */
                    if (numberOfAverages == maxNumberOfAverages)
                    {
                        done = true;
                    }
                    else
                    {
                        numberOfAverages = maxNumberOfAverages;
                    }
                }
                else
                {
                    /* Even if targeted counts are not reached, we're done if it's maximum integration time */
                    if (integrationTime == CALIBRATION_MAX_TIME_PER_SPECTRUM)
                    {
                        done = true;
                    }
                    else
                    {
                        /* Scale integration time to the middle of the 'acceptable value interval' */
                        float factor = (double)CALIBRATION_COUNTS_TARGET / maxCounts;

                        /* Set new integration time */
                        integrationTime = round(integrationTime * factor);

                        /* Check if integration time exceed time limit */
                        if ((integrationTime * numberOfAverages) > CALIBRATION_MAX_TIME_PER_SPECTRUM)
                        {
                            /* Check if we have to limit the integration time */
                            if (integrationTime > CALIBRATION_MAX_TIME_PER_SPECTRUM)
                            {
                                /* Set integration time to maximum and number of averages to one */
                                integrationTime = CALIBRATION_MAX_TIME_PER_SPECTRUM;
                                numberOfAverages = 1;
                            }
                            else
                            {
                                /* Calculate new number of averages */
                                numberOfAverages = CALIBRATION_MAX_TIME_PER_SPECTRUM / integrationTime;
                            }
                        }
                    }
                }
            }
            else
            {
                /* Calibration failed */
                status |= PROCESS_FAILURE;

                /* Create message box */
                showCritical(QString("Unable to start the measurement of diffuse reflection on spectrometer %1. Calibration aborted.").
                               arg(ptrSpectrometers[idRd]->getSerialNumber()),
                             QString("File:\t%1\nFunction:\t%2\nLine:\t%3\n\nbool startMeasurement(short numMeasurements) returned false.").
                               arg(__FILE__, __FUNCTION__, QString::number(__LINE__-3)));

                break;
            }
        }
        else
        {
            /* Calibration failed */
            status |= PROCESS_FAILURE;

            /* Create message box */
            showCritical(QString("Unable to prepare the measurement of diffuse reflection on spectrometer %1. Calibration aborted.").
                           arg(ptrSpectrometers[idRd]->getSerialNumber()),
                         QString("File:\t%1\nFunction:\t%2\nLine:\t%3\n\nbool prepareMeasurement(void) returned false.").
                           arg(__FILE__, __FUNCTION__, QString::number(__LINE__-3)));

            break;
        }
    /* Finished calibration or user pressed 'abort' button? */
    } while (!done && !(status & PROCESS_CLOSED));

    /* Calibration aborted or failure occurred? */
    if (!(status & PROCESS_RUNNING) || (status & PROCESS_FAILURE))
        return;

    /* Update progress bar */
    ui->progressBar->setValue(50);

    /* Set averaging to 10 spectra and disable dynamic dark correction */
    ptrSpectrometers[idRd]->setDynamicDarkCorrection(false);

    /* Prepare measurement; only continue if successful */
    if (ptrSpectrometers[idRd]->prepareMeasurement())
    {
        /* Get current number of measurements done */
        before = ptrSpectrometers[idRd]->getMeasCount();

        /* Measure one spectra */
        if (ptrSpectrometers[idRd]->startMeasurement(1))
        {
            /* Wait until done; update event loop */
            do
            {
                /* Handle events and update UI */
                Application::processEvents();

                /* Wait 1 ms */
                Timer::msleep(1);
            }
            while (ptrSpectrometers[idRd]->getMeasCount() < before + 1);
        }
        else
        {
            /* Calibration failed */
            status |= PROCESS_FAILURE;

            /* Create message box */
            showCritical(QString("Unable to start the measurement of diffuse reflection on spectrometer %1. Calibration aborted.").
                           arg(ptrSpectrometers[idRd]->getSerialNumber()),
                         QString("File:\t%1\nFunction:\t%2\nLine:\t%3\n\nbool startMeasurement(short numMeasurements) returned false.").
                           arg(__FILE__, __FUNCTION__, QString::number(__LINE__-3)));
        }
    }
    else
    {
        /* Calibration failed */
        status |= PROCESS_FAILURE;

        /* Create message box */
        showCritical(QString("Unable to prepare the measurement of diffuse reflection on spectrometer %1. Calibration aborted.").
                       arg(ptrSpectrometers[idRd]->getSerialNumber()),
                     QString("File:\t%1\nFunction:\t%2\nLine:\t%3\n\nbool prepareMeasurement(void) returned false.").
                       arg(__FILE__, __FUNCTION__, QString::number(__LINE__-3)));
    }

    /* Calibration aborted or failure occurred? */
    if (!(status & PROCESS_RUNNING) || (status & PROCESS_FAILURE))
        return;

    /* Update progress bar */
    ui->progressBar->setValue(75);

    /* Save current spectrum with counts normalized per second */
    memcpy(diffuseReflection_counts, ptrSpectrometers[idRd]->getCounts(), ptrSpectrometers[idRd]->getNumberOfPixels());

    /* Save data to file */
    ptrSpectrometers[idRd]->saveData("measure/Rd_std.txt");

    /*
     * ---
     * Dark spectrum
     * ----
     */

    /* Close light source shutter */
    lightSource->closeShutter();

    /* Wait 500 ms */
    Timer::msleep(500);

    /* Prepare measurement; only continue if successful */
    if (ptrSpectrometers[idRd]->prepareMeasurement())
    {
        /* Get current number of measurements done */
        before = ptrSpectrometers[idRd]->getMeasCount();

        /* Measure one spectra */
        if (ptrSpectrometers[idRd]->startMeasurement(1))
        {
            /* Wait until done; update event loop */
            do
            {
                /* Handle events and update UI */
                Application::processEvents();

                /* Wait 1 ms */
                Timer::msleep(1);
            }
            while (ptrSpectrometers[idRd]->getMeasCount() < before + 1);

            /* Get maximum counts from last spectrum; has to be below THRESHOLD_COUNTS_DARK */
            if (THRESHOLD_COUNTS_DARK < ptrSpectrometers[idRd]->getMaxCounts())
            {
                /* Calibration failed */
                status |= PROCESS_FAILURE;

                /* Show message */
                showCritical(QString("Unable to measure dark spectra, counts value too high."), QString(""));
            }
        }
        else
        {
            /* Calibration failed */
            status |= PROCESS_FAILURE;

            /* Create message box */
            showCritical(QString("Unable to start the measurement of diffuse reflection on spectrometer %1. Calibration aborted.").
                           arg(ptrSpectrometers[idRd]->getSerialNumber()),
                         QString("File:\t%1\nFunction:\t%2\nLine:\t%3\n\nbool startMeasurement(short numMeasurements) returned false.").
                           arg(__FILE__, __FUNCTION__, QString::number(__LINE__-3)));
        }
    }
    else
    {
        /* Calibration failed */
        status |= PROCESS_FAILURE;

        /* Create message box */
        showCritical(QString("Unable to prepare the measurement of diffuse reflection on spectrometer %1. Calibration aborted.").
                       arg(ptrSpectrometers[idRd]->getSerialNumber()),
                     QString("File:\t%1\nFunction:\t%2\nLine:\t%3\n\nbool prepareMeasurement(void) returned false.").
                       arg(__FILE__, __FUNCTION__, QString::number(__LINE__-3)));
    }

    /* Calibration aborted or failure occurred? */
    if (!(status & PROCESS_RUNNING) || (status & PROCESS_FAILURE))
        return;

    /* Save dark spectrum for reflectance standard */
    ptrSpectrometers[idRd]->setDarkSpectrum();

    /* Save data to file */
    ptrSpectrometers[idRd]->saveData("measure/Rd_std_dark.txt");

    /* Update progress bar */
    ui->progressBar->setValue(100);

    /* Enable 'Next' button */
    ui->button_next->setEnabled(true);

    /* Calibration successful */
    status |= PROCESS_DONE | PROCESS_SUCCESS;
    status &= ~PROCESS_RUNNING;

    /* Wait for user pressing 'Next' button */
    while (!(status & PROCESS_CLOSED))
    {
        /* Handle events and update UI */
        Application::processEvents();

        /* Wait 1 ms */
        Timer::msleep(1);
    }
}

/**
 * @brief Returns status of calibration
 * @return Status bits
 */
unsigned char CalibrateIADPage02::getStatus(void)
{
    /* Return status bits */
    return status;
}

/**
 * @brief Get counts with reflection standard
 * @param id Spectrometer index
 * @return Counts
 */
double *CalibrateIADPage02::getCounts(void)
{
    return diffuseReflection_counts;
}

/**
 * @brief Quits the assistant
 */
void CalibrateIADPage02::abort(void)
{
    /* Disable all buttons */
    ui->button_next->setEnabled(false);
    ui->button_abort->setEnabled(false);

    /* Handle events and update UI */
    Application::processEvents();

    unsigned int i = 0;

    /* Loop through devices */
    for (i = 0; i < m_NrDevices; i++)
    {
        /* Spectrometer is measuring? */
        if (ptrSpectrometers[i]->isMeasuring())
        {
            /* Stop measurement on current device */
            ptrSpectrometers[i]->stopMeasurement();
        }
    }

    /* Calibration failed */
    status |= PROCESS_DONE | PROCESS_CLOSED | PROCESS_FAILURE;
    status &= ~PROCESS_RUNNING;
}

/**
 * @brief Continues the assistant
 */
void CalibrateIADPage02::next(void)
{
    /* Calibration done? */
    if (status & PROCESS_DONE)
    {
        /* Go to next calibration step */
        status |= PROCESS_CLOSED;
    }
    else
    {
        /* User pressed 'Begin' button? */
        if (status & PROCESS_READY)
        {
            /* Start calibration process */
            status |= PROCESS_RUNNING;

            /* Disable button and change text */
            ui->button_next->setText(QString("Next"));
            ui->button_next->setEnabled(false);

            /* Enable 'Abort' button */
            ui->button_abort->setEnabled(true);

            /* Handle events and update UI */
            Application::processEvents();
        }
    }
}

/**
 * @brief Destructor of 'CalibrateIADPage02' class
 */
CalibrateIADPage02::~CalibrateIADPage02(void)
{
    /* Check if memory allocated */
    if (nullptr != diffuseReflection_counts)
    {
        /* Free memory */
        delete[] diffuseReflection_counts;
        diffuseReflection_counts = nullptr;
    }

    /* Delete user interface */
    delete ui;
}
