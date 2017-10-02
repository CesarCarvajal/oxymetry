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

#ifndef PANEL_ABOUT_H
#define PANEL_ABOUT_H

/* External includes */
#include <QDialog>
#include <QWidget>
#include <QLabel>

namespace Ui {
    class PanelAbout;
}

/**
 * @brief The 'PanelAbout' class
 */
class PanelAbout : public QDialog
{
    Q_OBJECT

public:
    /* Constructor */
    explicit PanelAbout(QWidget *parent = 0);

    /* Destructor */
    ~PanelAbout(void);

private slots:
    void close(void);

private:
    Ui::PanelAbout *ui;

    /* Label for application icon */
    QLabel *imageLabel = nullptr;
};

#endif // PANEL_ABOUT_H
