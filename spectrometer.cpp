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

#define USE_POSTMESSAGE

/* External includes */
#include <QSettings>
#include <QTime>
#include <math.h>

/* Avantes AvaSpec library */
#include "avaspec.h"

/* Internal includes */
#include "application.h"
#include "messages.h"
#include "math_helper.h"
#include "spectrometer_eeprom.h"
#include "ui_spectrometer_eeprom.h"
#include "spectrometer.h"

/*
 * Global variables
 */
extern QSettings *settings;

/**
 * @brief Constructor of 'Spectrometer' class
 * @param a_pDeviceId Device identifier returned by AVS_Activate
 */
Spectrometer::Spectrometer(AvsIdentityType *a_pDeviceId)
{
    /* Remember spectrometer serial number */
    serialNumber = QString::fromLatin1(a_pDeviceId->SerialNumber);

    /* Zero pixels before initialization */
    a_pNumPixels = 0;

    /* Activate selected spectrometer for communication */
    a_hDevice = AVS_Activate(a_pDeviceId);

    /* Call of AVS_Activate successful? */
    if (INVALID_AVS_HANDLE_VALUE == a_hDevice)
    {
        /* Create message box */
        showWarning(QString("Unable to activate spectrometer %1 for communication.").
                    arg(serialNumber),
                    QString("File:\t%1\nFunction:\t%2\nLine:\t%3\n\nAvsHandle AVS_Activate(AvsIdentityType* a_pDeviceId) returned INVALID_AVS_HANDLE_VALUE.").
                    arg(__FILE__, __FUNCTION__, QString::number(__LINE__-9)));
    }
    else
    {
        /* Get the status of the software and version info of the different parts */
        int result = AVS_GetVersionInfo(a_hDevice, a_pFPGAVersion, a_pFirmwareVersion, a_pDLLVersion);

        /* Call of AVS_GetVersionInfo successful? */
        if (ERR_SUCCESS != result)
        {
            QString errorCode, detailedText;

            switch (result)
            {
            case ERR_DEVICE_NOT_FOUND:
            {
                /* Opening communication failed or time-out during communication occurred */
                errorCode = "ERR_DEVICE_NOT_FOUND";
                detailedText = "Opening communication failed or time-out during communication occurred";
                break;
            }

            case ERR_INVALID_DEVICE_ID:
            {
                /* AvsHandle is unknown in the DLL */
                errorCode = "ERR_INVALID_DEVICE_ID";
                detailedText =  "AvsHandle is unknown in the DLL";
                break;
            }

            case ERR_TIMEOUT:
            {
                /* No answer received from device */
                errorCode = "ERR_TIMEOUT";
                detailedText = "No answer received from device";
                break;
            }

            default:
            {
                /* Set error message */
                errorCode = "ERR_UNKNOWN";
                detailedText = QString("Unhandled error, code %1").arg(result);
                break;
            }
            }

            /* Create message box */
            showWarning(QString("Unable to get the status of the software and version info of the different parts of spectrometer %1.").
                        arg(a_pDeviceId->SerialNumber),
                        QString("File:\t%1\nFunction:\t%2\nLine:\t%3\n\nint AVS_GetVersionInfo(a_hDevice, a_pFPGAVersion, a_pFirmwareVersion, a_pDLLVersion) returned %4.").
                        arg(__FILE__, __FUNCTION__, QString::number(__LINE__-46), errorCode));
        }

        /* Get the number of pixels */
        result = AVS_GetNumPixels(a_hDevice, &a_pNumPixels);

        /* Call of AVS_GetNumPixels successful? */
        if (ERR_SUCCESS != result)
        {
            QString errorCode, detailedText;

            switch (result)
            {
            case ERR_DEVICE_NOT_FOUND:
            {
                /* Opening communication failed or time-out during communication occurred */
                errorCode = "ERR_DEVICE_NOT_FOUND";
                detailedText = "Opening communication failed or time-out during communication occurred";
                break;
            }

            case ERR_INVALID_DEVICE_ID:
            {
                /* AvsHandle is unknown in the DLL */
                errorCode = "ERR_INVALID_DEVICE_ID";
                detailedText = "AvsHandle is unknown in the DLL";
                break;
            }

            case ERR_INVALID_SIZE:
            {
                /* Allocated buffer size too small */
                errorCode = "ERR_INVALID_SIZE";
                detailedText = "Allocated buffer size too small";
                break;
            }

            default:
            {
                /* Set error message */
                errorCode = "ERR_UNKNOWN";
                detailedText = QString("Unhandled error, code %1").arg(result);
                break;
            }
            }

            /* Create message box */
            showWarning(QString("Unable to get the number of pixels of spectrometer %1.").
                        arg(a_pDeviceId->SerialNumber),
                        QString("File:\t%1\nFunction:\t%2\nLine:\t%3\n\nint AVS_GetNumPixels(a_hDevice, &a_pNumPixels) returned %4.").
                        arg(__FILE__, __FUNCTION__, QString::number(__LINE__-46), errorCode));
        }

        /* Valid number of detector elements? */
        if (!a_pNumPixels)
        {
            /* Create message box */
            showCritical(QString("Invalid number of detector elements of spectrometer %1.").
                         arg(a_pDeviceId->SerialNumber),
                         QString("File:\t%1\nFunction:\t%2\nLine:\t%3\n\nint AVS_GetNumPixels(a_hDevice, &a_pNumPixels) returned invalid a_pNumPixels.").
                         arg(__FILE__, __FUNCTION__, QString::number(__LINE__-56)));
        }

        unsigned int a_Size = 0;

        /* Get device information */
        result = AVS_GetParameter(a_hDevice, 0, &a_Size, a_pDeviceData);

        /* Call of AVS_GetParameter successful? */
        if (ERR_SUCCESS != result)
        {
            /* Allocated buffer size too small? */
            if (ERR_INVALID_SIZE == result)
            {
                /* Try to re-allocate memory for device information */
                a_pDeviceData = (DeviceConfigType*)new char[a_Size];
            }
            else
            {
                QString errorCode, detailedText;

                switch (result)
                {
                case ERR_DEVICE_NOT_FOUND:
                {
                    /* Opening communication failed or time-out during communication occurred */
                    errorCode = "ERR_DEVICE_NOT_FOUND";
                    detailedText = "Opening communication failed or time-out during communication occurred";
                    break;
                }

                case ERR_INVALID_DEVICE_ID:
                {
                    /* AvsHandle is unknown in the DLL */
                    errorCode = "ERR_INVALID_DEVICE_ID";
                    detailedText = "AvsHandle is unknown in the DLL";
                    break;
                }

                default:
                {
                    /* Set error message */
                    errorCode = "ERR_UNKNOWN";
                    detailedText = QString("Unhandled error, code %1").arg(result);
                    break;
                }
                }

                /* Create message box */
                showWarning(QString("Unable to get the device information of spectrometer %1.").
                            arg(a_pDeviceId->SerialNumber),
                            QString("File:\t%1\nFunction:\t%2\nLine:\t%3\n\nint AVS_GetParameter(a_hDevice, 0, &a_Size, a_pDeviceData) returned %4.").
                            arg(__FILE__, __FUNCTION__, QString::number(__LINE__-46), errorCode));
            }
        }

        /* Get device information */
        result = AVS_GetParameter(a_hDevice, a_Size, &a_Size, a_pDeviceData);

        /* Call of AVS_GetParameter successful? */
        if (ERR_SUCCESS != result)
        {
            QString errorCode, detailedText;

            switch (result)
            {
            case ERR_DEVICE_NOT_FOUND:
            {
                /* Opening communication failed or time-out during communication occurred */
                errorCode = "ERR_DEVICE_NOT_FOUND";
                detailedText = "Opening communication failed or time-out during communication occurred";
                break;
            }

            case ERR_INVALID_DEVICE_ID:
            {
                /* AvsHandle is unknown in the DLL */
                errorCode = "ERR_INVALID_DEVICE_ID";
                detailedText = "AvsHandle is unknown in the DLL";
                break;
            }

            case ERR_INVALID_SIZE:
            {
                /* Allocated buffer size too small */
                errorCode = "ERR_INVALID_SIZE";
                detailedText = "Allocated buffer size too small";
                break;
            }

            default:
            {
                /* Set error message */
                errorCode = "ERR_UNKNOWN";
                detailedText = QString("Unhandled error, code %1").arg(result);
                break;
            }
            }

            /* Create message box */
            showWarning(QString("Unable to get the device information of spectrometer %1.").
                        arg(a_pDeviceId->SerialNumber),
                        QString("File:\t%1\nFunction:\t%2\nLine:\t%3\n\nint AVS_GetParameter(a_hDevice, 0, &a_Size, a_pDeviceData) returned %4.").
                        arg(__FILE__, __FUNCTION__, QString::number(__LINE__-46), errorCode));
        }

        /* Memory for wavelengths allocated? */
        if (nullptr != a_pWavelength)
        {
            /* Delete old structure because number of pixels can be changed */
            delete[] a_pWavelength;
            a_pWavelength = nullptr;
        }

        /* Allocate memory for wavelengths */
        a_pWavelength = new double[a_pNumPixels];

        /* Get the wavelength values corresponding to the pixels */
        result = AVS_GetLambda(a_hDevice, a_pWavelength);

        /* Call of AVS_GetLambda successful? */
        if (ERR_SUCCESS != result)
        {
            QString errorCode, detailedText;

            switch (result)
            {
            case ERR_DEVICE_NOT_FOUND:
            {
                /* Opening communication failed or time-out during communication occurred */
                errorCode = "ERR_DEVICE_NOT_FOUND";
                detailedText = "Opening communication failed or time-out during communication occurred";
                break;
            }

            case ERR_INVALID_DEVICE_ID:
            {
                /* AvsHandle is unknown in the DLL */
                errorCode = "ERR_INVALID_DEVICE_ID";
                detailedText = "AvsHandle is unknown in the DLL";
                break;
            }

            default:
            {
                /* Set error message */
                errorCode = "ERR_UNKNOWN";
                detailedText = QString("Unhandled error, code %1").arg(result);
                break;
            }
            }

            /* Create message box */
            showWarning(QString("Unable to get the wavelength values corresponding to the pixels of spectrometer %1.").
                        arg(a_pDeviceId->SerialNumber),
                        QString("File:\t%1\nFunction:\t%2\nLine:\t%3\n\nint AVS_GetLambda(a_hDevice, a_pWavelength) returned %4.").
                        arg(__FILE__, __FUNCTION__, QString::number(__LINE__-38), errorCode));
        }

        /* Memory for spectrum allocated? */
        if (nullptr != a_pSpectrum)
        {
            /* Delete old structure because number of pixels can be changed */
            delete[] a_pSpectrum;
            a_pSpectrum = nullptr;
        }

        /* Allocate memory for spectrum */
        a_pSpectrum = new double[a_pNumPixels];

        /* Memory for saturated pixels allocated? */
        if (nullptr != a_pSaturated)
        {
            /* Delete old structure because number of pixels can be changed */
            delete[] a_pSaturated;
            a_pSaturated = nullptr;
        }

        /* Allocate memory for saturated pixels */
        a_pSaturated = new uint8[a_pNumPixels];

        /* Go to spectrometer group */
        settings->beginGroup(serialNumber);

        /* Read readable name from configuration file */
        readableName = settings->value(QString("ReadableName"), QString("")).toString();

        /* Read start pixel from configuration file */
        double value = settings->value(QString("StartPixel"), -1).toInt();

        /* Value found? */
        if (-1 != value)
        {
            a_pDeviceData->m_StandAlone.m_Meas.m_StartPixel = value;
        }

        /* Read stop pixel from configuration file */
        value = settings->value(QString("StopPixel"), -1).toInt();

        /* Value found? */
        if (-1 != value)
        {
            a_pDeviceData->m_StandAlone.m_Meas.m_StopPixel = value;
        }

        /* Read integration time from configuration file */
        value = settings->value(QString("IntegrationTime"), -1).toDouble();

        /* Value found? */
        if (-1 != value)
        {
            a_pDeviceData->m_StandAlone.m_Meas.m_IntegrationTime = value * 1000;
        }

        /* Read integration delay from configuration file */
        value = settings->value(QString("IntegrationDelay"), -1).toDouble();

        /* Value found? */
        if (-1 != value)
        {
            a_pDeviceData->m_StandAlone.m_Meas.m_IntegrationDelay = value * 1000;
        }

        /* Read number of averages from configuration file */
        value = settings->value(QString("NumberOfAverages"), -1).toDouble();

        /* Value found? */
        if (-1 != value)
        {
            a_pDeviceData->m_StandAlone.m_Meas.m_NrAverages = value;
        }

        /* Read dynamic dark correction from configuration file */
        a_pDeviceData->m_StandAlone.m_Meas.m_CorDynDark.m_Enable = settings->value(QString("DynamicDarkCorrection"), QString("true")).toBool();
        a_pDeviceData->m_StandAlone.m_Meas.m_CorDynDark.m_ForgetPercentage = settings->value(QString("ForgetPercentage"), 100).toInt();

        /* Read readable name from configuration file */
        readableName = settings->value(QString("ReadableName"), QString("")).toString();

        /* Read high-resolution ADC flag from configuration file */
        bUseHighResADC = settings->value(QString("UseHighResADC"), QString("true")).toBool();

        /* Use the 16 bit resolution AD converter? */
        result = AVS_UseHighResAdc(a_hDevice, bUseHighResADC);

        /* Call of AVS_UseHighResAdc successful? */
        if (ERR_SUCCESS != result)
        {
            QString errorCode, detailedText;

            switch (result)
            {
            case ERR_OPERATION_NOT_SUPPORTED:
            {
                /* This function is not supported by AS5216 hardware version R1C or earlier */
                errorCode = "ERR_OPERATION_NOT_SUPPORTED";
                detailedText = "This function is not supported by AS5216 hardware version R1C or earlier";
                break;
            }

            default:
            {
                /* Set error message */
                errorCode = "ERR_UNKNOWN";
                detailedText = QString("Unhandled error, code %1").arg(result);
                break;
            }
            }

            /* Create message box */
            showWarning(QString("Unable to enable high resolution mode on spectrometer %1.").
                        arg(a_pDeviceId->SerialNumber),
                        QString("File:\t%1\nFunction:\t%2\nLine:\t%3\n\nint AVS_UseHighResAdc(a_hDevice, bool a_Enable) returned %4.").
                        arg(__FILE__, __FUNCTION__, QString::number(__LINE__-28), errorCode));
        }

        /* Enable extended non-linearity correction? */
        a_pDeviceData->m_Detector.m_NLEnable = settings->value(QString("NonLinearityCorrection"), QString("true")).toBool();

        /* Close open group */
        settings->endGroup();
    }

    /* No measurement done, no measurements running */
    measCount = 0; bMeasuring = false; bEnabled = false;
}

