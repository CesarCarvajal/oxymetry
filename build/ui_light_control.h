/********************************************************************************
** Form generated from reading UI file 'light_control.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LIGHT_CONTROL_H
#define UI_LIGHT_CONTROL_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>
#include "plot.h"

QT_BEGIN_NAMESPACE

class Ui_ControlLight
{
public:
    QWidget *centralWidget;
    QPushButton *pushButton_connect;
    QLabel *label_status;
    Plot *qwtPlot_stats;
    QPushButton *pushButton_highPower_off;
    QLabel *label_highPower;
    QPushButton *pushButton_shutter_close;
    QPushButton *pushButton_highPower_on;
    QPushButton *pushButton_bulb_off;
    QPushButton *pushButton_shutter_open;
    QLabel *label_shutter;
    QPushButton *pushButton_bulb_on;
    QLabel *label_bulb;
    QLabel *label_bulbOnTime;
    QLabel *label_bulbOnTime_value;

    void setupUi(QMainWindow *ControlLight)
    {
        if (ControlLight->objectName().isEmpty())
            ControlLight->setObjectName(QStringLiteral("ControlLight"));
        ControlLight->resize(240, 360);
        centralWidget = new QWidget(ControlLight);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        pushButton_connect = new QPushButton(centralWidget);
        pushButton_connect->setObjectName(QStringLiteral("pushButton_connect"));
        pushButton_connect->setGeometry(QRect(150, 10, 75, 23));
        label_status = new QLabel(centralWidget);
        label_status->setObjectName(QStringLiteral("label_status"));
        label_status->setGeometry(QRect(15, 325, 125, 25));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        label_status->setFont(font);
        qwtPlot_stats = new Plot(centralWidget);
        qwtPlot_stats->setObjectName(QStringLiteral("qwtPlot_stats"));
        qwtPlot_stats->setGeometry(QRect(15, 180, 210, 140));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(qwtPlot_stats->sizePolicy().hasHeightForWidth());
        qwtPlot_stats->setSizePolicy(sizePolicy);
        pushButton_highPower_off = new QPushButton(centralWidget);
        pushButton_highPower_off->setObjectName(QStringLiteral("pushButton_highPower_off"));
        pushButton_highPower_off->setEnabled(false);
        pushButton_highPower_off->setGeometry(QRect(165, 110, 55, 23));
        label_highPower = new QLabel(centralWidget);
        label_highPower->setObjectName(QStringLiteral("label_highPower"));
        label_highPower->setGeometry(QRect(20, 110, 75, 23));
        label_highPower->setFont(font);
        pushButton_shutter_close = new QPushButton(centralWidget);
        pushButton_shutter_close->setObjectName(QStringLiteral("pushButton_shutter_close"));
        pushButton_shutter_close->setEnabled(false);
        pushButton_shutter_close->setGeometry(QRect(165, 50, 55, 23));
        pushButton_highPower_on = new QPushButton(centralWidget);
        pushButton_highPower_on->setObjectName(QStringLiteral("pushButton_highPower_on"));
        pushButton_highPower_on->setGeometry(QRect(105, 110, 55, 23));
        pushButton_bulb_off = new QPushButton(centralWidget);
        pushButton_bulb_off->setObjectName(QStringLiteral("pushButton_bulb_off"));
        pushButton_bulb_off->setEnabled(false);
        pushButton_bulb_off->setGeometry(QRect(165, 80, 55, 23));
        pushButton_shutter_open = new QPushButton(centralWidget);
        pushButton_shutter_open->setObjectName(QStringLiteral("pushButton_shutter_open"));
        pushButton_shutter_open->setGeometry(QRect(105, 50, 55, 23));
        label_shutter = new QLabel(centralWidget);
        label_shutter->setObjectName(QStringLiteral("label_shutter"));
        label_shutter->setGeometry(QRect(20, 50, 75, 23));
        label_shutter->setFont(font);
        pushButton_bulb_on = new QPushButton(centralWidget);
        pushButton_bulb_on->setObjectName(QStringLiteral("pushButton_bulb_on"));
        pushButton_bulb_on->setGeometry(QRect(105, 80, 55, 23));
        label_bulb = new QLabel(centralWidget);
        label_bulb->setObjectName(QStringLiteral("label_bulb"));
        label_bulb->setGeometry(QRect(20, 80, 75, 23));
        label_bulb->setFont(font);
        label_bulbOnTime = new QLabel(centralWidget);
        label_bulbOnTime->setObjectName(QStringLiteral("label_bulbOnTime"));
        label_bulbOnTime->setGeometry(QRect(20, 140, 75, 20));
        label_bulbOnTime->setFont(font);
        label_bulbOnTime_value = new QLabel(centralWidget);
        label_bulbOnTime_value->setObjectName(QStringLiteral("label_bulbOnTime_value"));
        label_bulbOnTime_value->setGeometry(QRect(105, 140, 120, 20));
        QFont font1;
        font1.setBold(false);
        font1.setWeight(50);
        label_bulbOnTime_value->setFont(font1);
        label_bulbOnTime_value->setAlignment(Qt::AlignCenter);
        ControlLight->setCentralWidget(centralWidget);

        retranslateUi(ControlLight);

        QMetaObject::connectSlotsByName(ControlLight);
    } // setupUi

    void retranslateUi(QMainWindow *ControlLight)
    {
        ControlLight->setWindowTitle(QApplication::translate("ControlLight", "Light source", Q_NULLPTR));
        pushButton_connect->setText(QApplication::translate("ControlLight", "Connect", Q_NULLPTR));
        label_status->setText(QApplication::translate("ControlLight", "<is connected?>", Q_NULLPTR));
        pushButton_highPower_off->setText(QApplication::translate("ControlLight", "Off", Q_NULLPTR));
        label_highPower->setText(QApplication::translate("ControlLight", "High power", Q_NULLPTR));
        pushButton_shutter_close->setText(QApplication::translate("ControlLight", "Close", Q_NULLPTR));
        pushButton_highPower_on->setText(QApplication::translate("ControlLight", "On", Q_NULLPTR));
        pushButton_bulb_off->setText(QApplication::translate("ControlLight", "Off", Q_NULLPTR));
        pushButton_shutter_open->setText(QApplication::translate("ControlLight", "Open", Q_NULLPTR));
        label_shutter->setText(QApplication::translate("ControlLight", "Shutter", Q_NULLPTR));
        pushButton_bulb_on->setText(QApplication::translate("ControlLight", "On", Q_NULLPTR));
        label_bulb->setText(QApplication::translate("ControlLight", "Bulb", Q_NULLPTR));
        label_bulbOnTime->setText(QApplication::translate("ControlLight", "Bulb on time", Q_NULLPTR));
        label_bulbOnTime_value->setText(QApplication::translate("ControlLight", "00:00:00", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ControlLight: public Ui_ControlLight {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LIGHT_CONTROL_H
