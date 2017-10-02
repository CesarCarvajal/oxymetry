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

/* External includes */
#include <QApplication>
#include <QString>
#include <QSettings>
#include <QRect>
#include <windows.h>

/* Internal includes */
#include "application.h"
#include "spectrometer.h"
#include "messages.h"
#include "panel.h"
#include "splash.h"
#include "fluidic_control.h"
#include "light_control.h"

/*
 * Global variables
 */
extern QSettings *settings;
Spectrometer** ptrSpectrometers = nullptr;
unsigned int m_NrDevices = 0;

/*
 * Widget handles (e.g. toolkits)
 */
Panel *mainWindow = nullptr;
ControlFluidic *fluidicCircuit = nullptr;
ControlLight *lightSource = nullptr;

/**
 * @brief Application entry point
 * @param argc Parameter count
 * @param argv Parameter vector
 * @return EXIT_SUCCESS if successful, else EXIT_FAILURE
 */
int main(int argc, char *argv[])
{
    Application app(argc, argv);

    /* Go to [panel] group */
    settings->beginGroup(QString("Panel"));

    Splash *splash = nullptr;

    /* Show splashscreen? */
    if (settings->value(QString("ShowSplashscreen"), QString("true")).toBool())
    {
        /* Splash screen image */
        QPixmap splashImage(QString(":/laboratory.ico"));

        /* Create splash screen */
        splash = new Splash(splashImage);

        /* Set message position and text */
        splash->setMessageRect(QRect(0, 220, 256, 20), Qt::AlignCenter);
        splash->showStatusMessage(QString("Initializing"), QColor(Qt::white));

        /* Show splash screen */
        splash->show();

        /*
         * To intercept mouseclick to hide splash screen. Since the
         * splash screen is typically displayed before the event loop
         * has started running, it is necessary to periodically call.
         */
        app.processEvents();
    }

    /* Get settings for USB/Ethernet connection */
    bool bConnectUSB = settings->value(QString("ConnectUSB"), QString("true")).toBool();
    bool bConnectEthernet = settings->value(QString("ConnectEthernet"), QString("true")).toBool();

    short a_Port = 0;

    /* Use both, ethernet and USB ports? */
    if (bConnectUSB && bConnectEthernet)
    {
        a_Port = -1;
    }
    else
    {
        /* Use USB port? */
        if (bConnectUSB)
        {
            a_Port = 0;
        }
        else
        {
            /* Use Ethernet port? */
            if (bConnectEthernet)
            {
                a_Port = 256;
            }
        }
    }

    /* Close open group */
    settings->endGroup();

    /*
     * Opens the communication with the spectrometer and initializes internal data structures.
     */
    int l_Port = AVS_Init(a_Port);

    /* Successful? */
    if (l_Port < 0)
    {
        /* Close library */
        AVS_Done();

        /* Create message box */
        showCritical(QString("Initialization of the Avantes AvaSpec library failed."),
                     QString("File:\t%1\nFunction:\t%2\nLine:\t%3\n\nint AVS_Init(short a_Port) returned < 0.").
                        arg(__FILE__, __FUNCTION__, QString::number(__LINE__-11)));

        /* Quit after failure */
        exit(EXIT_FAILURE);
    }

    /* Splashscreen shown? */
    if (nullptr != splash)
    {
        /* Update messages */
        splash->showStatusMessage(QString("Getting device info"), QColor(Qt::white));
        app.processEvents();
    }

    /*
     * Internally checks the list of connected devices and returns the number of devices attached.
     */

    /* Use USB port? */
    if (bConnectUSB)
    {
        /*
         * Internally checks the list of connected USB devices and returns the number of devices attached.
         * If AVS_Init is called with a_Port=-1, the return value also includes the number of ETH devices.
         */
        AVS_UpdateUSBDevices();
    }

    unsigned int l_Size = 0;
    unsigned int l_RequiredSize = 0;
    char *l_pData = nullptr;

    /* Use ethernet port? */
    if (bConnectEthernet)
    {
        /*
         * Internally checks the list of connected ETH devices and returns the number of devices in the device
         * list. If AVS_Init is called with a_Port=-1, the return value also includes the number of USB devices.
         */
        AVS_UpdateETHDevices(0, &l_RequiredSize, NULL);

        /* Allocate memory for data structures */
        l_pData = new char[l_RequiredSize];
        l_Size = l_RequiredSize;

        BroadcastAnswerType *l_pAnswer = (BroadcastAnswerType*)l_pData;

        /*
         * Internally checks the list of connected ETH devices and returns the number of devices in the device
         * list. If AVS_Init is called with a_Port=-1, the return value also includes the number of USB devices.
         */
        AVS_UpdateETHDevices(l_Size, &l_RequiredSize, l_pAnswer);
    }

    /*
     * Returns device information for each spectrometer connected to the ports indicated at AVS_Init.
     */
    m_NrDevices = AVS_GetList(0, &l_RequiredSize, NULL);

    /* Devices attached? */
    if (m_NrDevices > 0)
    {
        /* Allocate memory for data structures */
        char *l_pData2 = new char[l_RequiredSize];
        AvsIdentityType *l_pId = (AvsIdentityType*)l_pData2;
        l_Size = l_RequiredSize;

        /*
         * Returns device information for each spectrometer connected to the ports indicated at AVS_Init.
         */
        m_NrDevices = AVS_GetList(l_Size, &l_RequiredSize, l_pId);

        /* Devices attached? */
        if (m_NrDevices > 0)
        {
            /* Allocate memory for an array of activated devices */
            ptrSpectrometers = new Spectrometer *[m_NrDevices];

            /*
             * i: Index in array 'attached devices' from AvaSpec library
             * j: Index in spectrometer array
             * n: Number of attached devices
             */
            unsigned int i = 0, j = 0, n = m_NrDevices;

            /* Which spectrometer(s) should be activated? */
            for (i = 0, j = 0; i < n; i++)
            {
                /* Create new spectrometer object in spectrometer array */
                ptrSpectrometers[j] = new Spectrometer(&l_pId[i]);

                /* Creation of spectrometer object failed? */
                if (!ptrSpectrometers[j]->getNumberOfPixels())
                {
                    /* Decrease spectrometer count */
                    m_NrDevices--;
                }
                /* Creation of spectrometer object succeeded? */
                else
                {
                    /* Go to next index in spectrometer array */
                    j++;
                }
            }

            /*
             * If the creation of all spectrometer objects failed, we can close our AvaSpec library
             */

            /* Devices successfully initiated? */
            if (m_NrDevices > 0)
            {
                /* Splashscreen shown? */
                if (nullptr != splash)
                {
                    /* Update messages */
                    splash->showStatusMessage(QString("%1 device(s) found").arg(m_NrDevices), QColor(Qt::white));
                    app.processEvents();
                }
            }
            /* No devices successfully initiated? */
            else
            {
                /* Memory allocated? */
                if (nullptr != l_pData)
                {
                    /* Free memory */
                    delete[] l_pData;
                    l_pData = nullptr;
                }

                /* Memory allocated? */
                if (nullptr != l_pData2)
                {
                    /* Free memory */
                    delete[] l_pData2;
                    l_pData2 = nullptr;
                }

                /* Close library */
                AVS_Done();

                /* Splashscreen shown? */
                if (nullptr != splash)
                {
                    /* Update messages */
                    splash->showStatusMessage(QString("Error(s) occurred"), QColor(Qt::white));
                    app.processEvents();
                }

                /* Show warning */
                showWarning(QString("Error(s) occurred"), QString(""));
            }
        }
        /* No devices attached? */
        else
        {
            /* Memory allocated? */
            if (nullptr != l_pData)
            {
                /* Free memory */
                delete[] l_pData;
                l_pData = nullptr;
            }

            /* Memory allocated? */
            if (nullptr != l_pData2)
            {
                /* Free memory */
                delete[] l_pData2;
                l_pData2 = nullptr;
            }

            /* Close library */
            AVS_Done();

            /* Splashscreen shown? */
            if (nullptr != splash)
            {
                /* Update messages */
                splash->showStatusMessage(QString("No device(s) found"), QColor(Qt::white));
                app.processEvents();
            }

            /* Show information */
            showInformation(QString("No device(s) found"), QString(""));
       }
    }
    else
    {
        /* Memory allocated? */
        if (nullptr != l_pData)
        {
            /* Free memory */
            delete[] l_pData;
            l_pData = nullptr;
        }

        /* Close library */
        AVS_Done();

        /* Splashscreen shown? */
        if (nullptr != splash)
        {
            /* Update messages */
            splash->showStatusMessage(QString("No device(s) found"), QColor(Qt::white));
            app.processEvents();
        }
    }

    /* Splashscreen shown? */
    if (nullptr != splash)
    {
        /* Close splash screen */
        splash->close();

        /* Free memory */
        delete splash;
        splash = nullptr;
    }

    /* Show application window */
    mainWindow = new Panel(NULL);
    mainWindow->show();

    /* Go to [panel] group */
    settings->beginGroup(QString("Toolkits"));

    /* Show fluidic circuit toolkit? */
    if (settings->value(QString("FluidicControl"), QString("true")).toBool())
    {
        /* Show fluidic tool */
        fluidicCircuit = new ControlFluidic(mainWindow);
        fluidicCircuit->show();
    }

    /* Show light source toolkit? */
    if (settings->value(QString("LightControl"), QString("true")).toBool())
    {
        /* Show light source tool */
        lightSource = new ControlLight(mainWindow);
        lightSource->show();
    }

    /* Close open group */
    settings->endGroup();

    /* Execute application */
    int result = app.exec();

    /* Fluidic toolkit opened? */
    if (nullptr != fluidicCircuit)
    {
        /* Free memory */
        delete fluidicCircuit;
        fluidicCircuit = nullptr;
    }

    /* Light source toolkit opened? */
    if (nullptr != lightSource)
    {
        /* Free memory */
        delete lightSource;
        lightSource = nullptr;
    }

    /* Main window opened? */
    if (nullptr != mainWindow)
    {
        /* Free memory */
        delete mainWindow;
        mainWindow = nullptr;
    }
    return result;
}
