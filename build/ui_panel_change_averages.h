/********************************************************************************
** Form generated from reading UI file 'panel_change_averages.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PANEL_CHANGE_AVERAGES_H
#define UI_PANEL_CHANGE_AVERAGES_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PanelChangeAverages
{
public:
    QPushButton *button_apply;
    QSpinBox *spinbox_value;

    void setupUi(QWidget *PanelChangeAverages)
    {
        if (PanelChangeAverages->objectName().isEmpty())
            PanelChangeAverages->setObjectName(QStringLiteral("PanelChangeAverages"));
        PanelChangeAverages->resize(180, 42);
        button_apply = new QPushButton(PanelChangeAverages);
        button_apply->setObjectName(QStringLiteral("button_apply"));
        button_apply->setGeometry(QRect(105, 10, 65, 22));
        spinbox_value = new QSpinBox(PanelChangeAverages);
        spinbox_value->setObjectName(QStringLiteral("spinbox_value"));
        spinbox_value->setGeometry(QRect(10, 10, 80, 22));
        spinbox_value->setMinimum(1);
        spinbox_value->setMaximum(10000);
        QWidget::setTabOrder(spinbox_value, button_apply);

        retranslateUi(PanelChangeAverages);

        QMetaObject::connectSlotsByName(PanelChangeAverages);
    } // setupUi

    void retranslateUi(QWidget *PanelChangeAverages)
    {
        PanelChangeAverages->setWindowTitle(QApplication::translate("PanelChangeAverages", "Change # of averages", Q_NULLPTR));
        button_apply->setText(QApplication::translate("PanelChangeAverages", "Set", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class PanelChangeAverages: public Ui_PanelChangeAverages {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PANEL_CHANGE_AVERAGES_H
