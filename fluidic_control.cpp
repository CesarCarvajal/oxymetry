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
#include <QString>
#include <QCloseEvent>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QBitArray>

/* Qwt library */
#include "qwt_plot_curve.h"

/* Internal includes */
#include "messages.h"
#include "fluidic_connect.h"
#include "fluidic_control.h"
#include "ui_fluidic_control.h"

/* Global variables */
extern QSerialPort serial;

/**
 * @brief Constructor of 'ControlFluidic' class
 * @param parent
 */
ControlFluidic::ControlFluidic(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ControlFluidic)
{
    /* Set up user interface */
    ui->setupUi(this);

    /* Disable resize of elements */
    this->setFixedSize(this->size());

    /* Adjust window geometry and set window flags */
    this->setGeometry(20, 50, this->width(), this->height());
    this->setWindowFlags(Qt::Tool | Qt::WindowStaysOnTopHint);

    unsigned char i = 0;

    for (i = 0; i < 8; i++)
    {
        checkBox_valve[i] = new QCheckBox(ui->tab_2);
        checkBox_valve[i]->setGeometry(10 + 20 * i, 31, 16, 21);
        checkBox_valve[i]->show();
    }

    /* Connect functions to buttons */
    connect(ui->pushButton_connect, SIGNAL(clicked()), this, SLOT(connectCOM()));
    connect(ui->pushButton_apply, SIGNAL(clicked(bool)), this, SLOT(apply()));
    connect(&serial, SIGNAL(readyRead()), this, SLOT(readData()));

    /* Set axis and title of preview plot */
    ui->qwtPlot_stats->setXAxisTitle("time in s");
    ui->qwtPlot_stats->setXAxis(0.0, 60.0);
    ui->qwtPlot_stats->setYAxis(0.0, 60.0);
    ui->qwtPlot_stats->enableAxis(QwtPlot::yLeft, false);
    ui->qwtPlot_stats->hideGrid();
    ui->qwtPlot_stats->disableZoom();

    /* Add curve for voltage */
    rpm = new QwtPlotCurve("RPM");
    rpm->setPen(QPen("blue"));
    rpm->attach(ui->qwtPlot_stats);

    /* Remember: Is not connected */
    isConnected = false;

    /* Update GUI elements */
    ui->label_status->setText("Not connected");
    ui->label_status->setStyleSheet("color: red;");
}

/**
 * @brief Close event of 'ControlFluidic' class
 * @param event
 */
void ControlFluidic::closeEvent(QCloseEvent *event) {
    Q_UNUSED(event);

    /* Serial connection established? */
    if (serial.isOpen())
    {
        /* Close connection */
        serial.close();
    }
}

/**
 * @brief Button 'connect' clicked
 */
void ControlFluidic::connectCOM(void)
{
    /* Disable button */
    ui->pushButton_connect->setEnabled(false);

    /* Check if already connected */
    if (!isConnected)
    {
        ConnectFluidic setup;

        /* Execute connection dialog */
        if (QDialog::Accepted == setup.exec())
        {
            /* Successfully connected! Change button text from 'Connect' to 'Disconnect' */
            ui->pushButton_connect->setText("Disconnect");
            ui->pushButton_apply->setEnabled(true);

            /* Apply settings */
            apply();

            /* Remember: Is connected */
            isConnected = true;
        }
    }
    else
    {
        /* Close connection */
        serial.close();

        /* Connection failed! Set button text to 'Connect' */
        ui->pushButton_connect->setText("Connect");
        ui->pushButton_apply->setEnabled(false);

        /* Remember: Is not connected */
        isConnected = false;
    }

    /* Update GUI elements */
    ui->label_status->setText(isConnected ? QString("Connected") : QString("Not connected"));
    ui->label_status->setStyleSheet(isConnected ? "color: green;" : "color: red;");

    /* Enable button */
    ui->pushButton_connect->setEnabled(true);
}

/**
 * @brief Button 'apply' clicked
 */
void ControlFluidic::apply(void)
{
    QBitArray bits(32, false);

    unsigned char i = 0;

    /* Set bits for valves */
    for (i = 0; i < 8; i++)
    {
        bits.setBit(i, checkBox_valve[7 - i]->isChecked());
    }

    /* Set bits for speed */
    for (i = 0; i < 12; i++)
    {
        bits.setBit(19 - i, ui->horizontalSlider_speed->value() & (int)pow(2, i));
    }

    /* Set bit for direction */
    bits.setBit(22, ui->checkBox_direction->isChecked());

    /* Set bit for brake */
    bits.setBit(23, ui->checkBox_brake->isChecked());

    QByteArray bytes(4, 0);

    /* Convert from QBitArray to QByteArray */
    for (i = 0; i < 4; i++)
    {
        unsigned char j = 0;

        for (j = 0; j < 8; j++)
        {
            bytes[i] = bytes.at(i) | ((bits[i * 8 + j] ? 1:0) << (7 - j));
        }
    }

    /* Serial connection established? */
    if (serial.isOpen())
    {
        /* Output bytes */
        serial.write(bytes);
    }
}

/**
 * @brief Called if new data arrived at serial port
 */
void ControlFluidic::readData(void)
{
    QByteArray data = serial.readAll();

    /* We've got 2 bytes! */
    if (data.length() >= 2)
    {
        /* Only continue if light source is connected */
        if (!isConnected) { return; }

        /* End of buffer reached? */
        if (valueIndex > UPDATE_RATE * MAX_TIME_FRAME - 1)
        {
            unsigned int i = 0;

            /* Loop through buffer elements */
            for (i = 1; i < UPDATE_RATE * MAX_TIME_FRAME; i++)
            {
                rpm_values[i - 1] = rpm_values[i];
            }

            /* Decrease buffer pointer */
            valueIndex--;
        }

        /* Get voltage and current */
        rpm_values[valueIndex] = (double)((unsigned char)data[1] | ((unsigned char)data[0] << 8)) * 0.011 * UPDATE_RATE;
        time_values[valueIndex] = (double)valueIndex / UPDATE_RATE;

        /* Update graph values */
        rpm->setSamples(time_values, rpm_values, valueIndex);

        double mean_rpm = 0.0;

        unsigned char i = 0;

        /* Calculate mean RPM over a period of one second */
        for (i = 0; i < ((valueIndex >= UPDATE_RATE) ? UPDATE_RATE : valueIndex); i++)
        {
            mean_rpm += rpm_values[valueIndex + i];
        }

        /* Show RPM to user */
        ui->label_rpm->setText(QString::number(mean_rpm, 'f', 1) + " RPM");

        /* End of buffer not reached yet? */
        if (valueIndex < UPDATE_RATE * MAX_TIME_FRAME)
        {
            /* Increase buffer pointer */
            valueIndex++;
        }

        /* Update graph */
        ui->qwtPlot_stats->replot();

        /* Remove 2 bytes from buffer */
        data.remove(0, 2);
    }
}

/**
 * @brief Destructor of 'ControlFluidic' class
 */
ControlFluidic::~ControlFluidic(void)
{
    /* Serial connection established? */
    if (serial.isOpen())
    {
        /* Close connection */
        serial.close();
    }

    /* Delete user interface */
    delete ui;
}
