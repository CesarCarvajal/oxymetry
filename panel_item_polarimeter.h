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

#ifndef PANEL_ITEM_POLARIMETER_H
#define PANEL_ITEM_POLARIMETER_H

/* External includes */
#include <QWidget>
#include <QString>

namespace Ui {
    class PanelItem_Pol;
}

/**
 * @brief The 'PanelItem' class
 */
class PanelItem_Pol : public QWidget
{
    Q_OBJECT

public:
    /* Constructor */
    explicit PanelItem_Pol(QWidget *parent = 0, QString name = NULL);

    /* Set name of panel item */
    void setName(QString name);

    /* Get or set integration time */
    float getIntegrationTime(void);
    void setIntegrationTime(float value);

    /* Get or set number of averages */
    int getNumberOfAverages(void);
    void setNumberOfAverages(int value);

    /* Get or set is saturated */
    bool getIsSaturated(void);
    void setIsSaturated(bool value);

    /* Get or set is enabled */
    bool getIsEnabled(void);
    void setIsEnabled(bool value);

    /* Enable/disable clickable labels */
    void setClickableLabelsEnabled(bool value);
    void setClickableLabelsDisabled(bool value);

    /* Destructor */
    ~PanelItem_Pol(void);

    /* User interface */
    Ui::PanelItem_Pol *ui;

private:
    float integrationTime;  /* Integration time */
    int numberOfAverages;   /* Number of averages */
    bool isSaturated;       /* Has saturated pixels? */
    bool isEnabled;         /* Spectrometer enabled? */
};

#endif // PANEL_ITEM_POLARIMETER_H
