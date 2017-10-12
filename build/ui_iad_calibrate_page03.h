/********************************************************************************
** Form generated from reading UI file 'iad_calibrate_page03.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IAD_CALIBRATE_PAGE03_H
#define UI_IAD_CALIBRATE_PAGE03_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_CalibrateIADPage03
{
public:
    QLabel *label;
    QPushButton *button_abort;
    QDoubleSpinBox *doubleSpinBox_diffuseReflection_integrationTime;
    QLabel *label_diffuseReflection;
    QLabel *label_diffuseTransmission;
    QDoubleSpinBox *doubleSpinBox_diffuseTransmission_integrationTime;
    QLabel *label_4;
    QLabel *label_5;
    QDoubleSpinBox *doubleSpinBox_unscatteredTransmission_integrationTime;
    QLabel *label_6;
    QLabel *label_unscatteredTransmission;
    QLabel *label_saturation;
    QLabel *label_noSignal;
    QProgressBar *progressBar;
    QPushButton *button_next;
    QLabel *label_10;
    QProgressBar *progressBar_diffuseReflection;
    QProgressBar *progressBar_diffuseTransmission;
    QProgressBar *progressBar_unscatteredTransmission;
    QLabel *label_11;
    QLabel *label_13;
    QLabel *label_12;
    QLabel *label_14;
    QLabel *label_15;
    QSpinBox *spinBox_diffuseReflection_numberOfAverages;
    QSpinBox *spinBox_diffuseTransmission_numberOfAverages;
    QSpinBox *spinBox_unscatteredTransmission_numberOfAverages;
    QSpinBox *spinBox_diffuseReflection_counts;
    QSpinBox *spinBox_diffuseTransmission_counts;
    QSpinBox *spinBox_unscatteredTransmission_counts;

    void setupUi(QDialog *CalibrateIADPage03)
    {
        if (CalibrateIADPage03->objectName().isEmpty())
            CalibrateIADPage03->setObjectName(QStringLiteral("CalibrateIADPage03"));
        CalibrateIADPage03->resize(640, 480);
        label = new QLabel(CalibrateIADPage03);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(60, 10, 571, 31));
        label->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        label->setWordWrap(true);
        button_abort = new QPushButton(CalibrateIADPage03);
        button_abort->setObjectName(QStringLiteral("button_abort"));
        button_abort->setEnabled(true);
        button_abort->setGeometry(QRect(550, 440, 75, 23));
        doubleSpinBox_diffuseReflection_integrationTime = new QDoubleSpinBox(CalibrateIADPage03);
        doubleSpinBox_diffuseReflection_integrationTime->setObjectName(QStringLiteral("doubleSpinBox_diffuseReflection_integrationTime"));
        doubleSpinBox_diffuseReflection_integrationTime->setGeometry(QRect(161, 330, 60, 22));
        doubleSpinBox_diffuseReflection_integrationTime->setReadOnly(true);
        doubleSpinBox_diffuseReflection_integrationTime->setButtonSymbols(QAbstractSpinBox::NoButtons);
        doubleSpinBox_diffuseReflection_integrationTime->setMaximum(10000);
        doubleSpinBox_diffuseReflection_integrationTime->setValue(0);
        label_diffuseReflection = new QLabel(CalibrateIADPage03);
        label_diffuseReflection->setObjectName(QStringLiteral("label_diffuseReflection"));
        label_diffuseReflection->setGeometry(QRect(150, 110, 80, 30));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        label_diffuseReflection->setFont(font);
        label_diffuseReflection->setAlignment(Qt::AlignCenter);
        label_diffuseReflection->setWordWrap(true);
        label_diffuseTransmission = new QLabel(CalibrateIADPage03);
        label_diffuseTransmission->setObjectName(QStringLiteral("label_diffuseTransmission"));
        label_diffuseTransmission->setGeometry(QRect(280, 110, 80, 30));
        label_diffuseTransmission->setFont(font);
        label_diffuseTransmission->setAlignment(Qt::AlignCenter);
        label_diffuseTransmission->setWordWrap(true);
        doubleSpinBox_diffuseTransmission_integrationTime = new QDoubleSpinBox(CalibrateIADPage03);
        doubleSpinBox_diffuseTransmission_integrationTime->setObjectName(QStringLiteral("doubleSpinBox_diffuseTransmission_integrationTime"));
        doubleSpinBox_diffuseTransmission_integrationTime->setGeometry(QRect(290, 330, 60, 22));
        doubleSpinBox_diffuseTransmission_integrationTime->setReadOnly(true);
        doubleSpinBox_diffuseTransmission_integrationTime->setButtonSymbols(QAbstractSpinBox::NoButtons);
        doubleSpinBox_diffuseTransmission_integrationTime->setMaximum(10000);
        doubleSpinBox_diffuseTransmission_integrationTime->setValue(0);
        label_4 = new QLabel(CalibrateIADPage03);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(230, 330, 20, 22));
        label_5 = new QLabel(CalibrateIADPage03);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(360, 330, 20, 22));
        doubleSpinBox_unscatteredTransmission_integrationTime = new QDoubleSpinBox(CalibrateIADPage03);
        doubleSpinBox_unscatteredTransmission_integrationTime->setObjectName(QStringLiteral("doubleSpinBox_unscatteredTransmission_integrationTime"));
        doubleSpinBox_unscatteredTransmission_integrationTime->setGeometry(QRect(420, 330, 60, 22));
        doubleSpinBox_unscatteredTransmission_integrationTime->setReadOnly(true);
        doubleSpinBox_unscatteredTransmission_integrationTime->setButtonSymbols(QAbstractSpinBox::NoButtons);
        doubleSpinBox_unscatteredTransmission_integrationTime->setMaximum(10000);
        doubleSpinBox_unscatteredTransmission_integrationTime->setValue(0);
        label_6 = new QLabel(CalibrateIADPage03);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(490, 330, 20, 22));
        label_unscatteredTransmission = new QLabel(CalibrateIADPage03);
        label_unscatteredTransmission->setObjectName(QStringLiteral("label_unscatteredTransmission"));
        label_unscatteredTransmission->setGeometry(QRect(410, 110, 80, 30));
        label_unscatteredTransmission->setFont(font);
        label_unscatteredTransmission->setAlignment(Qt::AlignCenter);
        label_unscatteredTransmission->setWordWrap(true);
        label_saturation = new QLabel(CalibrateIADPage03);
        label_saturation->setObjectName(QStringLiteral("label_saturation"));
        label_saturation->setGeometry(QRect(480, 150, 80, 22));
        QFont font1;
        font1.setBold(false);
        font1.setWeight(50);
        label_saturation->setFont(font1);
        label_saturation->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        label_noSignal = new QLabel(CalibrateIADPage03);
        label_noSignal->setObjectName(QStringLiteral("label_noSignal"));
        label_noSignal->setGeometry(QRect(480, 290, 80, 22));
        label_noSignal->setFont(font1);
        label_noSignal->setAlignment(Qt::AlignBottom|Qt::AlignLeading|Qt::AlignLeft);
        progressBar = new QProgressBar(CalibrateIADPage03);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setGeometry(QRect(10, 440, 451, 21));
        progressBar->setValue(0);
        button_next = new QPushButton(CalibrateIADPage03);
        button_next->setObjectName(QStringLiteral("button_next"));
        button_next->setEnabled(true);
        button_next->setGeometry(QRect(470, 440, 75, 23));
        label_10 = new QLabel(CalibrateIADPage03);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(10, 10, 41, 21));
        label_10->setFont(font);
        label_10->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        label_10->setWordWrap(true);
        progressBar_diffuseReflection = new QProgressBar(CalibrateIADPage03);
        progressBar_diffuseReflection->setObjectName(QStringLiteral("progressBar_diffuseReflection"));
        progressBar_diffuseReflection->setGeometry(QRect(180, 150, 20, 160));
        progressBar_diffuseReflection->setMaximum(65535);
        progressBar_diffuseReflection->setValue(0);
        progressBar_diffuseReflection->setTextVisible(false);
        progressBar_diffuseReflection->setOrientation(Qt::Vertical);
        progressBar_diffuseTransmission = new QProgressBar(CalibrateIADPage03);
        progressBar_diffuseTransmission->setObjectName(QStringLiteral("progressBar_diffuseTransmission"));
        progressBar_diffuseTransmission->setGeometry(QRect(310, 150, 20, 160));
        progressBar_diffuseTransmission->setMaximum(65535);
        progressBar_diffuseTransmission->setValue(0);
        progressBar_diffuseTransmission->setTextVisible(false);
        progressBar_diffuseTransmission->setOrientation(Qt::Vertical);
        progressBar_unscatteredTransmission = new QProgressBar(CalibrateIADPage03);
        progressBar_unscatteredTransmission->setObjectName(QStringLiteral("progressBar_unscatteredTransmission"));
        progressBar_unscatteredTransmission->setGeometry(QRect(440, 150, 20, 160));
        progressBar_unscatteredTransmission->setMaximum(65535);
        progressBar_unscatteredTransmission->setValue(0);
        progressBar_unscatteredTransmission->setTextVisible(false);
        progressBar_unscatteredTransmission->setOrientation(Qt::Vertical);
        label_11 = new QLabel(CalibrateIADPage03);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setGeometry(QRect(640, 380, 51, 21));
        label_11->setAlignment(Qt::AlignBottom|Qt::AlignLeading|Qt::AlignLeft);
        label_13 = new QLabel(CalibrateIADPage03);
        label_13->setObjectName(QStringLiteral("label_13"));
        label_13->setGeometry(QRect(640, 240, 51, 21));
        label_13->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        label_12 = new QLabel(CalibrateIADPage03);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setGeometry(QRect(10, 390, 140, 22));
        label_12->setFont(font);
        label_12->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_12->setWordWrap(true);
        label_14 = new QLabel(CalibrateIADPage03);
        label_14->setObjectName(QStringLiteral("label_14"));
        label_14->setGeometry(QRect(10, 330, 140, 22));
        label_14->setFont(font);
        label_14->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_14->setWordWrap(true);
        label_15 = new QLabel(CalibrateIADPage03);
        label_15->setObjectName(QStringLiteral("label_15"));
        label_15->setGeometry(QRect(10, 360, 140, 22));
        label_15->setFont(font);
        label_15->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_15->setWordWrap(true);
        spinBox_diffuseReflection_numberOfAverages = new QSpinBox(CalibrateIADPage03);
        spinBox_diffuseReflection_numberOfAverages->setObjectName(QStringLiteral("spinBox_diffuseReflection_numberOfAverages"));
        spinBox_diffuseReflection_numberOfAverages->setGeometry(QRect(160, 360, 60, 22));
        spinBox_diffuseReflection_numberOfAverages->setReadOnly(true);
        spinBox_diffuseReflection_numberOfAverages->setButtonSymbols(QAbstractSpinBox::NoButtons);
        spinBox_diffuseReflection_numberOfAverages->setMinimum(1);
        spinBox_diffuseReflection_numberOfAverages->setMaximum(1000);
        spinBox_diffuseTransmission_numberOfAverages = new QSpinBox(CalibrateIADPage03);
        spinBox_diffuseTransmission_numberOfAverages->setObjectName(QStringLiteral("spinBox_diffuseTransmission_numberOfAverages"));
        spinBox_diffuseTransmission_numberOfAverages->setGeometry(QRect(290, 360, 60, 22));
        spinBox_diffuseTransmission_numberOfAverages->setReadOnly(true);
        spinBox_diffuseTransmission_numberOfAverages->setButtonSymbols(QAbstractSpinBox::NoButtons);
        spinBox_diffuseTransmission_numberOfAverages->setMinimum(1);
        spinBox_diffuseTransmission_numberOfAverages->setMaximum(1000);
        spinBox_unscatteredTransmission_numberOfAverages = new QSpinBox(CalibrateIADPage03);
        spinBox_unscatteredTransmission_numberOfAverages->setObjectName(QStringLiteral("spinBox_unscatteredTransmission_numberOfAverages"));
        spinBox_unscatteredTransmission_numberOfAverages->setGeometry(QRect(420, 360, 60, 22));
        spinBox_unscatteredTransmission_numberOfAverages->setReadOnly(true);
        spinBox_unscatteredTransmission_numberOfAverages->setButtonSymbols(QAbstractSpinBox::NoButtons);
        spinBox_unscatteredTransmission_numberOfAverages->setMinimum(1);
        spinBox_unscatteredTransmission_numberOfAverages->setMaximum(1000);
        spinBox_diffuseReflection_counts = new QSpinBox(CalibrateIADPage03);
        spinBox_diffuseReflection_counts->setObjectName(QStringLiteral("spinBox_diffuseReflection_counts"));
        spinBox_diffuseReflection_counts->setGeometry(QRect(160, 390, 60, 22));
        spinBox_diffuseReflection_counts->setReadOnly(true);
        spinBox_diffuseReflection_counts->setButtonSymbols(QAbstractSpinBox::NoButtons);
        spinBox_diffuseReflection_counts->setMinimum(0);
        spinBox_diffuseReflection_counts->setMaximum(65535);
        spinBox_diffuseTransmission_counts = new QSpinBox(CalibrateIADPage03);
        spinBox_diffuseTransmission_counts->setObjectName(QStringLiteral("spinBox_diffuseTransmission_counts"));
        spinBox_diffuseTransmission_counts->setGeometry(QRect(290, 390, 60, 22));
        spinBox_diffuseTransmission_counts->setReadOnly(true);
        spinBox_diffuseTransmission_counts->setButtonSymbols(QAbstractSpinBox::NoButtons);
        spinBox_diffuseTransmission_counts->setMinimum(0);
        spinBox_diffuseTransmission_counts->setMaximum(65535);
        spinBox_unscatteredTransmission_counts = new QSpinBox(CalibrateIADPage03);
        spinBox_unscatteredTransmission_counts->setObjectName(QStringLiteral("spinBox_unscatteredTransmission_counts"));
        spinBox_unscatteredTransmission_counts->setGeometry(QRect(420, 390, 60, 22));
        spinBox_unscatteredTransmission_counts->setReadOnly(true);
        spinBox_unscatteredTransmission_counts->setButtonSymbols(QAbstractSpinBox::NoButtons);
        spinBox_unscatteredTransmission_counts->setMinimum(0);
        spinBox_unscatteredTransmission_counts->setMaximum(65535);

        retranslateUi(CalibrateIADPage03);

        QMetaObject::connectSlotsByName(CalibrateIADPage03);
    } // setupUi

    void retranslateUi(QDialog *CalibrateIADPage03)
    {
        CalibrateIADPage03->setWindowTitle(QApplication::translate("CalibrateIADPage03", "Calibration of IAD method", Q_NULLPTR));
        label->setText(QApplication::translate("CalibrateIADPage03", "Please remove any sample from between the integrating spheres. Open the lamp shutter. Press the 'Begin' button if you are ready. The integration times will be adjusted for maximum signal to noise ratio (SNR).", Q_NULLPTR));
        button_abort->setText(QApplication::translate("CalibrateIADPage03", "Abort", Q_NULLPTR));
        label_diffuseReflection->setText(QApplication::translate("CalibrateIADPage03", "Diffuse reflection", Q_NULLPTR));
        label_diffuseTransmission->setText(QApplication::translate("CalibrateIADPage03", "Diffuse transmission", Q_NULLPTR));
        label_4->setText(QApplication::translate("CalibrateIADPage03", "ms", Q_NULLPTR));
        label_5->setText(QApplication::translate("CalibrateIADPage03", "ms", Q_NULLPTR));
        label_6->setText(QApplication::translate("CalibrateIADPage03", "ms", Q_NULLPTR));
        label_unscatteredTransmission->setText(QApplication::translate("CalibrateIADPage03", "Unscattered transmission", Q_NULLPTR));
        label_saturation->setText(QApplication::translate("CalibrateIADPage03", "Saturation", Q_NULLPTR));
        label_noSignal->setText(QApplication::translate("CalibrateIADPage03", "No signal", Q_NULLPTR));
        button_next->setText(QApplication::translate("CalibrateIADPage03", "Begin", Q_NULLPTR));
        label_10->setText(QApplication::translate("CalibrateIADPage03", "Step 3:", Q_NULLPTR));
        label_11->setText(QApplication::translate("CalibrateIADPage03", "No signal", Q_NULLPTR));
        label_13->setText(QApplication::translate("CalibrateIADPage03", "Saturation", Q_NULLPTR));
        label_12->setText(QApplication::translate("CalibrateIADPage03", "Maximum counts:", Q_NULLPTR));
        label_14->setText(QApplication::translate("CalibrateIADPage03", "Integration time:", Q_NULLPTR));
        label_15->setText(QApplication::translate("CalibrateIADPage03", "Number of averages:", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class CalibrateIADPage03: public Ui_CalibrateIADPage03 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IAD_CALIBRATE_PAGE03_H
