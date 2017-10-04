/********************************************************************************
** Form generated from reading UI file 'panel_item.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PANEL_ITEM_H
#define UI_PANEL_ITEM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>
#include "clickablelabel.h"

QT_BEGIN_NAMESPACE

class Ui_PanelItem
{
public:
    QPushButton *button_config;
    QPushButton *button_eeprom;
    QProgressBar *progress_measurement;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_saturatedPixels;
    QLabel *label_timeBase;
    ClickableLabel *label_integrationTime;
    ClickableLabel *label_numberOfAverages;
    QCheckBox *checkBox_enabled;
    QLineEdit *lineEdit_name;
    ClickableLabel *label_autoAdjust;

    void setupUi(QWidget *PanelItem)
    {
        if (PanelItem->objectName().isEmpty())
            PanelItem->setObjectName(QStringLiteral("PanelItem"));
        PanelItem->resize(220, 170);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(PanelItem->sizePolicy().hasHeightForWidth());
        PanelItem->setSizePolicy(sizePolicy);
        PanelItem->setMinimumSize(QSize(0, 0));
        button_config = new QPushButton(PanelItem);
        button_config->setObjectName(QStringLiteral("button_config"));
        button_config->setGeometry(QRect(10, 45, 70, 25));
        QFont font;
        font.setPointSize(8);
        font.setKerning(true);
        button_config->setFont(font);
        button_eeprom = new QPushButton(PanelItem);
        button_eeprom->setObjectName(QStringLiteral("button_eeprom"));
        button_eeprom->setGeometry(QRect(85, 45, 70, 25));
        QFont font1;
        font1.setPointSize(8);
        button_eeprom->setFont(font1);
        progress_measurement = new QProgressBar(PanelItem);
        progress_measurement->setObjectName(QStringLiteral("progress_measurement"));
        progress_measurement->setGeometry(QRect(10, 35, 200, 5));
        sizePolicy.setHeightForWidth(progress_measurement->sizePolicy().hasHeightForWidth());
        progress_measurement->setSizePolicy(sizePolicy);
        progress_measurement->setMaximum(100);
        progress_measurement->setValue(100);
        progress_measurement->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        progress_measurement->setTextVisible(false);
        progress_measurement->setInvertedAppearance(false);
        label = new QLabel(PanelItem);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 75, 120, 25));
        QFont font2;
        font2.setBold(false);
        font2.setWeight(50);
        label->setFont(font2);
        label->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_2 = new QLabel(PanelItem);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(10, 115, 120, 25));
        label_2->setFont(font2);
        label_2->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_saturatedPixels = new QLabel(PanelItem);
        label_saturatedPixels->setObjectName(QStringLiteral("label_saturatedPixels"));
        label_saturatedPixels->setGeometry(QRect(10, 135, 120, 25));
        label_saturatedPixels->setFont(font2);
        label_saturatedPixels->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_timeBase = new QLabel(PanelItem);
        label_timeBase->setObjectName(QStringLiteral("label_timeBase"));
        label_timeBase->setGeometry(QRect(190, 75, 20, 25));
        label_timeBase->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_integrationTime = new ClickableLabel(PanelItem);
        label_integrationTime->setObjectName(QStringLiteral("label_integrationTime"));
        label_integrationTime->setGeometry(QRect(135, 75, 50, 25));
        QFont font3;
        font3.setUnderline(true);
        label_integrationTime->setFont(font3);
        label_integrationTime->setCursor(QCursor(Qt::PointingHandCursor));
        label_integrationTime->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_numberOfAverages = new ClickableLabel(PanelItem);
        label_numberOfAverages->setObjectName(QStringLiteral("label_numberOfAverages"));
        label_numberOfAverages->setGeometry(QRect(135, 115, 50, 25));
        label_numberOfAverages->setFont(font3);
        label_numberOfAverages->setCursor(QCursor(Qt::PointingHandCursor));
        label_numberOfAverages->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        checkBox_enabled = new QCheckBox(PanelItem);
        checkBox_enabled->setObjectName(QStringLiteral("checkBox_enabled"));
        checkBox_enabled->setGeometry(QRect(195, 10, 15, 15));
        sizePolicy.setHeightForWidth(checkBox_enabled->sizePolicy().hasHeightForWidth());
        checkBox_enabled->setSizePolicy(sizePolicy);
        checkBox_enabled->setIconSize(QSize(15, 15));
        checkBox_enabled->setChecked(true);
        lineEdit_name = new QLineEdit(PanelItem);
        lineEdit_name->setObjectName(QStringLiteral("lineEdit_name"));
        lineEdit_name->setGeometry(QRect(10, 10, 175, 15));
        sizePolicy.setHeightForWidth(lineEdit_name->sizePolicy().hasHeightForWidth());
        lineEdit_name->setSizePolicy(sizePolicy);
        QFont font4;
        font4.setBold(true);
        font4.setWeight(75);
        lineEdit_name->setFont(font4);
        lineEdit_name->setMaxLength(24);
        lineEdit_name->setFrame(false);
        label_autoAdjust = new ClickableLabel(PanelItem);
        label_autoAdjust->setObjectName(QStringLiteral("label_autoAdjust"));
        label_autoAdjust->setGeometry(QRect(20, 95, 181, 25));
        label_autoAdjust->setFont(font3);
        label_autoAdjust->setCursor(QCursor(Qt::PointingHandCursor));
        label_autoAdjust->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        retranslateUi(PanelItem);

        QMetaObject::connectSlotsByName(PanelItem);
    } // setupUi

    void retranslateUi(QWidget *PanelItem)
    {
        PanelItem->setWindowTitle(QApplication::translate("PanelItem", "Form", Q_NULLPTR));
        button_config->setText(QApplication::translate("PanelItem", "Configure", Q_NULLPTR));
        button_eeprom->setText(QApplication::translate("PanelItem", "EEPROM", Q_NULLPTR));
        label->setText(QApplication::translate("PanelItem", "Integration time:", Q_NULLPTR));
        label_2->setText(QApplication::translate("PanelItem", "Number of averages:", Q_NULLPTR));
        label_saturatedPixels->setText(QApplication::translate("PanelItem", "<saturated pixels>", Q_NULLPTR));
        label_timeBase->setText(QApplication::translate("PanelItem", "ms", Q_NULLPTR));
        label_integrationTime->setText(QApplication::translate("PanelItem", "<value>", Q_NULLPTR));
        label_numberOfAverages->setText(QApplication::translate("PanelItem", "<value>", Q_NULLPTR));
        checkBox_enabled->setText(QString());
        lineEdit_name->setText(QApplication::translate("PanelItem", "<name>", Q_NULLPTR));
        label_autoAdjust->setText(QApplication::translate("PanelItem", "Automatic adjustment", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class PanelItem: public Ui_PanelItem {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PANEL_ITEM_H
