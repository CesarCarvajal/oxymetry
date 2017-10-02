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
#include <QSettings>
#include <QWidget>
#include <QDialog>
#include <QString>
#include <QComboBox>

/* Internal includes */
#include "application.h"
#include "spectrometer.h"
#include "messages.h"
#include "iad_configure_page01.h"
#include "ui_iad_configure_page01.h"

/*
 * Global variables
 */
extern QSettings *settings;
extern Spectrometer** ptrSpectrometers;
extern unsigned int m_NrDevices;

/**
 * @brief Constructor of 'ConfigureIADPage01' class
 * @param parent Parent widget
 */
ConfigureIADPage01::ConfigureIADPage01(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfigureIADPage01)
{
    /* Set up user interface */
    ui->setupUi(this);

    /* Set window flags */
    this->setWindowFlags(Qt::Dialog | Qt::WindowTitleHint | Qt::WindowStaysOnTopHint);

    /* Disable resize of elements */
    this->setFixedSize(this->size());

    /* Limited IAD possible? */
    if (m_NrDevices < 3)
    {
        /* User can't measure unscattered transmittance */
        ui->combo_unscatteredTransmission->clear();
        ui->combo_unscatteredTransmission->addItem("No spectrometer");
    }

    unsigned int i = 0;

    /* Add serial numbers of activated spectrometers to diffuse reflectance combo box */
    for (i = 0; i < m_NrDevices; i++)
    {
        ui->combo_diffuseReflection->addItem(ptrSpectrometers[i]->getSerialNumber());
    }

    /* Make checkboxes transparent for mouse events */
    ui->checkBox_absorptionCoefficient->setAttribute(Qt::WA_TransparentForMouseEvents);
    ui->checkBox_scatteringCoefficient->setAttribute(Qt::WA_TransparentForMouseEvents);
    ui->checkBox_reducedScatteringCoefficient->setAttribute(Qt::WA_TransparentForMouseEvents);
    ui->checkBox_anisotropy->setAttribute(Qt::WA_TransparentForMouseEvents);

    /* Don't allow checkboxes to get focus */
    ui->checkBox_absorptionCoefficient->setFocusPolicy(Qt::NoFocus);
    ui->checkBox_scatteringCoefficient->setFocusPolicy(Qt::NoFocus);
    ui->checkBox_reducedScatteringCoefficient->setFocusPolicy(Qt::NoFocus);
    ui->checkBox_anisotropy->setFocusPolicy(Qt::NoFocus);

    /* Connect combo box signal handles */
    connect(ui->combo_diffuseReflection, SIGNAL(currentIndexChanged(int)), this, SLOT(update()));
    connect(ui->combo_diffuseTransmission, SIGNAL(currentIndexChanged(int)), this, SLOT(update()));
    connect(ui->combo_unscatteredTransmission, SIGNAL(currentIndexChanged(int)), this, SLOT(update()));

    /* Connect button signal handles */
    connect(ui->button_cancel, SIGNAL(clicked(bool)), this, SLOT(cancel()));
    connect(ui->button_next, SIGNAL(clicked(bool)), this, SLOT(next()));
}

/**
 * @brief Loads settings from configuration file
 * @param fileName Path to configuration file
 */
