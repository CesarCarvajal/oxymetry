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
#include <QApplication>
#include <QWidget>
#include <QString>
#include <QTimer>
#include <QDateTime>

/* LibUSB library */
#include "libusb.h"

/* Qwt library */
#include "qwt_plot_curve.h"
#include "qwt_scale_engine.h"

/* Internal includes */
#include "application.h"
#include "messages.h"
#include "light_control.h"
#include "ui_light_control.h"

/**
 * @brief Constructor of 'ControlLight' class
 * @param parent
 */
ControlLight::ControlLight(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ControlLight)
{
    /* Set up user interface */
    ui->setupUi(this);

    /* Disable resize of elements */
    this->setFixedSize(this->size());

    /* Adjust window geometry and set window flags */
    this->setGeometry(20, 450, this->width(), this->height());
    this->setWindowFlags(Qt::Tool | Qt::WindowStaysOnTopHint);

    /* Connect functions to buttons */
    connect(ui->pushButton_connect, SIGNAL(clicked()), this, SLOT(connectButton()));
    connect(ui->pushButton_shutter_open, SIGNAL(clicked(bool)), this, SLOT(openShutter()));
    connect(ui->pushButton_shutter_close, SIGNAL(clicked(bool)), this, SLOT(closeShutter()));
    connect(ui->pushButton_bulb_on, SIGNAL(clicked(bool)), this, SLOT(turnBulbOn()));
    connect(ui->pushButton_bulb_off, SIGNAL(clicked(bool)), this, SLOT(turnBulbOff()));
    connect(ui->pushButton_highPower_on, SIGNAL(clicked(bool)), this, SLOT(enableHighPower()));
    connect(ui->pushButton_highPower_off, SIGNAL(clicked(bool)), this, SLOT(disableHighPower()));

    /* Create timer object */
    timer = new QTimer(this);

    /* If timer times out, things should be updated */
    connect(timer, SIGNAL(timeout()), this, SLOT(updateData()));

    /* Set axis and title of preview plot */
    ui->qwtPlot_stats->setXAxisTitle("time in s");
    ui->qwtPlot_stats->setXAxis(0.0, 60.0);
    ui->qwtPlot_stats->setYAxis(0.0, 6000.0);
    ui->qwtPlot_stats->enableAxis(QwtPlot::yLeft, false);
    ui->qwtPlot_stats->hideGrid();
    ui->qwtPlot_stats->disableZoom();

    /* Add curve for voltage */
    voltage = new QwtPlotCurve("voltage");
    voltage->setPen(QPen("blue"));
    voltage->attach(ui->qwtPlot_stats);

    /* Add curve for current */
    current = new QwtPlotCurve("current");
    current->setPen(QPen("red"));
    current->attach(ui->qwtPlot_stats);

    /* Remember: Is not connected */
    isConnected = false;

    /* Update GUI elements */
    ui->label_status->setText("Not connected");
    ui->label_status->setStyleSheet("color: red;");

    /* Auto connect */
    connectButton();
}

/**
 * @brief Is connection established?
 * @return TRUE if connected, else FALSE
 */
bool ControlLight::getIsConnected(void)
{
    return isConnected;
}

/**
 * @brief Connect light source
 * @return TRUE if successful, else FALSE
 */