/**
 * @brief Get readable name
 * @return Readable name
 */
QString Spectrometer::getReadableName(void)
{
    /* Return readable name */
    return readableName;
}

/**
 * @brief Set readable name
 * @param[in] value Readable name
 */
void Spectrometer::setReadableName(QString value)
{
    /* Set readable name */
    readableName = value;
}

/**
 * @brief Does the spectrometer has a readable name?
 * @return TRUE if spectrometer has readable name, else FALSE
 */
bool Spectrometer::hasReadableName(void)
{
    return (readableName.length() > 0);
}

/**
 * @brief Get serial number
 * @return Serial number
 */
QString Spectrometer::getSerialNumber(void)
{
    return serialNumber;
}

/**
 * @brief Shows EEPROM dialog
 */
void Spectrometer::showEEPROM(void)
{
    SpectrometerEEPROM eepromDialog;

    /* Set spectrometer serial number */
    eepromDialog.ui->lineEdit_structureLength->setText(QString::number(a_pDeviceData->m_Len));
    eepromDialog.ui->lineEdit_structureVersion->setText(QString::number(a_pDeviceData->m_ConfigVersion));

    /* Does the spectrometer has a readable name? */
    if (readableName.length() > 0)
    {
        eepromDialog.ui->lineEdit_information->setText(QString("%1 (%2)").arg(serialNumber, readableName));
    }
    else
    {
        eepromDialog.ui->lineEdit_information->setText(serialNumber);
    }

    /* Set FPGA, firmware and DLL version info */
    eepromDialog.ui->a_pFPGAVersion->setText(a_pFPGAVersion);
    eepromDialog.ui->a_pFirmwareVersion->setText(a_pFirmwareVersion);
    eepromDialog.ui->a_pDLLVersion->setText(a_pDLLVersion);

    /* Set number of pixels */
    eepromDialog.ui->a_pNumPixels->setText(QString::number(a_pNumPixels));

    QString detectorName;

    /* Set detector type */
    switch (a_pDeviceData->m_Detector.m_SensorType)
    {
    case SENS_HAMS8378_256      : detectorName = "HAMS8378_256";
        break;
    case SENS_HAMS8378_1024     : detectorName = "HAMS8378_1024";
        break;
    case SENS_ILX554            : detectorName = "ILX554";
        break;
    case SENS_HAMS9201          : detectorName = "HAMS9201";
        break;
    case SENS_TCD1304           : detectorName = "TCD1304";
        break;
    case SENS_TSL1301           : detectorName = "TSL1301";
        break;
    case SENS_TSL1401           : detectorName = "TSL1401";
        break;
    case SENS_HAMS8378_512      : detectorName = "HAMS8378_512";
        break;
    case SENS_HAMS9840          : detectorName = "HAMS9840";
        break;
    case SENS_ILX511            : detectorName = "ILX511";
        break;
    case SENS_HAMS10420_2048X64 : detectorName = "HAMS10420_2048X64";
        break;
    case SENS_HAMS11071_2048X64 : detectorName = "HAMS11071_2048X64";
        break;
    case SENS_HAMS7031_1024X122 : detectorName = "HAMS7031_1024X122";
        break;
    case SENS_HAMS7031_1024X58  : detectorName = "HAMS7031_1024X58";
        break;
    case SENS_HAMS11071_2048X16 : detectorName = "HAMS11071_2048X16";
        break;
    case SENS_SU256LSB          : detectorName = "SU256LSB";
        break;
    case SENS_SU512LDB          : detectorName = "SU512LDB";
        break;
    default                     : detectorName = "???";
        break;
    }
    eepromDialog.ui->detectorType->setText(detectorName);

    /* Calculate ip address */
    eepromDialog.ui->m_IpAddr->setText(QString("%1.%2.%3.%4").arg(QString::number(a_Data.m_IpAddr & 0xFF),
                                                                  QString::number((a_Data.m_IpAddr >> 8) & 0xFF),
                                                                  QString::number((a_Data.m_IpAddr >> 16) & 0xFF),
                                                                  QString::number((a_Data.m_IpAddr >> 24) & 0xFF)));

    /* Calculate net mask */
    eepromDialog.ui->m_NetMask->setText(QString("%1.%2.%3.%4").arg(QString::number(a_Data.m_NetMask & 0xFF),
                                                                   QString::number((a_Data.m_NetMask >> 8) & 0xFF),
                                                                   QString::number((a_Data.m_NetMask >> 16) & 0xFF),
                                                                   QString::number((a_Data.m_NetMask >> 24) & 0xFF)));

    /* Calculate gateway */
    eepromDialog.ui->m_Gateway->setText(QString("%1.%2.%3.%4").arg(QString::number(a_Data.m_Gateway & 0xFF),
                                                                   QString::number((a_Data.m_Gateway >> 8) & 0xFF),
                                                                   QString::number((a_Data.m_Gateway >> 16) & 0xFF),
                                                                   QString::number((a_Data.m_Gateway >> 24) & 0xFF)));

    /* Check DHCP state and get TCP port */
    eepromDialog.ui->m_DhcpEnabled->setChecked(a_Data.m_DhcpEnabled > 0);
    eepromDialog.ui->m_TcpPort->setText(QString::number(a_Data.m_TcpPort));

    /* Set wavelength calibration */
    eepromDialog.ui->lineEdit_wavelengthCalibration_intercept->setText(QString::number(a_pDeviceData->m_Detector.m_aFit[0]));
    eepromDialog.ui->lineEdit_wavelengthCalibration_X1->setText(QString::number(a_pDeviceData->m_Detector.m_aFit[1]));
    eepromDialog.ui->lineEdit_wavelengthCalibration_X2->setText(QString::number(a_pDeviceData->m_Detector.m_aFit[2]));
    eepromDialog.ui->lineEdit_wavelengthCalibration_X3->setText(QString::number(a_pDeviceData->m_Detector.m_aFit[3]));
    eepromDialog.ui->lineEdit_wavelengthCalibration_X4->setText(QString::number(a_pDeviceData->m_Detector.m_aFit[4]));

    /*
     * Set defective pixel list
     */

    /* Clear list */
    eepromDialog.ui->listWidget_defectivePixels->clear();

    unsigned char i = 0;

    /* Loop through defective pixel list */
    for (i = 0; i < 30; i++)
    {
        uint8_t pixelNumber = 0;

        pixelNumber = a_pDeviceData->m_Detector.m_DefectivePixels[i];

        if (0 != pixelNumber)
        {
            eepromDialog.ui->listWidget_defectivePixels->addItem(QString::number(pixelNumber));
        }
    }

    /* Set detector gain */
    eepromDialog.ui->doubleSpinBox_gain1->setValue(a_pDeviceData->m_Detector.m_Gain[0]);
    eepromDialog.ui->doubleSpinBox_gain2->setValue(a_pDeviceData->m_Detector.m_Gain[1]);
    eepromDialog.ui->doubleSpinBox_offset1->setValue(a_pDeviceData->m_Detector.m_Offset[0]);
    eepromDialog.ui->doubleSpinBox_offset2->setValue(a_pDeviceData->m_Detector.m_Offset[1]);
    eepromDialog.ui->doubleSpinBox_extOffset->setValue(a_pDeviceData->m_Detector.m_ExtOffset);

    /* Set nonlinearity correction */
    eepromDialog.ui->lineEdit_nonlinearityCalibration_intercept->setText(QString::number(a_pDeviceData->m_Detector.m_aNLCorrect[0]));
    eepromDialog.ui->lineEdit_nonlinearityCalibration_X1->setText(QString::number(a_pDeviceData->m_Detector.m_aNLCorrect[1]));
    eepromDialog.ui->lineEdit_nonlinearityCalibration_X2->setText(QString::number(a_pDeviceData->m_Detector.m_aNLCorrect[2]));
    eepromDialog.ui->lineEdit_nonlinearityCalibration_X3->setText(QString::number(a_pDeviceData->m_Detector.m_aNLCorrect[3]));
    eepromDialog.ui->lineEdit_nonlinearityCalibration_X4->setText(QString::number(a_pDeviceData->m_Detector.m_aNLCorrect[4]));
    eepromDialog.ui->lineEdit_nonlinearityCalibration_X5->setText(QString::number(a_pDeviceData->m_Detector.m_aNLCorrect[5]));
    eepromDialog.ui->lineEdit_nonlinearityCalibration_X6->setText(QString::number(a_pDeviceData->m_Detector.m_aNLCorrect[6]));
    eepromDialog.ui->lineEdit_nonlinearityCalibration_X7->setText(QString::number(a_pDeviceData->m_Detector.m_aNLCorrect[7]));
    eepromDialog.ui->lineEdit_nonlinearityCalibration_lowCounts->setText(QString::number(a_pDeviceData->m_Detector.m_aLowNLCounts));
    eepromDialog.ui->lineEdit_nonlinearityCalibration_highCounts->setText(QString::number(a_pDeviceData->m_Detector.m_aHighNLCounts));
    eepromDialog.ui->checkBox_nonlinearityCorrection_enabled->setChecked(a_pDeviceData->m_Detector.m_NLEnable);

    /* Execute dialog */
    if (QDialog::Accepted == eepromDialog.exec())
    {
        a_pDeviceData->m_Detector.m_NLEnable = eepromDialog.ui->checkBox_nonlinearityCorrection_enabled->isChecked();
    }
}

