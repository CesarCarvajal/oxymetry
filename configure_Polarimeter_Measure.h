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

#ifndef PANEL_CONFIGUREPOLMEASURE_H
#define PANEL_CONFIGUREPOLMEASURE_H

/* External includes */
#include <QDialog>
#include <QWidget>
#include <QList>
#include <QStringList>

namespace Ui {
class configurePolMeasure;
}

/**
 * @brief The 'configurePolMeasure' class
 */
class configurePolMeasure : public QDialog
{
    Q_OBJECT

public:
    /* Constructor */
    explicit configurePolMeasure(QWidget *parent = 0);

    int numSpectra;
    QList<double> timePoint;
    float integrationTime;
    int numberOfAverages;
    int freqToMeasure;
    bool configured = false;
    QString path;

    /* Time pattern configuration */
    QStringList fileName;

    void cleanAll(void);

    /* Destructor */
    ~configurePolMeasure(void);

private slots:
    /* Select path */
    void selectPath(void);

private:
    /* User interface */
    Ui::configurePolMeasure *ui;

    /* Abort run if set to FALSE */
    bool bRunTimePattern = false;


};

#endif // PANEL_CONFIGUREPOLMEASURE_H
