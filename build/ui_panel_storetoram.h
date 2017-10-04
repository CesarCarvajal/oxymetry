/********************************************************************************
** Form generated from reading UI file 'panel_storetoram.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PANEL_STORETORAM_H
#define UI_PANEL_STORETORAM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_PanelStoreToRAM
{
public:
    QPushButton *pushButton_select;
    QLabel *label_filename;
    QLineEdit *lineEdit_path;
    QPushButton *pushButton_start;
    QLabel *label_name;
    QLabel *label_number;
    QLabel *label_totalTime;

    void setupUi(QDialog *PanelStoreToRAM)
    {
        if (PanelStoreToRAM->objectName().isEmpty())
            PanelStoreToRAM->setObjectName(QStringLiteral("PanelStoreToRAM"));
        PanelStoreToRAM->resize(360, 100);
        pushButton_select = new QPushButton(PanelStoreToRAM);
        pushButton_select->setObjectName(QStringLiteral("pushButton_select"));
        pushButton_select->setGeometry(QRect(270, 10, 80, 23));
        label_filename = new QLabel(PanelStoreToRAM);
        label_filename->setObjectName(QStringLiteral("label_filename"));
        label_filename->setGeometry(QRect(10, 10, 60, 23));
        QFont font;
        font.setBold(false);
        font.setWeight(50);
        label_filename->setFont(font);
        lineEdit_path = new QLineEdit(PanelStoreToRAM);
        lineEdit_path->setObjectName(QStringLiteral("lineEdit_path"));
        lineEdit_path->setEnabled(false);
        lineEdit_path->setGeometry(QRect(65, 10, 195, 23));
        pushButton_start = new QPushButton(PanelStoreToRAM);
        pushButton_start->setObjectName(QStringLiteral("pushButton_start"));
        pushButton_start->setEnabled(false);
        pushButton_start->setGeometry(QRect(270, 40, 80, 23));
        label_name = new QLabel(PanelStoreToRAM);
        label_name->setObjectName(QStringLiteral("label_name"));
        label_name->setGeometry(QRect(10, 75, 60, 20));
        QFont font1;
        font1.setBold(true);
        font1.setWeight(75);
        label_name->setFont(font1);
        label_number = new QLabel(PanelStoreToRAM);
        label_number->setObjectName(QStringLiteral("label_number"));
        label_number->setGeometry(QRect(120, 75, 20, 20));
        label_number->setFont(font1);
        label_totalTime = new QLabel(PanelStoreToRAM);
        label_totalTime->setObjectName(QStringLiteral("label_totalTime"));
        label_totalTime->setGeometry(QRect(200, 75, 290, 20));
        label_totalTime->setFont(font1);

        retranslateUi(PanelStoreToRAM);

        QMetaObject::connectSlotsByName(PanelStoreToRAM);
    } // setupUi

    void retranslateUi(QDialog *PanelStoreToRAM)
    {
        PanelStoreToRAM->setWindowTitle(QApplication::translate("PanelStoreToRAM", "Store to RAM", Q_NULLPTR));
        pushButton_select->setText(QApplication::translate("PanelStoreToRAM", "Select", Q_NULLPTR));
        label_filename->setText(QApplication::translate("PanelStoreToRAM", "Filename:", Q_NULLPTR));
        lineEdit_path->setText(QApplication::translate("PanelStoreToRAM", "Please select a filename", Q_NULLPTR));
        pushButton_start->setText(QApplication::translate("PanelStoreToRAM", "Start", Q_NULLPTR));
        label_name->setText(QApplication::translate("PanelStoreToRAM", "Name", Q_NULLPTR));
        label_number->setText(QApplication::translate("PanelStoreToRAM", "#", Q_NULLPTR));
        label_totalTime->setText(QApplication::translate("PanelStoreToRAM", "Total time", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class PanelStoreToRAM: public Ui_PanelStoreToRAM {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PANEL_STORETORAM_H
