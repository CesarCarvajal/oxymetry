/********************************************************************************
** Form generated from reading UI file 'panel_about.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PANEL_ABOUT_H
#define UI_PANEL_ABOUT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PanelAbout
{
public:
    QPushButton *button_close;
    QLabel *label_title;
    QLabel *label_compiler;
    QLabel *label_build;
    QLabel *label_copyright;
    QLabel *label_license;
    QTabWidget *tabWidget;
    QWidget *tab;
    QPlainTextEdit *plainTextEdit_changelog;
    QWidget *tab_2;
    QPlainTextEdit *plainTextEdit_contributors;

    void setupUi(QDialog *PanelAbout)
    {
        if (PanelAbout->objectName().isEmpty())
            PanelAbout->setObjectName(QStringLiteral("PanelAbout"));
        PanelAbout->resize(470, 400);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(PanelAbout->sizePolicy().hasHeightForWidth());
        PanelAbout->setSizePolicy(sizePolicy);
        PanelAbout->setSizeIncrement(QSize(0, 0));
        button_close = new QPushButton(PanelAbout);
        button_close->setObjectName(QStringLiteral("button_close"));
        button_close->setGeometry(QRect(380, 190, 75, 23));
        button_close->setFlat(false);
        label_title = new QLabel(PanelAbout);
        label_title->setObjectName(QStringLiteral("label_title"));
        label_title->setGeometry(QRect(140, 10, 311, 21));
        QFont font;
        font.setPointSize(10);
        font.setBold(true);
        font.setWeight(75);
        label_title->setFont(font);
        label_compiler = new QLabel(PanelAbout);
        label_compiler->setObjectName(QStringLiteral("label_compiler"));
        label_compiler->setGeometry(QRect(140, 40, 310, 20));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label_compiler->sizePolicy().hasHeightForWidth());
        label_compiler->setSizePolicy(sizePolicy1);
        label_compiler->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        label_build = new QLabel(PanelAbout);
        label_build->setObjectName(QStringLiteral("label_build"));
        label_build->setGeometry(QRect(140, 60, 311, 21));
        label_build->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        label_copyright = new QLabel(PanelAbout);
        label_copyright->setObjectName(QStringLiteral("label_copyright"));
        label_copyright->setGeometry(QRect(140, 80, 311, 31));
        label_copyright->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        label_license = new QLabel(PanelAbout);
        label_license->setObjectName(QStringLiteral("label_license"));
        label_license->setGeometry(QRect(140, 120, 311, 61));
        label_license->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        tabWidget = new QTabWidget(PanelAbout);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setGeometry(QRect(10, 210, 451, 181));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        plainTextEdit_changelog = new QPlainTextEdit(tab);
        plainTextEdit_changelog->setObjectName(QStringLiteral("plainTextEdit_changelog"));
        plainTextEdit_changelog->setGeometry(QRect(10, 10, 425, 135));
        plainTextEdit_changelog->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        plainTextEdit_changelog->setReadOnly(true);
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        plainTextEdit_contributors = new QPlainTextEdit(tab_2);
        plainTextEdit_contributors->setObjectName(QStringLiteral("plainTextEdit_contributors"));
        plainTextEdit_contributors->setGeometry(QRect(10, 10, 425, 135));
        plainTextEdit_contributors->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        plainTextEdit_contributors->setReadOnly(true);
        tabWidget->addTab(tab_2, QString());
        label_license->raise();
        button_close->raise();
        label_title->raise();
        label_compiler->raise();
        label_build->raise();
        label_copyright->raise();
        tabWidget->raise();

        retranslateUi(PanelAbout);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(PanelAbout);
    } // setupUi

    void retranslateUi(QDialog *PanelAbout)
    {
        PanelAbout->setWindowTitle(QApplication::translate("PanelAbout", "About Oxymetry", Q_NULLPTR));
        button_close->setText(QApplication::translate("PanelAbout", "Close", Q_NULLPTR));
        label_title->setText(QApplication::translate("PanelAbout", "Oxymetry 0.4.3", Q_NULLPTR));
        label_compiler->setText(QApplication::translate("PanelAbout", "<Compiler info>", Q_NULLPTR));
        label_build->setText(QApplication::translate("PanelAbout", "<Build info>", Q_NULLPTR));
        label_copyright->setText(QApplication::translate("PanelAbout", "<Copyright info>", Q_NULLPTR));
        label_license->setText(QApplication::translate("PanelAbout", "<License>", Q_NULLPTR));
        plainTextEdit_changelog->setPlainText(QApplication::translate("PanelAbout", "Version 0.4.3: (26.10.2017)\n"
"\n"
"Polarimeter Tab:\n"
"+ Live Average Raw Signal Display with time dependency.\n"
"+ Autoadjust of Plot X and Y axis according to the ploted data.\n"
"+ Load of data from FFT file or Raw Data File.\n"
"+ Save option of FFT Analyzed Data.\n"
"+ Save Graphs to PDF.\n"
"+ Measurement Profile Load or Edition.\n"
"+ Calibration Option for Polarimeter Tab.\n"
"+ Plot of the FFT at the selected wavelength.\n"
"+ Raw Signal Plot independent from Preview Tab.\n"
"+ Spectra, Integration Time and Averaging Profile are now shown in Measurement Profile.\n"
"+ Colored Start/Stop measurement toggle button.\n"
"- Disabled preview/polarimeter setup when one preview/polarimeter setup is active.\n"
"\n"
"Version 0.4.2: (08.10.2017)\n"
"\n"
"- Dropped support for 32-bit OS\n"
"+ Code cleanup and restructuring\n"
"\n"
"Version 0.4.1: (06.10.2017)\n"
"\n"
"+ Added button for polarimeter setup\n"
"+ Implemented FFT data analysis\n"
"+ Disabled preview/polarimeter setup when one preview/polarimeter "
                        "setup is active\n"
"+ Modification of polarimeter setup tab panel\n"
"+ Toggle button for polarimeter setup\n"
"+ File and folder creation when polarimetric measurement starts\n"
"\n"
"Version 0.4.0: (02.10.2017)\n"
"\n"
"+ Added files for polarimeter control\n"
"+ Added FFTW library and data folder\n"
"\n"
"Version 0.3.0: (29.09.2017)\n"
"\n"
"* Legend now shows 'unknown' if serial number or readable name of spectrometer are not available\n"
"* Fixed spectra count in StoreToRAM files\n"
"* Changes of readable name are now accepted\n"
"* Disabling/enabling of a device now disables all elements in device item\n"
"+ Many code optimizations, especially to the StoreToRAM function and the spectrometer configuration dialog\n"
"+ Time-controlled measurements can now be automated via button 'time pattern'\n"
"+ The serial number of the device is no longer attached to the file names of StoreToRAM\n"
"+ StoreToRAM now supports more than 10000 spectra\n"
"+ Wavelengths are shown belong pixel numbers in configuration dial"
                        "og\n"
"+ Combined 'preview start' and 'preview stop' buttons into one single button\n"
"\n"
"Version 0.2.6: (04.09.2017)\n"
"\n"
"* Fixed a bug that prevented data export\n"
"+ Increased maximum of StoreToRAM spectra\n"
"+ StoreToRAM dialog remembers last path\n"
"\n"
"Version 0.2.5: (14.08.2017)\n"
"\n"
"* Updated AvaSpec library to version 9.6.0.0\n"
"\n"
"Version 0.2.4: (19.06.2017)\n"
"\n"
"+ Support of increased peristaltic pump RPM update rate\n"
"+ RPM in fluidic toolbox is now calculated over a period of one second\n"
"* Compatibility check for Qt 5.9.0\n"
"\n"
"Version 0.2.3: (14.06.2017)\n"
"\n"
"+ The user must now confirm whether existing files should be overwritten during data export\n"
"\n"
"Version 0.2.2: (29.05.2017)\n"
"\n"
"* Fixed calculation of fluidic circuit rollerpump RPM\n"
"* Fixed bug that prevented the first pinch valve from being switched\n"
"* Fixed a bug that caused the user to be overwhelmed with error messages when the light source was disconnected during operation\n"
"+ Added f"
                        "luidic circuit auto-connect functionality\n"
"+ Added changelog and contributors lists\n"
"- Removed message if no spectrometers were found\n"
"\n"
"Version 0.2.1 (24.05.2017):\n"
"\n"
"+ The spectral data from the spectrometers are now stored in separate files\n"
"+ Additional information (dynamic dark correction enabled, time and date, ...) is now stored within the saved spectra\n"
"\n"
"Version 0.2:\n"
"\n"
"Initial release", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("PanelAbout", "Changelog", Q_NULLPTR));
        plainTextEdit_contributors->setPlainText(QApplication::translate("PanelAbout", "Benjamin Redmer, Cesar Andres Carvajal Arrieta, Torben Kruse, Isabeau Dibbern", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("PanelAbout", "Contributors", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class PanelAbout: public Ui_PanelAbout {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PANEL_ABOUT_H
