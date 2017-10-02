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
#include <QSplashScreen>
#include <QPixmap>
#include <QFont>
#include <QPainter>
#include <QString>
#include <QColor>
#include <QRect>
#include <QObject>
#include <QEvent>

/* Internal includes */
#include "splash.h"

/**
 * @brief Constructor of 'Splash' class
 * @param pixmap Pixmap for splashscreen
 */
Splash::Splash(const QPixmap& pixmap)
{
    /* Set window flags. Make it frameless. */
    setWindowFlags(Qt::SplashScreen | Qt::FramelessWindowHint);

    /* Assign icon */
    setPixmap(pixmap);

    QFont splashFont;

    /* Set message font */
    splashFont.setFamily("Arial");
    splashFont.setPointSize(9);
    setFont(splashFont);

    /* Handle events, e.g. mouse clicks */
    this->installEventFilter(this);
}

/**
 * @brief Handle events
 * @param target
 * @param event
 * @return
 */
bool Splash::eventFilter(QObject *target, QEvent *event)
{
    /* Don't show 'unused parameter' warning */
    Q_UNUSED(target);

    return ((event->type() == QEvent::MouseButtonPress) ||
            (event->type() == QEvent::MouseButtonDblClick));
}

/**
 * @brief Draw splash screen
 * @param painter
 */
void Splash::drawContents(QPainter *painter)
{
    QPixmap textPix = QSplashScreen::pixmap();

    /* Set color and draw text */
    painter->setPen(this->color);
    painter->drawText(this->rect, this->alignment, this->message);
}

/**
 * @brief Update message text and color
 * @param message
 * @param color
 */
void Splash::showStatusMessage(const QString &message, const QColor &color)
{
    this->message = message;
    this->color = color;
    this->showMessage(this->message, this->alignment, this->color);
}

/**
 * @brief Update message position and alignment
 * @param rect
 * @param alignment
 */
void Splash::setMessageRect(QRect rect, int alignment)
{
    this->rect = rect;
    this->alignment = alignment;
}

/**
 * @brief Destructor of 'Splash' class
 */
Splash::~Splash(void)
{
}
