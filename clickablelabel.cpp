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
#include <QWidget>
#include <QLabel>
#include <QMouseEvent>

/* Internal includes */
#include "clickablelabel.h"

/**
 * @brief Constructor of 'ClickableLabel' class
 */
ClickableLabel::ClickableLabel(QWidget* parent)
    : QLabel(parent)
{
    /* Nothing */
}

/**
 * @brief Receive mouse press events for the widget
 * @param event Event
 */
void ClickableLabel::mousePressEvent(QMouseEvent* event)
{
    /* Don't show 'unused parameter' warning */
    Q_UNUSED(event);

    emit clicked();
}

/**
 * @brief Destructor of 'ClickableLabel' class
 */
ClickableLabel::~ClickableLabel(void)
{
    /* Nothing */
}
