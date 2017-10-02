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

#ifndef SPECTROMETER_CONFIG_H
#define SPECTROMETER_CONFIG_H

/* External includes */
#include <QDialog>
#include <QWidget>

namespace Ui {
    class SpectrometerConfig;
}

/**
 * @brief The 'SpectrometerConfig' class
 */
class SpectrometerConfig : public QDialog
{
    Q_OBJECT

public:
    /* Constructor */
    explicit SpectrometerConfig(QWidget *parent = 0);

    /* Assign spectrometer to dialog */
    void assignSpectrometer(unsigned int id);

    /* Destructor */
    ~SpectrometerConfig(void);

    Ui::SpectrometerConfig *ui;

private slots:
    /* Button 'apply' clicked */
    void apply(void);

    /* Update calculated values */
    void updateValues(void);

    /* Button 'cancel' clicked */
    void cancel(void);

private:
    unsigned int deviceId;
};

#endif // SPECTROMETER_CONFIG_H
