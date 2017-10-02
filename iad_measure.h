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

#ifndef IAD_MEASURE_H
#define IAD_MEASURE_H

/* External includes */
#include <QString>
#include <QDate>
#include <QTime>

/**
 * @brief The 'MeasureIAD' class
 */
class MeasureIAD
{
public:
    /* Constructor */
    explicit MeasureIAD(void);

    /* Get or set measurement name */
    QString getName(void);
    void setName(QString name);

    /* Get or set measurement description */
    QString getDescription(void);
    void setDescription(QString description);

    bool measure(void);

    bool save(QString fileName);

    QDate getDate(void);
    QTime getTime(void);

    /* Destructor */
    ~MeasureIAD(void);

private:
    /* Measurement name and description */
    QString name = NULL, description = NULL;

    QDate date;
    QTime time;
};

#endif // IAD_MEASURE_H
