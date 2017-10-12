/********************************************************************************
** Form generated from reading UI file 'iad_calibrate_page01.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IAD_CALIBRATE_PAGE01_H
#define UI_IAD_CALIBRATE_PAGE01_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_CalibrateIADPage01
{
public:
    QLabel *label;
    QPushButton *button_next;
    QPushButton *button_abort;
    QLabel *label_10;
    QProgressBar *progressBar_unscatteredTransmission;
    QLabel *label_9;
    QLabel *label_4;
    QLabel *label_8;

    void setupUi(QDialog *CalibrateIADPage01)
    {
        if (CalibrateIADPage01->objectName().isEmpty())
            CalibrateIADPage01->setObjectName(QStringLiteral("CalibrateIADPage01"));
        CalibrateIADPage01->resize(640, 480);
        label = new QLabel(CalibrateIADPage01);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(60, 10, 571, 41));
        label->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        label->setWordWrap(true);
        button_next = new QPushButton(CalibrateIADPage01);
        button_next->setObjectName(QStringLiteral("button_next"));
        button_next->setEnabled(false);
        button_next->setGeometry(QRect(470, 440, 75, 23));
        button_abort = new QPushButton(CalibrateIADPage01);
        button_abort->setObjectName(QStringLiteral("button_abort"));
        button_abort->setGeometry(QRect(550, 440, 75, 23));
        label_10 = new QLabel(CalibrateIADPage01);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(10, 10, 41, 21));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        label_10->setFont(font);
        label_10->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        label_10->setWordWrap(true);
        progressBar_unscatteredTransmission = new QProgressBar(CalibrateIADPage01);
        progressBar_unscatteredTransmission->setObjectName(QStringLiteral("progressBar_unscatteredTransmission"));
        progressBar_unscatteredTransmission->setGeometry(QRect(310, 150, 20, 160));
        progressBar_unscatteredTransmission->setMaximum(65535);
        progressBar_unscatteredTransmission->setValue(0);
        progressBar_unscatteredTransmission->setTextVisible(false);
        progressBar_unscatteredTransmission->setOrientation(Qt::Vertical);
        label_9 = new QLabel(CalibrateIADPage01);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(350, 290, 50, 20));
        label_9->setAlignment(Qt::AlignBottom|Qt::AlignLeading|Qt::AlignLeft);
        label_4 = new QLabel(CalibrateIADPage01);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(280, 110, 80, 30));
        label_4->setFont(font);
        label_4->setAlignment(Qt::AlignCenter);
        label_4->setWordWrap(true);
        label_8 = new QLabel(CalibrateIADPage01);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(350, 150, 50, 20));
        label_8->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);

        retranslateUi(CalibrateIADPage01);

        QMetaObject::connectSlotsByName(CalibrateIADPage01);
    } // setupUi

    void retranslateUi(QDialog *CalibrateIADPage01)
    {
        CalibrateIADPage01->setWindowTitle(QApplication::translate("CalibrateIADPage01", "Calibration of IAD method", Q_NULLPTR));
        label->setText(QApplication::translate("CalibrateIADPage01", "Unscattered transmission pinhole will be adjusted. Please be sure that no sample is positioned between the integrating spheres. The spheres have to be in their end position as they will be during later measurements.", Q_NULLPTR));
        button_next->setText(QApplication::translate("CalibrateIADPage01", "Next", Q_NULLPTR));
        button_abort->setText(QApplication::translate("CalibrateIADPage01", "Abort", Q_NULLPTR));
        label_10->setText(QApplication::translate("CalibrateIADPage01", "Step 1:", Q_NULLPTR));
        label_9->setText(QApplication::translate("CalibrateIADPage01", "No signal", Q_NULLPTR));
        label_4->setText(QApplication::translate("CalibrateIADPage01", "Unscattered transmission", Q_NULLPTR));
        label_8->setText(QApplication::translate("CalibrateIADPage01", "Saturation", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class CalibrateIADPage01: public Ui_CalibrateIADPage01 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IAD_CALIBRATE_PAGE01_H
