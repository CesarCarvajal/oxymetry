/********************************************************************************
** Form generated from reading UI file 'panel_change_Wave_FFT.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PANEL_CHANGE_WAVE_FFT_H
#define UI_PANEL_CHANGE_WAVE_FFT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PanelChangeWaveFFT
{
public:
    QPushButton *button_apply;
    QComboBox *WaveList;
    QLabel *label;

    void setupUi(QWidget *PanelChangeWaveFFT)
    {
        if (PanelChangeWaveFFT->objectName().isEmpty())
            PanelChangeWaveFFT->setObjectName(QStringLiteral("PanelChangeWaveFFT"));
        PanelChangeWaveFFT->resize(204, 36);
        button_apply = new QPushButton(PanelChangeWaveFFT);
        button_apply->setObjectName(QStringLiteral("button_apply"));
        button_apply->setGeometry(QRect(130, 10, 65, 22));
        WaveList = new QComboBox(PanelChangeWaveFFT);
        WaveList->setObjectName(QStringLiteral("WaveList"));
        WaveList->setGeometry(QRect(10, 10, 91, 22));
        label = new QLabel(PanelChangeWaveFFT);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(110, 10, 20, 22));

        retranslateUi(PanelChangeWaveFFT);

        QMetaObject::connectSlotsByName(PanelChangeWaveFFT);
    } // setupUi

    void retranslateUi(QWidget *PanelChangeWaveFFT)
    {
        PanelChangeWaveFFT->setWindowTitle(QApplication::translate("PanelChangeWaveFFT", "Select a Wavelength", Q_NULLPTR));
        button_apply->setText(QApplication::translate("PanelChangeWaveFFT", "Set", Q_NULLPTR));
        label->setText(QApplication::translate("PanelChangeWaveFFT", "nm", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class PanelChangeWaveFFT: public Ui_PanelChangeWaveFFT {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PANEL_CHANGE_WAVE_FFT_H
