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
#include <messages.h>

/* FFT */
#include "fft.h"
#include <fftw3.h>
#include <complex.h>

/* Panel */
#include "ui_panel.h"
#include "panel.h"

/* Spectrometer control */
#include "spectrometer.h"

/*
 * Global variables
 */
extern Spectrometer** ptrSpectrometers;
extern unsigned int m_NrDevices;

/**
 * @brief Get the FFT analysis plots from FFT Type Data
 */
void fft::getFFTfromFFTData(QFileInfo fileInformation)
{

    /* Get the File Path and Name */
    QString FileName = fileInformation.absoluteFilePath();
    QFile file(FileName);

    /* Does the File exists? */
    if(!file.exists()){
        showWarning("File not Found!", "");
    }

    /* Get Information from File Name */
    ReadFileName(fileInformation.completeBaseName(), fileInformation.absoluteFilePath(), true);

    /* Create the readed row and skip the first 10 lines */
    QString Row;
    int k = -10;

    /* Open the file */
    if(file.open(QIODevice::ReadOnly)) {

        /* Get lines from file */
        QTextStream stream(&file);

        while(!stream.atEnd()){

            /* Read the current line in file */
            Row = stream.readLine();

            /* Have already skipped the first lines and there is information to save? */
            if (k>=0 && Row!=""){

                /* Get the values from the line */
                QStringList Readed_Row = Row.split("\t\t");
                Readed_Row.replaceInStrings(",",".");
                QString Row_waves = Readed_Row.at(0);

                /* Save the wavelengths on file */
                wavelengths[k] = Row_waves.toDouble();

                /* Save the DC, W and 2W amplitudes saved in the file */
                QString Row_Dat = Readed_Row.at(1);
                fft_DC[k] = Row_Dat.toDouble();
                Row_Dat = Readed_Row.at(2);
                fft_W[k] = Row_Dat.toDouble();
                Row_Dat = Readed_Row.at(3);
                fft_2W[k] = Row_Dat.toDouble();
                fft_Compensation_Signal[k] = fft_W[k]/fft_2W[k];

                /* What is the modulation frequency? */
                f_w = NrSpectra*(IntTime/1000)*FrequencyF;

                /* By default show the FFT values for the wavelength 537,57 nm */
                if (k == 438){

                    for ( int  i = 0; i < NrSpectra/2; i++ )
                    {
                        if (i != 0 || i != f_w || i != 2*f_w){

                            /* Amplitude at all other frequencies are set to zero */
                            fft_data[i] = 0;

                        }

                        /* Which frequencies are shown in the FFT? */
                        time[i] = i/(NrSpectra*(IntTime/1000));
                    }

                    fft_data[0] = fft_DC[k];
                    fft_data[f_w] = fft_W[k];
                    fft_data[2*f_w] = fft_2W[k];

                }
            }

            /* Counter of File Lines */
            k = k+1;
        }
    }

    /* Close file */
    file.close();

    return ;

}

/**
 * @brief Get the FFT analysis from Raw Data
 */
void fft::getFFTfromRawData(QFileInfo fileInformation)
{

    /* Get the File Path and Name */
    QString FileName = fileInformation.absoluteFilePath();
    QFile file(FileName);

    /* Does the File exists? */
    if(!file.exists()){
        showWarning("File not Found!", "");
    }

    /* Initialize the counters and spliter according to the type of file TXT or CS */
    int k = -6;
    QString spliter = "\t\t";
    int beginer = 1;
    QString Row;
    fftw_complex *outputFFT;

    /* Is it a txt from Avantes Software or a CS from Oxymetry Software? */
    bool isTXT = false;
    if(fileInformation.suffix()=="TXT"){
        k = -10;
        spliter = ";";
        beginer = 3;
        isTXT = true;
    }

    /* Get Information from File Name */
    ReadFileName(fileInformation.completeBaseName(), fileInformation.absoluteFilePath(), isTXT);

    /* Open the file */
    if(file.open(QIODevice::ReadOnly)) {

        /* Get lines from file */
        QTextStream stream(&file);

        while(!stream.atEnd()){

            /* Read the current line in file */
            Row = stream.readLine();

            /* Have already skipped the first lines and there is information to save? */
            if (k>=0 && Row!=""){

                /* Get the values from the line */
                QStringList Readed_Row = Row.split(spliter);
                Readed_Row.replaceInStrings(",",".");
                QString Row_waves = Readed_Row.at(0);

                /* Save the wavelengths on file */
                wavelengths[k] = Row_waves.toDouble();

                /* Save all the counts in saved in rows at the file */
                for (int j=beginer; j < Readed_Row.length()-1; j++){
                    QString Row_counts = Readed_Row.at(j);
                    counts[j] = Row_counts.toDouble();
                }

                /* With the current counts from a row, calculate the FFT */
                outputFFT = CalculateFFT(NrSpectra, counts);

                /* What is the modulation frequency? */
                f_w = NrSpectra*(IntTime/1000)*FrequencyF;

                /* From the Output array of FFT, save each of the frequency amplitudes */
                fft_DC[k] = fabs(outputFFT[0][0]);
                fft_W[k] = fabs(outputFFT[f_w][0]);
                fft_2W[k] = fabs(outputFFT[2*f_w][0]);
                fft_Compensation_Signal[k] = fft_W[k]/fft_2W[k];

                /* By default show the FFT values for the wavelength 537,57 nm */
                if (k == 438){
                    for ( int  i = 0; i < NrSpectra/2; i++ )
                    {
                        fft_data[i] = fabs(outputFFT[i][0]);
                        time[i] = i/(NrSpectra*(IntTime/1000));
                    }
                }
            }

            /* Counter of File Lines */
            k = k+1;
        }
    }

    /* Close file and Free Memory*/
    file.close();
    return ;
}

