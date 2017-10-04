/********************************************************************************
** Form generated from reading UI file 'panel_legend.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PANEL_LEGEND_H
#define UI_PANEL_LEGEND_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_PanelLegend
{
public:
    QPushButton *pushButton_close;
    QTableWidget *tableWidget;

    void setupUi(QDialog *PanelLegend)
    {
        if (PanelLegend->objectName().isEmpty())
            PanelLegend->setObjectName(QStringLiteral("PanelLegend"));
        PanelLegend->resize(320, 200);
        pushButton_close = new QPushButton(PanelLegend);
        pushButton_close->setObjectName(QStringLiteral("pushButton_close"));
        pushButton_close->setGeometry(QRect(250, 170, 60, 23));
        tableWidget = new QTableWidget(PanelLegend);
        if (tableWidget->columnCount() < 3)
            tableWidget->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->setGeometry(QRect(10, 10, 300, 150));
        tableWidget->setFocusPolicy(Qt::NoFocus);
        tableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        tableWidget->setAutoScroll(false);
        tableWidget->setSelectionMode(QAbstractItemView::NoSelection);
        tableWidget->horizontalHeader()->setHighlightSections(false);
        tableWidget->verticalHeader()->setVisible(false);
        tableWidget->verticalHeader()->setHighlightSections(false);

        retranslateUi(PanelLegend);

        QMetaObject::connectSlotsByName(PanelLegend);
    } // setupUi

    void retranslateUi(QDialog *PanelLegend)
    {
        PanelLegend->setWindowTitle(QApplication::translate("PanelLegend", "Legend", Q_NULLPTR));
        pushButton_close->setText(QApplication::translate("PanelLegend", "Close", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem->setText(QApplication::translate("PanelLegend", "Serial number", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem1->setText(QApplication::translate("PanelLegend", "Readable name", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class PanelLegend: public Ui_PanelLegend {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PANEL_LEGEND_H
