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
#include <QWidget>
#include <QTableWidget>
#include <QHeaderView>
#include <QAbstractItemView>
#include <QDate>
#include <QTime>
#include <QSignalMapper>
#include <QHBoxLayout>
#include <QCursor>
#include <QFileInfo>

/* Internal includes */
#include "spectrometer.h"
#include "messages.h"
#include "clickablelabel.h"
#include "measurementstable.h"

/*
 * Global variables
 */
extern Spectrometer** ptrSpectrometers;
extern unsigned int m_NrDevices;

/**
 * @brief Constructor of 'MeasurementsTable' class
 */
MeasurementsTable::MeasurementsTable(QWidget* parent)
    : QTableWidget(parent)
{
    /* Prevent user from resizing the header */
    horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);

    /* Left align column titles */
    horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);

    /* Prevent user from editing the cells */
    setEditTriggers(QAbstractItemView::NoEditTriggers);

    /* Four columns */
    setColumnCount(4);

    /* Set column widths */
    setColumnWidth(0, 200);
    setColumnWidth(1, 100);
    setColumnWidth(2, 100);
    setColumnWidth(3, 140);
add(QString("bla"), QString("bla"), QDate::currentDate(), QTime::currentTime());
    signalMapper = new QSignalMapper(this);

    /* Connect signal mapper action */
    connect(signalMapper, SIGNAL(mapped(QWidget *)), this, SLOT(handleClicked(QWidget *)));

}

bool MeasurementsTable::add(QString fileName, QString name, QDate date, QTime time)
{
    //QFileInfo checkFile(fileName);

    /* Check if file exists and if yes: Is it really a file and no directory? */
    //if (checkFile.exists() && checkFile.isFile())
    {
        /* Get current row count */
        setRowCount(this->rowCount() + 1);

        int i = numMeasurements++;

        pFileName.append(new QString(fileName));
        pWidget.append(new QWidget(this));
        pClickableLabel.append(new ClickableLabel(this));
        pLayout.append(new QHBoxLayout(pWidget[i]));

        pLayout[i]->addWidget(pClickableLabel[i]);
                pClickableLabel[i]->setText(QString("calculate"));
                pClickableLabel[i]->setStyleSheet("QLabel { color: blue; text-decoration: underline; }");
                pClickableLabel[i]->setCursor(QCursor(Qt::PointingHandCursor));
                pLayout[i]->setAlignment(Qt::AlignCenter);
                pLayout[i]->setContentsMargins(0, 0, 0, 0);
                pWidget[i]->setLayout(pLayout[i]);

                /* Put the checkbox for module activation into the first column */
                setCellWidget(i, 3, pWidget[i]);


                QLabel *nt = new QLabel();
                    nt->setText(name);
nt->setStyleSheet(QString("margin-left: 2px;"));
                    nt->setMaximumWidth(180);
                    setCellWidget(i,0,nt);

                    QLabel *nt2 = new QLabel();
                        nt2->setText(date.toString(QString("dd.MM.yyyy")));
    nt2->setStyleSheet(QString("margin-left: 2px;"));
                        nt2->setMaximumWidth(80);
                        setCellWidget(i,1,nt2);

                        QLabel *nt3 = new QLabel();
                        nt3->setText(time.toString(QString("hh:mm:ss")));
        nt3->setStyleSheet(QString("margin-left: 2px;"));
                            nt3->setMaximumWidth(80);
                            setCellWidget(i,2,nt3);

                //connect(pClickableLabel[i], SIGNAL(clicked()), signalMapper, SLOT(map()));
                //signalMapper->setMapping(pClickableLabel[i], pClickableLabel[i]);

            return true;
        }
    return false;
}

void MeasurementsTable::handleClicked(QWidget *widget)
{
    ClickableLabel *label = qobject_cast<ClickableLabel *>(widget);

    unsigned int i = 0;

    /* Loop through measurements */
    for (i = 0; i < numMeasurements; i++)
    {
        if (label == pClickableLabel[i])
        {
            calculate(i);
        }
    }
}

void MeasurementsTable::calculate(int index)
{
    pProcess.append(new QProcess(this));

    QString iad = QString("iad.exe ") + QString(*pFileName[index]);
    pProcess.last()->start(iad);
}

/**
 * @brief Destructor of 'MeasurementsTable' class
 */
MeasurementsTable::~MeasurementsTable(void)
{
}