void ConfigureIADPage01::load(QString fileName)
{
    /* Invalid file name? */
    if (NULL == fileName)
        return;

    /* Open configuration file */
    QSettings *config = new QSettings(fileName, QSettings::IniFormat);

    /* Import from [Setup] group */
    config->beginGroup(QString("Setup"));

    QString Rd, Td, Tu;

    /* If available, get assigned spectrometer serial numbers from configuration file */
    Rd = config->value(QString("DiffuseReflection"), QString("")).toString();
    Td = config->value(QString("DiffuseTransmission"), QString("")).toString();
    Tu = config->value(QString("UnscatteredTransmission"), QString("")).toString();

    /* Finish import */
    config->endGroup();

    /* Close file */
    delete config;
    config = nullptr;

    /*
     * Select assigned spectrometers from combo boxes
     */

    unsigned int i = 0; unsigned char j = 0;

    /* Loop through devices */
    for (i = 0; i < m_NrDevices; i++)
    {
        int result = 0;

        /* Found an entry for diffuse reflectance in configuration file? */
        if (!Rd.isEmpty())
        {
            /* Not assigned yet? */
            if (!(j & 1))
            {
                /* Get index of spectrometer for diffuse reflectance in combo box */
                result = ui->combo_diffuseReflection->findText(Rd, Qt::MatchContains);

                /* Spectrometer connected? */
                if (-1 != result)
                {
                    /* Select spectrometer */
                    ui->combo_diffuseReflection->setCurrentIndex(result);

                    /* Assigned spectrometer is connected */
                    j |= 1;
                }
            }
        }

        /* Found an entry for diffuse transmittance in configuration file? */
        if (!Td.isEmpty())
        {
            /* Not assigned yet? */
            if (!(j & 2))
            {
                /* Get index of spectrometer for diffuse transmittance in combo box */
                result = ui->combo_diffuseTransmission->findText(Td, Qt::MatchContains);

                /* Spectrometer connected? */
                if (-1 != result)
                {
                    /* Select spectrometer */
                    ui->combo_diffuseTransmission->setCurrentIndex(result);

                    /* Assigned spectrometer is connected */
                    j |= 2;
                }
            }
        }

        /* Found an entry for unscattered transmittance in configuration file? */
        if (!Tu.isEmpty())
        {
            /* Not assigned yet? */
            if (!(j & 4))
            {
                /* Get index of spectrometer for unscattered transmittance in combo box */
                result = ui->combo_unscatteredTransmission->findText(Tu, Qt::MatchContains);

                /* Spectrometer connected? */
                if (-1 != result)
                {
                    /* Select spectrometer */
                    ui->combo_unscatteredTransmission->setCurrentIndex(result);

                    /* Assigned spectrometer is connected */
                    j |= 4;
                }
            }
        }
    }

    /*
     * If there are assigned spectrometers which could not be found,
     * typically not connected, inform the user.
     */

    /* Spectrometer for diffuse reflectance connected? */
    if (!(j & 1))
    {
        /* Show message */
        showWarning(QString("Diffuse reflectance on spectrometer '%1' not available.").arg(Rd), NULL);
    }

    /* Spectrometer for diffuse transmittance connected? */
    if (!(j & 2))
    {
        /* Show message */
        showWarning(QString("Diffuse transmittance on spectrometer '%1' not available.").arg(Td), NULL);
    }

    /* Spectrometer for unscattered transmittance connected? */
    if (!(j & 4))
    {
        /* Show message */
        showWarning(QString("Unscattered transmittance on spectrometer '%1' not available.").arg(Tu), NULL);
    }
}

/**
 * @brief Saves settings from configuration file
 * @param fileName Path to configuration file
 */
void ConfigureIADPage01::save(QString fileName)
{
    /* Invalid file name? */
    if (NULL == fileName)
        return;

    /* Open configuration file */
    QSettings *config = new QSettings(fileName, QSettings::IniFormat);

    /* Export to [Setup] group */
    config->beginGroup(QString("Setup"));

    /* Save assigned spectrometer serial numbers to configuration file */
    config->setValue(QString("DiffuseReflection"), ui->combo_diffuseReflection->currentText());
    config->setValue(QString("DiffuseTransmission"), ui->combo_diffuseTransmission->currentText());
    config->setValue(QString("UnscatteredTransmission"), ui->combo_unscatteredTransmission->currentText());

    /* Finish export */
    config->endGroup();

    /* Close file */
    delete config;
    config = nullptr;
}

/**
 * @brief Update combo boxes on index change
 */
