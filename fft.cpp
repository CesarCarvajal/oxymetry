#include "fft.h"
#include <fftw3.h>
#include <complex.h>
#include <iostream>

#include <QFile>
#include <QTextStream>
#include <QIODevice>
#include <QString>
#include <QStringList>
#include <QDebug>
#include <math.h>
#include <algorithm>

using namespace std;

/**
 * @brief Constructor of 'FFT' class
 */

void fft::getFFT(int n)
{

       QString FileName = "Data/Data.TXT";
       QFile file(FileName);

       fftw_complex *in;
       fftw_complex *out;
       fftw_plan plan_forward;

         /*
           Create the input array.
         */
         in = (fftw_complex *)fftw_malloc(sizeof(fftw_complex) * n);

       if(!file.exists()){
       qDebug() << "File: " << FileName << "doesn't exists!";
       }

       QString Row;

       if(file.open(QIODevice::ReadOnly)) {

       QTextStream stream(&file);

       int k = 0;

            while(!stream.atEnd()){

                Row = stream.readLine();

                QStringList Readed_Row = Row.split(';');

                Readed_Row.replaceInStrings(",",".");

                QString Row_waves = Readed_Row.at(0);

                wavelengths[k] = Row_waves.toDouble();

                for (int j=0; j <= Readed_Row.length()-4; j++){

                    QString Row_counts = Readed_Row.at(j+3);

                    counts[j] = Row_counts.toDouble();

                    time[j] = j/(n*0.01);
                    in[j][1] = 0;
                    in[j][0] = counts[j];

                }

            /*
             *FFT part
             *
              Create the output array.
            */

              out = (fftw_complex *)fftw_malloc(sizeof(fftw_complex) * n);

              plan_forward = fftw_plan_dft_1d ( n, in, out, FFTW_FORWARD, FFTW_ESTIMATE );

              fftw_execute ( plan_forward );

             // double max = fabs(out[0][0]); // Normalize

              fft_DC[k] = fabs(out[0][0]);
              fft_W[k] = fabs(out[20][0]);
              fft_2W[k] = fabs(out[40][0]);
              fft_Compensation_Signal[k] = fft_W[k]/fft_2W[k];

             // fft_ratio[k] =

              if (k == 438){
              for ( int  i = 0; i < n/2; i++ )
              {
                fft_data[i] = fabs(out[i][0]);
              //  qDebug() << time[i] << " " << fft_data[i];
             }
              }

              k = k+1;

}

              /*
              Free up the allocated memory.
            */

        }

       file.close();

       fftw_destroy_plan ( plan_forward );
       fftw_free ( in );
       fftw_free ( out );


     return ;
}



