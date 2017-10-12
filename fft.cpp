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

/*
 * External includes
 */

/* Qt libraries */
#include <QMessageBox>
#include <QFileInfo>
#include <QFile>
#include <QTextStream>
#include <QIODevice>
#include <QString>
#include <QStringList>
#include <QDebug>
#include <QDir>
#include <QTime>
#include <QDate>

/*
 * Internal includes
 */

/* General stuff */
#include <math.h>
#include <algorithm>

/* FFT */
#include "fft.h"
#include <fftw3.h>
#include <complex.h>

/* Panel */
#include "ui_panel.h"
#include "panel.h"

/**
 * @brief Constructor of 'FFT' class
 */

fftw_complex* fft::CalculateFFT(int N, double Data[])
{

    fftw_complex *in;
    fftw_complex *out;
    fftw_plan plan_forward;

    /*
    Create the input and output arrays.
    */
    in = (fftw_complex *)fftw_malloc(sizeof(fftw_complex) * N);
    out = (fftw_complex *)fftw_malloc(sizeof(fftw_complex) * N);

    /*
    Create the Plan of the FFT.
    */
    plan_forward = fftw_plan_dft_1d ( N, in, out, FFTW_FORWARD, FFTW_ESTIMATE );

    for (int j=0; j < N; j++){

        in[j][1] = 0;
        in[j][0] = Data[j];

    }

    fftw_execute ( plan_forward );

    fftw_destroy_plan ( plan_forward );
    fftw_free ( in );

    return out;

    fftw_free ( out );

    }


void fft::getFFTfromRawData(QFileInfo fileInformation)
{

    QString FileName = fileInformation.absoluteFilePath();
    QFile file(FileName);

    if(!file.exists()){
        qDebug() << "File: " << FileName << "doesn't exists!";
    }

    QString Row;
    fftw_complex *outputFFT;

    if(file.open(QIODevice::ReadOnly)) {

        QTextStream stream(&file);

        int k = -6;
        QString spliter = "\t\t";
        int beginer = 1;

        if(fileInformation.suffix()=="TXT"){
            k = -10;
            spliter = ";";
            beginer = 3;
        }

        double AverageDC =0, AverageW = 0, Average2W = 0;

        while(!stream.atEnd()){

            Row = stream.readLine();

            if (k>=0 && Row!=""){

                QStringList Readed_Row = Row.split(spliter);
                Readed_Row.replaceInStrings(",",".");
                QString Row_waves = Readed_Row.at(0);
                wavelengths[k] = Row_waves.toDouble();

                for (int j=beginer; j < Readed_Row.length(); j++){

                    QString Row_counts = Readed_Row.at(j);
                    counts[j] = Row_counts.toDouble();
            }

            outputFFT = CalculateFFT(Readed_Row.length() - beginer, counts);

            fft_DC[k] = fabs(outputFFT[0][0]);
            fft_W[k] = fabs(outputFFT[20][0]);
            fft_2W[k] = fabs(outputFFT[40][0]);
            fft_Compensation_Signal[k] = fft_W[k]/fft_2W[k];

            AverageDC = AverageDC + fft_DC[k];
            AverageW = AverageW + fft_W[k];
            Average2W = Average2W + fft_2W[k];

            if (k == 438){

                for ( int  i = 0; i < 500; i++ )
                {
                    fft_data[i] = fabs(outputFFT[i][0]);
                    time[i] = i/(1000*0.01);
                }
            }

        /*
        Average the Analyzed Signals
      */

        for ( int  i = 0; i < 500; i++ )
        {
            fft_Average_DC_signal[i] = AverageDC/1000;
            fft_Average_W_signal[i] = AverageW/1000;
            fft_Average_2W_signal[i] = Average2W/1000;
        }
            }
                     k = k+1;
        }
    }

       /*
       Free up the allocated memory.
     */

    /* Close file */
    file.close();

    fftw_free ( outputFFT );

    return ;
}


/*

    // Saving Option of the FFT
    QString date = QDate::currentDate().toString("dd MM yyyy");

    QDir().mkdir("FFT Polarimeter Measurements");
    QString folderOne = "FFT Data " + date;
    QDir("FFT Polarimeter Measurements").mkdir(folderOne);

    QString FFT_File_Name = "FFT_" + date + ".txt";
    QString path = "FFT Polarimeter Measurements/"+folderOne+"/"+FFT_File_Name;

    QFile FFT_File(path);
    QFileInfo checkFile(path);
    FILE *fileFFT = fopen(path.toLatin1().data(), "wt");

    //Check if file exists
    if (checkFile.exists() && checkFile.isFile())
    {

        // Later Develop
        qDebug() << "FFT File Exists";

    }
    else
    {
        File doesn't exist; export data for current spectrometer
        qDebug() << "FFT File Created";

     //    Write serial number
      fprintf(file, "Serial number: %s\n", getSerialNumber().toLatin1().data());

      //  Check for readable name
        if (hasReadableName())
        {
         //   Write readable name
           fprintf(file, "Readable name: %s\n", getReadableName().toLatin1().data());
       }

        //Write integration time, number of averages and dynamic dark correction
        fprintf(file, "Integration time: %.2f ms\n", getIntegrationTime());
        fprintf(file, "Number of averages: %i\n", getNumberOfAverages());
        fprintf(file, "Dynamic dark correction: %s\n", getDynamicDarkCorrection() ? "true" : "false");
        fprintf(file, "Timestamp: %s\n\n", QDateTime::currentDateTime().toString().toLatin1().data());
}
        fclose(fileFFT);

*/
