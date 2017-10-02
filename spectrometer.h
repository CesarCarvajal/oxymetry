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

#ifndef SPECTROMETER_H
#define SPECTROMETER_H

/* External includes */
#include <QString>
#include <QElapsedTimer>

/* Qwt library */
#include "qwt_plot_curve.h"

/* Avantes AvaSpec library */
#include "avaspec.h"

/**
 * @brief The 'Spectrometer' class
 */
class Spectrometer
{
public:
    /* Constructor */
    explicit Spectrometer(AvsIdentityType* a_pDeviceId);

    /* Get serial number */
    QString getSerialNumber(void);

    /* Get, set or check readable name */
    QString getReadableName(void);
    void setReadableName(QString value);
    bool hasReadableName(void);

    /* Show configuration or EEPROM dialog */
    void showEEPROM(void);

    /* Forces StoreToRAM at next measurement with given number of measurements */
    void forceStoreToRAM(QString path, unsigned short numberOfMeasurements);
    QString getStoreToRAMPath(void);

    /* Prepare, start or stop a measurement */
    bool prepareMeasurement(void);
    bool startMeasurement(short numMeasurements);
    bool stopMeasurement(void);

    /* Handle updates */
    void handleEvent(void);

    /* Get number of detector elements */
    unsigned short getNumberOfPixels(void);

    /* Get or set start pixel */
    unsigned short getStartPixel(void);
    void setStartPixel(unsigned short value);

    /* Get or set stop pixel */
    unsigned short getStopPixel(void);
    void setStopPixel(unsigned short value);

    /* Get start or stop wavelength */
    double getStartWavelength(void);
    double getStopWavelength(void);

    /* Get or set integration time */
    float getIntegrationTime(void);
    void setIntegrationTime(float value);

    /* Get or set integration delay */
    float getIntegrationDelay(void);
    void setIntegrationDelay(float value);

    /* Get or set number of averages */
    int getNumberOfAverages(void);
    void setNumberOfAverages(int value);

    /* Get time per measurement */
    float getTimePerMeasurement(void);

    /* Get or set dynamic dark correction */
    void setDynamicDarkCorrection(bool enabled);
    bool getDynamicDarkCorrection(void);

    /* Get or set forget percentage */
    void setForgetPercentage(unsigned char value);
    unsigned char getForgetPercentage(void);

    /* Get or set non-linearity correction */
    void setNonLinearityCorrection(bool enabled);
    bool getNonLinearityCorrection(void);

    /* Get or set high resolution ADC */
    void setUseHighResADC(bool enabled);
    bool getUseHighResADC(void);

    /* Is the detector saturated? */
    bool isSaturated(void);

    /* Is the spectrometer measuring? */
    bool isMeasuring(void);

    /* Enable spectrometer/get enabled status */
    void setEnabled(bool value);
    bool isEnabled(void);

    /* Get time elapsed since last update in milliseconds */
    qint64 getTimeElapsed(void);

    /* Get pointer to wavelengths/counts */
    double *getWavelengths(void);
    double *getCounts(void);
    void getData(double *wavelengths, double *counts);

    /* Get counts statistics */
    double getMinCounts(void);
    double getMeanCounts(void);
    double getMaxCounts(void);

    /* Get total number of measurements */
    unsigned long getMeasCount(void);

    /* Set current spectrum as dark spectrum */
    void setDarkSpectrum(void);

    /* Clear saved dark spectrum */
    void clearDarkSpectrum(void);

    /* Check if dark spectrum saved */
    bool hasDarkSpectrum(void);

    /* Get dark spectrum counts */
    double *getDarkCounts(void);

    double *getNormalizedCountsPerSecond(void);

    bool saveData(QString fileName);

    /* Get device handle */
    AvsHandle getHandle(void);

    /* Destructor */
    ~Spectrometer(void);

    bool bMeasuring = false;            /* Running a measurement */

private:
    AvsHandle a_hDevice = INVALID_AVS_HANDLE_VALUE;

    /* Serial number and readable name */
    QString serialNumber, readableName;

    char a_pFPGAVersion[16];            /* FPGA software version */
    char a_pFirmwareVersion[16];        /* Microcontroller software version */
    char a_pDLLVersion[16];             /* DLL software version */

    unsigned short a_pNumPixels;        /* Number of detector elements */

    EthernetSettingsType a_Data;        /* Ethernet settings */

    DeviceConfigType* a_pDeviceData = nullptr;

    double *a_pWavelength = nullptr;    /* Array containing wavelengths */
    double *a_pSpectrum = nullptr;      /* Array containing counts */
    uint8 *a_pSaturated = nullptr;      /* Array containing saturation status */

    double *a_pDarkSpectrum = nullptr;  /* Array containing dark counts */
    float fDarkIntegrationTime = 0.0f;  /* Integration time of dark spectrum */

    bool saturated = false;             /* Are there saturated pixels? */
    bool bEnabled = false;              /* Spectrometer enabled */

    bool bUseHighResADC = true;         /* High-resolution ADC enabled? */

    unsigned long measCount = 0;        /* Total number of measurements */

    /* 0: No StoreToRAM at next measurement, else number of StoreToRAM measurements */
    unsigned short numberToRAM = 0;

    /* Path of StoreToRAM file */
    QString storeToRAMPath;

    QElapsedTimer m_Time;
    unsigned int l_Time = 0;
};

#endif // SPECTROMETER_H
