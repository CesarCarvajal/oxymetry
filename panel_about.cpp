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
#include <QDialog>
#include <QWidget>
#include <QLabel>
#include <QPixmap>

/* Internal includes */
#include "panel_about.h"
#include "ui_panel_about.h"

/**
 * @brief Contructor of the 'PanelAbout' class
 * @param parent Parent widget
 */
PanelAbout::PanelAbout(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PanelAbout)
{
    /* Set up user interface */
    ui->setupUi(this);

    /* Set window flags */
    this->setWindowFlags(Qt::Dialog | Qt::WindowTitleHint | Qt::WindowStaysOnTopHint | Qt::WindowCloseButtonHint);

    /* Disable resize of elements */
    this->setFixedSize(this->size());

    /* Set text of labels */
#ifdef i686
    ui->label_title->setText(ui->label_title->text().append(QString(" (32 bit)")));
#elif amd64
    ui->label_title->setText(ui->label_title->text().append(QString(" (64 bit)")));
#endif
    ui->label_compiler->setText(QString("Based on QT %1 (compiled with GNU C++ Compiler %2)").arg(QT_VERSION_STR, __VERSION__));
    ui->label_build->setText(QString("Build at %1 %2").arg(__DATE__, __TIME__));
    ui->label_copyright->setText(QString("Medical Sensors- and Devices Laboratory (MSGT)\nLübeck University of Applied Sciences (FHL)"));
    ui->label_license->setText(QString("This program is distributed in the hope that it will be useful,\n"\
                                       "but WITHOUT ANY WARRANTY; without even the implied\n"\
                                       "warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR\n"\
                                       "PURPOSE. See the GNU General Public License for more details."));

    imageLabel = new QLabel(this);

    /* Create label for icon */
    imageLabel->setObjectName(QString("imageLabel"));
    imageLabel->setGeometry(QRect(20, 20, 100, 100));
    imageLabel->setScaledContents(true);

    QPixmap logo = QPixmap(QString(":/laboratory.ico"));

    /* Load and show icon */
    logo.scaled(100, 100);
    imageLabel->setPixmap(logo);

    /* Connect close button signal */
    connect(ui->button_close, SIGNAL(clicked(bool)), this, SLOT(close()));
}

/**
 * @brief Close the about dialog
 */
void PanelAbout::close(void)
{
    /* All fine */
    accept();
}

/**
 * @brief Destructor of the 'PanelAbout' class
 */
PanelAbout::~PanelAbout(void)
{
    /* Check handle */
    if (nullptr != imageLabel)
    {
        /* Free memory */
        delete imageLabel;
        imageLabel = nullptr;
    }

    /* Delete user interface */
    delete ui;
}
