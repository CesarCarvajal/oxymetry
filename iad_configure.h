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

#ifndef IAD_CONFIGURE_H
#define IAD_CONFIGURE_H

/* External includes */
#include <QString>

/**
 * @brief The 'ConfigureIAD' class
 */
class ConfigureIAD
{
public:
    /* Constructor */
    explicit ConfigureIAD(QString fileName);

    /* Did the user run the assistant? */
    bool getIsConfigured(void);

    /* Get configuration name */
    QString getConfigurationName(void);

    /* Destructor */
    ~ConfigureIAD(void);

private:
    /* User configurated IAD */
    bool isConfigured = false;

    /* Path to configuration file */
    QString configPath = NULL;
};

#endif // IAD_CONFIGURE_H