/**
 * @brief Get number of detector elements
 * @return Number of detector elements
 */
unsigned short Spectrometer::getNumberOfPixels(void)
{
    return a_pNumPixels;
}

/**
 * @brief Get start pixel
 * @return Number of start pixel
 */
unsigned short Spectrometer::getStartPixel(void)
{
    return a_pDeviceData->m_StandAlone.m_Meas.m_StartPixel;
}

/**
 * @brief Set start pixel
 * @param[in] Number of start pixel
 */
void Spectrometer::setStartPixel(unsigned short value)
{
    a_pDeviceData->m_StandAlone.m_Meas.m_StartPixel = value;
}

/**
 * @brief Get stop pixel
 * @return Number of stop pixel
 */
unsigned short Spectrometer::getStopPixel(void)
{
    return a_pDeviceData->m_StandAlone.m_Meas.m_StopPixel;
}

/**
 * @brief Set stop pixel
 * @param[in] Number of stop pixel
 */
void Spectrometer::setStopPixel(unsigned short value)
{
    a_pDeviceData->m_StandAlone.m_Meas.m_StopPixel = value;
}

/**
 * @brief Get start wavelength
 * @return Lowest wavelength in nm, else NULL
 */
double Spectrometer::getStartWavelength(void)
{
    /* Memory for wavelengths allocated? */
    if (nullptr != a_pWavelength)
    {
        return a_pWavelength[a_pDeviceData->m_StandAlone.m_Meas.m_StartPixel];
    }
    return 0.0;
}

