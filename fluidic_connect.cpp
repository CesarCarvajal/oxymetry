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
#include <QList>
#include <QSerialPort>
#include <QSerialPortInfo>

/* Internal includes */
#include "messages.h"
#include "fluidic_connect.h"
#include "ui_fluidic_connect.h"

/* Global variables */
QSerialPort serial;

/**
 * @brief Constructor 'ConnectFluidic' class
 * @param parent
 */
ConnectFluidic::ConnectFluidic(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConnectFluidic)
{
    /* Set up user interface */
    ui->setupUi(this);

    /* Disable resize of elements */
    this->setFixedSize(this->size());

    /* Set window flags */
    this->setWindowFlags(Qt::Tool | Qt::WindowStaysOnTopHint);

    /* Fill combobox baudrate */
    ui->comboBox_baudrate->addItem(QStringLiteral("9600"), QSerialPort::Baud9600);
    ui->comboBox_baudrate->addItem(QStringLiteral("19200"), QSerialPort::Baud19200);
    ui->comboBox_baudrate->addItem(QStringLiteral("38400"), QSerialPort::Baud38400);
    ui->comboBox_baudrate->addItem(QStringLiteral("57600"), QSerialPort::Baud57600);
    ui->comboBox_baudrate->addItem(QStringLiteral("115200"), QSerialPort::Baud115200);
    ui->comboBox_baudrate->setCurrentIndex(3);

    /* Fill combobox databits */
    ui->comboBox_dataBits->addItem(QStringLiteral("5"), QSerialPort::Data5);
    ui->comboBox_dataBits->addItem(QStringLiteral("6"), QSerialPort::Data6);
    ui->comboBox_dataBits->addItem(QStringLiteral("7"), QSerialPort::Data7);
    ui->comboBox_dataBits->addItem(QStringLiteral("8"), QSerialPort::Data8);
    ui->comboBox_dataBits->setCurrentIndex(3);

    /* Fill combobox parity */
    ui->comboBox_parity->addItem(tr("None"), QSerialPort::NoParity);
    ui->comboBox_parity->addItem(tr("Even"), QSerialPort::EvenParity);
    ui->comboBox_parity->addItem(tr("Odd"), QSerialPort::OddParity);
    ui->comboBox_parity->addItem(tr("Mark"), QSerialPort::MarkParity);
    ui->comboBox_parity->addItem(tr("Space"), QSerialPort::SpaceParity);

    /* Fill combobox stopbits */
    ui->comboBox_stopBits->addItem(QStringLiteral("1"), QSerialPort::OneStop);
#ifdef Q_OS_WIN
    ui->comboBox_stopBits->addItem(tr("1.5"), QSerialPort::OneAndHalfStop);
#endif
    ui->comboBox_stopBits->addItem(QStringLiteral("2"), QSerialPort::TwoStop);

    /* Fill combobox flow control */
    ui->comboBox_flowControl->addItem(tr("None"), QSerialPort::NoFlowControl);
    ui->comboBox_flowControl->addItem(tr("RTS/CTS"), QSerialPort::HardwareControl);
    ui->comboBox_flowControl->addItem(tr("XON/XOFF"), QSerialPort::SoftwareControl);

    /* Clear serial port list */
    ui->comboBox_port->clear();

    /* Connect buttons */
    connect(ui->pushButton_connect, SIGNAL(clicked(bool)), this, SLOT(apply()));
    connect(ui->pushButton_cancel, SIGNAL(clicked(bool)), this, SLOT(cancel()));
    connect(ui->pushButton_update, SIGNAL(clicked(bool)), this, SLOT(refresh()));

    /* Get list of available ports */
    ports = QSerialPortInfo::availablePorts();

    /* Loop through serial ports (COMxx) */
    foreach (const QSerialPortInfo &info, ports)
    {
        /* Add current port name to combo box */
        ui->comboBox_port->addItem(info.portName());
    }

    /* Loop through serial ports (COMxx) */
    foreach (const QSerialPortInfo &info, ports)
    {
        /* Check if we have the fluidic circuit connected */
        if ((TEENSY_VENDOR_ID == info.vendorIdentifier()) &&
            (TEENSY_DEVICE_ID == info.productIdentifier()))
        {
            /* Select identified port */
            ui->comboBox_port->setCurrentIndex(ui->comboBox_port->findText(info.portName()));

            /* Configure serial connection */
            serial.setPortName(info.portName());
            serial.setBaudRate(QSerialPort::Baud57600);
            serial.setDataBits(QSerialPort::Data8);
            serial.setParity(QSerialPort::NoParity);
            serial.setStopBits(QSerialPort::OneStop);
            serial.setFlowControl(QSerialPort::NoFlowControl);

            /* Try to establish serial connection */
            if (serial.open(QIODevice::ReadWrite))
            {
                /* Was successful; close dialog again */
                QMetaObject::invokeMethod(this, "accept", Qt::QueuedConnection);
            }
        }
    }
}

/**
 * @brief Button 'apply' clicked
 */
void ConnectFluidic::apply(void)
{
    /* Did the user select a COM port? */
    if (ui->comboBox_port->currentText().length() <= 0)
    {
        /* Show warning */
        showWarning(QString("No COM port selected!"), QString(""));
        return;
    }

    /* Configure serial connection */
    serial.setPortName(ui->comboBox_port->currentText());
    serial.setBaudRate(ui->comboBox_baudrate->currentData().toInt());
    serial.setDataBits((QSerialPort::DataBits)ui->comboBox_dataBits->currentData().toInt());
    serial.setParity((QSerialPort::Parity)ui->comboBox_parity->currentData().toInt());
    serial.setStopBits((QSerialPort::StopBits)ui->comboBox_stopBits->currentData().toInt());
    serial.setFlowControl((QSerialPort::FlowControl)ui->comboBox_flowControl->currentData().toInt());

    /* Try to establish serial connection */
    if (!serial.open(QIODevice::ReadWrite))
    {
        /* Show critical */
        showCritical(QString("Unable to open COM port %s with %i baudrate!").arg(ui->comboBox_port->currentText(), ui->comboBox_baudrate->currentData().toInt()), QString(""));
        reject();
    }
    else
    {
        /* All fine */
        accept();
    }
}

/**
 * @brief Button 'cancel' clicked
 */
void ConnectFluidic::cancel(void)
{
    reject();
}

/**
 * @brief Button 'refresh' clicked
 */
void ConnectFluidic::refresh(void)
{
    /* Clear serial port list */
    ui->comboBox_port->clear();

    /* Get list of available ports */
    ports = QSerialPortInfo::availablePorts();

    /* Loop through serial ports (COMxx) */
    foreach (const QSerialPortInfo &info, ports)
    {
        /* Add current port name to combo box */
        ui->comboBox_port->addItem(info.portName());
    }

    /* Loop through serial ports (COMxx) */
    foreach (const QSerialPortInfo &info, ports)
    {
        /* Check if we have the fluidic circuit connected */
        if ((TEENSY_VENDOR_ID == info.vendorIdentifier()) &&
            (TEENSY_DEVICE_ID == info.productIdentifier()))
        {
            /* Select identified port */
            ui->comboBox_port->setCurrentIndex(ui->comboBox_port->findText(info.portName()));
        }
    }
}

/**
 * @brief Destructor of 'ConnectFluidic' class
 */
ConnectFluidic::~ConnectFluidic(void)
{
    /* Delete user interface */
    delete ui;
}
