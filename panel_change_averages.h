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

#ifndef PANEL_CHANGE_AVERAGES_H
#define PANEL_CHANGE_AVERAGES_H

/* External includes */
#include <QDialog>
#include <QWidget>
#include <QTimer>

namespace Ui {
    class PanelChangeAverages;
}

/**
 * @brief The 'PanelChangeAverages' class
 */
class PanelChangeAverages : public QDialog
{
    Q_OBJECT

public:
    /* Constructor */
    explicit PanelChangeAverages(QWidget *parent = 0);

    /* Get or set number of averages */
    int getValue(void);
    void setValue(int value);

    /* Destructor */
    ~PanelChangeAverages(void);

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
    Ui::PanelChangeAverages *ui;
};

#endif // PANEL_CHANGE_AVERAGES_H
