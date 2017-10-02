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

#ifndef PANEL_CHANGE_TIME_H
#define PANEL_CHANGE_TIME_H

/* External includes */
#include <QDialog>
#include <QWidget>
#include <QTimer>

namespace Ui {
    class PanelChangeTime;
}

/**
 * @brief The 'PanelChangeTime' class
 */
class PanelChangeTime : public QDialog
{
    Q_OBJECT

public:
    /* Constructor */
    explicit PanelChangeTime(QWidget *parent = 0);

    /* Get or set integration time */
    float getValue(void);
    void setValue(float value);

    /* Destructor */
    ~PanelChangeTime(void);

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
    Ui::PanelChangeTime *ui;
};

#endif // PANEL_CHANGE_TIME_H