/**
 * @brief Get Information from File Name and from the file itself, for example the amount of frequencies or spectra used.
 */
void fft::ReadFileName(QString ExtractInfoName, QString FilePath, bool isTXT)
{
    /* Data to get from the File Name */
    QString Concentration1_File,Concentration2_File, IntTime_File, Frequency_File = "";
    ConcentrationC1 = IntTime = FrequencyF = ConcentrationC2 = NrAverage = NrWaves = NrSpectra = 0;

    /* Which "_" are we? */
    int l=0;

    /* Iterate through the name and find the "_" on it */
    for(int i=0; i < ExtractInfoName.length();i++){
        if (ExtractInfoName[i] == "_"){
            l = l+1;
            continue;
        }

        /* Extract the Data from the File Name depending on which "_" are we */
        if (l==0 && (ExtractInfoName[i] != 'C') && (ExtractInfoName[i-1] != 'C')){
            Concentration1_File = Concentration1_File + ExtractInfoName[i];
        } else if (l==1 && (ExtractInfoName[i] != 'C') && (ExtractInfoName[i-1] != 'C')){
            Concentration2_File = Concentration2_File + ExtractInfoName[i];
        }else if (l==2 && ExtractInfoName[i] != 'm' && ExtractInfoName[i] != 's'){
            IntTime_File = IntTime_File + ExtractInfoName[i];
        }else if (l==3 &&  ExtractInfoName[i] != 'H'){
            Frequency_File = Frequency_File + ExtractInfoName[i];
        }else{
            if (ExtractInfoName[i] == 'H'){ break;}
            continue;
        }
    }

    /* Get the number from file name and save it */
    ConcentrationC1 = Concentration1_File.toDouble();
    ConcentrationC2 = Concentration2_File.toDouble();
    IntTime = IntTime_File.toDouble();
    FrequencyF = Frequency_File.toDouble();

    /* There is some information in the file very important to know how many data are we using */
    InitializeFFTArrays(FilePath, isTXT);
}

/**
 * @brief Initialize the FFT arrays according to the information size given in the file.
 */
void fft::InitializeFFTArrays(QString FilePath, bool isTXT)
{
    /* Open the file to get the Nr of Spectra and Average Nr. */
    QFile file(FilePath);

    /* Is it a file from Avantes or from Oxymetry Software? It defines where to start reading the data */
    int line = (isTXT) ? 4 : 3;
    int counter = 1;

    /* Open the file */
    if(file.open(QIODevice::ReadOnly)) {

        QString ReadRow;
        QTextStream stream(&file);

        while(!stream.atEnd()){

            /* Read a line from the file */
            ReadRow = stream.readLine();
            QStringList Readed_Row = ReadRow.split(" ");
            QString RowInfo;

            /* Get the number of Averages and Spectra from the file depending on its type */
            if (counter==3 && isTXT==false){
                RowInfo = Readed_Row.at(line);
                NrAverage = RowInfo.toDouble();
            }else if (counter==4 && isTXT==false)
            {
                RowInfo = Readed_Row.at(line);
                NrSpectra = RowInfo.toInt();
            }else if (counter==3 && isTXT==true)
            {
                RowInfo = Readed_Row.at(line);
                NrSpectra = RowInfo.toInt();
                NrAverage = 0;
            }

            counter = counter+1;
        }

        /* How many wavelengths do we have? */
        NrWaves = (isTXT) ? (counter - 12): (counter - 7);
    }

    /* Initialize the variables according to the opened file */
    counts = new double[NrSpectra];
    time = new double[NrSpectra/2];
    fft_data = new double[NrSpectra/2];
    wavelengths = new double[NrWaves];
    fft_DC= new double[NrWaves];
    fft_W= new double[NrWaves];
    fft_2W= new double[NrWaves];
    fft_Compensation_Signal= new double[NrWaves];
}