/**
 * @brief Get stop wavelength
 * @return Highest wavelength in nm if successful, else NULL
 */
double Spectrometer::getStopWavelength(void)
{
    /* Memory for wavelengths allocated? */
    if (nullptr != a_pWavelength)
    {
        return a_pWavelength[a_pDeviceData->m_StandAlone.m_Meas.m_StopPixel];
    }
    return 0.0;
}

/**
 * @brief Get integration time
 * @return Integration time in milliseconds
 */
float Spectrometer::getIntegrationTime(void)
{
    return a_pDeviceData->m_StandAlone.m_Meas.m_IntegrationTime;
}

/**
 * @brief Set integration time
 * @param[in] value Integration time in milliseconds
 */
void Spectrometer::setIntegrationTime(float value)
{
    a_pDeviceData->m_StandAlone.m_Meas.m_IntegrationTime = value;
}

/**
 * @brief Get integration delay
 * @return Integration delay in milliseconds
 */
float Spectrometer::getIntegrationDelay(void)
{
    return a_pDeviceData->m_StandAlone.m_Meas.m_IntegrationDelay;
}

/**
 * @brief Set integration delay
 * @param[in] value Integration delay in milliseconds
 */
void Spectrometer::setIntegrationDelay(float value)
{
    a_pDeviceData->m_StandAlone.m_Meas.m_IntegrationDelay = value;
}