void ConfigureIADPage01::update(void)
{
    QComboBox *senderComboBox = qobject_cast <QComboBox*>(sender());

    /* User selected diffuse reflection combo box */
    if (ui->combo_diffuseReflection == senderComboBox)
    {
        /* Default entry resets other combo boxes */
        if (!senderComboBox->currentIndex())
        {
            /*
             * Reset unscattered transmittance combo box
             */

            /* Remove all items in combo box */
            ui->combo_unscatteredTransmission->clear();

            /* If less than 3 spectrometers, measurement of unscattered transmittance is not possible */
            if (m_NrDevices < 3)
            {
                /* Add item to combo box */
                ui->combo_unscatteredTransmission->addItem("No spectrometer");
            }
            else
            {
                /* Add item to combo box */
                ui->combo_unscatteredTransmission->addItem("Select spectrometer");
            }

            /* Disable combo box */
            ui->combo_unscatteredTransmission->setEnabled(false);

            /*
             * Reset diffuse transmittance combo box
             */

            /* Remove all items in combo box */
            ui->combo_diffuseTransmission->clear();

            /* Add item to combo box */
            ui->combo_diffuseTransmission->addItem("Select spectrometer");

            /* Disable combo box */
            ui->combo_diffuseTransmission->setEnabled(false);
        }
        /* User selected a spectrometer */
        else
        {
            /*
             * Reset unscattered transmittance combo box
             */

            /* Remove all items in combo box */
            ui->combo_unscatteredTransmission->clear();

            /* If less than 3 spectrometers, measurement of unscattered transmittance is not possible */
            if (m_NrDevices < 3)
            {
                /* Add item to combo box */
                ui->combo_unscatteredTransmission->addItem("No spectrometer");
            }
            else
            {
                /* Add item to combo box */
                ui->combo_unscatteredTransmission->addItem("Select spectrometer");
            }

            /* Disable combo box */
            ui->combo_unscatteredTransmission->setEnabled(false);

            /*
             * Set diffuse transmittance combo box
             */

            /* Remove all items in combo box */
            ui->combo_diffuseTransmission->clear();

            /* Add item to combo box */
            ui->combo_diffuseTransmission->addItem("Select spectrometer");

            unsigned int i = 0;

            /* Loop through devices */
            for (i = 0; i < m_NrDevices; i++)
            {
                /* Add non-selected spectrometers to diffuse transmittance combo box */
                if (QString::compare(ptrSpectrometers[i]->getSerialNumber(), ui->combo_diffuseReflection->currentText(), Qt::CaseInsensitive))
                {
                    /* Add current spectrometer's serial number to combo box */
                    ui->combo_diffuseTransmission->addItem(ptrSpectrometers[i]->getSerialNumber());
                }
            }

            /* Enable combo box */
            ui->combo_diffuseTransmission->setEnabled(true);
        }

        /* User is not allowed to finish the assistant */
        ui->button_next->setEnabled(false);
    }
    /* User selected diffuse transmittance combo box */
    else if (ui->combo_diffuseTransmission == senderComboBox)
    {
        /* Default entry resets other combo boxes */
        if (!senderComboBox->currentIndex())
        {
            /*
             * Reset unscattered transmittance combo box
             */

            /* Remove all items in combo box */
            ui->combo_unscatteredTransmission->clear();

            /* If less than 3 spectrometers, measurement of unscattered transmittance is not possible */
            if (m_NrDevices < 3)
            {
                /* Add item to combo box */
                ui->combo_unscatteredTransmission->addItem("No spectrometer");
            }
            else
            {
                /* Add item to combo box */
                ui->combo_unscatteredTransmission->addItem("Select spectrometer");
            }

            /* Disable combo box */
            ui->combo_unscatteredTransmission->setEnabled(false);

            /* User is not allowed to finish the assistant */
            ui->button_next->setEnabled(false);
        }
        /* Spectrometer selected */
        else
        {
            /* Is there a spectrometer left? */
            if (m_NrDevices > 2)
            {
                /*
                 * Set unscattered transmittance combo box
                 */

                /* Remove all items in combo box */
                ui->combo_unscatteredTransmission->clear();

                /* If less than 3 spectrometers, measurement of unscattered transmittance is not possible */
                if (m_NrDevices < 3)
                {
                    /* Add item to combo box */
                    ui->combo_unscatteredTransmission->addItem("No spectrometer");
                }
                else
                {
                    /* Add item to combo box */
                    ui->combo_unscatteredTransmission->addItem("Select spectrometer");
                }

                unsigned int i = 0;

                /* Loop through devices */
                for (i = 0; i < m_NrDevices; i++)
                {
                    /* Add non-selected spectrometers to unscattered transmittance combo box */
                    if ((QString::compare(ptrSpectrometers[i]->getSerialNumber(), ui->combo_diffuseReflection->currentText(), Qt::CaseInsensitive)) &&
                        (QString::compare(ptrSpectrometers[i]->getSerialNumber(), ui->combo_diffuseTransmission->currentText(), Qt::CaseInsensitive)))
                    {
                        ui->combo_unscatteredTransmission->addItem(ptrSpectrometers[i]->getSerialNumber());
                    }
                }

                /* User is not allowed to finish the assistant */
                ui->button_next->setEnabled(false);
            }
            else
            {
                /*
                 * Reset unscattered transmittance combo box
                 */

                /* Remove all items from combo box */
                ui->combo_unscatteredTransmission->clear();

                /* Add item to combo box */
                ui->combo_unscatteredTransmission->addItem("No spectrometer");

                /* User is allowed to finish the assistant */
                ui->button_next->setEnabled(true);
            }

            /* Enable combo box */
            ui->combo_unscatteredTransmission->setEnabled(true);
        }
    }
    /* User selected unscattered transmittance combo box */
    else if (ui->combo_unscatteredTransmission == senderComboBox)
    {
        /* User is allowed to finish the assistant */
        ui->button_next->setEnabled(true);
    }

    /*
     * Update list of parameters that can be calculated
     */

    /* Are diffuse reflectance and diffuse transmittance available? */
    if ((ui->combo_diffuseReflection->currentIndex() > 0) &&
        (ui->combo_diffuseTransmission->currentIndex() > 0))
    {
        /* We can calculate the absorption coefficient and reduced scattering coefficient */
        ui->checkBox_absorptionCoefficient->setChecked(true);
        ui->checkBox_reducedScatteringCoefficient->setChecked(true);

        /* Is unscattered transmittance available? */
        if (ui->combo_unscatteredTransmission->currentIndex() > 0)
        {
            /* We can calculate scattering anisotropy */
            ui->checkBox_scatteringCoefficient->setChecked(true);
            ui->checkBox_anisotropy->setChecked(true);
        }
        else
        {
            /* No, so we can't calculate scattering anisotropy */
            ui->checkBox_scatteringCoefficient->setChecked(false);
            ui->checkBox_anisotropy->setChecked(false);
        }
    }
    else
    {
        /* No, so we can't calculate anything */
        ui->checkBox_absorptionCoefficient->setChecked(false);
        ui->checkBox_scatteringCoefficient->setChecked(false);
        ui->checkBox_reducedScatteringCoefficient->setChecked(false);
        ui->checkBox_anisotropy->setChecked(false);
    }
}

/**
 * @brief Quits the assistant
 */
void ConfigureIADPage01::cancel(void)
{
    /* Quit the assistant */
    reject();
}

/**
 * @brief Continues the assistant
 */
void ConfigureIADPage01::next(void)
{
    /* Go to next assistant page */
    accept();
}

/**
 * @brief Destructor of 'ConfigureIADPage01' class
 */
ConfigureIADPage01::~ConfigureIADPage01(void)
{
    /* Delete user interface */
    delete ui;
}
