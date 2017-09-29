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

#ifndef FLUIDIC_CONTROL_H
#define FLUIDIC_CONTROL_H

/* External includes */
#include <QMainWindow>
#include <QWidget>
#include <QCloseEvent>
#include <QCheckBox>

/* Qwt library */
#include "qwt_plot_curve.h"

namespace Ui {
    class ControlFluidic;
}

/* Update rate of µC in Hz */
#define UPDATE_RATE 10

/* Maximum observeable time frame */
#define MAX_TIME_FRAME 60

/**
 * @brief The 'ControlFluidic' class
 */
class ControlFluidic : public QMainWindow
{
    Q_OBJECT

public:
    /* Constructor */
    explicit ControlFluidic(QWidget *parent = 0);

    /* Destructor */
    ~ControlFluidic(void);

protected:
    /* Event when window is closed */
    void closeEvent(QCloseEvent *event);

private slots:
    /* Button 'connect' clicked */
    void connectCOM(void);

    /* Button 'apply' clicked */
    void apply(void);

    /* Serial data available */
    void readData(void);

private:
    Ui::ControlFluidic *ui;

    QCheckBox *checkBox_valve[8];

    /* User connected to fluidic circuit */
    bool isConnected = false;

    QwtPlotCurve *rpm = nullptr;

    double time_values[UPDATE_RATE * MAX_TIME_FRAME] = { 0.0 };
    double rpm_values[UPDATE_RATE * MAX_TIME_FRAME] = { 0.0 };
    unsigned int valueIndex = 0;
};

#endif // FLUIDIC_CONTROL_H
