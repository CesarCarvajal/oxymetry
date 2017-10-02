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
#include <QDesktopWidget>
#include <QFileDialog>
#include <QDir>
#include <QLineEdit>
#include <QList>
#include <QTimer>

/* Internal includes */
#include "application.h"
#include "messages.h"
#include "spectrometer.h"
#include "timer.h"
#include "panel_storetoram.h"
#include "ui_panel_storetoram.h"

/*
 * Global variables
 */
extern Spectrometer** ptrSpectrometers;
extern unsigned int m_NrDevices;
extern QString defaultColors[];

/**
 * @brief Constructor of 'PanelStoreToRAM' class
 * @param[in] parent Parent widget
 */
PanelStoreToRAM::PanelStoreToRAM(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PanelStoreToRAM)
{
    /* Set up user interface */
    ui->setupUi(this);

    /* Set window flags */
    this->setWindowFlags(Qt::Dialog | Qt::WindowTitleHint | Qt::WindowStaysOnTopHint | Qt::WindowCloseButtonHint);

    /* Disable resize of elements */
    this->setFixedSize(this->size());

    /* Connect buttons to signal mapper */
    connect(ui->pushButton_select, SIGNAL(clicked()), this, SLOT(selectPath()));
    connect(ui->pushButton_start, SIGNAL(clicked()), this, SLOT(startButton()));
}

/**
 * @brief Update total time value
 */
void PanelStoreToRAM::updateTotalTime(void)
{
    unsigned int i = 0;

    /* Loop through devices */
    for (i = 0; i < (unsigned int)id.length(); i++)
    {
        /* Total time is the product of integration time, number of averages and number of measurements */
        float result = ptrSpectrometers[id[i]]->getIntegrationTime() *
                       ptrSpectrometers[id[i]]->getNumberOfAverages() *
                       numberMeasurements[i]->value();

        QString time;

        /* Show calculated time in minutes if result is < 60000 ms */
        if (result >= 60000.0f)
        {
            unsigned int minutes = result / 60000.0f;
            unsigned int seconds = (result - (minutes * 60000.0f)) / 1000.0f;
            unsigned int milliseconds = result - (minutes * 60000.0f) - (seconds * 1000.0f);

            /* Generate string with minutes, seconds and milliseconds */
            time = QString("%1 min %2 s %3 ms").arg(QString::number(minutes),
                                                    QString::number(seconds),
                                                    QString::number(milliseconds));
        }
        /* Show calculated time in seconds if result is < 1000 ms */
        else if (result >= 1000.0f)
        {
            unsigned int seconds = result / 1000.0f;
            unsigned int milliseconds = result - (seconds * 1000.0f);

            /* Generate string with minutes and seconds */
            time = QString("%1 s %2 ms").arg(QString::number(seconds),
                                             QString::number(milliseconds));
        }
        /* Show calculated time in milliseconds */
        else
        {
            /* Generate string with milliseconds */
            time = QString("%1 ms").arg(QString::number(result));
        }

        /* Set total time */
        this->totalTime[i]->setText(time);
    }
}

/**
 * @brief Add spectrometer to device list
 * @param[in] id Index in spectrometer array
 */
void PanelStoreToRAM::addSpectrometer(unsigned int id)
{
    /* Get current window geometry */
    QRect currentRect = this->geometry();

    /* Increase window height about one row */
    currentRect.setHeight(currentRect.height() + 33);

    /* Disable resize of elements */
    this->setFixedHeight(currentRect.height());

    /* Get screen geometry */
    const QRect screenGeometry = QApplication::desktop()->screenGeometry(this);

    /* Center dialog on screen */
    this->setGeometry(QStyle::alignedRect(Qt::LeftToRight,
                                          Qt::AlignCenter,
                                          currentRect.size(),
                                          screenGeometry));

    /* Current offset in list of spectrometers */
    int offset = this->id.length();

    /* Add ID of new spectrometer */
    this->id.append(id);

    /* Add serial number of new spectrometer */
    serialNumber.append(new QLabel(this));
    serialNumber[offset]->setText(ptrSpectrometers[id]->getSerialNumber());
    serialNumber[offset]->setStyleSheet("QLabel { color: " + defaultColors[id % 5] + "; }");
    serialNumber[offset]->setGeometry(10, 130 + 30 * (offset - 1), 100, 23);

    /* Add number of measurements for StoreToRAM measurement */
    numberMeasurements.append(new QSpinBox(this));
    numberMeasurements[offset]->setGeometry(120, 130 + 30 * (offset - 1), 60, 23);
    numberMeasurements[offset]->setValue(1);
    numberMeasurements[offset]->setMinimum(1);
    numberMeasurements[offset]->setMaximum(10000);

    /* Update total time if number of measurements changes */
    connect(numberMeasurements[offset], SIGNAL(valueChanged(int)), this, SLOT(updateTotalTime()));

    /* Add total time of StoreToRAM measurement */
    totalTime.append(new QLabel(this));
    totalTime[offset]->setGeometry(200, 130 + 30 * (offset - 1), 150, 23);

    /* Calculate total time */
    updateTotalTime();
}

