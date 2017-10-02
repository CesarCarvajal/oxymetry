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

#ifndef MEASUREMENTSTABLE_H
#define MEASUREMENTSTABLE_H

/* External includes */
#include <QTableWidget>
#include <QWidget>
#include <QString>
#include <QList>
#include <QHBoxLayout>
#include <QProcess>
#include <QSignalMapper>

/* Internal includes */
#include "ClickableLabel.h"

/**
 * @brief The 'MeasurementsTable' class
 */
class MeasurementsTable : public QTableWidget
{
    Q_OBJECT

public:
    /* Constructor */
    explicit MeasurementsTable(QWidget* parent = 0);

    /* Add entry to table */
    bool add(QString fileName, QString name, QDate date, QTime time);

    /* Destructor */
    ~MeasurementsTable(void);

private slots:
    void handleClicked(QWidget *widget);

private:
    void calculate(int index);

    unsigned int numMeasurements = 0;

    QList<QString *> pFileName;
    QList<QWidget *> pWidget;
    QList<ClickableLabel *> pClickableLabel;
    QList<QHBoxLayout *> pLayout;
    QList<QProcess *> pProcess;
    QSignalMapper *signalMapper;
};

#endif // MEASUREMENTSTABLE_H