bool ControlLight::connectUSB(void)
{
    /* Already connected? */
    if (isConnected)
    {
        /* Show message box */
        showWarning(QString("Unable to connect light source. Light source is already connected."), QString(""));
        return false;
    }

    /* Initiate libUSB library */
    int result = libusb_init(NULL);

    /* Check if successful */
    if (LIBUSB_SUCCESS != result)
    {
        /* Show message box */
        showWarning(QString("Unable to initiate libUSB library."), QString(""));
        return false;
    }

    libusb_device **devs = nullptr;
    ssize_t numDevices = 0;

    /* Get a list of USB devices currently attached to the system */
    numDevices = libusb_get_device_list(NULL, &devs);

    /* Check number of devices */
    if (numDevices < 0)
    {
        /* Close libUSB library */
        libusb_exit(NULL);

        /* Show message box */
        showWarning(QString("Unable to get list of currently attached USB devices."), QString(""));
        return false;
    }

    unsigned int i = 0;

    /* Loop through devices */
    for (i = 0; devs[i]; i++)
    {
        struct libusb_device_descriptor desc;

        /* Get the USB device descriptor for a given device */
        result = libusb_get_device_descriptor(devs[i], &desc);

        /* Check if successful */
        if (LIBUSB_SUCCESS != result)
        {
            /* Close libUSB library */
            libusb_exit(NULL);

            /* Show message box */
            showWarning(QString("Failed to get device descriptor."), QString(""));
            return false;
        }

        /* Did we find the HL-4 light source by Ocean Optics? */
        if ((desc.idVendor == 0x2457) && (desc.idProduct == 0x7000))
        {
            /* Open a device and obtain a device handle */
            result = libusb_open(devs[i], &handle);

            /* Check if successful */
            if (LIBUSB_SUCCESS != result)
            {
                /* Close libUSB library */
                libusb_exit(NULL);

                /* Show message box */
                showWarning(QString("Unable to obtain a device handle."), QString(""));
                return false;
            }

            /* Remember our device */
            dev = devs[i];

            /* Remember bus number and device address */
            busNumber = libusb_get_bus_number(dev);
            devAddress = libusb_get_device_address(dev);

            /* Get first USB configuration descriptor */
            result = libusb_get_config_descriptor(dev, 0, &config);

            /* Check if successful */
            if (LIBUSB_SUCCESS != result)
            {
                /* Close device handle */
                libusb_close(handle);
                handle = nullptr;

                /* Close libUSB library */
                libusb_exit(NULL);

                /* Show message box */
                showWarning(QString("Couldn't retrieve descriptors."), QString(""));
                return false;
            }

            /* Remember device interface */
            interface = &config->interface[0];

            /* Check if number of endpoints is correct */
            if (interface->altsetting->bNumEndpoints != 2)
            {
                /* Free obtained configuration descriptor */
                libusb_free_config_descriptor(config);
                config = nullptr;

                /* Close device handle */
                libusb_close(handle);
                handle = nullptr;

                /* Close libUSB library */
                libusb_exit(NULL);

                /* Show message box */
                showWarning(QString("Invalid number of endpoints (has to be 2)."), QString(""));
                return false;
            }

            /* Remember endpoints */
            endpoint[0] = &interface->altsetting->endpoint[0];
            endpoint[1] = &interface->altsetting->endpoint[1];

        #ifndef Q_OS_WIN
            /* Determine if a kernel driver is active on an interface */
            if (libusb_kernel_driver_active(handle, 0))
            {
                /* Detach a kernel driver from an interface */
                result = libusb_detach_kernel_driver(handle, 0);

                /* Check if successful */
                if (LIBUSB_SUCCESS != result)
                {
                    QString errorCode, detailedText;

                    switch (result)
                    {
                        case LIBUSB_ERROR_NOT_FOUND:
                        {
                            /* Set up messages */
                            errorCode = QString("Unable to detach a kernel driver from an interface. No kernel driver was active!");
                            detailedText = QString("LIBUSB_ERROR_NOT_FOUND from libusb_detach_kernel_driver");
                            break;
                        }

                        case LIBUSB_ERROR_INVALID_PARAM:
                        {
                            /* Set up messages */
                            errorCode = QString("Unable to detach a kernel driver from an interface. The interface does not exist!");
                            detailedText = QString("LIBUSB_ERROR_INVALID_PARAM from libusb_detach_kernel_driver");
                            break;
                        }

                        case LIBUSB_ERROR_NO_DEVICE:
                        {
                            /* Set up messages */
                            errorCode = QString("Unable to detach a kernel driver from an interface. The device has been disconnected!");
                            detailedText = QString("LIBUSB_ERROR_NO_DEVICE from libusb_detach_kernel_driver");
                            break;
                        }

                        case LIBUSB_ERROR_NOT_SUPPORTED:
                        {
                            /* Set up messages */
                            errorCode = QString("Unable to detach a kernel driver from an interface. On platforms where the functionality is not available!");
                            detailedText = QString("LIBUSB_ERROR_NOT_SUPPORTED from libusb_detach_kernel_driver");
                            break;
                        }

                        default:
                        {
                            /* Set up messages */
                            errorCode = QString("Unable to detach a kernel driver from an interface. Unknown error!");
                            detailedText = QString("Unknown error from libusb_detach_kernel_driver");
                            break;
                        }
                    }

                    /* Show warning */
                    showWarning(errorCode, detailedText);

                    /* Free obtained configuration descriptor */
                    libusb_free_config_descriptor(config);
                    config = nullptr;

                    /* Close device handle */
                    libusb_close(handle);
                    handle = nullptr;

                    /* Close libUSB library */
                    libusb_exit(NULL);

                    return false;
                }
            }
        #endif

            /* Claim an interface on a given device handle */
            result = libusb_claim_interface(handle, 0);

            /* Check if successful */
            if (LIBUSB_SUCCESS != result)
            {
                QString errorCode, detailedText;

                switch (result)
                {
                    case LIBUSB_ERROR_NOT_FOUND:
                    {
                        /* Set up messages */
                        errorCode = QString("Unable to claim an interface on a given device handle. The requested interface does not exist!");
                        detailedText = QString("LIBUSB_ERROR_NOT_FOUND from libusb_claim_interface");
                        break;
                    }

                    case LIBUSB_ERROR_BUSY:
                    {
                        /* Set up messages */
                        errorCode = QString("Unable to claim an interface on a given device handle. Another program or driver has claimed the interface!");
                        detailedText = QString("LIBUSB_ERROR_BUSY from libusb_claim_interface");
                        break;
                    }

                    case LIBUSB_ERROR_NO_DEVICE:
                    {
                        /* Set up messages */
                        errorCode = QString("Unable to claim an interface on a given device handle. The device has been disconnected!");
                        detailedText = QString("LIBUSB_ERROR_NO_DEVICE from libusb_claim_interface");
                        break;
                    }

                    default:
                    {
                        /* Set up messages */
                        errorCode = QString("Unable to claim an interface on a given device handle. Unknown error!");
                        detailedText = QString("Unknown error from libusb_claim_interface");
                        break;
                    }
                }

                /* Show warning */
                showWarning(errorCode, detailedText);

                /* Free obtained configuration descriptor */
                libusb_free_config_descriptor(config);
                config = nullptr;

                /* Close device handle */
                libusb_close(handle);

                /* Close libUSB library */
                libusb_exit(NULL);

                return false;
            }

            /* Device connected */
            isConnected = true;
        }
    }

    /* Frees a list of devices previously discovered using libusb_get_device_list() */
    libusb_free_device_list(devs, 1);

    /* Successful if device connected */
    return isConnected;
}

