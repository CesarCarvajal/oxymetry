/********************************************************************************
** Form generated from reading UI file 'fluidic_connect.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FLUIDIC_CONNECT_H
#define UI_FLUIDIC_CONNECT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_ConnectFluidic
{
public:
    QComboBox *comboBox_port;
    QLabel *label;
    QLabel *label_2;
    QComboBox *comboBox_baudrate;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QComboBox *comboBox_dataBits;
    QComboBox *comboBox_parity;
    QComboBox *comboBox_stopBits;
    QComboBox *comboBox_flowControl;
    QPushButton *pushButton_cancel;
    QPushButton *pushButton_connect;
    QPushButton *pushButton_update;

    void setupUi(QDialog *ConnectFluidic)
    {
        if (ConnectFluidic->objectName().isEmpty())
            ConnectFluidic->setObjectName(QStringLiteral("ConnectFluidic"));
        ConnectFluidic->resize(220, 240);
        comboBox_port = new QComboBox(ConnectFluidic);
        comboBox_port->setObjectName(QStringLiteral("comboBox_port"));
        comboBox_port->setGeometry(QRect(110, 10, 100, 20));
        label = new QLabel(ConnectFluidic);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 10, 80, 20));
        label_2 = new QLabel(ConnectFluidic);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(10, 40, 80, 20));
        comboBox_baudrate = new QComboBox(ConnectFluidic);
        comboBox_baudrate->setObjectName(QStringLiteral("comboBox_baudrate"));
        comboBox_baudrate->setGeometry(QRect(110, 40, 100, 20));
        label_3 = new QLabel(ConnectFluidic);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(10, 70, 80, 20));
        label_4 = new QLabel(ConnectFluidic);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(10, 100, 80, 20));
        label_5 = new QLabel(ConnectFluidic);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(10, 130, 80, 20));
        label_6 = new QLabel(ConnectFluidic);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(10, 160, 80, 20));
        comboBox_dataBits = new QComboBox(ConnectFluidic);
        comboBox_dataBits->setObjectName(QStringLiteral("comboBox_dataBits"));
        comboBox_dataBits->setGeometry(QRect(110, 70, 100, 20));
        comboBox_parity = new QComboBox(ConnectFluidic);
        comboBox_parity->setObjectName(QStringLiteral("comboBox_parity"));
        comboBox_parity->setGeometry(QRect(110, 100, 100, 20));
        comboBox_stopBits = new QComboBox(ConnectFluidic);
        comboBox_stopBits->setObjectName(QStringLiteral("comboBox_stopBits"));
        comboBox_stopBits->setGeometry(QRect(110, 130, 100, 20));
        comboBox_flowControl = new QComboBox(ConnectFluidic);
        comboBox_flowControl->setObjectName(QStringLiteral("comboBox_flowControl"));
        comboBox_flowControl->setGeometry(QRect(110, 160, 100, 20));
        pushButton_cancel = new QPushButton(ConnectFluidic);
        pushButton_cancel->setObjectName(QStringLiteral("pushButton_cancel"));
        pushButton_cancel->setGeometry(QRect(150, 200, 60, 23));
        pushButton_connect = new QPushButton(ConnectFluidic);
        pushButton_connect->setObjectName(QStringLiteral("pushButton_connect"));
        pushButton_connect->setGeometry(QRect(10, 200, 60, 23));
        pushButton_update = new QPushButton(ConnectFluidic);
        pushButton_update->setObjectName(QStringLiteral("pushButton_update"));
        pushButton_update->setGeometry(QRect(80, 200, 60, 23));

        retranslateUi(ConnectFluidic);

        QMetaObject::connectSlotsByName(ConnectFluidic);
    } // setupUi

    void retranslateUi(QDialog *ConnectFluidic)
    {
        ConnectFluidic->setWindowTitle(QApplication::translate("ConnectFluidic", "Init COM", Q_NULLPTR));
        label->setText(QApplication::translate("ConnectFluidic", "COM port:", Q_NULLPTR));
        label_2->setText(QApplication::translate("ConnectFluidic", "Baudrate:", Q_NULLPTR));
        comboBox_baudrate->setCurrentText(QString());
        label_3->setText(QApplication::translate("ConnectFluidic", "Data bits:", Q_NULLPTR));
        label_4->setText(QApplication::translate("ConnectFluidic", "Parity:", Q_NULLPTR));
        label_5->setText(QApplication::translate("ConnectFluidic", "Stop bits:", Q_NULLPTR));
        label_6->setText(QApplication::translate("ConnectFluidic", "Flow control:", Q_NULLPTR));
        pushButton_cancel->setText(QApplication::translate("ConnectFluidic", "Cancel", Q_NULLPTR));
        pushButton_connect->setText(QApplication::translate("ConnectFluidic", "Connect", Q_NULLPTR));
        pushButton_update->setText(QApplication::translate("ConnectFluidic", "Update", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ConnectFluidic: public Ui_ConnectFluidic {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FLUIDIC_CONNECT_H