/**
 * @brief Get number of averages
 * @return Number of averages
 */
int Spectrometer::getNumberOfAverages(void)
{
    return a_pDeviceData->m_StandAlone.m_Meas.m_NrAverages;
}

/**
 * @brief Set number of averages
 * @param[in] value Number of averages
 */
void Spectrometer::setNumberOfAverages(int value)
{
    a_pDeviceData->m_StandAlone.m_Meas.m_NrAverages = value;
}

/**
 * @brief Get time per measurement
 * @return Time per measurement in milliseconds
 */
float Spectrometer::getTimePerMeasurement(void)
{
    /* Integration time multiplied with number of averages makes the time per measurement */
    return a_pDeviceData->m_StandAlone.m_Meas.m_IntegrationTime * a_pDeviceData->m_StandAlone.m_Meas.m_NrAverages;
}

/**
 * @brief Set dynamic dark correction
 * @param[in] enabled TRUE if enabled, else FALSE
 */
void Spectrometer::setDynamicDarkCorrection(bool enabled)
{
    a_pDeviceData->m_StandAlone.m_Meas.m_CorDynDark.m_Enable = enabled;
}

/**
 * @brief Get dynamic dark correction
 * @return TRUE if enabled, else FALSE
 */
bool Spectrometer::getDynamicDarkCorrection(void)
{
    return a_pDeviceData->m_StandAlone.m_Meas.m_CorDynDark.m_Enable;
}

/**
 * @brief Set forget percentage
 * @return Forget percentage
 */
void Spectrometer::setForgetPercentage(unsigned char value)
{
    a_pDeviceData->m_StandAlone.m_Meas.m_CorDynDark.m_ForgetPercentage = value;
}

/**
 * @brief Get forget percentage
 * @return Forget percentage
 */
unsigned char Spectrometer::getForgetPercentage(void)
{
    return a_pDeviceData->m_StandAlone.m_Meas.m_CorDynDark.m_ForgetPercentage;
}

/**
 * @brief Set non-linearity correction
 * @param[in] enabled TRUE if enabled, else FALSE
 */
void Spectrometer::setNonLinearityCorrection(bool enabled)
{
    a_pDeviceData->m_Detector.m_NLEnable = enabled;
}

/**
 * @brief Get non-linearity correction
 * @return TRUE if enabled, else FALSE
 */
bool Spectrometer::getNonLinearityCorrection(void)
{
    return a_pDeviceData->m_Detector.m_NLEnable;
}

/**
 * @brief Set high resolution ADC status
 * @param[in] enabled TRUE if enabled, else FALSE
 */
void Spectrometer::setUseHighResADC(bool enabled)
{
    bUseHighResADC = enabled;
}

/**
 * @brief Get high resolution ADC status
 * @return TRUE if enabled, else FALSE
 */
bool Spectrometer::getUseHighResADC(void)
{
    return bUseHighResADC;
}

/**
 * @brief Set number of measurements for StoreToRAM
 * @param[in] path Path for StoreToRAM file
 * @param[in] numberOfMeasurements Number of measurements
 */
void Spectrometer::forceStoreToRAM(QString path, unsigned short numberOfMeasurements)
{
    /* Remember path for StoreToRAM file */
    storeToRAMPath = path;

    /* Remember number of StoreToRAM measurements */
    numberToRAM = numberOfMeasurements;
}

/**
 * @brief Get path of StoreToRAM file
 * @return Path of StoreToRAM file
 */
QString Spectrometer::getStoreToRAMPath(void)
{
    return storeToRAMPath;
}

/**
 * @brief Prepare spectrometer for measurement
 * @return TRUE if successful, else FALSE
 */