/**
 * @brief Disconnect light source
 */
void ControlLight::disconnectUSB(void)
{
    /* Not connected? */
    if (!isConnected)
    {
        /* Show message box */
        showWarning(QString("Unable to disconnect light source. Light source is not connected."), QString(""));
        return;
    }

    /* Valid device handle? */
    if (nullptr != handle)
    {
        /* Valid configuration handle? */
        if (nullptr != config)
        {
            /* Free obtained configuration descriptor */
            libusb_free_config_descriptor(config);
        }

        /* Release claimed interface */
        libusb_release_interface(handle, 0);

        /* Close device handle */
        libusb_close(handle);
    }

    /* Close libUSB library */
    libusb_exit(NULL);

    /* Not connected anymore */
    isConnected = false;
}

/**
 * @brief Send opcode to light source
 * @param[in] opcode Unsigned char array containing the opcode
 * @return NULL if failed, else answer from light source
 */
QString ControlLight::sendOpcode(const char opcode[])
{
    /* Connected to light source? */
    if (!isConnected)
    {
        /* Failure */
        return NULL;
    }

    int length = strlen(opcode);
    int actual_length = 0;

    /* Send USB out request */
    int result = libusb_bulk_transfer(handle, endpoint[1]->bEndpointAddress, (unsigned char *)opcode, length, &actual_length, 2000);

    /* Check if successful */
    if (LIBUSB_SUCCESS != result)
    {
        QString errorCode, detailedText;

        switch (result)
        {
            case LIBUSB_ERROR_TIMEOUT:
            {
                /* Set up messages */
                errorCode = QString("Unable to send opcode to light source. The transfer timed out.");
                detailedText = QString("LIBUSB_ERROR_TIMEOUT from libusb_bulk_transfer");
                break;
            }

            case LIBUSB_ERROR_PIPE:
            {
                /* Set up messages */
                errorCode = QString("Unable to send opcode to light source. The endpoint halted.");
                detailedText = QString("LIBUSB_ERROR_PIPE from libusb_bulk_transfer");
                break;
            }

            case LIBUSB_ERROR_OVERFLOW:
            {
                /* Set up messages */
                errorCode = QString("Unable to send opcode to light source. The device offered more data.");
                detailedText = QString("LIBUSB_ERROR_OVERFLOW from libusb_bulk_transfer");
                break;
            }

            case LIBUSB_ERROR_NO_DEVICE:
            {
                /* Set up messages */
                errorCode = QString("Unable to send opcode to light source. The device has been disconnected.");
                detailedText = QString("LIBUSB_ERROR_NO_DEVICE from libusb_bulk_transfer");
                break;
            }

            default:
            {
                /* Set up messages */
                errorCode = QString("Unable to send opcode to light source. Unknown error.");
                detailedText = QString("Unknown error from libusb_bulk_transfer");
                break;
            }

            /* Show message box */
            showWarning(errorCode, detailedText);

            return NULL;
        }
    }
    else
    {
        /* Check if number of bytes sent is equal to number of data bytes */
        if (actual_length != length)
        {
            /* Show message box */
            showWarning(QString("Number of bytes sent is not equal to number of data bytes."), QString(""));
            return NULL;
        }
    }

    unsigned char buffer[64];

    /* Send USB in request */
    result = libusb_bulk_transfer(handle, endpoint[0]->bEndpointAddress, buffer, 64, &actual_length, 2000);

    /* Check if successful */
    if (LIBUSB_SUCCESS != result)
    {
        QString errorCode, detailedText;

        switch (result)
        {
            case LIBUSB_ERROR_TIMEOUT:
            {
                /* Set up messages */
                errorCode = QString("Unable to get answer from light source. The transfer timed out.");
                detailedText = QString("LIBUSB_ERROR_TIMEOUT from libusb_bulk_transfer");
                break;
            }

            case LIBUSB_ERROR_PIPE:
            {
                /* Set up messages */
                errorCode = QString("Unable to get answer from light source. The endpoint halted.");
                detailedText = QString("LIBUSB_ERROR_PIPE from libusb_bulk_transfer");
                break;
            }

            case LIBUSB_ERROR_OVERFLOW:
            {
                /* Set up messages */
                errorCode = QString("Unable to get answer from light source. The device offered more data.");
                detailedText = QString("LIBUSB_ERROR_OVERFLOW from libusb_bulk_transfer");
                break;
            }

            case LIBUSB_ERROR_NO_DEVICE:
            {
                /* Set up messages */
                errorCode = QString("Unable to get answer from light source. The device has been disconnected.");
                detailedText = QString("LIBUSB_ERROR_NO_DEVICE from libusb_bulk_transfer");
                break;
            }

            default:
            {
                /* Set up messages */
                errorCode = QString("Unable to get answer from light source. Unknown error.");
                detailedText = QString("Unknown error from libusb_bulk_transfer");
                break;
            }

            /* Show message box */
            showWarning(errorCode, detailedText);

            return NULL;
        }
    }

    /* Nothing recieved? */
    if (actual_length <= 0)
    {
        /* Stop timer */
        timer->stop();

        /* Disconnect light source */
        disconnectUSB();

        /* Update GUI elements */
        ui->label_status->setText("Not connected");
        ui->label_status->setStyleSheet("color: red;");
        ui->pushButton_connect->setText("Connect");

        /* Show message box */
        showWarning(QString("Unable to get answer from light source. Please reconnect the light source."), QString(""));

        /* Failure */
        return NULL;
    }

    QString answer = QString::fromLatin1((const char *)buffer);

    /* Check if issued command was valid */
    if (answer.indexOf(QString("INVCOMMAND")) >= 0)
    {
        /* Show message box */
        showWarning(QString("Light source did not recognize invalid opcode '%1'.").arg(QString::fromLatin1((const char *)opcode)), QString(""));

        /* Failure */
        return NULL;
    }
    return answer;
}