/**
 * @brief Select path for StoreToRAM files
 */
void PanelStoreToRAM::selectPath(void)
{
    QString path;

    /* No filename chosen until now? */
    if (!ui->lineEdit_path->isEnabled())
    {
        /* Get path for StoreToRAM file */
        path = QFileDialog::getSaveFileName(this, "StoreToRAM file", QDir::currentPath(), "Text files (*.txt)");
    }
    else
    {
        /* Get path for StoreToRAM file */
        path = QFileDialog::getSaveFileName(this, "StoreToRAM file", ui->lineEdit_path->text(), "Text files (*.txt)");
    }

    /* Did user select a path? */
    if (!path.isEmpty())
    {
        /* Copy path into line edit */
        ui->lineEdit_path->setText(path);

        /* Enable directory field and 'start' button */
        ui->lineEdit_path->setEnabled(true);
        ui->pushButton_start->setEnabled(true);
    }
}

/**
 * @brief Button 'start' clicked
 */
void PanelStoreToRAM::startButton(void)
{
    /* Get path for StoreToRAM file */
    QString path = ui->lineEdit_path->text();

    /* Is path empty? */
    if (path.isEmpty())
    {
        /* Show message */
        showWarning("No path for StoreToRAM file specified!", "");
        return;
    }

    /* Disable GUI elements */
    ui->lineEdit_path->setEnabled(false);
    ui->pushButton_select->setEnabled(false);
    ui->pushButton_start->setEnabled(false);

    /* Handle events and update UI */
    Application::processEvents();

    unsigned int i = 0;

    /* Loop through devices */
    for (i = 0; i < (unsigned int)id.length(); i++)
    {
        /* Remove file extension '.txt' and append serial number */
        path = path.remove(path.length() - 4, 4);
        path.append(QString("_%1.txt").arg(ptrSpectrometers[i]->getSerialNumber()));

        /* Prepare for new StoreToRAM measurement */
        ptrSpectrometers[i]->forceStoreToRAM(path, numberMeasurements[this->id.indexOf(i)]->value());
        if (ptrSpectrometers[i]->prepareMeasurement())
        {
            /* If successful, start measurement */
            ptrSpectrometers[i]->startMeasurement(1);
        }
    }

    bool isMeasuring = false;

    do
    {
        /* Start FALSE, gets TRUE if at least one spectrometer is measuring */
        isMeasuring = false;

        /* Loop through devices */
        for (i = 0; i < (unsigned int)id.length(); i++)
        {
            /* Set to TRUE if current spectrometer is measuring */
            isMeasuring = isMeasuring | ptrSpectrometers[i]->isMeasuring();
        }

        /* Handle events and update UI */
        Application::processEvents();

        /* Wait 1 ms */
        Timer::msleep(1);
    }
    while (isMeasuring);

    /* Enable GUI elements */
    ui->pushButton_start->setEnabled(true);
    ui->pushButton_select->setEnabled(true);
    ui->lineEdit_path->setEnabled(true);
}

/* Destuctor of PanelStoreToRAM class*/
PanelStoreToRAM::~PanelStoreToRAM(void)
{
    /* Delete user interface */
    delete ui;
}
