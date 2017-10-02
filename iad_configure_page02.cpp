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

/* Internal includes */
#include "application.h"
#include "spectrometer.h"
#include "messages.h"
#include "iad_configure_page02.h"
#include "ui_iad_configure_page02.h"

/*
 * Global variables
 */
extern QSettings *settings;
extern Spectrometer** ptrSpectrometers;
extern unsigned int m_NrDevices;

/**
 * @brief Constructor of 'ConfigureIADPage02' class
 * @param parent Parent widget
 */
ConfigureIADPage02::ConfigureIADPage02(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfigureIADPage02)
{
    /* Set up user interface */
    ui->setupUi(this);

    /* Set window flags */
    this->setWindowFlags(Qt::Dialog | Qt::WindowTitleHint | Qt::WindowStaysOnTopHint);

    /* Disable resize of elements */
    this->setFixedSize(this->size());

    /* Connect combo box signal handles */
    connect(ui->comboBox_calibrationStandard, SIGNAL(currentIndexChanged(int)), this, SLOT(update()));
    connect(ui->comboBox_rSphereWallMaterial, SIGNAL(currentIndexChanged(int)), this, SLOT(update()));
    connect(ui->comboBox_tSphereWallMaterial, SIGNAL(currentIndexChanged(int)), this, SLOT(update()));

    /* Connect button signal handles */
    connect(ui->button_cancel, SIGNAL(clicked(bool)), this, SLOT(cancel()));
    connect(ui->button_finish, SIGNAL(clicked(bool)), this, SLOT(finish()));
}

/**
 * @brief Loads settings from configuration file
 * @param fileName Path to configuration file
 */
void ConfigureIADPage02::load(QString fileName)
{
    /* Invalid file name? */
    if (NULL == fileName)
        return;

    /* Open configuration file */
    QSettings *config = new QSettings(fileName, QSettings::IniFormat);

    /* Import from [Setup] group */
    config->beginGroup(QString("Setup"));
    ui->doubleSpinBox_indexOfRefractionOfSample->setValue(config->value(QString("IndexOfRefractionOfSample"), ui->doubleSpinBox_indexOfRefractionOfSample->value()).toDouble());
    ui->doubleSpinBox_indexOfRefractionOfSample->setValue(config->value(QString("IndexOfRefractionOfTopSlide"), ui->doubleSpinBox_indexOfRefractionOfSample->value()).toDouble());
    ui->doubleSpinBox_thicknessOfSample->setValue(config->value(QString("ThicknessOfSample"), ui->doubleSpinBox_thicknessOfSample->value()).toDouble());
    ui->doubleSpinBox_thicknessOfSlides->setValue(config->value(QString("ThicknessOfSlides"), ui->doubleSpinBox_thicknessOfSlides->value()).toDouble());
    ui->doubleSpinBox_diameterOfIlluminationBeam->setValue(config->value(QString("DiameterOfIlluminationBeam"), ui->doubleSpinBox_diameterOfIlluminationBeam->value()).toDouble());
    ui->comboBox_calibrationStandard->setCurrentIndex(\
                ui->comboBox_calibrationStandard->findText(\
                    config->value(QString("CalibrationStandard"), QString("Select standard")).toString(), Qt::MatchContains));
    config->endGroup();

    /* Import from [ReflectionSphere] group */
    config->beginGroup(QString("ReflectionSphere"));
    ui->doubleSpinBox_rSphereDiameter->setValue(config->value(QString("SphereDiameter"), ui->doubleSpinBox_rSphereDiameter->value()).toDouble());
    ui->doubleSpinBox_rSamplePortDiameter->setValue(config->value(QString("SamplePortDiameter"), ui->doubleSpinBox_rSamplePortDiameter->value()).toDouble());
    ui->doubleSpinBox_rEntrancePortDiameter->setValue(config->value(QString("EntrancePortDiameter"), ui->doubleSpinBox_rEntrancePortDiameter->value()).toDouble());
    ui->doubleSpinBox_rDetectorPortDiameter->setValue(config->value(QString("DetectorPortDiameter"), ui->doubleSpinBox_rDetectorPortDiameter->value()).toDouble());
    ui->comboBox_rSphereWallMaterial->setCurrentIndex(\
                ui->comboBox_rSphereWallMaterial->findText(\
                    config->value(QString("SphereWallMaterial"), QString("Select material")).toString(), Qt::MatchContains));
    config->endGroup();

    /* Import from [TransmissionSphere] group */
    config->beginGroup(QString("TransmissionSphere"));
    ui->doubleSpinBox_tSphereDiameter->setValue(config->value(QString("SphereDiameter"), ui->doubleSpinBox_tSphereDiameter->value()).toDouble());
    ui->doubleSpinBox_tSamplePortDiameter->setValue(config->value(QString("SamplePortDiameter"), ui->doubleSpinBox_tSamplePortDiameter->value()).toDouble());
    ui->doubleSpinBox_tEntrancePortDiameter->setValue(config->value(QString("EntrancePortDiameter"), ui->doubleSpinBox_tEntrancePortDiameter->value()).toDouble());
    ui->doubleSpinBox_tDetectorPortDiameter->setValue(config->value(QString("DetectorPortDiameter"), ui->doubleSpinBox_tDetectorPortDiameter->value()).toDouble());
    ui->comboBox_tSphereWallMaterial->setCurrentIndex(\
                ui->comboBox_tSphereWallMaterial->findText(\
                    config->value(QString("SphereWallMaterial"), QString("Select material")).toString(), Qt::MatchContains));
    config->endGroup();

    /* Close file */
    delete config;
    config = nullptr;
}

