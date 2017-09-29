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
#include <QString>
#include <QFileDialog>
#include <QSettings>
#include <stdio.h>
#include <stdlib.h>

/* Internal includes */
#include "application.h"
#include "spectrometer.h"
#include "messages.h"
#include "math_helper.h"
#include "iad_configure.h"
#include "iad_configure_page01.h"
#include "ui_iad_configure_page01.h"
#include "iad_configure_page02.h"
#include "ui_iad_configure_page02.h"

/*
 * Global variables
 */
extern QSettings *settings;
extern Spectrometer** ptrSpectrometers;
extern unsigned int m_NrDevices;

double *RstdWavelengths = nullptr;
double *RstdCounts = nullptr;

/**
 * @brief Constructor of 'ConfigureIAD' class
 */
ConfigureIAD::ConfigureIAD(QString fileName)
{
    /* Not configured yet */
    isConfigured = false;

    /*
     * At least 2 spectrometers are required for the Inverse Adding-Doubling method, so check
     * the number of connected devices first before showing the configuration dialog.
     */

    /* Do we have less than 2 spectrometer? */
    if (m_NrDevices < 2)
    {
        /* Show message */
        showCritical("At least 2 spectrometers are required for the Inverse Adding-Doubling method.", NULL);
        return;
    }

    /*
     * Show the first configuration page
     */

    /* Create first configuration assistant page */
    ConfigureIADPage01 *page01 = new ConfigureIADPage01();

    /* Path to configuration file given as argument? */
    if (NULL != fileName)
    {
        /* Load settings from configuration file */
        page01->load(fileName);
    }

    /* Run first page and check result */
    if (QDialog::Accepted == page01->exec())
    {
        /*
         * The user has finished the first configuration page. Change the
         * spectrometer names from serial numbers to more readable names.
         */
        unsigned int i = 0;

        /* Loop through devices */
        for (i = 0; i < m_NrDevices; i++)
        {
            /* Is the current device used for measurement of diffuse reflection? */
            if (!QString::compare(ptrSpectrometers[i]->getSerialNumber(), page01->ui->combo_diffuseReflection->currentText(), Qt::CaseInsensitive))
            {
                ptrSpectrometers[i]->setReadableName(QString("Diffuse reflection"));
            }
            /* Or is the current device used for measurement of diffuse transmission? */
            else if (!QString::compare(ptrSpectrometers[i]->getSerialNumber(), page01->ui->combo_diffuseTransmission->currentText(), Qt::CaseInsensitive))
            {
                ptrSpectrometers[i]->setReadableName(QString("Diffuse transmission"));
            }
            /* Or is the current device used for measurement of unscattered transmission? */
            else if (!QString::compare(ptrSpectrometers[i]->getSerialNumber(), page01->ui->combo_unscatteredTransmission->currentText(), Qt::CaseInsensitive))
            {
                ptrSpectrometers[i]->setReadableName(QString("Unscattered transmission"));
            }

            /* Go to spectrometer group */
            settings->beginGroup(ptrSpectrometers[i]->getSerialNumber());

            /* Write readable name rom configuration file */
            settings->setValue(QString("ReadableName"), ptrSpectrometers[i]->getReadableName());

            /* Close open group */
            settings->endGroup();
        }

        /*
         * Load database for wall coatings
         */

        /* Path to be in the search for the files; is always a subdirectory in the application path */
        QString pathCoatings(QString("%1%2").arg(QDir::currentPath(), "/database/wall coatings"));

        QDir dir(pathCoatings);

        /* Check if directory exists */
        if (!dir.exists())
        {
            /* Free memory */
            delete page01;
            page01 = nullptr;

            /* Show message */
            showCritical(QString("Database for wall coatings not found."), QString("Reference tables for wall coatings have to be in path '%1'.").arg(pathCoatings));
            return;
        }

        /* Get list of files in directory */
        QFileInfoList files = dir.entryInfoList(QDir::Files);

        QStringList listCoatings;

        /* Loop through list of files */
        foreach (QFileInfo file, files)
        {
            /* Just load the files with file extension '.dat' */
            if (!QString::compare(file.suffix(), QString("dat"), Qt::CaseSensitive))
            {
                /* Add wall coating to list */
                listCoatings.append(file.baseName());
            }
        }

        /* No files loaded from directory? */
        if (0 >= listCoatings.count())
        {
            /* Free memory */
            delete page01;
            page01 = nullptr;

            /* Show message */
            showCritical(QString("No reference tables for wall coatings found."), NULL);
            return;
        }

        /*
         * Load database for reflectance standards
         */

        /* Path to be in the search for the files; is always a subdirectory in the application path */
        QString pathStandards(QString("%1%2").arg(QDir::currentPath(), "/database/reflectance standards"));

        dir = pathStandards;

        /* Check if directory exists */
        if (!dir.exists())
        {
            /* Free memory */
            delete page01;
            page01 = nullptr;

            /* Show message */
            showCritical(QString("Database for reflectance standards not found."), QString("Reference tables for reflectance standards have to be in path '%1'.").arg(pathStandards));
            return;
        }

        /* Get list of files in directory */
        files = dir.entryInfoList(QDir::Files);

        QStringList listStandards;

        /* Loop through list of files */
        foreach (QFileInfo file, files)
        {
            /* Just load the files with file extension '.dat' */
            if (!QString::compare(file.suffix(), QString("dat"), Qt::CaseSensitive))
            {
                /* Add reflectance standard to list */
                listStandards.append(file.baseName());
            }
        }

        /* No files loaded from directory? */
        if (0 >= listStandards.count())
        {
            /* Free memory */
            delete page01;
            page01 = nullptr;

            /* Show message */
            showCritical(QString("No reference tables for reflectance standards found."), NULL);
            return;
        }

        /*
         * Show the seconds configuration page
         */

        /* Create second configuration assistant page */
        ConfigureIADPage02 *page02 = new ConfigureIADPage02();

        /* Add reflectance standards and wall materials; let the user choose */
        page02->ui->comboBox_calibrationStandard->addItems(listStandards);
        page02->ui->comboBox_rSphereWallMaterial->addItems(listCoatings);
        page02->ui->comboBox_tSphereWallMaterial->addItems(listCoatings);

        /* Path to configuration file given as argument? */
        if (NULL != fileName)
        {
            /* Load settings from configuration file */
            page02->load(fileName);
        }

        /* Run second page */
        if (QDialog::Accepted == page02->exec())
        {
            QString path = QString("%1%2%3.dat").arg(QDir::currentPath(), "/database/reflectance standards/", page02->ui->comboBox_calibrationStandard->currentText());

            FILE *file = fopen(path.toLatin1(), "rt");

            if (nullptr == file)
            {
                showWarning(path, "");
                return;
            }

            int ch, number_of_lines = 0;

            do
            {
                ch = fgetc(file);
                if(ch == '\n')
                    number_of_lines++;
            } while (ch != EOF);

            // last line doesn't end with a new line!
            // but there has to be a line at least before the last line
            if(ch != '\n' && number_of_lines != 0)
                number_of_lines++;

            double *wavelengths = new double[number_of_lines];
            double *counts = new double[number_of_lines];

            rewind(file);

            char line[100];
i = 0;
            while(fgets(line, 100, file) != NULL)
            {
                sscanf(line, "%lf %lf", &wavelengths[i], &counts[i]);
                i++;
            }
           // showWarning(QString("Wavelength: %1, value: %2").arg(QString::number(wavelengths[0]), QString::number(counts[0])), NULL);

double toInterpolate[] = {  553.57, 600.54 };

double *result = interp1(wavelengths, counts, toInterpolate, number_of_lines, 2);

if (nullptr == result) {
    fclose(file);
    file = nullptr;
    delete[] wavelengths;
    wavelengths = nullptr;
    delete[] counts;
    counts = nullptr;
    showCritical(QString("CRITICAL"), NULL);
    return; }

unsigned int num = 2;

for (i = 0; i < num; i++)
{
    showWarning(QString("Wavelength: %1, value: %2").arg(QString::number(toInterpolate[i]), QString::number(result[i])), NULL);
}

delete[] wavelengths;
wavelengths = nullptr;
delete[] counts;
counts = nullptr;

//delete result;
//result = nullptr;


            fclose(file);
            file = nullptr;

            /* Create new configuration file? */
            if (NULL == fileName)
            {
                /* Let the user choose path and filename */
                fileName = QFileDialog::getSaveFileName(NULL, QString("Save configuration"), "./config", QString("Configuration file (*.cfg)"));

                /* User quit dialog */
                if (NULL == fileName)
                {
                    /* Free memory */
                    delete page02;
                    page02 = nullptr;

                    return;
                }
            }

            /* Remember configuration path */
            configPath = fileName;

            /* Save settings to configuration file */
            page01->save(fileName);
            page02->save(fileName);

            /* Configuration successful */
            isConfigured = true;
        }

        /* Free memory */
        delete page02;
        page02 = nullptr;
    }

    /* Free memory */
    delete page01;
    page01 = nullptr;
}

/**
 * @brief Get 'is configured' status
 * @return TRUE if user has successfully run the assistant, else FALSE
 */
bool ConfigureIAD::getIsConfigured(void)
{
    return isConfigured;
}

/**
 * @brief Get configuration name
 * @return Name of configuration file
 */
QString ConfigureIAD::getConfigurationName(void)
{
    return configPath;
}

/**
 * @brief Destructor of 'ConfigureIAD' class
 */
ConfigureIAD::~ConfigureIAD(void)
{
}
