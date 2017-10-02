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

#ifndef SPLASH_H
#define SPLASH_H

/* External includes */
#include <QSplashScreen>
#include <QPixmap>
#include <QPainter>
#include <QString>
#include <QColor>
#include <QRect>
#include <QObject>
#include <QEvent>

/**
 * @brief The 'Splash' class
 */
class Splash : public QSplashScreen
{
public:
    /* Constructor */
    explicit Splash(const QPixmap& pixmap);

    virtual void drawContents(QPainter *painter);
    void showStatusMessage(const QString &message, const QColor &color = Qt::black);
    void setMessageRect(QRect rect, int alignment = Qt::AlignLeft);

    /* Destructor */
    ~Splash(void);

protected:
    bool eventFilter(QObject *target, QEvent *event);

private:
    QString message;
    int alignment;
    QColor color;
    QRect rect;
};

#endif // SPLASH_H
