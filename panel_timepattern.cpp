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
#include <QDialog>
#include <QWidget>
#include <QFileDialog>
#include <QDir>
#include <QLineEdit>
#include <QList>
#include <QTimer>
#include <QElapsedTimer>
#include <QFile>

/* Internal includes */
#include "application.h"
#include "messages.h"
#include "spectrometer.h"
#include "timer.h"
#include "panel_timepattern.h"
#include "ui_panel_timepattern.h"

/*
 * Global variables
 */
extern Spectrometer** ptrSpectrometers;
extern unsigned int m_NrDevices;

/**
 * @brief Constructor of 'PanelTimePattern' class
 * @param[in] parent Parent widget
 */
PanelTimePattern::PanelTimePattern(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PanelTimePattern)
{
    /* Set up user interface */
    ui->setupUi(this);

    /* Set window flags */
    this->setWindowFlags(Qt::Dialog | Qt::WindowTitleHint | Qt::WindowStaysOnTopHint | Qt::WindowCloseButtonHint);

    /* Disable resize of elements */
    this->setFixedSize(this->size());

    /* Prevent user from resizing the header */
    ui->tableWidget_cmds->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);

    /* Left align column titles */
    ui->tableWidget_cmds->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);

    /* Prevent user from editing the cells */
    ui->tableWidget_cmds->setEditTriggers(QAbstractItemView::NoEditTriggers);

    /* Adjust table widget */
    ui->tableWidget_cmds->setColumnWidth(0, 30);
    ui->tableWidget_cmds->setColumnWidth(1, 80);
    ui->tableWidget_cmds->setColumnWidth(2, 190);
    ui->tableWidget_cmds->setColumnWidth(3, 60);
    ui->tableWidget_cmds->setColumnWidth(4, 130);
    ui->tableWidget_cmds->setColumnWidth(5, 130);

    unsigned int i = 0;

    /* Loop through devices */
    for (i = 0; i < m_NrDevices; i++)
    {
        /* Does current device has a readable name? */
        if (ptrSpectrometers[i]->hasReadableName())
        {
            /* Yes, add it to the combo box */
            ui->comboBox_device->addItem(ptrSpectrometers[i]->getReadableName(), i);
        }
        else
        {
            /* No, use serial number instead */
            ui->comboBox_device->addItem(ptrSpectrometers[i]->getSerialNumber(), i);
        }
    }

    /* Connect buttons to signal mapper */
    connect(ui->pushButton_select, SIGNAL(clicked()), this, SLOT(selectPath()));
    connect(ui->pushButton_start, SIGNAL(clicked()), this, SLOT(startButton()));
}

/**
 * @brief Select path for StoreToRAM files
 */
