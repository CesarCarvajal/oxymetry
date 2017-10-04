/********************************************************************************
** Form generated from reading UI file 'fluidic_control.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FLUIDIC_CONTROL_H
#define UI_FLUIDIC_CONTROL_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>
#include "plot.h"

QT_BEGIN_NAMESPACE

class Ui_ControlFluidic
{
public:
    QWidget *centralWidget;
    QPushButton *pushButton_apply;
    QPushButton *pushButton_connect;
    QTabWidget *tabWidget;
    QWidget *tab;
    QWidget *tab_2;
    QLabel *label_10;
    QLabel *label_7;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_8;
    QLabel *label_6;
    QLabel *label_5;
    QLabel *label_9;
    QLabel *label;
    QSlider *horizontalSlider_speed;
    QCheckBox *checkBox_direction;
    QCheckBox *checkBox_brake;
    QLabel *label_2;
    QLabel *label_12;
    Plot *qwtPlot_stats;
    QLabel *label_rpm;
    QLabel *label_status;

    void setupUi(QMainWindow *ControlFluidic)
    {
        if (ControlFluidic->objectName().isEmpty())
            ControlFluidic->setObjectName(QStringLiteral("ControlFluidic"));
        ControlFluidic->resize(240, 360);
        centralWidget = new QWidget(ControlFluidic);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        pushButton_apply = new QPushButton(centralWidget);
        pushButton_apply->setObjectName(QStringLiteral("pushButton_apply"));
        pushButton_apply->setEnabled(false);
        pushButton_apply->setGeometry(QRect(150, 325, 75, 23));
        pushButton_connect = new QPushButton(centralWidget);
        pushButton_connect->setObjectName(QStringLiteral("pushButton_connect"));
        pushButton_connect->setGeometry(QRect(150, 10, 75, 23));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setGeometry(QRect(10, 20, 221, 151));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        label_10 = new QLabel(tab_2);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(10, 10, 20, 21));
        label_7 = new QLabel(tab_2);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(70, 10, 20, 21));
        label_3 = new QLabel(tab_2);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(150, 10, 20, 21));
        label_4 = new QLabel(tab_2);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(130, 10, 20, 21));
        label_8 = new QLabel(tab_2);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(50, 10, 20, 21));
        label_6 = new QLabel(tab_2);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(90, 10, 20, 21));
        label_5 = new QLabel(tab_2);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(110, 10, 20, 21));
        label_9 = new QLabel(tab_2);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(30, 10, 20, 21));
        label = new QLabel(tab_2);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(170, 10, 41, 21));
        horizontalSlider_speed = new QSlider(tab_2);
        horizontalSlider_speed->setObjectName(QStringLiteral("horizontalSlider_speed"));
        horizontalSlider_speed->setGeometry(QRect(50, 60, 151, 22));
        horizontalSlider_speed->setMaximum(4095);
        horizontalSlider_speed->setOrientation(Qt::Horizontal);
        horizontalSlider_speed->setTickPosition(QSlider::TicksBelow);
        horizontalSlider_speed->setTickInterval(256);
        checkBox_direction = new QCheckBox(tab_2);
        checkBox_direction->setObjectName(QStringLiteral("checkBox_direction"));
        checkBox_direction->setGeometry(QRect(10, 100, 61, 17));
        checkBox_brake = new QCheckBox(tab_2);
        checkBox_brake->setObjectName(QStringLiteral("checkBox_brake"));
        checkBox_brake->setGeometry(QRect(80, 100, 61, 17));
        checkBox_brake->setChecked(true);
        label_2 = new QLabel(tab_2);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(10, 50, 47, 41));
        label_2->setWordWrap(true);
        label_12 = new QLabel(tab_2);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setGeometry(QRect(170, 30, 41, 21));
        tabWidget->addTab(tab_2, QString());
        qwtPlot_stats = new Plot(centralWidget);
        qwtPlot_stats->setObjectName(QStringLiteral("qwtPlot_stats"));
        qwtPlot_stats->setGeometry(QRect(15, 180, 210, 140));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(qwtPlot_stats->sizePolicy().hasHeightForWidth());
        qwtPlot_stats->setSizePolicy(sizePolicy);
        label_rpm = new QLabel(qwtPlot_stats);
        label_rpm->setObjectName(QStringLiteral("label_rpm"));
        label_rpm->setGeometry(QRect(142, 8, 60, 15));
        label_rpm->setAlignment(Qt::AlignRight|Qt::AlignTop|Qt::AlignTrailing);
        label_status = new QLabel(centralWidget);
        label_status->setObjectName(QStringLiteral("label_status"));
        label_status->setGeometry(QRect(15, 325, 125, 23));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        label_status->setFont(font);
        ControlFluidic->setCentralWidget(centralWidget);
        tabWidget->raise();
        pushButton_apply->raise();
        pushButton_connect->raise();
        qwtPlot_stats->raise();
        label_status->raise();

        retranslateUi(ControlFluidic);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(ControlFluidic);
    } // setupUi

    void retranslateUi(QMainWindow *ControlFluidic)
    {
        ControlFluidic->setWindowTitle(QApplication::translate("ControlFluidic", "Fluidic circuit", Q_NULLPTR));
        pushButton_apply->setText(QApplication::translate("ControlFluidic", "Apply", Q_NULLPTR));
        pushButton_connect->setText(QApplication::translate("ControlFluidic", "Connect", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("ControlFluidic", "Auto", Q_NULLPTR));
        label_10->setText(QApplication::translate("ControlFluidic", "1", Q_NULLPTR));
        label_7->setText(QApplication::translate("ControlFluidic", "4", Q_NULLPTR));
        label_3->setText(QApplication::translate("ControlFluidic", "8", Q_NULLPTR));
        label_4->setText(QApplication::translate("ControlFluidic", "7", Q_NULLPTR));
        label_8->setText(QApplication::translate("ControlFluidic", "3", Q_NULLPTR));
        label_6->setText(QApplication::translate("ControlFluidic", "5", Q_NULLPTR));
        label_5->setText(QApplication::translate("ControlFluidic", "6", Q_NULLPTR));
        label_9->setText(QApplication::translate("ControlFluidic", "2", Q_NULLPTR));
        label->setText(QApplication::translate("ControlFluidic", "valve", Q_NULLPTR));
        checkBox_direction->setText(QApplication::translate("ControlFluidic", "direction", Q_NULLPTR));
        checkBox_brake->setText(QApplication::translate("ControlFluidic", "brake", Q_NULLPTR));
        label_2->setText(QApplication::translate("ControlFluidic", "motor speed", Q_NULLPTR));
        label_12->setText(QApplication::translate("ControlFluidic", "on/off", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("ControlFluidic", "Manual", Q_NULLPTR));
        label_rpm->setText(QApplication::translate("ControlFluidic", "0.0 RPM", Q_NULLPTR));
        label_status->setText(QApplication::translate("ControlFluidic", "<is connected?>", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ControlFluidic: public Ui_ControlFluidic {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FLUIDIC_CONTROL_H
