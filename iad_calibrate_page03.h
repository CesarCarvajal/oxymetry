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

#ifndef IAD_CALIBRATE_PAGE03_H
#define IAD_CALIBRATE_PAGE03_H

/* External includes */
#include <QDialog>
#include <QWidget>

/* Internal includes */
#include "iad_calibrate.h"

namespace Ui {
    class CalibrateIADPage03;
}

/**
 * @brief The 'CalibrateIADPage03' class
 */
class CalibrateIADPage03 : public QDialog
{
    Q_OBJECT

public:
    /* Constructor */
    explicit CalibrateIADPage03(QWidget *parent = 0);

    /* Does the calibration */
    void process(unsigned int idRd, unsigned int idTd, unsigned int idTu);

    /* Returns status bits */
    unsigned char getStatus(void);

    /* Get counts with reflection standard */
    double *getCounts(unsigned int id);

    /* Destructor */
    ~CalibrateIADPage03(void);

private slots:
    /* Aborts calibration */
    void abort(void);

    /* Goes to next calibration step */
    void next(void);

private:
    /* User interface */
    Ui::CalibrateIADPage03 *ui;

    /* Status bits */
    unsigned char status = PROCESS_READY;

    /* Spectrometer assignment */
    unsigned int idRd, idTd, idTu;

    /* Counts without sample */
    double *diffuseReflection_counts = nullptr;
    double *diffuseTransmission_counts = nullptr;
    double *unscatteredTransmission_counts = nullptr;
};

#endif // IAD_CALIBRATE_PAGE03_H
