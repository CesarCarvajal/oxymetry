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

#ifndef PANEL_TIMEPATTERN_H
#define PANEL_TIMEPATTERN_H

/* External includes */
#include <QDialog>
#include <QWidget>
#include <QList>
#include <QStringList>

namespace Ui {
    class PanelTimePattern;
}

/**
 * @brief The 'PanelTimePattern' class
 */
class PanelTimePattern : public QDialog
{
    Q_OBJECT

public:
    /* Constructor */
    explicit PanelTimePattern(QWidget *parent = 0);

    /* Destructor */
    ~PanelTimePattern(void);

private slots:
    /* Select path */
    void selectPath(void);

    /* Button 'start' clicked */
    void startButton(void);

private:
    /* User interface */
    Ui::PanelTimePattern *ui;

    /* Abort run if set to FALSE */
    bool bRunTimePattern = false;

    /* Time pattern configuration */
    QList<double> timePoint;
    QStringList fileName;
    QList<unsigned int> numSpectra;
    QList<float> integrationTime;
    QList<unsigned int> numberOfAverages;
};

#endif // PANEL_TIMEPATTERN_H
