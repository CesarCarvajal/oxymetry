#ifndef FFT_H
#define FFT_H

/* External includes */
#include <fftw3.h>

/**
 * @brief The 'Application' class
 */

class fft
{


public:

    void getFFT(int N);

    double wavelengths[1500];
    double counts[1000];
    double time[1000];
    double fft_data[500];

    double fft_DC[1500];
    double fft_W[1500];
    double fft_2W[1500];
    double fft_Compensation_Signal[1500];

};

#endif // FFT_H