bool Spectrometer::prepareMeasurement(void)
{
    /* Already running a measurement? */
    if (bMeasuring)
    {
        /* Show warning */
        showWarning(QString("Unable to prepare measurement on spectrometer %1. Measurement already running.").arg(serialNumber), QString(""));
        return false;
    }

    /* Spectrometer not enabled? */
    if (!bEnabled)
    {
        /* Show warning */
        showWarning(QString("Unable to prepare measurement on spectrometer %1. Spectrometer not enabled.").arg(serialNumber), QString(""));
        return false;
    }

    MeasConfigType a_pMeasConfig;

    /* Set measurement configuration */
    a_pMeasConfig.m_StartPixel = a_pDeviceData->m_StandAlone.m_Meas.m_StartPixel;
    a_pMeasConfig.m_StopPixel = a_pDeviceData->m_StandAlone.m_Meas.m_StopPixel;
    a_pMeasConfig.m_IntegrationTime = a_pDeviceData->m_StandAlone.m_Meas.m_IntegrationTime;
    a_pMeasConfig.m_IntegrationDelay = a_pDeviceData->m_StandAlone.m_Meas.m_IntegrationDelay;
    a_pMeasConfig.m_NrAverages = a_pDeviceData->m_StandAlone.m_Meas.m_NrAverages;

    /* Check for valid stop pixel (not zero, not smaller than start pixel, not greater than total number of pixels) */
    if (((0 == a_pMeasConfig.m_StopPixel) ||
         (a_pMeasConfig.m_StopPixel < a_pMeasConfig.m_StartPixel) ||
         (a_pMeasConfig.m_StopPixel > a_pNumPixels)))
    {
        /* Show critical error */
        showCritical(QString("Invalid stop pixel on spectrometer %1!").arg(serialNumber), QString(""));
        return false;
    }

    /* Check for valid integration time (not smaller or equal to zero) */
    if (a_pMeasConfig.m_IntegrationTime <= 0.0f)
    {
        /* Show critical error */
        showCritical(QString("Invalid integration time on spectrometer %1!").arg(serialNumber), QString(""));
        return false;
    }

    /* Check for valid number of averages (not zero) */
    if (!a_pMeasConfig.m_NrAverages)
    {
        /* Show critical error */
        showCritical(QString("Invalid number of averages on spectrometer %1!").arg(serialNumber), QString(""));
        return false;
    }

    /* Set dark correction */
    a_pMeasConfig.m_CorDynDark.m_Enable = a_pDeviceData->m_StandAlone.m_Meas.m_CorDynDark.m_Enable;
    a_pMeasConfig.m_CorDynDark.m_ForgetPercentage = a_pDeviceData->m_StandAlone.m_Meas.m_CorDynDark.m_ForgetPercentage;

    /* Set smoothing */
    a_pMeasConfig.m_Smoothing.m_SmoothPix = 0;
    a_pMeasConfig.m_Smoothing.m_SmoothModel = 0;

    /* We want saturation detection */
    a_pMeasConfig.m_SaturationDetection = 1;

    /* Set trigger */
    a_pMeasConfig.m_Trigger.m_Mode = 0;
    a_pMeasConfig.m_Trigger.m_Source = 0;
    a_pMeasConfig.m_Trigger.m_SourceType = 0;

    /* Set control */
    a_pMeasConfig.m_Control.m_LaserDelay = 0;
    a_pMeasConfig.m_Control.m_LaserWaveLength = 0;
    a_pMeasConfig.m_Control.m_LaserWidth = 0;
    a_pMeasConfig.m_Control.m_StoreToRam = numberToRAM;
    a_pMeasConfig.m_Control.m_StrobeControl = 0;

    /* Prepare measurement */
    int result = AVS_PrepareMeasure(a_hDevice, &a_pMeasConfig);

    /* Call of AVS_PrepareMeasure successful? */
    if (ERR_SUCCESS != result)
    {
        QString errorCode, detailedText;

        switch (result)
        {
        case ERR_DEVICE_NOT_FOUND:
        {
            /* Set error message */
            errorCode = "ERR_DEVICE_NOT_FOUND";
            detailedText = "Opening communication failed or time-out during communication occurred.";
            break;
        }

        case ERR_OPERATION_PENDING:
        {
            /* Set error message */
            errorCode = "ERR_OPERATION_PENDING";
            detailedText = "Function is called while result of previous call to AVS_Measure is not received yet.";
            break;
        }

        case ERR_INVALID_DEVICE_ID:
        {
            /* Set error message */
            errorCode = "ERR_INVALID_DEVICE_ID";
            detailedText = "AvsHandle is unknown in the DLL.";
            break;
        }

        case ERR_INVALID_PARAMETER:
        {
            /* Set error message */
            errorCode = "ERR_INVALID_PARAMETER";
            detailedText = "Function called with invalid parameter value.";
            break;
        }

        case ERR_INVALID_PIXEL_RANGE:
        {
            /* Set error message */
            errorCode = "ERR_INVALID_PIXEL_RANGE";
            detailedText = "Measurement preparation failed because pixel range is invalid.";
            break;
        }

        case ERR_INVALID_CONFIGURATION:
        {
            /* Set error message */
            errorCode = "ERR_INVALID_CONFIGURATION";
            detailedText = "Invalid measurement configuration.";
            break;
        }

        case ERR_TIMEOUT:
        {
            /* Set error message */
            errorCode = "ERR_TIMEOUT";
            detailedText = "No answer received from device.";
            break;
        }

        case ERR_INVALID_MEASPARAM_DYNDARK:
        {
            /* Set error message */
            errorCode = "ERR_INVALID_MEASPARAM_DYNDARK";
            detailedText = "Dynamic Dark Correction not supported.";
            break;
        }

        default:
        {
            /* Set error message */
            errorCode = "ERR_UNKNOWN";
            detailedText = QString("Unhandled error, code %1").arg(result);
            break;
        }
        }

        /* Create message box */
        showCritical(QString("Unable to prepare the measurement on spectrometer %1.").
                     arg(serialNumber),
                     QString("File:\t%1\nFunction:\t%2\nLine:\t%3\n\nint AVS_PrepareMeasure(AvsHandle a_hDevice, MeasConfigType* a_pMeasConfig) returned %4.").
                     arg(__FILE__, __FUNCTION__, QString::number(__LINE__-86), errorCode));

        /* Failure */
        return false;
    }

    /* Successful */
    return true;
}

/**
 * @brief Start measurement on the spectrometer
 * @param[in] a_hWnd Window handle
 * @param[in] a_Nmsr Number of measurement (-1: infinite)
 * @return TRUE if successful, else FALSE
 */
bool Spectrometer::startMeasurement(short numMeasurements)
{
    /* Already running a measurement? */
    if (bMeasuring)
    {
        /* Show warning */
        showWarning(QString("Unable to start measurement on spectrometer %1. Measurement already running.").arg(serialNumber), QString(""));
        return false;
    }

    /* Spectrometer not enabled? */
    if (!bEnabled)
    {
        /* Show warning */
        showWarning(QString("Unable to start measurement on spectrometer %1. Spectrometer not enabled.").arg(serialNumber), QString(""));
        return false;
    }

    /* Start counter */
    m_Time.start();

    int result = 0;

    /* Set up measurement callback
      * If receives -1 directly, the signal comes from Preview.
      * If receives -2 the signal comes from the polarimetry Measurement - Improvement Pending.
*/
    if(numMeasurements == -2 || numMeasurements==2){
        numMeasurements = numMeasurements - (numMeasurements/2);
        result = AVS_MeasureCallback(a_hDevice, &Application::callPolback, numMeasurements);
    }else{
        result = AVS_MeasureCallback(a_hDevice, &Application::callback, numMeasurements);
    }

    /* Call of AVS_MeasureCallback successful? */
    if (ERR_SUCCESS != result)
    {
        QString errorCode, detailedText;

        switch (result)
        {
        case ERR_INVALID_PARAMETER:
        {
            /* Set error message */
            errorCode = "ERR_INVALID_PARAMETER";
            detailedText = "Invalid parameter";
            break;
        }

        default:
        {
            /* Set error message */
            errorCode = "ERR_UNKNOWN";
            detailedText = QString("Unhandled error, code %1").arg(result);
            break;
        }
        }

        /* Create message box */
        showCritical(QString("Unable to start the measurement on spectrometer %1.").
                     arg(serialNumber),
                     QString("File:\t%1\nFunction:\t%2\nLine:\t%3\n\nint AVS_MeasureCallback(AvsHandle a_hDevice, void (*__Done)(AvsHandle*, int*), short a_Nmsr) returned %4.").
                     arg(__FILE__, __FUNCTION__, QString::number(__LINE__-30), errorCode));

        /* Not successful */
        return false;
    }

    /* Is measuring */
    if ((numMeasurements == -1) || (numberToRAM > 0))
    {
        bMeasuring = true;
    }

    /* Doing StoreToRAM? */
    if (numberToRAM > 0)
    {
        /* Disable afterwards */
        numberToRAM = 0;
    }

    /* Successful */
    return true;
}

/**
 * @brief Stop the measurement
 */
