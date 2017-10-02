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
#include <QFileDialog>
#include <QString>
#include <QDate>
#include <QTime>
#include <stdio.h>

/* Internal includes */
#include "application.h"
#include "spectrometer.h"
#include "messages.h"
#include "iad_measure.h"

/*
 * Global variables
 */
extern Spectrometer** ptrSpectrometers;
extern unsigned int m_NrDevices;

/**
 * @brief Constructor of 'MeasureIAD' class
 */
MeasureIAD::MeasureIAD(void)
{
}

/**
 * @brief Gets measurement name
 * @return Measurement name
 */
QString MeasureIAD::getName(void)
{
    return name;
}

/**
 * @brief Sets measurement name
 * @param name Measurement name
 */
void MeasureIAD::setName(QString name)
{
    this->name = name;
}

/**
 * @brief Gets measurement description
 * @return Measurement description
 */
QString MeasureIAD::getDescription(void)
{
    return description;
}

/**
 * @brief Sets measurement description
 * @param description Measurement description
 */
void MeasureIAD::setDescription(QString description)
{
    this->description = description;
}

/**
 * @brief Runs measurement
 * @return TRUE if successful, else FALSE
 */
bool MeasureIAD::measure(void)
{
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
            showCritical(QString("Unable to get spectrometer assignment from IAD configuration file."), NULL);
            return false;
        }

        /* Check to which measured variable the current spectrometer is assigned */
        if (!QString::compare(ptrSpectrometers[i]->getReadableName(), QString("Diffuse reflectance"), Qt::CaseInsensitive))
        {
            /* Current spectrometer measures 'diffuse reflection' */
            idRd = i;
        }
        else if (!QString::compare(ptrSpectrometers[i]->getReadableName(), QString("Diffuse transmittance"), Qt::CaseInsensitive))
        {
            /* Current spectrometer measures 'diffuse transmission' */
            idTd = i;
        }
        else if (!QString::compare(ptrSpectrometers[i]->getReadableName(), QString("Unscattered transmittance"), Qt::CaseInsensitive))
        {
            /* Current spectrometer measures 'unscattered transmission' */
            idTu = i;
        }
    }

    unsigned int id[3] = { idRd, idTd, idTu };

    /* Loop through devices */
    for (i = 0; i < 3; i++)
    {
        /* Set averaging to one spectra and enable dynamic dark correction */
        //ptrSpectrometers[id[i]]->setIntegrationTime(intTime);
        //ptrSpectrometers[id[i]]->setNumberOfAverages(1);
        //ptrSpectrometers[id[i]]->setDynamicDarkCorrection(true);

        /* Prepare measurement; only continue if successful */
        if (ptrSpectrometers[id[i]]->prepareMeasurement())
        {
            /* Measure one spectra */
            ptrSpectrometers[id[i]]->startMeasurement(1);

            /* Handle events and update UI */
            Application::processEvents();
        }

        /* Get maximum counts from last spectrum */
        if (ptrSpectrometers[id[i]]->isSaturated())
        {
            /* Show message */
            showCritical(QString("Spectrometer is saturated!"), NULL);
            return false;
        }
        ptrSpectrometers[id[i]]->saveData(QString("Bla-%1.txt").arg(i));
    }
    return true;
}

/**
 * @brief Saves measurement data
 * @return TRUE if successful, else FALSE
 */
