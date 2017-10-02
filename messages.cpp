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

/* External includes */
#include <QMessageBox>
#include <QString>
#include <QSpacerItem>
#include <QGridLayout>

/* Internal includes */
#include "messages.h"

/**
 * Message box types
 */
typedef enum
{
    CRITICAL,
    WARNING,
    INFORMATION
} MESSAGE_TYPE;

/*
 * Prototypes
 */
void showMessage(QString caption, QString text, QString details, MESSAGE_TYPE type);

/**
 * @brief Shows critical message box
 * @param[in] text Text for message box
 * @param informativeText
 * @param detailedText
 */
void showCritical(QString text, QString details)
{
    showMessage("Critical error", text, details, CRITICAL);
}

/**
 * @brief Shows warning message box
 * @param text
 * @param informativeText
 * @param detailedText
 */
void showWarning(QString text, QString details)
{
    showMessage("Warning", text, details, WARNING);
}

/**
 * @brief Shows information message box
 * @param text
 * @param informativeText
 * @param detailedText
 */
void showInformation(QString text, QString details)
{
    showMessage("Information", text, details, INFORMATION);
}

/**
 * @brief Shows message box
 * @param text
 * @param informativeText
 * @param detailedText
 * @param type
 */
void showMessage(QString caption, QString text, QString details, MESSAGE_TYPE type)
{
    QMessageBox msgBox;

    /* Configure message box */
    msgBox.setWindowTitle(caption);
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setDefaultButton(QMessageBox::Ok);
    msgBox.setWindowFlags(Qt::WindowStaysOnTopHint);
    msgBox.setText(text);

    /* Does a detailed text exist? */
    if (NULL != details)
    {
        /* Set message box detailed text */
        msgBox.setDetailedText(details);
    }

    switch (type)
    {
        case CRITICAL:
        {
            /* Set critical icon */
            msgBox.setIcon(QMessageBox::Critical);
            break;
        }

        case WARNING:
        {
            /* Set warning icon */
            msgBox.setIcon(QMessageBox::Warning);
            break;
        }

        case INFORMATION:
        {
            /* Set information icon */
            msgBox.setIcon(QMessageBox::Information);
            break;
        }

        default:
            break;
    }

    /* Set minimum dialog width to 320 pixel */
    QSpacerItem *horizontalSpacer = new QSpacerItem(320, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
    QGridLayout *layout = (QGridLayout *)msgBox.layout();
    layout->addItem(horizontalSpacer, layout->rowCount(), 0, 1, layout->columnCount());

    /* Execute message box */
    msgBox.exec();
}
