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
    fftw_complex *CalculateFFT(int N, double Data[]);

    double counts[1000];
    double time[500];
    double fft_data[500];

    double wavelengths[2048];
    double fft_DC[2048], fft_W[2048], fft_2W[2048];
    double fft_Compensation_Signal[2048];
    double fft_Average_DC_signal[500], fft_Average_W_signal[500], fft_Average_2W_signal[500];

};

#endif // FFT_H
