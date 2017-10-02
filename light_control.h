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

#ifndef LIGHT_CONTROL_H
#define LIGHT_CONTROL_H

/* External includes */
#include <QMainWindow>
#include <QWidget>
#include <QString>
#include <QCloseEvent>
#include <QTimer>

/* libUSB library */
#include "libusb.h"

/* Qwt library */
#include "qwt_plot_curve.h"

namespace Ui {
    class ControlLight;
}

struct bulbStatus {
    bool isOn;
    bool isError;
    bool isEEPROMError;
    bool isStdMode;
    bool isWarmedUp;
    bool isLT90;
    bool isLT100;
    bool isHeaterActive;
};

#define LENGTH_MEMORY 60

/**
 * @brief The 'ControlLight' class
 */
class ControlLight : public QMainWindow
{
    Q_OBJECT

public:
    /* Constructor */
    explicit ControlLight(QWidget *parent = 0);

    /* Connect or disconnect light source via USB */
    bool connectUSB(void);
    void disconnectUSB(void);

    /* Connection established? */
    bool getIsConnected(void);

    /* Get device name */
    QString getDeviceName(void);

    /* Get device description */
    QString getDeviceDesc(void);

    /* Get manufacturing date */
    QString getManufacturingDate(void);

    /* Get serial number */
    QString getSerialNumber(void);

    /* Get firmware version */
    QString getFirmwareVersion(void);

    float getBulbOnTime(void);
    float getBulbWarmupTime(void);
    float getBulbCurrent(void);
    float getBulbVoltage(void);

    /* Destructor */
    ~ControlLight(void);

public slots:
    /* Open/close shutter */
    void openShutter(void);
    void closeShutter(void);

    /* Turn bulb on/off */
    void turnBulbOn(void);
    void turnBulbOff(void);

    /* Enable/disable high power */
    void enableHighPower(void);
    void disableHighPower(void);

protected:
    /* Event when window is closed */
    void closeEvent(QCloseEvent *event);

private slots:
    /* Button 'connect' clicked */
    void connectButton(void);

    /* Update data (e.g. bulb voltage and current) */
    void updateData(void);

private:
    Ui::ControlLight *ui;

    /* Get or set shutter status */
    bool getShutterStatus(void);
    bool setShutterStatus(bool value);

    /* Set or get bulb status */
    bool setBulbStatus(bool value);
    bulbStatus getBulbStatus(void);

    /* Set or get bulb power mode */
    bool setBulbPowerMode(bool mode);
    bool getBulbPowerMode(void);

    /* Send opcode to light source and get answer */
    QString sendOpcode(const char opcode[]);

    /* User connected to light source */
    bool isConnected = false;

    /* Handles and structures for libUSB */
    libusb_device *dev = nullptr;
    libusb_device_handle *handle = nullptr;
    unsigned char busNumber, devAddress;
    struct libusb_config_descriptor *config;
    const struct libusb_interface *interface;
    const struct libusb_endpoint_descriptor *endpoint[2];

    QTimer *timer = nullptr;

    QwtPlotCurve *voltage = nullptr;
    QwtPlotCurve *current = nullptr;

    double time_values[LENGTH_MEMORY] = { 0 };
    double voltage_values[LENGTH_MEMORY] = { 0 };
    double current_values[LENGTH_MEMORY] = { 0 };
    unsigned int valueIndex = 0;
};

#endif // LIGHT_CONTROL_H
