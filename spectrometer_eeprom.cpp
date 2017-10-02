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
#include "spectrometer_eeprom.h"
#include "ui_spectrometer_eeprom.h"

/**
 * @brief Constructor of 'SpectrometerEEPROM' class
 * @param parent
 */
SpectrometerEEPROM::SpectrometerEEPROM(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SpectrometerEEPROM)
{
    /* Set up user interface */
    ui->setupUi(this);

    /* Set window flags */
    this->setWindowFlags(Qt::Dialog | Qt::WindowTitleHint | Qt::WindowStaysOnTopHint | Qt::WindowCloseButtonHint);

    /* Disable resize of elements */
    this->setFixedSize(this->size());

    /* Connect button signal handles */
    connect(ui->button_close, SIGNAL(clicked(bool)), this, SLOT(close()));
    connect(ui->button_read, SIGNAL(clicked(bool)), this, SLOT(readEEPROM()));
    connect(ui->button_write, SIGNAL(clicked(bool)), this, SLOT(writeEEPROM()));
    connect(ui->button_backupCreate, SIGNAL(clicked(bool)), this, SLOT(createBackup()));
    connect(ui->button_backupRestore, SIGNAL(clicked(bool)), this, SLOT(restoreBackup()));
}

/**
 * @brief Closes EEPROM dialog
 */
void SpectrometerEEPROM::close(void)
{
    /* Reject changes */
    reject();
}

/**
 * @brief Reads spectrometer EEPROM
 */
void SpectrometerEEPROM::readEEPROM(void)
{
    /* Accept changes */
    accept();
}

/**
 * @brief Writes spectrometer EEPROM
 */
void SpectrometerEEPROM::writeEEPROM(void)
{
    /* Accept changes */
    accept();
}

/**
 * @brief Creates backup from EEPROM on disk
 */
void SpectrometerEEPROM::createBackup(void)
{
    /* Accept changes */
    accept();
}

/**
 * @brief Restores backup from EEPROM from disk
 */
void SpectrometerEEPROM::restoreBackup(void)
{
    /* Accept changes */
    accept();
}

/**
 * @brief Destructor of 'SpectrometerEEPROM' class
 */
SpectrometerEEPROM::~SpectrometerEEPROM(void)
{
    /* Delete user interface */
    delete ui;
}
