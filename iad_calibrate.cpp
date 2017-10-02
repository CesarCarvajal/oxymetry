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

/* Internal includes */
#include "application.h"
#include "spectrometer.h"
#include "messages.h"
#include "light_control.h"
#include "iad_calibrate_page01.h"
#include "iad_calibrate_page02.h"
#include "iad_calibrate_page03.h"
#include "iad_calibrate.h"

/*
 * Global variables
 */
extern Spectrometer** ptrSpectrometers;
extern unsigned int m_NrDevices;
extern ControlLight* lightSource;

/**
 * @brief Constructor of 'CalibrateIAD' class
 */
CalibrateIAD::CalibrateIAD(double *Rd_factor, double *Td_factor, double *Tu_factor)
{
    /* Check spectrometer count */
    if (m_NrDevices < 3)
    {
        QString errorCode = (m_NrDevices < 2) ? "At least 2 spectrometers are required for Inverse Adding-Doubling." :\
                                                "At least 3 spectrometers are required for full Inverse Adding-Doubling.";

        /* Show message box */
        showCritical(errorCode, QString(""));
        return;
    }

    /* No light source toolkit? */
    if (nullptr == lightSource)
    {
        /* Show message box */
        showCritical(QString("Calibration requires a connected light source."), QString(""));
        return;
    }

    /* Light source connected? */
    if (!lightSource->getIsConnected())
    {
        /* Show message box */
        showCritical(QString("Please connect to light source and try again. Calibration requires a connected light source."), QString(""));
        return;
    }

    /* ID's of spectrometer assignments */
    unsigned int idRd = 0, idTd = 0, idTu = 0;

    unsigned int i = 0;

    /* Loop through devices */
    for (i = 0; i < m_NrDevices; i++)
    {
        /* Does the current spectrometer has a readable name? */
        if (!ptrSpectrometers[i]->hasReadableName())
        {
            /* Show message */
            showCritical(QString("Unable to get spectrometer assignment from IAD configuration!"), QString("no 'readableName' property"));
            return;
        }

        /* Check to which measured variable the current spectrometer is assigned */
        if (!QString::compare(ptrSpectrometers[i]->getReadableName(), QString("Diffuse reflection"), Qt::CaseInsensitive))
        {
            /* Current spectrometer measures 'diffuse reflection' */
            idRd = i;
        }
        else if (!QString::compare(ptrSpectrometers[i]->getReadableName(), QString("Diffuse transmission"), Qt::CaseInsensitive))
        {
            /* Current spectrometer measures 'diffuse transmission' */
            idTd = i;
        }
        else if (!QString::compare(ptrSpectrometers[i]->getReadableName(), QString("Unscattered transmission"), Qt::CaseInsensitive))
        {
            /* Current spectrometer measures 'unscattered transmission' */
            idTu = i;
        }
        else
        {
            /* Show message */
            showCritical(QString("Unable to get spectrometer assignment from IAD configuration!"), QString("Spectrometer not for reflection or transmission"));
            return;
        }
    }

    /*
     * ----------
     * First calibration step: Adjust pinhole
     * ---------------------
     */

    unsigned char status = 0;

    /* Create calibration assistant page */
    CalibrateIADPage01 *page01 = new CalibrateIADPage01();

    /* Show dialog, do calibration, close dialog */
    page01->show();
    page01->process(idTu);
    page01->close();

    /* Get status of calibration step */
    status = page01->getStatus();

    /* Free memory */
    delete page01;
    page01 = nullptr;

    /* Continue if calibration step was successful */
    if (status & PROCESS_FAILURE)
        return;

    /*
     * ----------
     * Second calibration step: Measure reflectance standard
     * ---------------------
     */

    /* Create calibration assistant page */
    CalibrateIADPage02 *page02 = new CalibrateIADPage02();

    /* Show dialog, do calibration, close dialog */
    page02->show();
    page02->process(idRd);
    page02->close();

    /* Get status of calibration step */
    status = page02->getStatus();

    /* Continue if calibration step was successful */
    if (status & PROCESS_FAILURE)
    {
        /* Free memory */
        delete page02;
        page02 = nullptr;

        return;
    }

    /*
     * ----------
     * Third calibration step: Measure counts without a sample + dark counts
     * ---------------------
     */

    /* Create calibration assistant page */
    CalibrateIADPage03 *page03 = new CalibrateIADPage03();

    /* Show dialog, do calibration, close dialog */
    page03->show();
    page03->process(idRd, idTd, idTu);
    page03->close();

    /* Get status of calibration step */
    status = page03->getStatus();

    /* Continue if calibration step was successful */
    if (status & PROCESS_FAILURE)
    {
        /* Free memory */
        delete page02;
        page02 = nullptr;

        /* Free memory */
        delete page03;
        page03 = nullptr;

        return;
    }

    /*
     * -----------------------------------------------------------
     * Allocate memory for spectra without sample (full intensity)
     * -----------------------------------------------------------
     */

    /* Check if memory allocated */
    if (nullptr != Rd_factor)
    {
        /* Free memory */
        delete[] Rd_factor;
        Rd_factor = nullptr;
    }

    /* Allocate memory for diffuse reflection (no sample) factor */
    Rd_factor = new double[ptrSpectrometers[idRd]->getNumberOfPixels()];

    /* Check if memory allocated */
    if (nullptr == Rd_factor)
    {
        /* Calibration failed */
        status |= PROCESS_FAILURE;

        /* Create message box */
        showCritical(QString("Unable to allocate memory for diffuse reflection correction factor. Calibration aborted."),
                     QString("File:\t%1\nFunction:\t%2\nLine:\t%3").arg(__FILE__, __FUNCTION__, QString::number(__LINE__-3)));

        /* Free memory */
        delete page02;
        page02 = nullptr;

        /* Free memory */
        delete page03;
        page03 = nullptr;

        return;
    }

    /* Check if memory allocated */
    if (nullptr != Td_factor)
    {
        /* Free memory */
        delete[] Td_factor;
        Td_factor = nullptr;
    }

    /* Allocate memory for diffuse transmission (no sample) factor */
    Td_factor = new double[ptrSpectrometers[idTd]->getNumberOfPixels()];

    /* Check if memory allocated */
    if (nullptr == Td_factor)
    {
        /* Calibration failed */
        status |= PROCESS_FAILURE;

        /* Create message box */
        showCritical(QString("Unable to allocate memory for diffuse transmission correction factor. Calibration aborted."),
                     QString("File:\t%1\nFunction:\t%2\nLine:\t%3").arg(__FILE__, __FUNCTION__, QString::number(__LINE__-3)));

        /* Free memory */
        delete page02;
        page02 = nullptr;

        /* Free memory */
        delete page03;
        page03 = nullptr;

        return;
    }

    /* Check if memory allocated */
    if (nullptr != Tu_factor)
    {
        /* Free memory */
        delete[] Tu_factor;
        Tu_factor = nullptr;
    }

    /* Allocate memory for unscattered transmission (no sample) factor */
    Tu_factor = new double[ptrSpectrometers[idTu]->getNumberOfPixels()];

    /* Check if memory allocated */
    if (nullptr == Tu_factor)
    {
        /* Calibration failed */
        status |= PROCESS_FAILURE;

        /* Create message box */
        showCritical(QString("Unable to allocate memory for unscattered transmission correction factor. Calibration aborted."),
                     QString("File:\t%1\nFunction:\t%2\nLine:\t%3").arg(__FILE__, __FUNCTION__, QString::number(__LINE__-3)));

        /* Free memory */
        delete page02;
        page02 = nullptr;

        /* Free memory */
        delete page03;
        page03 = nullptr;

        return;
    }

    /*
     * -------------------------------------------------------
     * Calculate correction factors for normalized intensities
     * -------------------------------------------------------
     */

    /* Loop through diffuse reflection pixels (reflection standard) */
    for (i = 0; i < ptrSpectrometers[idRd]->getNumberOfPixels(); i++)
    {
        /* Subtract dark counts from counts without sample (full intensity) */
        Rd_factor[i] = page02->getCounts()[i];// - page04->getCounts(idRd)[i];
    }

    /* Loop through diffuse transmission pixels */
    for (i = 0; i < ptrSpectrometers[idTd]->getNumberOfPixels(); i++)
    {
        /* Subtract dark counts from counts without sample (full intensity) */
        Td_factor[i] = page03->getCounts(idTd)[i];// - page04->getCounts(idTd)[i];
    }

    /* Loop through unscattered transmission pixels */
    for (i = 0; i < ptrSpectrometers[idTu]->getNumberOfPixels(); i++)
    {
        /* Subtract dark counts from counts without sample (full intensity) */
        Tu_factor[i] = page03->getCounts(idTu)[i];// - page04->getCounts(idTu)[i];
    }

    /* Free memory */
    delete page02;
    page02 = nullptr;

    /* Free memory */
    delete page03;
    page03 = nullptr;

    /* TRUE if successful, else FALSE */
    isCalibrated = true;
}

/**
 * @brief Get 'is calibrated' status
 * @return TRUE if user has successfully run the assistant, else FALSE
 */
bool CalibrateIAD::getIsCalibrated(void)
{
    return isCalibrated;
}

/**
 * @brief Destructor of 'CalibrateIAD' class
 */
CalibrateIAD::~CalibrateIAD(void)
{
    /* Nothing */
}
