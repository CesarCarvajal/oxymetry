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

#ifndef SPECTROMETER_EEPROM_H
#define SPECTROMETER_EEPROM_H

/* External includes */
#include <QDialog>
#include <QWidget>

namespace Ui {
    class SpectrometerEEPROM;
}

/**
 * @brief The 'SpectrometerEEPROM' class
 */
class SpectrometerEEPROM : public QDialog
{
    Q_OBJECT

public:
    /* Constructor */
    explicit SpectrometerEEPROM(QWidget *parent = 0);

    /* Destructor */
    ~SpectrometerEEPROM(void);

    Ui::SpectrometerEEPROM *ui;

private slots:
    /* Reject changes */
    void close(void);

    /* Accept changes */
    void readEEPROM(void);
    void writeEEPROM(void);
    void createBackup(void);
    void restoreBackup(void);
};

#endif // SPECTROMETER_EEPROM_H
