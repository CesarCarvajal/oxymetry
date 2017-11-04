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

#ifndef FFT_H
#define FFT_H


/*
 * External includes
 */

/* Qt library */
#include <QString>
#include <QFileDialog>

/*
 * Internal includes
 */

/* FFT Library */
#include <fftw3.h>

/**
 * @brief The 'Application' class
 */

class fft
{

public:

    void getFFTfromRawData(QFileInfo FileName);
    void getFFTfromFFTData(QFileInfo FileName);

    void Calculate_Live_FFT(double *Data);

    void saveFFTtoFile(QFileInfo FileDetails);
    void InitializeFFTArrays(QString FilePath, bool isTXT);
    fftw_complex *CalculateFFT(int N, double Data[]);

    /* Size of Nr Spectra */
    double *counts = nullptr;
    double *time = nullptr;
    double *fft_data = nullptr;

    /* Size of Nr Waves */
    double *wavelengths = nullptr;
    double *fft_DC, *fft_W, *fft_2W = nullptr;
    double *fft_Compensation_Signal = nullptr;

    int NrSpectra;
    int NrWaves=0;
    int f_w;
    double IntTime;
    double FrequencyF;

private:

    double ConcentrationC1;
    double ConcentrationC2;
    double NrAverage;

    void ReadFileName(QString ExtractInfoName, QString FilePath, bool isTXT);

};

#endif // FFT_H
