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
#include "panel_change_averages.h"
#include "ui_panel_change_averages.h"

/**
 * @brief Constructor of 'PanelChangeAverages' class
 * @param parent
 */
PanelChangeAverages::PanelChangeAverages(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PanelChangeAverages)
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
 * @brief Get number of averages
 * @return Number of averages
 */
int PanelChangeAverages::getValue(void)
{
    return ui->spinbox_value->value();
}

/**
 * @brief Set number of averages
 * @param[in] value Number of averages
 */
void PanelChangeAverages::setValue(int value)
{
    ui->spinbox_value->setValue(value);
}

/**
 * @brief Accepts changed value
 */
void PanelChangeAverages::applyButton(void)
{
    /* All fine */
    accept();
}

/**
 * @brief Destructor of 'PanelChange' class
 */
PanelChangeAverages::~PanelChangeAverages(void)
{
    /* Delete user interface */
    delete ui;
}
