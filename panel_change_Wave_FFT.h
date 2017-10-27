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

#ifndef PANEL_CHANGE_WAVE_FFT_H
#define PANEL_CHANGE_WAVE_FFT_H

/* External includes */
#include <QDialog>
#include <QWidget>
#include <QTimer>

namespace Ui {
    class PanelChangeWaveFFT;
}

/**
 * @brief The 'PanelChangeWaveFFT' class
 */
class PanelChangeWaveFFT : public QDialog
{
    Q_OBJECT

public:
    /* Constructor */
    explicit PanelChangeWaveFFT(QWidget *parent = 0);

    /* Get or set number of averages */
    int getValue(void);
    void setValue(double value);

    /* Destructor */
    ~PanelChangeWaveFFT(void);

public slots:
    /* Brings the window to foreground at creation */
    void activateWindow(void)
    {
        QDialog::activateWindow();
    }

private slots:
    /* User pressed 'apply' button */
    void applyButton(void);

private:
    Ui::PanelChangeWaveFFT *ui;
};

#endif // PANEL_CHANGE_WAVE_FFT_H