void PanelTimePattern::selectPath(void)
{
    QString path;

    /* No directory chosen until now? */
    if (!ui->lineEdit_path->isEnabled())
    {
        /* Get path of configuration file */
        path = QFileDialog::getOpenFileName(this, "Configuration file", QDir::currentPath(), "Text files (*.txt)");

    }
    else
    {
        /* Get path of configuration file */
        path = QFileDialog::getOpenFileName(this, "Configuration file", path, "Text files (*.txt)");
    }

    /* Did user select a path? */
    if (!path.isEmpty())
    {
        QFile file(path);

        /* Open configuration file */
        if (!file.open(QIODevice::ReadOnly))
        {
            /* Show message */
            showCritical("Unable to open configuration file!", "");
            return;
        }

        /*
         * Read in configuration file
         */

        QStringList wordList;

        /* Loop through lines in file */
        while (!file.atEnd())
        {
            wordList.append(file.readLine().split(',').first());
        }

        /* Close file */
        file.close();

        /*
         * Process configuration file
         */

        /* Zero row count */
        ui->tableWidget_cmds->setRowCount(0);

        /* Clear lists */
        timePoint.clear();
        fileName.clear();
        numSpectra.clear();
        integrationTime.clear();
        numberOfAverages.clear();

        /* Check format of configuration file; we need at least 4 semicolons per line */
        if (wordList[0].count(QLatin1Char(';')) != 4)
        {
            /* Show message */
            showWarning("Malformed configuration file!", "");
            return;
        }

        unsigned int i = 0;

        /* Loop through elements */
        for (i = 0; i < (unsigned int)wordList.length(); i++)
        {
            QStringList list = wordList[i].split(';');

            /* Copy entries to lists */
            timePoint.append(list[0].toInt());
            fileName.append(list[1]);
            numSpectra.append(list[2].toInt());
            integrationTime.append(list[3].toFloat());
            numberOfAverages.append(list[4].toInt());

            /* At least second entry? */
            if (i > 0)
            {
                /* Calculate duration of entry before current entry */
                double duration = numSpectra[i - 1] * integrationTime[i - 1] * numberOfAverages[i - 1];

                /* Check if there's a time overlap between last and current entry */
                if ((timePoint[i - 1] + duration) > timePoint[i])
                {
                    /* Zero row count */
                    ui->tableWidget_cmds->setRowCount(0);

                    /* Clear lists */
                    timePoint.clear();
                    fileName.clear();
                    numSpectra.clear();
                    integrationTime.clear();
                    numberOfAverages.clear();

                    QString message;

                    /* Create message */
                    message = QString("Error in configuration file! Time overlap between entries %1 and %2.").arg(QString::number(i - 1),
                                                                                                                  QString::number(i));

                    /* Show message */
                    showCritical(message, "");
                    return;
                }
            }

            /* Increase current row count */
            ui->tableWidget_cmds->setRowCount(ui->tableWidget_cmds->rowCount() + 1);

            QLabel *nt = new QLabel();

            /* Create label for index */
            nt->setText(QString::number(i));
            nt->setStyleSheet("QLabel { margin-left: 2px; }");
            ui->tableWidget_cmds->setCellWidget(i, 0, nt);

            QLabel *nt2 = new QLabel();

            /* Create label for time point */
            nt2->setText(list[0]);
            nt2->setStyleSheet("QLabel { margin-left: 2px; }");
            ui->tableWidget_cmds->setCellWidget(i, 1, nt2);

            QLabel *nt3 = new QLabel();

            /* Create label for file name */
            nt3->setText(list[1]);
            nt3->setStyleSheet("QLabel { margin-left: 2px; }");
            ui->tableWidget_cmds->setCellWidget(i, 2, nt3);

            QLabel *nt4 = new QLabel();

            /* Create label for number of spectra */
            nt4->setText(list[2]);
            nt4->setStyleSheet("QLabel { margin-left: 2px; }");
            ui->tableWidget_cmds->setCellWidget(i, 3, nt4);

            QLabel *nt5 = new QLabel();

            /* Create label for integration time */
            nt5->setText(list[3]);
            nt5->setStyleSheet("QLabel { margin-left: 2px; }");
            ui->tableWidget_cmds->setCellWidget(i, 4, nt5);

            QLabel *nt6 = new QLabel();

            /* Create label for number of averages */
            nt6->setText(list[4]);
            nt6->setStyleSheet("QLabel { margin-left: 2px; }");
            ui->tableWidget_cmds->setCellWidget(i, 5, nt6);
        }

        /* Select first row */
        ui->tableWidget_cmds->setSelectionBehavior(QAbstractItemView::SelectRows);
        ui->tableWidget_cmds->setSelectionMode(QAbstractItemView::SingleSelection);
        ui->tableWidget_cmds->selectRow(0);
        ui->tableWidget_cmds->setSelectionMode(QAbstractItemView::NoSelection);

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
void PanelTimePattern::startButton(void)
{
    /* Reset progress bars */
    ui->progressBar_current->setValue(0);
    ui->progressBar_total->setValue(0);

    /* Disable GUI elements */
    ui->pushButton_select->setEnabled(false);
    ui->lineEdit_path->setEnabled(false);

    /* No measurement running? */
    if (!bRunTimePattern)
    {
        /* Change caption to 'stop' */
        ui->pushButton_start->setText("Stop");

        /* Run measurements */
        bRunTimePattern = true;

        unsigned int id = ui->comboBox_device->itemData(ui->comboBox_device->currentIndex()).toInt();

        QElapsedTimer timer;

        /* Start timer */
        timer.start();

        unsigned int i = 0;

        do
        {
            /* Check if we have more entries to do */
            if (i < (unsigned int)timePoint.length())
            {
                /* Next measurement starts now? */
                if (timer.elapsed() >= timePoint[i])
                {
                    /* Generate absolute path for StoreToRAM files */
                    QFileInfo fileInfo(ui->lineEdit_path->text());
                    QString path(fileInfo.absoluteDir().path());
                    path.append(fileName[i]);

                    /* Check if spectrometer is still measuring */
                    if (ptrSpectrometers[id]->isMeasuring())
                    {
                        /* Show message */
                        showWarning("Spectrometer is still measuring! Too small time steps?", "");
                    }
                    else
                    {
                        /* Configure spectrometer */
                        ptrSpectrometers[id]->setIntegrationTime(integrationTime[i]);
                        ptrSpectrometers[id]->setNumberOfAverages(numberOfAverages[i]);

                        /* Prepare StoreToRAM measurement */
                        ptrSpectrometers[id]->forceStoreToRAM(path, numSpectra[i]);
                        if (ptrSpectrometers[id]->prepareMeasurement())
                        {
                            /* Start measurement */
                            ptrSpectrometers[id]->startMeasurement(1);
                        }
                    }

                    /* Select the row that belongs to the measurement */
                    ui->tableWidget_cmds->setSelectionBehavior(QAbstractItemView::SelectRows);
                    ui->tableWidget_cmds->setSelectionMode(QAbstractItemView::SingleSelection);
                    ui->tableWidget_cmds->selectRow(i);
                    ui->tableWidget_cmds->setSelectionMode(QAbstractItemView::NoSelection);

                    /* Go to next entry */
                    i++;
                }
            }

            int progress = 0;

            /* Calculate progress for first entry? */
            if (i == 0)
            {
                progress = 100 - (timePoint[0] - timer.elapsed()) / timePoint[0] * 100;
            }
            /* Calculate progress for last entry? */
            else if (i >= (unsigned int)timePoint.length())
            {
                /* Abort while loop if no measurement is running anymore */
                bRunTimePattern = ptrSpectrometers[id]->isMeasuring();

                /* Progress done */
                progress = 100;
            }
            /* Calculate progress for any other entry? */
            else
            {
                /* Current progress is calculated by the difference between actual time and next measurement */
                progress = 100 - (timePoint[i] - timer.elapsed()) / (timePoint[i] - timePoint[i-1]) * 100;
            }

            /* Update progress bars */
            ui->progressBar_current->setValue(progress);
            ui->progressBar_total->setValue((i - 1) * 100 / timePoint.count());

            /* Handle events and update UI */
            Application::processEvents();

            /* Wait 1 ms */
            Timer::msleep(1);
        }
        while (bRunTimePattern);
    }

    /* Stop measurements */
    bRunTimePattern = false;

    /* Change caption to 'start' */
    ui->pushButton_start->setText("Start");

    /* Reset selected row */
    ui->tableWidget_cmds->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget_cmds->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidget_cmds->selectRow(0);
    ui->tableWidget_cmds->setSelectionMode(QAbstractItemView::NoSelection);

    /* Set progress bars to 100 percent */
    ui->progressBar_current->setValue(100);
    ui->progressBar_total->setValue(100);

    /* Enable GUI elements */
    ui->lineEdit_path->setEnabled(true);
    ui->pushButton_select->setEnabled(true);
}

/**
 * @brief Destructor of 'PanelTimePattern' class
 */
PanelTimePattern::~PanelTimePattern(void)
{
    delete ui;
}
