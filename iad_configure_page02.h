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

#ifndef IAD_CONFIGURE_PAGE02_H
#define IAD_CONFIGURE_PAGE02_H

/* External includes */
#include <QDialog>
#include <QWidget>
#include <QString>

namespace Ui {
    class ConfigureIADPage02;
}

/**
 * @brief The 'ConfigureIADPage02' class
 */
class ConfigureIADPage02 : public QDialog
{
    Q_OBJECT

public:
    /* Constructor */
    explicit ConfigureIADPage02(QWidget *parent = 0);

    /* Load settings from configuration file */
    void load(QString fileName);

    /* Save settings to configuration file */
    void save(QString fileName);

    /* Destructor */
    ~ConfigureIADPage02(void);

    Ui::ConfigureIADPage02 *ui;

private slots:
    void update(void);
    void cancel(void);
    void finish(void);
};

#endif // IAD_CONFIGURE_PAGE02_H
