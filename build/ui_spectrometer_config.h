/********************************************************************************
** Form generated from reading UI file 'spectrometer_config.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SPECTROMETER_CONFIG_H
#define UI_SPECTROMETER_CONFIG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_SpectrometerConfig
{
public:
    QPushButton *button_cancel;
    QPushButton *button_apply;
    QDoubleSpinBox *integrationTime;
    QSpinBox *startPixel;
    QLabel *label_14;
    QLabel *label_16;
    QLabel *label_17;
    QDoubleSpinBox *integrationDelay;
    QLabel *label_18;
    QLabel *label_20;
    QSpinBox *stopPixel;
    QLabel *label_15;
    QSpinBox *numberOfAverages;
    QLabel *label_19;
    QCheckBox *checkBox_dynamicDarkCorrection;
    QSpinBox *forgetPercentage;
    QLabel *label_21;
    QCheckBox *checkBox_highResADC;
    QLabel *label_22;
    QLabel *label_lambdaStart;
    QLabel *label_lambdaStop;

    void setupUi(QDialog *SpectrometerConfig)
    {
        if (SpectrometerConfig->objectName().isEmpty())
            SpectrometerConfig->setObjectName(QStringLiteral("SpectrometerConfig"));
        SpectrometerConfig->resize(260, 240);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(SpectrometerConfig->sizePolicy().hasHeightForWidth());
        SpectrometerConfig->setSizePolicy(sizePolicy);
        button_cancel = new QPushButton(SpectrometerConfig);
        button_cancel->setObjectName(QStringLiteral("button_cancel"));
        button_cancel->setGeometry(QRect(135, 210, 70, 23));
        button_apply = new QPushButton(SpectrometerConfig);
        button_apply->setObjectName(QStringLiteral("button_apply"));
        button_apply->setEnabled(false);
        button_apply->setGeometry(QRect(55, 210, 70, 23));
        integrationTime = new QDoubleSpinBox(SpectrometerConfig);
        integrationTime->setObjectName(QStringLiteral("integrationTime"));
        integrationTime->setGeometry(QRect(120, 55, 60, 20));
        integrationTime->setMinimum(1.05);
        integrationTime->setMaximum(60000);
        integrationTime->setValue(1.05);
        startPixel = new QSpinBox(SpectrometerConfig);
        startPixel->setObjectName(QStringLiteral("startPixel"));
        startPixel->setGeometry(QRect(120, 5, 60, 20));
        startPixel->setMaximum(2047);
        label_14 = new QLabel(SpectrometerConfig);
        label_14->setObjectName(QStringLiteral("label_14"));
        label_14->setGeometry(QRect(10, 5, 100, 20));
        label_16 = new QLabel(SpectrometerConfig);
        label_16->setObjectName(QStringLiteral("label_16"));
        label_16->setGeometry(QRect(10, 55, 100, 20));
        label_17 = new QLabel(SpectrometerConfig);
        label_17->setObjectName(QStringLiteral("label_17"));
        label_17->setGeometry(QRect(190, 55, 20, 20));
        integrationDelay = new QDoubleSpinBox(SpectrometerConfig);
        integrationDelay->setObjectName(QStringLiteral("integrationDelay"));
        integrationDelay->setGeometry(QRect(120, 80, 60, 20));
        integrationDelay->setMaximum(1000);
        label_18 = new QLabel(SpectrometerConfig);
        label_18->setObjectName(QStringLiteral("label_18"));
        label_18->setGeometry(QRect(10, 80, 100, 20));
        label_20 = new QLabel(SpectrometerConfig);
        label_20->setObjectName(QStringLiteral("label_20"));
        label_20->setGeometry(QRect(10, 105, 100, 20));
        stopPixel = new QSpinBox(SpectrometerConfig);
        stopPixel->setObjectName(QStringLiteral("stopPixel"));
        stopPixel->setGeometry(QRect(120, 30, 60, 20));
        stopPixel->setMaximum(2047);
        label_15 = new QLabel(SpectrometerConfig);
        label_15->setObjectName(QStringLiteral("label_15"));
        label_15->setGeometry(QRect(10, 30, 100, 20));
        numberOfAverages = new QSpinBox(SpectrometerConfig);
        numberOfAverages->setObjectName(QStringLiteral("numberOfAverages"));
        numberOfAverages->setGeometry(QRect(120, 105, 60, 20));
        numberOfAverages->setMinimum(1);
        numberOfAverages->setMaximum(1000);
        numberOfAverages->setValue(1);
        label_19 = new QLabel(SpectrometerConfig);
        label_19->setObjectName(QStringLiteral("label_19"));
        label_19->setGeometry(QRect(190, 80, 20, 20));
        checkBox_dynamicDarkCorrection = new QCheckBox(SpectrometerConfig);
        checkBox_dynamicDarkCorrection->setObjectName(QStringLiteral("checkBox_dynamicDarkCorrection"));
        checkBox_dynamicDarkCorrection->setGeometry(QRect(10, 130, 140, 20));
        forgetPercentage = new QSpinBox(SpectrometerConfig);
        forgetPercentage->setObjectName(QStringLiteral("forgetPercentage"));
        forgetPercentage->setGeometry(QRect(120, 155, 60, 20));
        forgetPercentage->setMaximum(100);
        label_21 = new QLabel(SpectrometerConfig);
        label_21->setObjectName(QStringLiteral("label_21"));
        label_21->setGeometry(QRect(10, 155, 100, 20));
        checkBox_highResADC = new QCheckBox(SpectrometerConfig);
        checkBox_highResADC->setObjectName(QStringLiteral("checkBox_highResADC"));
        checkBox_highResADC->setGeometry(QRect(10, 180, 200, 20));
        label_22 = new QLabel(SpectrometerConfig);
        label_22->setObjectName(QStringLiteral("label_22"));
        label_22->setGeometry(QRect(190, 155, 20, 20));
        label_lambdaStart = new QLabel(SpectrometerConfig);
        label_lambdaStart->setObjectName(QStringLiteral("label_lambdaStart"));
        label_lambdaStart->setGeometry(QRect(190, 5, 60, 20));
        label_lambdaStop = new QLabel(SpectrometerConfig);
        label_lambdaStop->setObjectName(QStringLiteral("label_lambdaStop"));
        label_lambdaStop->setGeometry(QRect(190, 30, 60, 20));

        retranslateUi(SpectrometerConfig);

        QMetaObject::connectSlotsByName(SpectrometerConfig);
    } // setupUi

    void retranslateUi(QDialog *SpectrometerConfig)
    {
        SpectrometerConfig->setWindowTitle(QApplication::translate("SpectrometerConfig", "Configuration", Q_NULLPTR));
        button_cancel->setText(QApplication::translate("SpectrometerConfig", "Cancel", Q_NULLPTR));
        button_apply->setText(QApplication::translate("SpectrometerConfig", "Apply", Q_NULLPTR));
        label_14->setText(QApplication::translate("SpectrometerConfig", "Start pixel", Q_NULLPTR));
        label_16->setText(QApplication::translate("SpectrometerConfig", "Integration time", Q_NULLPTR));
        label_17->setText(QApplication::translate("SpectrometerConfig", "ms", Q_NULLPTR));
        label_18->setText(QApplication::translate("SpectrometerConfig", "Integration delay", Q_NULLPTR));
        label_20->setText(QApplication::translate("SpectrometerConfig", "Number of averages", Q_NULLPTR));
        label_15->setText(QApplication::translate("SpectrometerConfig", "Stop pixel", Q_NULLPTR));
        label_19->setText(QApplication::translate("SpectrometerConfig", "ms", Q_NULLPTR));
        checkBox_dynamicDarkCorrection->setText(QApplication::translate("SpectrometerConfig", "Dynamic dark correction", Q_NULLPTR));
        label_21->setText(QApplication::translate("SpectrometerConfig", "Forget percentage", Q_NULLPTR));
        checkBox_highResADC->setText(QApplication::translate("SpectrometerConfig", "High-resolution ADC", Q_NULLPTR));
        label_22->setText(QApplication::translate("SpectrometerConfig", "%", Q_NULLPTR));
        label_lambdaStart->setText(QApplication::translate("SpectrometerConfig", "??? nm", Q_NULLPTR));
        label_lambdaStop->setText(QApplication::translate("SpectrometerConfig", "??? nm", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class SpectrometerConfig: public Ui_SpectrometerConfig {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SPECTROMETER_CONFIG_H
