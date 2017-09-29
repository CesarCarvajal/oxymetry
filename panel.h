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

#ifndef PANEL_H
#define PANEL_H

/* External includes */
#include <QDialog>
#include <QWidget>
#include <QListWidget>
#include <QListWidgetItem>
#include <QSignalMapper>
#include <QList>
#include <QTimer>

/* Qwt library */
#include "qwt_plot_curve.h"

/* Internal includes */
#include "panel_item.h"

namespace Ui {
    class Panel;
}

/**
 * @brief The 'Panel' class
 */
class Panel : public QDialog
{
    Q_OBJECT

public:
    /* Constructor */
    explicit Panel(QWidget *parent = 0);

    /* Graphical functions */
    bool isCurveVisible(unsigned int i);
    void setCurveVisible(unsigned int i, bool value);
    void updateGraph(void);

    /* Destructor */
    ~Panel(void);

public slots:
    /* Called if new data signal arrived */
    void ReceiveDataIsHere(int WParam, int LParam);

private slots:
    /* Functions for preview */
    void togglePreview(void);
    void startPreview(void);
    void stopPreview(void);
    void storeToRam(void);
    void timePattern(void);
    void showLegend(void);
    void saveGraph(void);
    void exportData(void);
    void showAbout(void);
    void updateProgress(void);

    /* Functions for spectrometer items */
    void handleClickEvent(QWidget *widget);

    /* Functions for Inverse Adding-Doubling */
    void newConfigurationIAD(void);
    void openConfigurationIAD(void);
    void showConfigurationIAD(void);
    void calibrateIAD(void);
    void measureIAD(void);
    void liveViewIAD(void);

private:
    /* Automatic adjustment of integration time */
    void adjustIntegrationTime(unsigned int id);

    /* General stuff */
    bool previewRunning = false;

    /* Preview stuff */
    Ui::Panel *ui;
    QSignalMapper *signalMapper;
    QList<PanelItem *> devices;
    QTimer *timer;

    /* Device graph */
    QList<QwtPlotCurve *> curves;

    /* Last path for data export */
    QString lastExportPath;

    /* Inverse Adding-Doubling stuff */
    QString configPath;

    double *Rd_factor = nullptr;
    double *Td_factor = nullptr;
    double *Tu_factor = nullptr;

    QwtPlotCurve *M_R;
    QwtPlotCurve *M_T;
    QwtPlotCurve *M_U;
};

#endif // PANEL_H