/**
 * @brief Saves settings from configuration file
 * @param fileName Path to configuration file
 */
void ConfigureIADPage02::save(QString fileName)
{
    /* Invalid file name? */
    if (NULL == fileName)
        return;

    /* Open configuration file */
    QSettings *config = new QSettings(fileName, QSettings::IniFormat);

    /* Export to [Setup] group */
    config->beginGroup(QString("Setup"));

    /* Save values */
    config->setValue(QString("IndexOfRefractionOfSample"), ui->doubleSpinBox_indexOfRefractionOfSample->value());
    config->setValue(QString("IndexOfRefractionOfTopSlide"), ui->doubleSpinBox_indexOfRefractionOfSample->value());
    config->setValue(QString("ThicknessOfSample"), ui->doubleSpinBox_thicknessOfSample->value());
    config->setValue(QString("ThicknessOfSlides"), ui->doubleSpinBox_thicknessOfSlides->value());
    config->setValue(QString("DiameterOfIlluminationBeam"), ui->doubleSpinBox_diameterOfIlluminationBeam->value());
    config->setValue(QString("CalibrationStandard"), ui->comboBox_calibrationStandard->currentText());

    /* Finish export */
    config->endGroup();

    /* Export to [ReflectionSphere] group */
    config->beginGroup(QString("ReflectionSphere"));

    /* Save values */
    config->setValue(QString("SphereDiameter"), ui->doubleSpinBox_rSphereDiameter->value());
    config->setValue(QString("SamplePortDiameter"), ui->doubleSpinBox_rSamplePortDiameter->value());
    config->setValue(QString("EntrancePortDiameter"), ui->doubleSpinBox_rEntrancePortDiameter->value());
    config->setValue(QString("DetectorPortDiameter"), ui->doubleSpinBox_rDetectorPortDiameter->value());
    config->setValue(QString("SphereWallMaterial"), ui->comboBox_rSphereWallMaterial->currentText());

    /* Finish export */
    config->endGroup();

    /* Export to [TransmissionSphere] group */
    config->beginGroup(QString("TransmissionSphere"));

    /* Save values */
    config->setValue(QString("SphereDiameter"), ui->doubleSpinBox_tSphereDiameter->value());
    config->setValue(QString("SamplePortDiameter"), ui->doubleSpinBox_tSamplePortDiameter->value());
    config->setValue(QString("EntrancePortDiameter"), ui->doubleSpinBox_tEntrancePortDiameter->value());
    config->setValue(QString("DetectorPortDiameter"), ui->doubleSpinBox_tDetectorPortDiameter->value());
    config->setValue(QString("SphereWallMaterial"), ui->comboBox_tSphereWallMaterial->currentText());

    /* Finish export */
    config->endGroup();

    /* Close file */
    delete config;
    config = nullptr;
}

/**
 * @brief Update dialog buttons on index change
 */
void ConfigureIADPage02::update(void)
{
    /* User should be able to finish the dialog if all combo boxes have valid data */
    bool enableFinish = (((0 < ui->comboBox_calibrationStandard->currentIndex()) &&
                          (0 < ui->comboBox_rSphereWallMaterial->currentIndex()) &&
                          (0 < ui->comboBox_tSphereWallMaterial->currentIndex())));

    /* Update 'finish' button */
    ui->button_finish->setEnabled(enableFinish);
}

/**
 * @brief Quits the assistant
 */
void ConfigureIADPage02::cancel(void)
{
    /* Quit the assistant */
    reject();
}

/**
 * @brief Finishes the assistant
 */
void ConfigureIADPage02::finish(void)
{
    /* TO DO: Save values. */
    accept();
}

/**
 * @brief Destructor of 'ConfigureIADPage02' class
 */
ConfigureIADPage02::~ConfigureIADPage02(void)
{
    /* Delete user interface */
    delete ui;
}