bool MeasureIAD::save(QString fileName)
{
    if (fileName.isEmpty())
    {
        /* Let the user choose path and filename */
        fileName = QFileDialog::getSaveFileName(nullptr, QString("Save measurement"), "./measure", QString("Measurement file (*.meas)"));

        /* User quit dialog */
        if (NULL == fileName)
        {
            /* Failure */
            return false;
        }
    }

    /* Open file to save measurement */
    FILE *file = fopen(fileName.toLatin1().data(), "wt");

    /* Error opening file */
    if (nullptr == file)
    {
        /* Show message */
        showCritical(QString("Unable to create measurement file."), QString("The file '%1' could not be created.").arg(fileName));
        return false;
    }

    date = QDate::currentDate();
    time = QTime::currentTime();

    fprintf(file, "IAD1   # Must be first four characters\n\n");

    fprintf(file, "# Name: %s\n", name.toLatin1().data());
    fprintf(file, "# Description: %s\n", description.toLatin1().data());
    fprintf(file, "\n");

    fprintf(file, "# Date: %s\n", QDate::currentDate().toString(QString("dd.MM.yyyy")).toLatin1().data());
    fprintf(file, "# Time: %s\n", QTime::currentTime().toString(QString("hh:mm:ss")).toLatin1().data());
    fprintf(file, "\n");

    /*fprintf(file, "%.2f\t# Index of refraction of the sample\n", page02->ui->doubleSpinBox_indexOfRefractionOfSample->value());
    fprintf(file, "%.2f\t# Index of refraction of the top and bottom slides\n", page02->ui->doubleSpinBox_indexOfRefractionOfTopSlide->value());
    fprintf(file, "%.1f\t# [mm] Thickness of sample\n", page02->ui->doubleSpinBox_thicknessOfSample->value());
    fprintf(file, "%.1f\t# [mm] Thickness of slides\n", page02->ui->doubleSpinBox_thicknessOfSlides->value());
    fprintf(file, "%.1f\t# [mm] Diameter of illumination beam\n", page02->ui->doubleSpinBox_diameteOfIlluminationBeam->value());
    fprintf(file, "%.2f\t# Reflectivity of the reflectance calibration standard\n\n", 0.1f);

    fprintf(file, "%i\t# Number of spheres used during each measurement\n\n", 2);

    fprintf(file, "\t# Properties of sphere used for reflection measurement\n");
    fprintf(file, "%.1f\t# [mm] Sphere Diameter\n", page02->ui->doubleSpinBox_rSphereDiameter->value());
    fprintf(file, "%.1f\t# [mm] Sample Port Diameter\n", page02->ui->doubleSpinBox_rSamplePortDiameter->value());
    fprintf(file, "%.1f\t# [mm] Entrance Port Diameter\n", page02->ui->doubleSpinBox_rEntrancePortDiameter->value());
    fprintf(file, "%.2f\t# [mm] Detector Port Diameter\n", page02->ui->doubleSpinBox_rDetectorPortDiameter->value());
    fprintf(file, "%.1f\t# Reflectivity of the sphere wall\n\n", 0.98);

    fprintf(file, "\t# Properties of sphere used for transmission measurement\n");
    fprintf(file, "%.1f\t# [mm] Sphere Diameter\n", page02->ui->doubleSpinBox_tSphereDiameter->value());
    fprintf(file, "%.1f\t# [mm] Sample Port Diameter\n", page02->ui->doubleSpinBox_tSamplePortDiameter->value());
    fprintf(file, "%.1f\t# [mm] Entrance Port Diameter\n", page02->ui->doubleSpinBox_tEntrancePortDiameter->value());
    fprintf(file, "%.2f\t# [mm] Detector Port Diameter\n", page02->ui->doubleSpinBox_tDetectorPortDiameter->value());
    fprintf(file, "%.1f\t# Reflectivity of the sphere wall\n\n", 0.98);

    fprintf(file, "6\t# Number of measurements\n\n");

    fprintf(file, "# %s\t\t%s\n", "wavelength in nm", "M_R");*/

    /* Close file */
    fclose(file);

    /* Successful */
    return true;
}

QDate MeasureIAD::getDate(void)
{
    return date;
}

QTime MeasureIAD::getTime(void)
{
    return time;
}

/**
 * @brief Destructor of 'MeasureIAD' class
 */
MeasureIAD::~MeasureIAD(void)
{
    /* Nothing */
}
