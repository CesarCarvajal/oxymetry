/********************************************************************************
** Form generated from reading UI file 'panel_timepattern.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PANEL_TIMEPATTERN_H
#define UI_PANEL_TIMEPATTERN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_PanelTimePattern
{
public:
    QLineEdit *lineEdit_path;
    QPushButton *pushButton_start;
    QPushButton *pushButton_select;
    QLabel *label_filename;
    QTableWidget *tableWidget_cmds;
    QLabel *label_current;
    QProgressBar *progressBar_current;
    QLabel *label_total;
    QProgressBar *progressBar_total;
    QLabel *label_device;
    QComboBox *comboBox_device;

    void setupUi(QDialog *PanelTimePattern)
    {
        if (PanelTimePattern->objectName().isEmpty())
            PanelTimePattern->setObjectName(QStringLiteral("PanelTimePattern"));
        PanelTimePattern->resize(640, 480);
        lineEdit_path = new QLineEdit(PanelTimePattern);
        lineEdit_path->setObjectName(QStringLiteral("lineEdit_path"));
        lineEdit_path->setEnabled(false);
        lineEdit_path->setGeometry(QRect(65, 10, 475, 23));
        lineEdit_path->setReadOnly(true);
        pushButton_start = new QPushButton(PanelTimePattern);
        pushButton_start->setObjectName(QStringLiteral("pushButton_start"));
        pushButton_start->setEnabled(false);
        pushButton_start->setGeometry(QRect(550, 40, 80, 23));
        pushButton_select = new QPushButton(PanelTimePattern);
        pushButton_select->setObjectName(QStringLiteral("pushButton_select"));
        pushButton_select->setGeometry(QRect(550, 10, 80, 23));
        label_filename = new QLabel(PanelTimePattern);
        label_filename->setObjectName(QStringLiteral("label_filename"));
        label_filename->setGeometry(QRect(10, 10, 60, 23));
        QFont font;
        font.setBold(false);
        font.setWeight(50);
        label_filename->setFont(font);
        tableWidget_cmds = new QTableWidget(PanelTimePattern);
        if (tableWidget_cmds->columnCount() < 6)
            tableWidget_cmds->setColumnCount(6);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget_cmds->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget_cmds->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget_cmds->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget_cmds->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget_cmds->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget_cmds->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        tableWidget_cmds->setObjectName(QStringLiteral("tableWidget_cmds"));
        tableWidget_cmds->setGeometry(QRect(10, 70, 621, 401));
        tableWidget_cmds->setFocusPolicy(Qt::NoFocus);
        tableWidget_cmds->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        tableWidget_cmds->setAutoScroll(false);
        tableWidget_cmds->setSelectionMode(QAbstractItemView::NoSelection);
        tableWidget_cmds->horizontalHeader()->setHighlightSections(false);
        tableWidget_cmds->verticalHeader()->setVisible(false);
        tableWidget_cmds->verticalHeader()->setHighlightSections(false);
        label_current = new QLabel(PanelTimePattern);
        label_current->setObjectName(QStringLiteral("label_current"));
        label_current->setGeometry(QRect(10, 40, 50, 23));
        label_current->setFont(font);
        progressBar_current = new QProgressBar(PanelTimePattern);
        progressBar_current->setObjectName(QStringLiteral("progressBar_current"));
        progressBar_current->setGeometry(QRect(65, 45, 100, 13));
        progressBar_current->setValue(0);
        progressBar_current->setTextVisible(false);
        label_total = new QLabel(PanelTimePattern);
        label_total->setObjectName(QStringLiteral("label_total"));
        label_total->setGeometry(QRect(195, 40, 40, 23));
        label_total->setFont(font);
        progressBar_total = new QProgressBar(PanelTimePattern);
        progressBar_total->setObjectName(QStringLiteral("progressBar_total"));
        progressBar_total->setGeometry(QRect(240, 45, 100, 13));
        progressBar_total->setValue(0);
        progressBar_total->setTextVisible(false);
        label_device = new QLabel(PanelTimePattern);
        label_device->setObjectName(QStringLiteral("label_device"));
        label_device->setGeometry(QRect(370, 40, 40, 23));
        label_device->setFont(font);
        comboBox_device = new QComboBox(PanelTimePattern);
        comboBox_device->setObjectName(QStringLiteral("comboBox_device"));
        comboBox_device->setGeometry(QRect(420, 40, 120, 22));

        retranslateUi(PanelTimePattern);

        QMetaObject::connectSlotsByName(PanelTimePattern);
    } // setupUi

    void retranslateUi(QDialog *PanelTimePattern)
    {
        PanelTimePattern->setWindowTitle(QApplication::translate("PanelTimePattern", "Time pattern", Q_NULLPTR));
        lineEdit_path->setText(QApplication::translate("PanelTimePattern", "Please select a configuration file", Q_NULLPTR));
        pushButton_start->setText(QApplication::translate("PanelTimePattern", "Start", Q_NULLPTR));
        pushButton_select->setText(QApplication::translate("PanelTimePattern", "Select", Q_NULLPTR));
        label_filename->setText(QApplication::translate("PanelTimePattern", "Filename:", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem = tableWidget_cmds->horizontalHeaderItem(1);
        ___qtablewidgetitem->setText(QApplication::translate("PanelTimePattern", "Time / ms", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget_cmds->horizontalHeaderItem(2);
        ___qtablewidgetitem1->setText(QApplication::translate("PanelTimePattern", "Filename", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget_cmds->horizontalHeaderItem(3);
        ___qtablewidgetitem2->setText(QApplication::translate("PanelTimePattern", "Spectra", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget_cmds->horizontalHeaderItem(4);
        ___qtablewidgetitem3->setText(QApplication::translate("PanelTimePattern", "Integration time / ms", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget_cmds->horizontalHeaderItem(5);
        ___qtablewidgetitem4->setText(QApplication::translate("PanelTimePattern", "Averaging", Q_NULLPTR));
        label_current->setText(QApplication::translate("PanelTimePattern", "Current:", Q_NULLPTR));
        label_total->setText(QApplication::translate("PanelTimePattern", "Total:", Q_NULLPTR));
        label_device->setText(QApplication::translate("PanelTimePattern", "Device:", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class PanelTimePattern: public Ui_PanelTimePattern {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PANEL_TIMEPATTERN_H