/*
 * -----------------------------------------
 * Public procedures of 'ControlLight' class
 *
 * Allow external access to the light source
 * -----------------------------------------
 */

/**
 * @brief Get device name
 * @return NULL if failed, else device name
 */
QString ControlLight::getDeviceName(void)
{
    /* Send opcode "gdname" */
    QString answer = sendOpcode("gdname");

    /* Check if successful */
    if (NULL != answer)
    {
        /* Return device name (cut at pipe character) */
        return answer.section('|', 1, -1);
    }
    return NULL;
}

/**
 * @brief Get device description
 * @return NULL if failed, else device name
 */
QString ControlLight::getDeviceDesc(void)
{
    /* Send opcode "gddesc" */
    QString answer = sendOpcode("gddesc");

    /* Check if successful */
    if (NULL != answer)
    {
        /* Return device description (cut at pipe character) */
        return answer.section('|', 1, -1);
    }
    return NULL;
}

/**
 * @brief Get manufacturing date
 * @return NULL if failed, else manufacturing date in the format "YYYYMMDD"
 */
QString ControlLight::getManufacturingDate(void)
{
    /* Send opcode "gdmfgdate" */
    QString answer = sendOpcode("gdmfgdate");

    /* Check if successful */
    if (NULL != answer)
    {
        /* Return manufacturing date (cut at pipe character) */
        return answer.section('|', 1, -1);
    }
    return NULL;
}

