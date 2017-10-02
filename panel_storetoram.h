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

#ifndef PANEL_STORETORAM_H
#define PANEL_STORETORAM_H

/* External includes */
#include <QDialog>
#include <QWidget>
#include <QString>
#include <QList>
#include <QLabel>
#include <QLineEdit>
#include <QSpinBox>

namespace Ui {
    class PanelStoreToRAM;
}

/**
 * @brief The 'PanelStoreToRAM' class
 */
class PanelStoreToRAM : public QDialog
{
    Q_OBJECT

public:
    /* Constructor */
    explicit PanelStoreToRAM(QWidget *parent = 0);

    /* Add spectrometer to device list */
    void addSpectrometer(unsigned int id);

    /* Destructor */
    ~PanelStoreToRAM(void);

private slots:
    /* Select path */
    void selectPath(void);

    /* Update total time */
    void updateTotalTime(void);

    /* Button 'start' clicked */
    void startButton(void);

private:
    /* User interface */
    Ui::PanelStoreToRAM *ui;

    /* StoreToRAM configuration */
    QList<unsigned int> id;
    QList<QLabel *> serialNumber;
    QList<QSpinBox *> numberMeasurements;
    QList<QLabel *> totalTime;
};

#endif // PANEL_STORETORAM_H
