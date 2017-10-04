/********************************************************************************
** Form generated from reading UI file 'iad_calibrate_page02.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IAD_CALIBRATE_PAGE02_H
#define UI_IAD_CALIBRATE_PAGE02_H

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

class Ui_CalibrateIADPage02
{
public:
    QLabel *label;
    QPushButton *button_abort;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_9;
    QProgressBar *progressBar;
    QPushButton *button_next;
    QLabel *label_10;
    QProgressBar *progressBar_diffuseReflection;
    QLabel *label_14;
    QLabel *label_4;
    QSpinBox *spinBox_diffuseReflection_counts;
    QDoubleSpinBox *doubleSpinBox_diffuseReflection_integrationTime;
    QSpinBox *spinBox_diffuseReflection_numberOfAverages;
    QLabel *label_15;
    QLabel *label_12;

    void setupUi(QDialog *CalibrateIADPage02)
    {
        if (CalibrateIADPage02->objectName().isEmpty())
            CalibrateIADPage02->setObjectName(QStringLiteral("CalibrateIADPage02"));
        CalibrateIADPage02->resize(640, 480);
        label = new QLabel(CalibrateIADPage02);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(60, 10, 571, 21));
        label->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        label->setWordWrap(true);
        button_abort = new QPushButton(CalibrateIADPage02);
        button_abort->setObjectName(QStringLiteral("button_abort"));
        button_abort->setEnabled(true);
        button_abort->setGeometry(QRect(550, 440, 75, 23));
        label_7 = new QLabel(CalibrateIADPage02);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(280, 110, 80, 30));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        label_7->setFont(font);
        label_7->setAlignment(Qt::AlignCenter);
        label_7->setWordWrap(true);
        label_8 = new QLabel(CalibrateIADPage02);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(350, 150, 50, 20));
        label_8->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        label_9 = new QLabel(CalibrateIADPage02);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(350, 290, 50, 20));
        label_9->setAlignment(Qt::AlignBottom|Qt::AlignLeading|Qt::AlignLeft);
        progressBar = new QProgressBar(CalibrateIADPage02);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setGeometry(QRect(10, 440, 451, 21));
        progressBar->setValue(0);
        button_next = new QPushButton(CalibrateIADPage02);
        button_next->setObjectName(QStringLiteral("button_next"));
        button_next->setEnabled(true);
        button_next->setGeometry(QRect(470, 440, 75, 23));
        label_10 = new QLabel(CalibrateIADPage02);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(10, 10, 41, 21));
        label_10->setFont(font);
        label_10->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        label_10->setWordWrap(true);
        progressBar_diffuseReflection = new QProgressBar(CalibrateIADPage02);
        progressBar_diffuseReflection->setObjectName(QStringLiteral("progressBar_diffuseReflection"));
        progressBar_diffuseReflection->setGeometry(QRect(310, 150, 20, 160));
        progressBar_diffuseReflection->setMaximum(65535);
        progressBar_diffuseReflection->setValue(0);
        progressBar_diffuseReflection->setTextVisible(false);
        progressBar_diffuseReflection->setOrientation(Qt::Vertical);
        label_14 = new QLabel(CalibrateIADPage02);
        label_14->setObjectName(QStringLiteral("label_14"));
        label_14->setGeometry(QRect(140, 330, 140, 22));
        label_14->setFont(font);
        label_14->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_14->setWordWrap(true);
        label_4 = new QLabel(CalibrateIADPage02);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(360, 330, 20, 22));
        spinBox_diffuseReflection_counts = new QSpinBox(CalibrateIADPage02);
        spinBox_diffuseReflection_counts->setObjectName(QStringLiteral("spinBox_diffuseReflection_counts"));
        spinBox_diffuseReflection_counts->setGeometry(QRect(290, 390, 60, 22));
        spinBox_diffuseReflection_counts->setReadOnly(true);
        spinBox_diffuseReflection_counts->setButtonSymbols(QAbstractSpinBox::NoButtons);
        spinBox_diffuseReflection_counts->setMinimum(0);
        spinBox_diffuseReflection_counts->setMaximum(65535);
        doubleSpinBox_diffuseReflection_integrationTime = new QDoubleSpinBox(CalibrateIADPage02);
        doubleSpinBox_diffuseReflection_integrationTime->setObjectName(QStringLiteral("doubleSpinBox_diffuseReflection_integrationTime"));
        doubleSpinBox_diffuseReflection_integrationTime->setGeometry(QRect(290, 330, 60, 22));
        doubleSpinBox_diffuseReflection_integrationTime->setReadOnly(true);
        doubleSpinBox_diffuseReflection_integrationTime->setButtonSymbols(QAbstractSpinBox::NoButtons);
        doubleSpinBox_diffuseReflection_integrationTime->setMaximum(10000);
        doubleSpinBox_diffuseReflection_integrationTime->setValue(0);
        spinBox_diffuseReflection_numberOfAverages = new QSpinBox(CalibrateIADPage02);
        spinBox_diffuseReflection_numberOfAverages->setObjectName(QStringLiteral("spinBox_diffuseReflection_numberOfAverages"));
        spinBox_diffuseReflection_numberOfAverages->setGeometry(QRect(290, 360, 60, 22));
        spinBox_diffuseReflection_numberOfAverages->setReadOnly(true);
        spinBox_diffuseReflection_numberOfAverages->setButtonSymbols(QAbstractSpinBox::NoButtons);
        spinBox_diffuseReflection_numberOfAverages->setMinimum(1);
        spinBox_diffuseReflection_numberOfAverages->setMaximum(1000);
        label_15 = new QLabel(CalibrateIADPage02);
        label_15->setObjectName(QStringLiteral("label_15"));
        label_15->setGeometry(QRect(140, 360, 140, 22));
        label_15->setFont(font);
        label_15->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_15->setWordWrap(true);
        label_12 = new QLabel(CalibrateIADPage02);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setGeometry(QRect(140, 390, 140, 22));
        label_12->setFont(font);
        label_12->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_12->setWordWrap(true);

        retranslateUi(CalibrateIADPage02);

        QMetaObject::connectSlotsByName(CalibrateIADPage02);
    } // setupUi

    void retranslateUi(QDialog *CalibrateIADPage02)
    {
        CalibrateIADPage02->setWindowTitle(QApplication::translate("CalibrateIADPage02", "Calibration of IAD method", Q_NULLPTR));
        label->setText(QApplication::translate("CalibrateIADPage02", "Please hold the reflectance standard at the sample port of the first integrating sphere.", Q_NULLPTR));
        button_abort->setText(QApplication::translate("CalibrateIADPage02", "Abort", Q_NULLPTR));
        label_7->setText(QApplication::translate("CalibrateIADPage02", "Diffuse reflection", Q_NULLPTR));
        label_8->setText(QApplication::translate("CalibrateIADPage02", "Saturation", Q_NULLPTR));
        label_9->setText(QApplication::translate("CalibrateIADPage02", "No signal", Q_NULLPTR));
        button_next->setText(QApplication::translate("CalibrateIADPage02", "Begin", Q_NULLPTR));
        label_10->setText(QApplication::translate("CalibrateIADPage02", "Step 2:", Q_NULLPTR));
        label_14->setText(QApplication::translate("CalibrateIADPage02", "Integration time:", Q_NULLPTR));
        label_4->setText(QApplication::translate("CalibrateIADPage02", "ms", Q_NULLPTR));
        label_15->setText(QApplication::translate("CalibrateIADPage02", "Number of averages:", Q_NULLPTR));
        label_12->setText(QApplication::translate("CalibrateIADPage02", "Maximum counts:", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class CalibrateIADPage02: public Ui_CalibrateIADPage02 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IAD_CALIBRATE_PAGE02_H