/**
 * @brief Calculate the FFT from incoming Data
 */
fftw_complex* fft::CalculateFFT(int N, double Data[])
{
    /* Create the arrays to save the FFT inputs and outputs */
    fftw_complex *in;
    fftw_complex *out;
    fftw_plan plan_forward;

    /* Initialize the input and output arrays. */
    in = (fftw_complex *)fftw_malloc(sizeof(fftw_complex) * N);
    out = (fftw_complex *)fftw_malloc(sizeof(fftw_complex) * N);

    /* Create the Plan of the FFT */
    plan_forward = fftw_plan_dft_1d ( N, in, out, FFTW_FORWARD, FFTW_ESTIMATE );

    /* Get the data from the function input and save it as the input for FFT */
    for (int j=0; j < N; j++){
        in[j][1] = 0;
        in[j][0] = Data[j];
    }

    /* Calculate the FFT of the given data */
    fftw_execute ( plan_forward );

    /* Free memory */
    fftw_destroy_plan ( plan_forward );
    fftw_free ( in );

    return out;
    fftw_free ( out );
}

/**
 * @brief Save the FFT Data to a File
 */
void fft::saveFFTtoFile(QFileInfo FileDetails)
{
    /* Save the data with a folder with the current date */
    QString date = QDate::currentDate().toString("dd MM yyyy");
    QDir().mkdir("FFT Polarimeter Measurements");
    QString folderOne = "FFT Data " + date;
    QDir("FFT Polarimeter Measurements").mkdir(folderOne);

    /* Save the file with the same input data name, but adding FFT at the end */
    QString FFT_File_Name = FileDetails.completeBaseName() + "_FFT.txt";

    QString path = "FFT Polarimeter Measurements/"+folderOne+"/"+FFT_File_Name;
    QFile FFT_File(path);
    QFileInfo checkFile(path);
    bool save = true;

    /* Check if file exists */
    if (checkFile.exists() && checkFile.isFile())
    {
        /* File exists. Did we ask the user if files should be overwritten or not? */
        if (QMessageBox::No == QMessageBox::question(NULL, "File already exists", "Do you want to overwrite the existing file?",
                                                     QMessageBox::Yes | QMessageBox::No))
        {
            /* Button 'No' pressed; Don't Save the FFT data to the folder on Bin */
            save = false;
        }
    }

    /* The user decided to save the data */
    if(save){

        FILE *fileFFT = fopen(path.toLatin1().data(), "wt");

        /* Write serial number */
        fprintf(fileFFT, "Serial number: %s\n", ptrSpectrometers[0]->getSerialNumber().toLatin1().data());

        /* Check for readable name */
        if (ptrSpectrometers[0]->hasReadableName())
        {
            /* Write readable name */
            fprintf(fileFFT, "Readable name: %s\n", ptrSpectrometers[0]->getReadableName().toLatin1().data());
        }

        /* Write integration time, number of averages, number of spectra, frequency and date on file */
        fprintf(fileFFT, "Number of Recorded Spectra: %i\n", NrSpectra);
        fprintf(fileFFT, "Integration time: %.2f ms\n", IntTime);
        fprintf(fileFFT, "Number of averages: %.1f\n", NrAverage);
        fprintf(fileFFT, "Frequency: %.2f Hz\n", FrequencyF);
        fprintf(fileFFT, "Number of Wavelenths: %i\n", NrWaves);
        fprintf(fileFFT, "FFT Analysis on: %s\n\n", QDateTime::currentDateTime().toString().toLatin1().data());

        /* Loop through the wavelengths */
        for (int z = 0; z < NrWaves; z++)
        {
            /* Write FFT data headers */
            if (z == 0)
            {
                fprintf(fileFFT, "Wavelength \t \t");
                fprintf(fileFFT, "DC Amplitude \t \t");
                fprintf(fileFFT, "W Amplitude \t");
                fprintf(fileFFT, "2W Amplitude \t");
                fprintf(fileFFT, "W/2W \n");
            }

            /* Write wavelengths and amplitudes */
            fprintf(fileFFT, "%.4f\t\t", wavelengths[z]);
            fprintf(fileFFT, "%.6f\t\t", fft_DC[z]);
            fprintf(fileFFT, "%.6f\t\t", fft_W[z]);
            fprintf(fileFFT, "%.5f\t\t", fft_2W[z]);
            fprintf(fileFFT, "%.5f\t\t", fft_Compensation_Signal[z]);

            fprintf(fileFFT, "\n");

        }

        fprintf(fileFFT, "\n");
        fclose(fileFFT);
    }
}


/**
 * @brief Calculate the live FFT
 */
void fft::Calculate_Live_FFT(double *Data)
{



}
