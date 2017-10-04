/********************************************************************************
** Form generated from reading UI file 'panel_change_time.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PANEL_CHANGE_TIME_H
#define UI_PANEL_CHANGE_TIME_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PanelChangeTime
{
public:
    QPushButton *button_apply;
    QDoubleSpinBox *spinbox_timeValue;
    QComboBox *combobox_timeBase;

    void setupUi(QWidget *PanelChangeTime)
    {
        if (PanelChangeTime->objectName().isEmpty())
            PanelChangeTime->setObjectName(QStringLiteral("PanelChangeTime"));
        PanelChangeTime->resize(225, 42);
        button_apply = new QPushButton(PanelChangeTime);
        button_apply->setObjectName(QStringLiteral("button_apply"));
        button_apply->setGeometry(QRect(150, 10, 65, 22));
        spinbox_timeValue = new QDoubleSpinBox(PanelChangeTime);
        spinbox_timeValue->setObjectName(QStringLiteral("spinbox_timeValue"));
        spinbox_timeValue->setGeometry(QRect(10, 10, 80, 22));
        spinbox_timeValue->setDecimals(2);
        spinbox_timeValue->setMinimum(1);
        spinbox_timeValue->setMaximum(10000);
        spinbox_timeValue->setSingleStep(0.1);
        combobox_timeBase = new QComboBox(PanelChangeTime);
        combobox_timeBase->setObjectName(QStringLiteral("combobox_timeBase"));
        combobox_timeBase->setGeometry(QRect(95, 10, 40, 22));
        spinbox_timeValue->raise();
        button_apply->raise();
        combobox_timeBase->raise();
        QWidget::setTabOrder(spinbox_timeValue, combobox_timeBase);
        QWidget::setTabOrder(combobox_timeBase, button_apply);

        retranslateUi(PanelChangeTime);

        QMetaObject::connectSlotsByName(PanelChangeTime);
    } // setupUi

    void retranslateUi(QWidget *PanelChangeTime)
    {
        PanelChangeTime->setWindowTitle(QApplication::translate("PanelChangeTime", "Change integration time", Q_NULLPTR));
        button_apply->setText(QApplication::translate("PanelChangeTime", "Apply", Q_NULLPTR));
        combobox_timeBase->clear();
        combobox_timeBase->insertItems(0, QStringList()
         << QApplication::translate("PanelChangeTime", "\302\265s", Q_NULLPTR)
         << QApplication::translate("PanelChangeTime", "ms", Q_NULLPTR)
         << QApplication::translate("PanelChangeTime", "s", Q_NULLPTR)
        );
    } // retranslateUi

};

namespace Ui {
    class PanelChangeTime: public Ui_PanelChangeTime {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PANEL_CHANGE_TIME_H
