#include "fft.h"
#include <fftw3.h>
#include <complex.h>
#include <iostream>
#include <QMessageBox>
#include <QFileInfo>
#include <QFile>
#include <QTextStream>
#include <QIODevice>
#include <QString>
#include <QStringList>
#include <QDebug>
#include <math.h>
#include <algorithm>
#include "ui_panel.h"
#include <qdir.h>
#include <QDate>
#include "panel.h"
#include <QTime>

using namespace std;

/**
 * @brief Constructor of 'FFT' class
 */

void fft::getFFT(int n)
{
    QString date = QDate::currentDate().toString("dd MM yyyy");
    //QString hour = QTime::currentTime().toString("hh mm");

    QDir().mkdir("FFT Polarimeter Measurements");
    QString folderOne = "FFT Data " + date;
    QDir("FFT Polarimeter Measurements").mkdir(folderOne);// + " - " + hour);

    QString FFT_File_Name = "FFT_" + date + ".txt";
    QString path = "FFT Polarimeter Measurements/"+folderOne+"/"+FFT_File_Name;

    QFile FFT_File(path);
    QFileInfo checkFile(path);
    FILE *fileFFT = fopen(path.toLatin1().data(), "wt");


    /* Check if file exists */
    if (checkFile.exists() && checkFile.isFile())
    {

        // Later Develop
        qDebug() << "FFT File Exists";

    }
    else
    {
        /* File doesn't exist; export data for current spectrometer */
        qDebug() << "FFT File Created";

    }

    QString FileName = "Data/Data.TXT";
    QFile file(FileName);

    fftw_complex *in;
    fftw_complex *out;
    fftw_plan plan_forward;

    /*
    Create the input array.
    */
    in = (fftw_complex *)fftw_malloc(sizeof(fftw_complex) * n);
    out = (fftw_complex *)fftw_malloc(sizeof(fftw_complex) * n);
    plan_forward = fftw_plan_dft_1d ( n, in, out, FFTW_FORWARD, FFTW_ESTIMATE );

    if(!file.exists()){
        qDebug() << "File: " << FileName << "doesn't exists!";
    }

    QString Row;

    if(file.open(QIODevice::ReadOnly)) {

        QTextStream stream(&file);
        int k = 0;
        double AverageDC =0, AverageW = 0, Average2W = 0;

        while(!stream.atEnd()){

            Row = stream.readLine();
            QStringList Readed_Row = Row.split(';');
            Readed_Row.replaceInStrings(",",".");
            QString Row_waves = Readed_Row.at(0);
            wavelengths[k] = Row_waves.toDouble();

            for (int j=0; j <= Readed_Row.length()-4; j++){

                QString Row_counts = Readed_Row.at(j+3);
                counts[j] = Row_counts.toDouble();
                in[j][1] = 0;
                in[j][0] = counts[j];
            }

            /*
             *FFT part
             *
              Create the output array.
            */

            fftw_execute ( plan_forward );
            fft_DC[k] = fabs(out[0][0]);
            fft_W[k] = fabs(out[20][0]);
            fft_2W[k] = fabs(out[40][0]);
            fft_Compensation_Signal[k] = fft_W[k]/fft_2W[k];

            AverageDC = AverageDC + fft_DC[k];
            AverageW = AverageW + fft_W[k];
            Average2W = Average2W + fft_2W[k];

            if (k == 438){

                for ( int  i = 0; i < n/2; i++ )
                {
                    fft_data[i] = fabs(out[i][0]);
                    time[i] = i/(n*0.01);
                }
            }

            k = k+1;
        }

        /*
        Average the Analyzed Signals
      */

        for ( int  i = 0; i < n/2; i++ )
        {
            fft_Average_DC_signal[i] = AverageDC/n;
            fft_Average_W_signal[i] = AverageW/n;
            fft_Average_2W_signal[i] = Average2W/n;
        }
    }

       /*
       Free up the allocated memory.
     */

    /* Close file */
    file.close();
    fclose(fileFFT);

    fftw_destroy_plan ( plan_forward );
    fftw_free ( in );
    fftw_free ( out );

    return ;
}



