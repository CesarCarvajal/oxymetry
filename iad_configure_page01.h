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

#ifndef IAD_CONFIGURE_PAGE01_H
#define IAD_CONFIGURE_PAGE01_H

/* External includes */
#include <QDialog>
#include <QWidget>
#include <QString>

namespace Ui {
    class ConfigureIADPage01;
}

/**
 * Assignment types
 */
typedef enum
{
    DIFFUSE_REFLECTION,
    DIFFUSE_TRANSMITTANCE,
    UNSCATTERED_TRANSMITTANCE
} ASSIGNMENT_TYPE;

/**
 * @brief The 'ConfigureIADPage01' class
 */
class ConfigureIADPage01 : public QDialog
{
    Q_OBJECT

public:
    /* Constructor */
    explicit ConfigureIADPage01(QWidget *parent = 0);

    /* Load settings from configuration file */
    void load(QString fileName);

    /* Save settings to configuration file */
    void save(QString fileName);

    /* Destructor */
    ~ConfigureIADPage01(void);

    Ui::ConfigureIADPage01 *ui;

private slots:
    void update(void);
    void cancel(void);
    void next(void);
};

#endif // IAD_CONFIGURE_PAGE01_H
