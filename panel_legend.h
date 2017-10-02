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

#ifndef PANEL_LEGEND_H
#define PANEL_LEGEND_H

/* External includes */
#include <QDialog>
#include <QWidget>
#include <QStringList>
#include <QString>
#include <QCheckBox>
#include <QHBoxLayout>

namespace Ui {
    class PanelLegend;
}

/**
 * @brief The 'PanelLegend' class
 */
class PanelLegend : public QDialog
{
    Q_OBJECT

public:
    /* Constructor */
    explicit PanelLegend(QWidget *parent = 0);

    /* Destructor */
    ~PanelLegend(void);

private slots:
    /* Button 'apply' clicked */
    void apply(void);

private:
    /* User interface */
    Ui::PanelLegend *ui;

    /* Lists for table widget */
    QList<QWidget *> pWidget;
    QList<QCheckBox *> pCheckBox;
    QList<QHBoxLayout *> pLayout;
};

#endif // PANEL_LEGEND_H
