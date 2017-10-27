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

#ifndef PANEL_POLARIMETER_H
#define PANEL_POLARIMETER_H

/*
 * External includes
 */

/* Qt includes */
#include <QWidget>
#include <QString>
#include <QListWidget>
#include <QListWidgetItem>
#include <QSignalMapper>
#include <QList>

/* Qwt library */
#include "qwt_plot_curve.h"

/*
 * Internal includes
 */

/* General stuff */
#include "panel_item_polarimeter.h"
#include "configure_Polarimeter_Measure.h"
#include "fft.h"

/*
 * Other stuff
 */

namespace Ui {
    class PanelPolarimeter;
}

/**
 * @brief The 'Polarimeter' class
 */
class PanelPolarimeter : public QWidget
{
    Q_OBJECT

 public:
    /* Constructor */
    explicit PanelPolarimeter(QWidget *parent = 0);

    /* Graphical functions */
    bool isCurveVisible();
    void setCurveVisible(bool value);
    void updateGraph(void);

    /* Disable/enable polarimeter */
    void enable_Polarimeter_Measurement(bool activate);
    void SelectedSpectrometer_Polarimeter(void);
    void Plot_FFT_Graphs(double FFTLwavelengths[], double FFTLtime[], double FFTLfft_data[], double FFTLfft_DC[], double FFTLfft_W[], double FFTLfft_2W[], double FFTLfft_Compensation_Signal[]);
    void adjustIntegrationTime();

    /* Destructor */
    ~PanelPolarimeter(void);

private slots:
    /* Functions for spectrometer items */
    void handleClickEvent(QWidget *widget);

    /* Called if new data signal arrived */
    void ReceiveDataIsHerePol(int WParam, int LParam);

    /* Functions for Polarimeter */
    void start_Pol_Measurement(void);
    void stop_Pol_Measurement(void);
    void toggle_Pol_Measurement(void);

    /* Save Functions for Polarimeter */
    void saveGraph_Pol(void);

    void AutoSave_FFT(void);
    void AutoSave_Raw(void);
    void clearPlots(void);

    void plotFFTatSelectedWave( double FFTLfft_data[], double FFTLtime[]);

    void LoadFromFFT(void);
    void LoadFromRawData(void);

    /* Configuration of Measurements for Polarimeter */
    void ConfSetup_Pol_Measurement(void);
    void toggle_Pol_Calibration(void);
    void Calibrate_Pol_Start(void);
    void Calibrate_Pol_Stop(void);

    /* Live Anaylisi Data */
    void liveFFTAnalysis(void);

private:

    /* User interface */
    Ui::PanelPolarimeter *ui;

    QSignalMapper *signalMapper;

    QList<QwtPlotCurve *> FFT;

    /* Inverse Adding-Doubling stuff */
    QString RawDataPath, FFTDataPath;

    /* Polarimetry stuff */
    QwtPlotCurve *FFT_oneWave;
    QwtPlotCurve *FFT_DC, *FFT_W, *FFT_2W;
    QwtPlotCurve *Compensation_Signal;
    QwtPlotCurve *Average_DC_Signal, *Average_W_Signal, *Average_2W_Signal;
    fft FFTL;

public:

    QList<PanelItem_Pol *> devices2; 
    QList<QwtPlotCurve *> curves_Pol;
    bool PolMeasurementRunning = false;
    bool isFFTData = true;
    int SpectrometerNumber;
    int selectedWave;
    bool measurement_Pol_profileLoaded = false;

    double averaged_Raw_Signal;
    QVector<double> averaged_Raw_Signal_Difference;
    QVector<double> averaged_Raw_Signal_time;

    configurePolMeasure ConfigureMeasurement;

};

#endif // PANEL_POLARIMETER_H