/**
 * @brief Get serial number
 * @return NULL if failed, else serial number
 */
QString ControlLight::getSerialNumber(void)
{
    /* Send opcode "gdsn" */
    QString answer = sendOpcode("gdsn");

    /* Check if successful */
    if (NULL != answer)
    {
        /* Return serial number (cut at pipe character) */
        return answer.section('|', 1, -1);
    }
    return NULL;
}

/**
 * @brief Get firmware version
 * @return NULL if failed, else firmware version
 */
QString ControlLight::getFirmwareVersion(void)
{
    /* Send opcode "gfw" */
    QString answer = sendOpcode("gfw");

    /* Check if successful */
    if (NULL != answer)
    {
        /* Cut at pipe character */
        answer = answer.section('|', 1, -1);

        QString major, minor, rev;

        /* Decode version information */
        major = answer.left(2).remove(QRegExp("^[0]*"));
        if (!major.length()) { major = QString("0"); }
        minor = answer.mid(2, 2).remove(QRegExp("^[0]*"));
        if (!minor.length()) { minor = QString("0"); }
        rev = answer.right(2).remove(QRegExp("^[0]*"));
        if (!rev.length()) { rev = QString("0"); }

        /* Return firmware version */
        return QString("%1.%2.%3").arg(major, minor, rev);
    }
    return NULL;
}

/**
 * @brief Get shutter status
 * @return FALSE if closed/error, else TRUE
 */
bool ControlLight::getShutterStatus(void)
{
    /* Send opcode "gshstatus" */
    QString answer = sendOpcode("gshstatus");

    /* Check if successful */
    if (NULL != answer)
    {
        /* Cut at pipe character */
        answer = answer.section('|', 1, -1);

        return !answer.compare(QString("1"), Qt::CaseSensitive);
    }
    return false;
}

/**
 * @brief Set shutter status
 * @param[in] value TRUE if shutter open, else FALSE
 * @return TRUE if successful, else FALSE
 */
