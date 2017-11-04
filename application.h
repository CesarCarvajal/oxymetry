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

#ifndef APPLICATION_H
#define APPLICATION_H

/* External includes */
#include <QApplication>

/* Avantes AvaSpec library */
#include "avaspec.h"

/**
 * @brief The 'Application' class
 */
class Application : public QApplication
{
    Q_OBJECT

public:
    /* Constructor */
    Application(int &argc, char *argv[]);

    void emitsignal(int WParam, int LParam);
    void emitPolsignal(int WParam, int LParam);
    static void callback(AvsHandle *handle, int *result);
    static void callPolback(AvsHandle *handle, int *result);

    /* Destructor */
    ~Application(void);

signals:
    /* Signal when spectrometers report new data */
    void DataIsHere(int WParam, int LParam);
    void DataPolIsHere(int WParam, int LParam);
};

#endif // APPLICATION_H
