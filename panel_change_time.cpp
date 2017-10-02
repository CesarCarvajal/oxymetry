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
#include <QDialog>
#include <QString>
#include <QTimer>

/* Internal includes */
#include "panel_change_time.h"
#include "ui_panel_change_time.h"

/**
 * @brief Constructor of 'PanelChangeTime' class
 * @param parent
 */
PanelChangeTime::PanelChangeTime(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PanelChangeTime)
{
    /* Set up user interface */
    ui->setupUi(this);

    /* Disable resize of elements */
    this->setFixedSize(this->size());

    /* Set window flags */
    this->setWindowFlags(Qt::Tool | Qt::WindowStaysOnTopHint);

    /* Get keyboard focus */
    QTimer::singleShot(0, this, SLOT(activateWindow()));

    /* Connect button signal handles */
    connect(ui->button_apply, SIGNAL(clicked(bool)), this, SLOT(applyButton()));
}

/**
 * @brief Get integration time
 * @return value Integration time in milliseconds
 */
float PanelChangeTime::getValue(void)
{
    float value = ui->spinbox_timeValue->value();

    /* Check if time base is set to microseconds */
    if (!QString::compare(ui->combobox_timeBase->currentText(), QString("µs")))
    {
        /* Convert from µs to ms */
        value /= 1000.0f;
    }
    /* Check if time base is set to seconds */
    else if (!QString::compare(ui->combobox_timeBase->currentText(), QString("s")))
    {
        /* Convert from s to ms */
        value *= 1000.0f;
    }

    /* Return integration time in milliseconds */
    return value;
}

/**
 * @brief Set integration time
 * @param[in] value Integration time in milliseconds
 */
void PanelChangeTime::setValue(float value)
{
    /* Is our integration time less than one millisecond? */
    if (value <= 1.0f)
    {
        /* Update time base to µs */
        ui->spinbox_timeValue->setValue(value * 1000.0f);
        ui->combobox_timeBase->setCurrentText(QString("µs"));
    }
    /* Is our integration time greater than one second? */
    else if (value >= 1000.0f)
    {
        /* Update time base to s */
        ui->spinbox_timeValue->setValue(value / 1000.0f);
        ui->combobox_timeBase->setCurrentText(QString("s"));
    }
    else
    {
        /* Time base will be set to ms */
        ui->spinbox_timeValue->setValue(value);
        ui->combobox_timeBase->setCurrentText(QString("ms"));
    }
}

/**
 * @brief User pressed 'apply' button
 */
void PanelChangeTime::applyButton(void)
{
    /* All fine */
    accept();
}

/**
 * @brief Destructor of 'PanelChangeTime' class
 */
PanelChangeTime::~PanelChangeTime(void)
{
    /* Delete user interface */
    delete ui;
}