bool Spectrometer::stopMeasurement(void)
{
    /* No measurement running? */
    if (!bMeasuring)
    {
        /* Show warning */
        showWarning(QString("Unable to stop measurement on spectrometer %1. No measurement running!").arg(serialNumber), QString(""));
        return false;
    }

    /* Stop the measurement */
    int result = AVS_StopMeasure(a_hDevice);

    /* Call of AVS_StopMeasure successful? */
    if (ERR_SUCCESS != result)
    {
        QString errorCode, detailedText;

        switch (result)
        {
        case ERR_DEVICE_NOT_FOUND:
        {
            /* Set error message */
            errorCode = "ERR_DEVICE_NOT_FOUND";
            detailedText = "Opening communication failed or time-out during communication occurred.";
            break;
        }

        case ERR_INVALID_DEVICE_ID:
        {
            /* Set error message */
            errorCode = "ERR_INVALID_DEVICE_ID";
            detailedText = "AvsHandle is unknown in the DLL.";
            break;
        }

        case ERR_TIMEOUT:
        {
            /* Set error message */
            errorCode = "ERR_TIMEOUT";
            detailedText = "No answer received from device.";
            break;
        }

        case ERR_INVALID_PARAMETER:
        {
            /* Set error message */
            errorCode = "ERR_INVALID_PARAMETER";
            detailedText = "Function called with invalid parameter value.";
            break;
        }

        default:
        {
            /* Set error message */
            errorCode = "ERR_UNKNOWN";
            detailedText = QString("Unhandled error, code %1").arg(result);
            break;
        }
        }

        /* Show warning */
        showWarning(QString("Unable to stop the measurement on spectrometer %1.").
                    arg(serialNumber),
                    QString("File:\t%1\nFunction:\t%2\nLine:\t%3\n\nint AVS_StopMeasure(AvsHandle a_hDevice) returned %4.").
                    arg(__FILE__, __FUNCTION__, QString::number(__LINE__-54), errorCode));

        /* Failure */
        return false;
    }

    /* Successful; not measuring anymore */
    return (bMeasuring = false);
}

/**
 * @brief Handle update event
 */
void Spectrometer::handleEvent(void)
{
    /* Get counts per second */
    if (ERR_SUCCESS == AVS_GetScopeData(a_hDevice, &l_Time, a_pSpectrum))
    {
        /* Get saturated pixels */
        if (ERR_SUCCESS == AVS_GetSaturatedPixels(a_hDevice, a_pSaturated))
        {
            saturated = false;

            unsigned int j = 0;

            /* Loop through pixel values */
            for (j = 0; j <= (unsigned int)(a_pDeviceData->m_StandAlone.m_Meas.m_StopPixel - a_pDeviceData->m_StandAlone.m_Meas.m_StartPixel); j++)
            {
                saturated = saturated || (0 != a_pSaturated[j]);
            }
        }

        /* Increment number of measurements */
        measCount++;

        /* Restart timer */
        m_Time.restart();
    }
}

/**
 * @brief Get spectrometer handle
 * @return Spectrometer handle
 */
AvsHandle Spectrometer::getHandle(void)
{
    return a_hDevice;
}

/**
 * @brief Are detector elements saturated?
 * @return FALSE if there are no saturated detector elements
 */
bool Spectrometer::isSaturated(void)
{
    return saturated;
}

/**
 * @brief Is a measurement running?
 * @return TRUE if a measurement is running
 */
bool Spectrometer::isMeasuring(void)
{
    return bMeasuring;
}

/**
 * @brief Set spectrometer enabled
 * @param[in] value TRUE to enable, else FALSE
 */
void Spectrometer::setEnabled(bool value)
{
    bEnabled = value;
}

/**
 * @brief Is spectrometer enabled?
 * @return TRUE if enabled, ELSE false
 */
bool Spectrometer::isEnabled(void)
{
    return bEnabled;
}

/**
 * @brief Get time elapsed since last update
 * @return Time elepased since last update in milliseconds
 */
qint64 Spectrometer::getTimeElapsed(void)
{
    return m_Time.elapsed();
}

/**
 * @brief Get pointer to array of wavelengths
 * @return Pointer to array of wavelengths
 */
double* Spectrometer::getWavelengths(void)
{
    return a_pWavelength;
}

/**
 * @brief Get pointer to array of counts per second
 * @return Pointer to array of counts per second
 */
double* Spectrometer::getCounts(void)
{
    return a_pSpectrum;
}

/**
 * @brief Get minimum of counts
 * @return Minimum counts of current spectrum
 */
double Spectrometer::getMinCounts(void)
{
    return getMinimum(a_pSpectrum, a_pNumPixels);
}

/**
 * @brief Get mean of counts
 * @return Mean counts of current spectrum
 */
double Spectrometer::getMeanCounts(void)
{
    return getMinimum(a_pSpectrum, a_pNumPixels);
}

/**
 * @brief Get maximum of counts
 * @return Maximum counts of current spectrum
 */
double Spectrometer::getMaxCounts(void)
{
    return getMaximum(a_pSpectrum, a_pNumPixels);
}

/**
 * @brief Get number of measurements done
 * @return Number of measurements done
 */
unsigned long Spectrometer::getMeasCount(void)
{
    return measCount;
}

/**
 * @brief Get pointer to wavelengths and counts
 * @param wavelengths Pointer to array of wavelengths
 * @param counts Pointer to array of counts
 */
void Spectrometer::getData(double *wavelengths, double *counts)
{
    *wavelengths = *a_pWavelength;
    *counts = *a_pSpectrum;
}

/**
 * @brief Set current spectrum as dark spectrum
 */
void Spectrometer::setDarkSpectrum(void)
{
    /* Clear dark spectrum */
    clearDarkSpectrum();

    /* Allocate memory for dark spectrum */
    a_pDarkSpectrum = new double[a_pNumPixels];

    /* Save current spectrum as dark spectrum */
    memcpy(a_pDarkSpectrum, a_pSpectrum, a_pNumPixels * sizeof(double));

    /* Save current integration time */
    fDarkIntegrationTime = a_pDeviceData->m_StandAlone.m_Meas.m_IntegrationTime;
}

/**
 * @brief Clear dark spectrum
 */
void Spectrometer::clearDarkSpectrum(void)
{
    /* Memory for dark spectrum allocated? */
    if (nullptr != a_pDarkSpectrum)
    {
        /* Delete old structure because number of pixels can be changed */
        delete[] a_pDarkSpectrum;
        a_pDarkSpectrum = nullptr;

        /* Reset integration time */
        fDarkIntegrationTime = 0.0f;
    }
}

/**
 * @brief Has dark spectrum saved?
 * @return TRUE if dark spectrum saved, else FALSE
 */
bool Spectrometer::hasDarkSpectrum(void)
{
    return (nullptr != a_pDarkSpectrum);
}

/**
 * @brief Get dark spectrum
 * @return Pointer to array of counts
 */
double *Spectrometer::getDarkCounts(void)
{
    return a_pDarkSpectrum;
}

