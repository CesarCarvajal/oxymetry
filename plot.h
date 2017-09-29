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

#ifndef PLOT_H
#define PLOT_H

/* External includes */
#include <QWidget>
#include <QSize>
#include <QString>
#include <QFont>

/* Qwt library */
#include "qwt_plot.h"
#include "qwt_plot_curve.h"
#include "qwt_plot_zoomer.h"
#include "qwt_plot_panner.h"
#include "qwt_plot_canvas.h"
#include "qwt_plot_renderer.h"
#include "qwt_plot_grid.h"
#include "qwt_legend.h"

/**
 * @brief The 'Plot' class
 */
class Plot : public QwtPlot
{
    Q_OBJECT

public:
    /* Constructor */
    explicit Plot(QWidget *parent = NULL);

    QSize minimumSizeHint(void) const;
    QSize sizeHint(void) const;

    void enableZoom(void);
    void disableZoom(void);

    /* Update graph */
    void update(void);

    /* Save graph */
    void save(QString filename);

    /* Set axis title */
    void setXAxisTitle(QString title);
    void setYAxisTitle(QString title);

    /* Set caption */
    void setCaption(QString caption);

    /* Set axis limits */
    void setXAxis(double min, double max);
    void setYAxis(double min, double max);

    /* Hide/show grid */
    void hideGrid(void);
    void showGrid(void);

    /* Destructor */
    ~Plot(void);

private:
    QwtPlotZoomer *zoomer = nullptr;
    QwtPlotGrid *grid = nullptr;
    QwtLegend *legend = nullptr;
    QwtPlotCanvas *canvas = nullptr;
    QFont plotFont, axisFont;
};

#endif  // PLOT_H
