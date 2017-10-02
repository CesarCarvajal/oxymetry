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

/* Qwt library */
#include "qwt_plot.h"
#include "qwt_plot_curve.h"
#include "qwt_plot_zoomer.h"
#include "qwt_plot_panner.h"
#include "qwt_plot_canvas.h"
#include "qwt_plot_renderer.h"
#include "qwt_legend.h"
#include "qwt_plot_legenditem.h"

/* Internal includes */
#include "plot.h"

/**
 * @brief Constructor of 'Plot' class
 * @param parent Parent widget
 */
Plot::Plot(QWidget *parent):
    QwtPlot(parent),
    legend(NULL)
{
    /* Set plot font */
    plotFont.setFamily("Arial");
    plotFont.setPointSize(8);

    /* Set axis font */
    axisFont.setFamily("Arial");
    axisFont.setBold(true);
    axisFont.setPointSize(10);

    /* Assign axis font */
    setAxisFont(xBottom, plotFont);
    setAxisFont(yLeft, plotFont);
    setAxisFont(yRight, plotFont);

    /* Set canvas style sheet */
    canvas = new QwtPlotCanvas();
    canvas->setStyleSheet("border: 0px; border-radius: 0px; background-color: white;");
    setCanvas(canvas);

    /* Set up zoom function */
    zoomer = new QwtPlotZoomer(canvas);
    zoomer->setMousePattern(QwtEventPattern::MouseSelect2,
        Qt::RightButton, Qt::ControlModifier);
    zoomer->setMousePattern(QwtEventPattern::MouseSelect3,
        Qt::RightButton);

    /* Set up grid */
    grid = new QwtPlotGrid;
    grid->enableXMin(true);
    grid->setMajorPen(Qt::gray, 0, Qt::DotLine);
    grid->setMinorPen(Qt::darkGray, 0, Qt::DotLine);
    grid->attach(this);

    /* Show legend */
    legend = new QwtLegend;
    insertLegend(legend, QwtPlot::BottomLegend);

    /* Show plot */
    this->show();
}

/**
 * @brief Set x-axis limits
 * @param[in] min Minimum
 * @param[in] max Maximum
 */
void Plot::setXAxis(double min, double max)
{
    setAxisScale(xBottom, min, max);
    zoomer->setZoomBase(true);
}

/**
 * @brief Set y-axis limits
 * @param[in] min Minimum
 * @param[in] max Maximum
 */
void Plot::setYAxis(double min, double max)
{
    setAxisScale(yLeft, min, max);
    zoomer->setZoomBase(true);
}

QSize Plot::minimumSizeHint(void) const
{
    return QSize(600, 400);
}

QSize Plot::sizeHint(void) const
{
    return QSize(600, 400);
}

void Plot::enableZoom(void)
{
    zoomer->setEnabled(true);
}

void Plot::disableZoom(void)
{
    zoomer->setEnabled(false);
}

/**
 * @brief Update graph
 */
void Plot::update(void)
{
    /* Update graph */
    replot();
}

/**
 * @brief Save graph
 */
void Plot::save(QString filename)
{
    QwtPlotRenderer renderer;

    /* Save to disk */
    renderer.exportTo(this, filename);
}

/**
 * @brief Set x-axis title
 * @param[in] title Axis title
 */
void Plot::setXAxisTitle(QString title)
{
    QwtText bottomTitle = title;

    /* Set font and update title */
    bottomTitle.setFont(axisFont);
    setAxisTitle(xBottom, bottomTitle);
}

/**
 * @brief Set y-axis title
 * @param[in] title Axis title
 */
void Plot::setYAxisTitle(QString title)
{
    QwtText leftTitle = title;

    /* Set font and update title */
    leftTitle.setFont(axisFont);
    setAxisTitle(yLeft, leftTitle);
}

/**
 * @brief Set graph caption
 * @param[in] caption Graph caption
 */
void Plot::setCaption(QString caption)
{
    QwtText title = caption;

    /* Set font and update caption */
    title.setFont(axisFont);
    setTitle(title);
}

/**
 * @brief Hide grid
 */
void Plot::hideGrid(void)
{
    grid->hide();
}

/**
 * @brief Show grid
 */
void Plot::showGrid(void)
{
    grid->show();
}

/**
 * @brief Destructor of 'Plot' class
 */
Plot::~Plot(void)
{
    /* Check handle */
    if (nullptr != zoomer)
    {
        /* Free memory */
        delete zoomer;
        zoomer = nullptr;
    }

    /* Check handle */
    if (nullptr != grid)
    {
        /* Free memory */
        delete grid;
        grid = nullptr;
    }

    /* Check handle */
    if (nullptr != legend)
    {
        /* Free memory */
        delete legend;
        legend = nullptr;
    }

    /* Check handle */
    if (nullptr != canvas)
    {
        /* Free memory */
        delete canvas;
        canvas = nullptr;
    }
}