/**
 * @brief Get normalized counts per second
 * @return
 */
double *Spectrometer::getNormalizedCountsPerSecond(void)
{
    /* Has dark spectrum saved? */
    if (nullptr == a_pDarkSpectrum)
    {
        /* Show warning */
        showWarning(QString("No dark spectrum saved yet"), QString("getNormalizedCountsPerSecond"));
        return nullptr;
    }

    if (fDarkIntegrationTime != a_pDeviceData->m_StandAlone.m_Meas.m_IntegrationTime)
    {
        /* Show warning */
        showWarning(QString("Dark spectrum has different integration time compared to current spectrum"), QString("getNormalizedCountsPerSecond"));
        return nullptr;
    }

    double *spectrum = new double[a_pNumPixels];

    unsigned int i = 0;

    for (i = 0; i < a_pNumPixels; i++)
    {
        spectrum[i] = *(a_pSpectrum+i) - *(a_pDarkSpectrum+i);

        if (spectrum[i] < 0) { spectrum[i] = 0; }

        spectrum[i] = spectrum[i] * 1000.0 / (double)a_pDeviceData->m_StandAlone.m_Meas.m_IntegrationTime;
    }

    if (a_pDeviceData->m_Detector.m_NLEnable)
    {
        double ADCFactor = bUseHighResADC ? 0.25 : 1.0;

        for (i = 0; i < a_pNumPixels; i++)
        {
            spectrum[i] = a_pDeviceData->m_Detector.m_aNLCorrect[0] +
                    a_pDeviceData->m_Detector.m_aNLCorrect[1] * (ADCFactor * spectrum[i]) +
                    a_pDeviceData->m_Detector.m_aNLCorrect[2] * pow(ADCFactor * spectrum[i], 2) +
                    a_pDeviceData->m_Detector.m_aNLCorrect[3] * pow(ADCFactor * spectrum[i], 3) +
                    a_pDeviceData->m_Detector.m_aNLCorrect[4] * pow(ADCFactor * spectrum[i], 4) +
                    a_pDeviceData->m_Detector.m_aNLCorrect[5] * pow(ADCFactor * spectrum[i], 5) +
                    a_pDeviceData->m_Detector.m_aNLCorrect[6] * pow(ADCFactor * spectrum[i], 6) +
                    a_pDeviceData->m_Detector.m_aNLCorrect[7] * pow(ADCFactor * spectrum[i], 7);
        }
    }
    return spectrum;
}

/**
 * @brief Save current spectrum to disk
 * @param[in] fileName Path to file
 * @return TRUE if successful, else FALSE
 */
bool Spectrometer::saveData(QString fileName)
{
    /* Open file for writing */
    FILE *file = fopen(fileName.toLatin1().data(), "wt");

    /* Check handle */
    if (nullptr == file)
    {
        /* Show message */
        showCritical(QString("Unable to create file '%1'.").arg(fileName), QString(""));
        return false;
    }

    /*
     * Write file header
     */

    /* Write serial number */
    fprintf(file, "Serial number: %s\n", getSerialNumber().toLatin1().data());

    /* Check for readable name */
    if (hasReadableName())
    {
        /* Write readable name */
        fprintf(file, "Readable name: %s\n", getReadableName().toLatin1().data());
    }

    /* Write integration time, number of averages and dynamic dark correction */
    fprintf(file, "Integration time: %.2f ms\n", getIntegrationTime());
    fprintf(file, "Number of averages: %i\n", getNumberOfAverages());
    fprintf(file, "Dynamic dark correction: %s\n", getDynamicDarkCorrection() ? "true" : "false");
    fprintf(file, "Timestamp: %s\n\n", QDateTime::currentDateTime().toString().toLatin1().data());

    /* Write header for spectral data */
    fprintf(file, "Wavelength\tCounts\n");

    unsigned int i = 0;

    /* Loop through pixel values */
    for (i = getStartPixel(); i < getStopPixel(); i++)
    {
        /* Write wavelength and counts */
        fprintf(file, "%.2f\t\t%.2f\n", *(a_pWavelength + i), *(a_pSpectrum + i));
    }

    /* Close file */
    fclose(file);

    /* Success */
    return true;
}

/**
 * @brief Destructor of 'Spectrometer' class
 */
Spectrometer::~Spectrometer(void)
{
    /* Stop measurement and reset handle */
    AVS_StopMeasure(a_hDevice);

    /* Memory reserved for wavelengths? */
    if (nullptr != a_pWavelength)
    {
        /* Delete old structure */
        delete[] a_pWavelength;
        a_pWavelength = nullptr;
    }

    /* Memory reserved for spectrum? */
    if (nullptr != a_pSpectrum)
    {
        /* Delete old structure */
        delete[] a_pSpectrum;
        a_pSpectrum = nullptr;
    }

    /* Memory reserved for saturated pixels? */
    if (nullptr != a_pSaturated)
    {
        /* Delete old structure */
        delete[] a_pSaturated;
        a_pSaturated = nullptr;
    }

    /* Clear dark spectrum */
    clearDarkSpectrum();

    /* Go to spectrometer group */
    settings->beginGroup(serialNumber);

    /* Check for readable name */
    if (hasReadableName())
    {
        /* Write readable name to configuration file */
        settings->setValue(QString("ReadableName"), readableName);
    }

    /* Write start and stoppixel to configuration file */
    settings->setValue(QString("StartPixel"), getStartPixel());
    settings->setValue(QString("StopPixel"), getStopPixel());

    /* Write integration time and delay to configuration file; in the Avantes AvaSpec library, these information are saved in milliseconds.
     * So the values have to be converted into seconds. */
    settings->setValue(QString("IntegrationTime"), QString::number(getIntegrationTime() / 1000.0f, 'e', 2));
    settings->setValue(QString("IntegrationDelay"), QString::number(getIntegrationDelay() / 1000.0f, 'e', 2));

    /* Write number of averages to configuration file */
    settings->setValue(QString("NumberOfAverages"), getNumberOfAverages());

    /* Write dynamic dark correction to configuration file */
    settings->setValue(QString("DynamicDarkCorrection"), getDynamicDarkCorrection() ? QString("true") : QString("false"));
    settings->setValue(QString("ForgetPercentage"), getForgetPercentage());

    /* Write high-resolution ADC flag to configuration file */
    settings->setValue(QString("UseHighResADC"), bUseHighResADC ? QString("true") : QString("false"));

    /* Write extended non-linearity correction to configuration file */
    settings->setValue(QString("NonLinearityCorrection"), getNonLinearityCorrection() ? QString("true") : QString("false"));

    /* Close open group */
    settings->endGroup();

    /* Close the communication with selected spectrometer */
    AVS_Deactivate(a_hDevice);
}
