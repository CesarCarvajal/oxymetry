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

/* Internal includes */
#include "application.h"
#include "messages.h"
#include "spectrometer.h"
#include "spectrometer_config.h"
#include "ui_spectrometer_config.h"

/*
 * Global variables
 */
extern Spectrometer** ptrSpectrometers;
extern unsigned int m_NrDevices;

/**
 * @brief Constructor of 'SpectrometerConfig' class
 * @param[in] parent Parent widget
 */
SpectrometerConfig::SpectrometerConfig(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SpectrometerConfig)
{
    /* Set up user interface */
    ui->setupUi(this);

    /* Set window flags */
    this->setWindowFlags(Qt::Dialog | Qt::WindowTitleHint | Qt::WindowStaysOnTopHint | Qt::WindowCloseButtonHint);

    /* Disable resize of elements */
    this->setFixedSize(this->size());

    /* Connect button signal handles */
    connect(ui->button_cancel, SIGNAL(clicked(bool)), this, SLOT(cancel()));
    connect(ui->button_apply, SIGNAL(clicked(bool)), this, SLOT(apply()));

    /* Handle value updates */
    connect(ui->startPixel, SIGNAL(valueChanged(int)), this, SLOT(updateValues()));
    connect(ui->stopPixel, SIGNAL(valueChanged(int)), this, SLOT(updateValues()));
    connect(ui->integrationTime, SIGNAL(valueChanged(double)), this, SLOT(updateValues()));
    connect(ui->integrationDelay, SIGNAL(valueChanged(double)), this, SLOT(updateValues()));
    connect(ui->checkBox_dynamicDarkCorrection, SIGNAL(stateChanged(int)), this, SLOT(updateValues()));
    connect(ui->forgetPercentage, SIGNAL(valueChanged(int)), this, SLOT(updateValues()));
    connect(ui->checkBox_highResADC, SIGNAL(stateChanged(int)), this, SLOT(updateValues()));
}

/**
 * @brief Assign spectrometer to dialog
 * @param[in] id Spectrometer ID
 */
void SpectrometerConfig::assignSpectrometer(unsigned int id)
{
    /* Remember device ID */
    deviceId = id;

    /* Get values from spectrometer and set dialog values */
    ui->startPixel->setMaximum(ptrSpectrometers[id]->getNumberOfPixels() - 1);
    ui->startPixel->setValue(ptrSpectrometers[id]->getStartPixel());
    ui->stopPixel->setMaximum(ptrSpectrometers[id]->getNumberOfPixels() - 1);
    ui->stopPixel->setValue(ptrSpectrometers[id]->getStopPixel());
    ui->integrationTime->setValue(ptrSpectrometers[id]->getIntegrationTime());
    ui->integrationDelay->setValue(ptrSpectrometers[id]->getIntegrationDelay());
    ui->numberOfAverages->setValue(ptrSpectrometers[id]->getNumberOfAverages());
    ui->checkBox_dynamicDarkCorrection->setChecked(ptrSpectrometers[id]->getDynamicDarkCorrection());
    ui->forgetPercentage->setValue(ptrSpectrometers[id]->getForgetPercentage());
    ui->checkBox_highResADC->setChecked(ptrSpectrometers[id]->getUseHighResADC());

    /* Update calculated values */
    updateValues();

    /* No changes have been made, block the 'apply' button */
    ui->button_apply->setEnabled(false);
}

/**
 * @brief Applies spectrometer parameters
 */
void SpectrometerConfig::apply(void)
{
    bool bNoErrors = true;

    /* Start pixel has always to be greater than stop pixel */
    if (ui->startPixel->value() >= ui->stopPixel->value())
    {
        /* Show message */
        showWarning("Start pixel must be smaller than stop pixel. Please adjust your settings.", "");

        /* Error occurred */
        bNoErrors = false;
    }

    /* No errors occurred? */
    if (bNoErrors)
    {
        /* Get values from spectrometer and set dialog values */
        ptrSpectrometers[deviceId]->setStartPixel(ui->startPixel->value());
        ptrSpectrometers[deviceId]->setStopPixel(ui->stopPixel->value());
        ptrSpectrometers[deviceId]->setIntegrationTime(ui->integrationTime->value());
        ptrSpectrometers[deviceId]->setIntegrationDelay(ui->integrationDelay->value());
        ptrSpectrometers[deviceId]->setNumberOfAverages(ui->numberOfAverages->value());
        ptrSpectrometers[deviceId]->setDynamicDarkCorrection(ui->checkBox_dynamicDarkCorrection->isChecked());
        ptrSpectrometers[deviceId]->setForgetPercentage(ui->forgetPercentage->value());
        ptrSpectrometers[deviceId]->setUseHighResADC(ui->checkBox_highResADC->isChecked());

        /* Disable 'apply' button to signal changes */
        ui->button_apply->setEnabled(false);
    }
}

/**
 * @brief Update calculated values
 */
void SpectrometerConfig::updateValues(void)
{
    /* Get wavelength vector */
    double *lambda = ptrSpectrometers[deviceId]->getWavelengths();

    /* Calculate wavelength of start and stop pixels */
    ui->label_lambdaStart->setText(QString("%1 nm").arg(QString::number(lambda[ui->startPixel->value()], 'f', 2)));
    ui->label_lambdaStop->setText(QString("%1 nm").arg(QString::number(lambda[ui->stopPixel->value()], 'f', 2)));

    /* Changes have been made, allow user to press 'apply' button */
    ui->button_apply->setEnabled(true);
}

/**
 * @brief Cancels spectrometer parameters
 */
void SpectrometerConfig::cancel(void)
{
    /* Reject changes */
    reject();
}

/**
 * @brief Destructor of 'SpectrometerConfig' class
 */
SpectrometerConfig::~SpectrometerConfig(void)
{
    /* Delete user interface */
    delete ui;
}
