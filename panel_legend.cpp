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
#include <QTimer>
#include <QLabel>
#include <QMainWindow>

/* Internal includes */
#include "spectrometer.h"
#include "panel.h"
#include "panel_legend.h"
#include "ui_panel_legend.h"

/*
 * Global variables
 */
extern Spectrometer** ptrSpectrometers;
extern unsigned int m_NrDevices;
extern QString defaultColors[];

/* Main window */
extern Panel *mainWindow;

/**
 * @brief Constructor of 'PanelLegend' class
 * @param[in] parent Parent widget
 */
PanelLegend::PanelLegend(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PanelLegend)
{
    /* Set up user interface */
    ui->setupUi(this);

    /* Set window flags */
    this->setWindowFlags(Qt::Dialog | Qt::WindowTitleHint | Qt::WindowStaysOnTopHint | Qt::WindowCloseButtonHint);

    /* Disable resize of elements */
    this->setFixedSize(this->size());

    /* Prevent user from resizing the header */
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);

    /* Left align column titles */
    ui->tableWidget->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);

    /* Prevent user from editing the cells */
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    /* Four columns */
    ui->tableWidget->setColumnCount(3);

    /* Set column widths */
    ui->tableWidget->setColumnWidth(0, 25);
    ui->tableWidget->setColumnWidth(1, 90);
    ui->tableWidget->setColumnWidth(2, 184);

    unsigned int i = 0;

    /* Loop through devices */
    for (i = 0; i < m_NrDevices; i++)
    {
        /* Increase current row count */
        ui->tableWidget->setRowCount(ui->tableWidget->rowCount() + 1);

        pWidget.append(new QWidget(this));
        pCheckBox.append(new QCheckBox(this));
        pLayout.append(new QHBoxLayout(pWidget[i]));

        pLayout[i]->addWidget(pCheckBox[i]);
        pCheckBox[i]->setCursor(QCursor(Qt::PointingHandCursor));
        pLayout[i]->setAlignment(Qt::AlignCenter);
        pLayout[i]->setContentsMargins(0, 0, 0, 0);
        pWidget[i]->setLayout(pLayout[i]);

        pCheckBox[i]->setChecked(mainWindow->isCurveVisible(i));

        /* Put the checkbox for module activation into the first column */
        ui->tableWidget->setCellWidget(i, 0, pWidget[i]);

        QString serialNumber = ptrSpectrometers[i]->getSerialNumber();

        if (serialNumber.isEmpty())
        {
            serialNumber = "Unknown";
        }

        QString readableName = ptrSpectrometers[i]->getReadableName();

        if (readableName.isEmpty())
        {
            readableName = "Unknown";
        }

        QLabel *nt = new QLabel();

        nt->setText(serialNumber);
        nt->setStyleSheet("QLabel { color: " + defaultColors[i % 5] + "; margin-left: 2px; }");
        ui->tableWidget->setCellWidget(i, 1, nt);

        QLabel *nt2 = new QLabel();

        nt2->setText(readableName);
        nt2->setStyleSheet("QLabel { color: " + defaultColors[i % 5] + "; margin-left: 2px; }");
        ui->tableWidget->setCellWidget(i, 2, nt2);
    }

    /* Connect button signal handles */
    connect(ui->pushButton_close, SIGNAL(clicked(bool)), this, SLOT(apply()));
}

/**
 * @brief Accepts changed value
 */
void PanelLegend::apply(void)
{
    unsigned int i = 0;

    /* Loop through devices */
    for (i = 0; i < m_NrDevices; i++)
    {
        mainWindow->setCurveVisible(i, pCheckBox[i]->isChecked());
    }
    mainWindow->updateGraph();

    /* All fine */
    accept();
}

/**
 * @brief Destructor of 'PanelLegend' class
 */
PanelLegend::~PanelLegend(void)
{
    /* Delete user interface */
    delete ui;
}