bool ControlLight::setShutterStatus(bool value)
{
    /* Send opcode "sshstatus" */
    QString answer = sendOpcode(value ? "sshstatus|1" : "sshstatus|0");

    /* Check if successful */
    if (NULL != answer)
    {
        /* Cut at pipe character */
        answer = answer.section('|', 1, -1);

        /* Status set correctly? */
        if (value && answer.compare(QString("1"), Qt::CaseSensitive))
        {
            /* Show message box */
            showWarning(QString("Setting shutter status failed!"), QString(""));

            return false;
        }
        return true;
    }
    return false;
}

/**
 * @brief Get bulp on time
 * @return Bulp on time in seconds
 */
float ControlLight::getBulbOnTime(void)
{
    /* Send opcode "gbaont" */
    QString answer = sendOpcode("gbaont|0");

    /* Check if successful */
    if (NULL != answer)
    {
        /* Cut at pipe character; convert to number */
        return answer.section('|', 1, -1).toFloat();
    }
    return 0.0f;
}

/**
 * @brief Get bulp warmup time
 * @return Bulp warmup time in minutes
 */
float ControlLight::getBulbWarmupTime(void)
{
    /* Send opcode "gbwut" */
    QString answer = sendOpcode("gbwut|0");

    /* Check if successful */
    if (NULL != answer)
    {
        /* Cut at pipe character; convert to number */
        return answer.section('|', 1, -1).toFloat();
    }
    return 0.0f;
}

/**
 * @brief Get bulb current
 * @return Bulb current in mA
 */
float ControlLight::getBulbCurrent(void)
{
    /* Send opcode "gbc" */
    QString answer = sendOpcode("gbc|0");

    /* Check if successful */
    if (NULL != answer)
    {
        /* Cut at pipe character */
        answer = answer.section('|', 1, -1);

        /* Convert to number */
        return answer.toFloat();
    }
    return 0.0f;
}

/**
 * @brief Get bulb voltage
 * @return Bulb voltage in mV
 */
float ControlLight::getBulbVoltage(void)
{
    /* Send opcode "gbv" */
    QString answer = sendOpcode("gbv|0");

    /* Check if successful */
    if (NULL != answer)
    {
        /* Cut at pipe character */
        answer = answer.section('|', 1, -1);

        /* Convert to number */
        return answer.toFloat();
    }
    return 0.0f;
}

/**
 * @brief Set bulb status
 * @param[in] value TRUE means on, FALSE means off
 * @return TRUE if successful, else FALSE
 */
bool ControlLight::setBulbStatus(bool value)
{
    /* Send opcode "sbon"/"sboff" */
    QString answer = sendOpcode(value ? "sbon|0" : "sboff|0");

    /* Check if successful */
    if (NULL != answer)
    {
        /* Cut at pipe character */
        answer = answer.section('|', 1, -1);

        /* Status set correctly? */
        if (value && answer.compare(QString("1"), Qt::CaseSensitive))
        {
            /* Show message box */
            showWarning(QString("Unable to set bulb status."), QString(""));

            return false;
        }
        return true;
    }
    return false;
}

/**
 * @brief Get bulb status
 * @return Bulb status structure
 */
bulbStatus ControlLight::getBulbStatus(void)
{
    bulbStatus data = { 0, 0, 0, 0, 0, 0, 0, 0 };

    /* Send opcode "gbstatus" */
    QString answer = sendOpcode("gbstatus|0");

    /* Check if successful */
    if (NULL != answer)
    {
        /* Check if left two characters are equal to "15"; this means success */
        if (answer.left(2).compare(QString("15"), Qt::CaseSensitive) != 0)
        {
            /* Show message box */
            showWarning(QString("Unable to get bulb status"), QString(""));
        }
        else
        {
            /* Cut at pipe character */
            answer = answer.section('|', 1, -1);

            /* Decode results */
            data.isOn = (answer[0] == QChar('1'));
            data.isError = (answer[1] == QChar('1'));
            data.isEEPROMError = (answer[2] == QChar('1'));
            data.isStdMode = (answer[3] == QChar('1'));
            data.isWarmedUp = (answer[4] == QChar('1'));
            data.isLT90 = (answer[5] == QChar('1'));
            data.isLT100 = (answer[6] == QChar('1'));
            data.isHeaterActive = (answer[7] == QChar('1'));
        }
    }
    return data;
}

