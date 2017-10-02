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
#include "iad_calibrate_page01.h"
#include "ui_iad_calibrate_page01.h"

/*
 * Global variables
 */
extern Spectrometer** ptrSpectrometers;
extern unsigned int m_NrDevices;
extern ControlLight* lightSource;

/**
 * @brief Constructor of 'CalibrateIADPage01' class
 */
CalibrateIADPage01::CalibrateIADPage01(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CalibrateIADPage01)
{
    /* Set up user interface */
    ui->setupUi(this);

    /* Set window flags */
    this->setWindowFlags(Qt::Dialog | Qt::WindowTitleHint | Qt::WindowStaysOnTopHint);

    /* Disable resize of elements */
    this->setFixedSize(this->size());

    /* Call destructor on close event */
    this->setAttribute(Qt::WA_DeleteOnClose);

    QLabel *label1 = new QLabel(this);

    /* Set up label for upper limit */
    label1->setGeometry(290 - 20 - 50, 310 - (THRESHOLD_COUNTS_HIGH * 160 / 65535), 50, 20);
    label1->setText(QString("Maximum"));
    label1->setAlignment(Qt::AlignRight);
    label1->show();

    QLabel *label2 = new QLabel(this);

    /* Set up label for lower limit */
    label2->setGeometry(290 - 20 - 50, 310 - (THRESHOLD_COUNTS_LOW * 160 / 65535), 50, 20);
    label2->setText(QString("Minimum"));
    label2->setAlignment(Qt::AlignRight);
    label2->show();

    /* Calibration step ready */
    status = PROCESS_READY;

    /* Connect button signal handles */
    connect(ui->button_abort, SIGNAL(clicked(bool)), this, SLOT(abort()));
    connect(ui->button_next, SIGNAL(clicked(bool)), this, SLOT(next()));
}

/**
 * @brief Adjusts the pinhole for unscattered transmission measurement
 *
 * @param[in] idTu Index of spectrometer for unscattered transmission
 */
void CalibrateIADPage01::process(unsigned int idTu)
{
    /* Calibration step running */
    status = PROCESS_RUNNING;

    /* Set integration time, number of averages and disable dynamic dark correction*/
    ptrSpectrometers[idTu]->setIntegrationTime(CALIBRATION_TU_START_INTEGRATION_TIME);
    ptrSpectrometers[idTu]->setNumberOfAverages(CALIBRATION_TU_START_NUM_AVERAGES);
    ptrSpectrometers[idTu]->setForgetPercentage(100);
    ptrSpectrometers[idTu]->setDynamicDarkCorrection(true);

    /* Open light source shutter */
    lightSource->openShutter();

    /* Wait 500 ms */
    Timer::msleep(500);

    /* Successfully prepared measurement? */
    if (ptrSpectrometers[idTu]->prepareMeasurement())
    {
        /* Start indefinite number of measurements */
        if (ptrSpectrometers[idTu]->startMeasurement(-1))
        {
            unsigned int i = 0;

            do
            {
                /* 10 Hz update rate for UI */
                if (!(i % 100))
                {
                    /* Get maximum counts from last spectrum */
                    double tempTu = ptrSpectrometers[idTu]->getMaxCounts();

                    /* Counts have to be between THRESHOLD_COUNTS_LOW and THRESHOLD_COUNTS_HIGH */
                    if ((tempTu >= THRESHOLD_COUNTS_LOW) && (tempTu <= THRESHOLD_COUNTS_HIGH))
                    {
                        /* Enable 'next' button */
                        ui->button_next->setEnabled(true);
                    }
                    else
                    {
                        /* Disable 'next' button */
                        ui->button_next->setEnabled(false);
                    }

                    /* Show counts */
                    ui->progressBar_unscatteredTransmission->setValue((int)tempTu);
                }

                /* Handle events and update UI */
                Application::processEvents();

                /* Increase counter every loop iteration */
                i++;

                /* Wait 1 ms */
                Timer::msleep(1);
            } while (!(status & PROCESS_DONE));

            /* Stop measurement */
            ptrSpectrometers[idTu]->stopMeasurement();
        }
        else
        {
            /* Calibration failed */
            status |= PROCESS_FAILURE;

            /* Create message box */
            showCritical(QString("Unable to start the measurement of unscattered transmission on spectrometer %1. Calibration aborted.").
                           arg(ptrSpectrometers[idTu]->getSerialNumber()),
                         QString("File:\t%1\nFunction:\t%2\nLine:\t%3\n\nbool startMeasurement(short numMeasurements) returned false.").
                           arg(__FILE__, __FUNCTION__, QString::number(__LINE__-3)));
        }
    }
    else
    {
        /* Calibration failed */
        status |= PROCESS_FAILURE;

        /* Create message box */
        showCritical(QString("Unable to prepare the measurement of unscattered transmission on spectrometer %1. Calibration aborted.").
                       arg(ptrSpectrometers[idTu]->getSerialNumber()),
                     QString("File:\t%1\nFunction:\t%2\nLine:\t%3\n\nbool prepareMeasurement(void) returned false.").
                       arg(__FILE__, __FUNCTION__, QString::number(__LINE__-3)));
    }

    /* Go to next calibration step */
    status |= PROCESS_CLOSED;
}

/**
 * @brief Returns status of calibration
 * @return Status bits
 */
unsigned char CalibrateIADPage01::getStatus(void)
{
    /* Return status bits */
    return status;
}

/**
 * @brief Quits the assistant
 */
void CalibrateIADPage01::abort(void)
{
    /* Disable all buttons */
    ui->button_next->setEnabled(false);
    ui->button_abort->setEnabled(false);

    /* Handle events and update UI */
    Application::processEvents();

    /* End calibration; aborted */
    status |= PROCESS_DONE | PROCESS_FAILURE;
}

/**
 * @brief Continues the assistant
 */
void CalibrateIADPage01::next(void)
{
    /* Disable all buttons */
    ui->button_next->setEnabled(false);
    ui->button_abort->setEnabled(false);

    /* Handle events and update UI */
    Application::processEvents();

    /* End calibration; successful */
    status |= PROCESS_DONE | PROCESS_SUCCESS;
}

/**
 * @brief Destructor of 'CalibrateIADPage01' class
 */
CalibrateIADPage01::~CalibrateIADPage01(void)
{
    /* Delete user interface */
    delete ui;
}
