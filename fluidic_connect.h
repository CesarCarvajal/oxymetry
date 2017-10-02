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

#ifndef FLUIDIC_CONNECT_H
#define FLUIDIC_CONNECT_H

/* ID's for auto-connect functionality */
#define TEENSY_VENDOR_ID 5824
#define TEENSY_DEVICE_ID 1155

/* External includes */
#include <QDialog>
#include <QWidget>
#include <QList>
#include <QSerialPortInfo>

namespace Ui {
    class ConnectFluidic;
}

/**
 * @brief The 'ConnectFluidic' class
 */
class ConnectFluidic : public QDialog
{
    Q_OBJECT

public:
    /* Constructor */
    explicit ConnectFluidic(QWidget *parent = 0);

    /* Destructor */
    ~ConnectFluidic(void);

private slots:
    /* Button 'apply' clicked */
    void apply(void);

    /* Button 'cancel' clicked */
    void cancel(void);

    /* Button 'refresh' clicked */
    void refresh(void);

private:
    Ui::ConnectFluidic *ui;

    /* Structure for port information */
    QList<QSerialPortInfo> ports;
};

#endif // FLUIDIC_CONNECT_H