/**
 * @brief Set bulp power mode
 * @param[in] mode Power mode (TRUE for standard power mode, FALSE for high power mode)
 * @return TRUE if successful, else FALSE
 */
bool ControlLight::setBulbPowerMode(bool mode)
{
    /* Send opcode "sbpmode" */
    QString answer = sendOpcode(mode ? "sbpmode|0|1" : "sbpmode|0|0");

    /* Check if successful */
    if (NULL != answer)
    {
        /* Cut at pipe character */
        answer = answer.section('|', 1, -1);

        /* High power mode? */
        if ((answer[0] == '1') && mode)
        {
            return true;
        }
        /* Standard power mode? */
        else if ((answer[0] == '0') && !mode)
        {
            return true;
        }
        return false;
    }

    /* Failure */
    return false;
}

/**
 * @brief Get bulp power mode
 * @return FALSE if standard power mode, HIGH if high power mode
 */
bool ControlLight::getBulbPowerMode(void)
{
    /* Send opcode "gbpmode" */
    QString answer = sendOpcode("gbpmode|0");

    /* Cut at pipe character */
    answer = answer.section('|', 1, -1);

    /* Check if successful */
    if (NULL == answer)
    {
        /* Standard power? */
        if (answer[0] == '0')
        {
            /* Standard power */
            return false;
        }
        /* High power? */
        else if (answer[0] == '1')
        {
            /* High power */
            return true;
        }
    }

    /* Failure */
    return false;
}

/*
 * --------------------------------------
 * Slots assigned to buttons on the panel
 * --------------------------------------
 */

/**
 * @brief Button 'connect' clicked
 */
void ControlLight::connectButton(void)
{
    /* Disable 'connect' button */
    ui->pushButton_connect->setEnabled(false);

	/* Run event handler once */
    QApplication::processEvents();

    /* Light source connected? */
    if (isConnected)
    {
        /* Stop timer */
        timer->stop();

        /* Disconnect light source */
        disconnectUSB();
    }
    else
    {
        /* Update GUI elements */
        ui->label_status->setText("Connecting");
        ui->label_status->setStyleSheet("color: blue;");

		/* Run event handler once */
        QApplication::processEvents();

        /* Connect light source */
        if (connectUSB())
        {
            /* Update data */
            updateData();

            /* Poll every second */
            timer->start(1000);
        }
    }

    /* Update GUI elements */
    ui->label_status->setText(isConnected ? "Connected" : "Not connected");
    ui->label_status->setStyleSheet(isConnected ? "color: green;" : "color: red;");
    ui->pushButton_connect->setText(isConnected ? "Disconnect" : "Connect");

    /* Enable 'connect' button */
    ui->pushButton_connect->setEnabled(true);
}

/**
 * @brief Open shutter
 */
void ControlLight::openShutter(void)
{
	/* Set shutter and get status */
    bool bShutterStatus = setShutterStatus(true);

	/* Update buttons accordings to status (success or failure) */
    ui->pushButton_shutter_open->setDisabled(bShutterStatus);
    ui->pushButton_shutter_close->setEnabled(bShutterStatus);
}

/**
 * @brief Close shutter
 */
void ControlLight::closeShutter(void)
{
	/* Set shutter and get status */
    bool bShutterStatus = setShutterStatus(false);

	/* Update buttons accordings to status (success or failure) */
    ui->pushButton_shutter_open->setEnabled(bShutterStatus);
    ui->pushButton_shutter_close->setDisabled(bShutterStatus);
}

/**
 * @brief Turn bulb on
 */
void ControlLight::turnBulbOn(void)
{
    bool bBulbStatus = setBulbStatus(true);

    /* Update buttons according to status (success or failure) */
    ui->pushButton_bulb_on->setDisabled(bBulbStatus);
    ui->pushButton_bulb_off->setEnabled(bBulbStatus);
}

/**
 * @brief Turn bulb off
 */
void ControlLight::turnBulbOff(void)
{
    bool bBulbStatus = setBulbStatus(false);

    /* Update buttons according to status (success or failure) */
    ui->pushButton_bulb_on->setEnabled(bBulbStatus);
    ui->pushButton_bulb_off->setDisabled(bBulbStatus);
}

void ControlLight::enableHighPower(void)
{
    bool bHighPower = setBulbPowerMode(true);

    /* Update buttons according to status (success or failure) */
    ui->pushButton_highPower_on->setDisabled(bHighPower);
    ui->pushButton_highPower_off->setEnabled(bHighPower);
}

void ControlLight::disableHighPower(void)
{
    bool bHighPower = setBulbPowerMode(false);

    /* Update buttons according to status (success or failure) */
    ui->pushButton_highPower_on->setEnabled(bHighPower);
    ui->pushButton_highPower_off->setDisabled(bHighPower);
}

/*
 * --------------------------------------
 * General things of 'ControlLight' class
 * --------------------------------------
 */

/**
 * @brief Update data (e.g. bulb voltage and current)
 */
void ControlLight::updateData(void)
{
    /* Only continue if light source is connected */
    if (!isConnected) { return; }

    /* End of buffer reached? */
    if (valueIndex > LENGTH_MEMORY - 1)
    {
        unsigned int i = 0;

        /* Loop through buffer elements */
        for (i = 1; i < LENGTH_MEMORY; i++)
        {
            voltage_values[i - 1] = voltage_values[i];
            current_values[i - 1] = current_values[i];
        }

        /* Decrease buffer pointer */
        valueIndex--;
    }

    /* Get voltage and current */
    voltage_values[valueIndex] = getBulbVoltage();
    current_values[valueIndex] = getBulbCurrent();
    time_values[valueIndex] = valueIndex;

    /* Update graph values */
    voltage->setSamples(time_values, voltage_values, valueIndex);
    current->setSamples(time_values, current_values, valueIndex);

    /* End of buffer not reached yet? */
    if (valueIndex < LENGTH_MEMORY)
    {
        /* Increase buffer pointer */
        valueIndex++;
    }

    /* Update graph */
    ui->qwtPlot_stats->replot();

    /* Get shutter status */
    bool bShutterStatus = getShutterStatus();

    /* Update buttons accordings to status (shutter open/closed) */
    ui->pushButton_shutter_open->setDisabled(bShutterStatus);
    ui->pushButton_shutter_close->setEnabled(bShutterStatus);

    /* Get bulb status */
    bulbStatus status = getBulbStatus();

    /* Update buttons according to status (bulb on/off) */
    ui->pushButton_bulb_on->setDisabled(status.isOn);
    ui->pushButton_bulb_off->setEnabled(status.isOn);

    /* Get power mode */
    bool bPowerMode = getBulbPowerMode();

    /* Update buttons according to status */
    ui->pushButton_highPower_on->setDisabled(bPowerMode);
    ui->pushButton_highPower_off->setEnabled(bPowerMode);

    /* Get bulb on time */
    QString sBulbOnTime = QDateTime::fromTime_t(getBulbOnTime()).toUTC().toString("hh:mm:ss");

    /* Update label according to the value */
    ui->label_bulbOnTime_value->setText(sBulbOnTime);
}

/**
 * @brief Close event of 'ControlLight' class
 * @param event
 */
void ControlLight::closeEvent(QCloseEvent *event) {
    Q_UNUSED(event);
}

/**
 * @brief Destructor of 'ControlLight' class
 */
ControlLight::~ControlLight(void)
{
    /* Light source connected? */
    if (isConnected)
    {
        /* Disconnect light source */
        disconnectUSB();
    }

    /* Check for voltage curve */
    if (nullptr != voltage)
    {
        /* Free memory */
        delete voltage;
        voltage = nullptr;
    }

    /* Check for current curve */
    if (nullptr != current)
    {
        /* Free memory */
        delete current;
        current = nullptr;
    }

    /* Timer running? */
    if (nullptr != timer)
    {
        /* Free memory */
        delete timer;
        timer = nullptr;
    }

    /* Delete user interface */
    delete ui;
}
