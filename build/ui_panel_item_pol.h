/********************************************************************************
** Form generated from reading UI file 'panel_item_pol.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PANEL_ITEM_POL_H
#define UI_PANEL_ITEM_POL_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QWidget>
#include "clickablelabel.h"

QT_BEGIN_NAMESPACE

class Ui_PanelItem_Pol
{
public:
    QLabel *label;
    QLabel *label_2;
    QLabel *label_saturatedPixels;
    QLabel *label_timeBase;
    ClickableLabel *label_integrationTime;
    ClickableLabel *label_numberOfAverages;
    QLineEdit *lineEdit_name;
    ClickableLabel *label_autoAdjust;
    QLabel *label_ActiveSpec_Pol;

    void setupUi(QWidget *PanelItem_Pol)
    {
        if (PanelItem_Pol->objectName().isEmpty())
            PanelItem_Pol->setObjectName(QStringLiteral("PanelItem_Pol"));
        PanelItem_Pol->resize(252, 116);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(PanelItem_Pol->sizePolicy().hasHeightForWidth());
        PanelItem_Pol->setSizePolicy(sizePolicy);
        PanelItem_Pol->setMinimumSize(QSize(0, 0));
        label = new QLabel(PanelItem_Pol);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 50, 120, 25));
        QFont font;
        font.setBold(false);
        font.setWeight(50);
        label->setFont(font);
        label->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_2 = new QLabel(PanelItem_Pol);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(10, 70, 120, 25));
        label_2->setFont(font);
        label_2->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_saturatedPixels = new QLabel(PanelItem_Pol);
        label_saturatedPixels->setObjectName(QStringLiteral("label_saturatedPixels"));
        label_saturatedPixels->setGeometry(QRect(10, 90, 120, 25));
        label_saturatedPixels->setFont(font);
        label_saturatedPixels->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_timeBase = new QLabel(PanelItem_Pol);
        label_timeBase->setObjectName(QStringLiteral("label_timeBase"));
        label_timeBase->setGeometry(QRect(230, 50, 20, 25));
        label_timeBase->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_integrationTime = new ClickableLabel(PanelItem_Pol);
        label_integrationTime->setObjectName(QStringLiteral("label_integrationTime"));
        label_integrationTime->setGeometry(QRect(170, 50, 50, 25));
        QFont font1;
        font1.setUnderline(true);
        label_integrationTime->setFont(font1);
        label_integrationTime->setCursor(QCursor(Qt::PointingHandCursor));
        label_integrationTime->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_numberOfAverages = new ClickableLabel(PanelItem_Pol);
        label_numberOfAverages->setObjectName(QStringLiteral("label_numberOfAverages"));
        label_numberOfAverages->setGeometry(QRect(170, 70, 50, 25));
        label_numberOfAverages->setFont(font1);
        label_numberOfAverages->setCursor(QCursor(Qt::PointingHandCursor));
        label_numberOfAverages->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lineEdit_name = new QLineEdit(PanelItem_Pol);
        lineEdit_name->setObjectName(QStringLiteral("lineEdit_name"));
        lineEdit_name->setGeometry(QRect(10, 30, 231, 20));
        sizePolicy.setHeightForWidth(lineEdit_name->sizePolicy().hasHeightForWidth());
        lineEdit_name->setSizePolicy(sizePolicy);
        QFont font2;
        font2.setBold(true);
        font2.setWeight(75);
        lineEdit_name->setFont(font2);
        lineEdit_name->setMaxLength(24);
        lineEdit_name->setFrame(false);
        lineEdit_name->setAlignment(Qt::AlignCenter);
        label_autoAdjust = new ClickableLabel(PanelItem_Pol);
        label_autoAdjust->setObjectName(QStringLiteral("label_autoAdjust"));
        label_autoAdjust->setGeometry(QRect(190, 90, 71, 25));
        label_autoAdjust->setFont(font1);
        label_autoAdjust->setCursor(QCursor(Qt::PointingHandCursor));
        label_autoAdjust->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_ActiveSpec_Pol = new QLabel(PanelItem_Pol);
        label_ActiveSpec_Pol->setObjectName(QStringLiteral("label_ActiveSpec_Pol"));
        label_ActiveSpec_Pol->setGeometry(QRect(0, 10, 251, 16));
        label_ActiveSpec_Pol->setAlignment(Qt::AlignCenter);

        retranslateUi(PanelItem_Pol);

        QMetaObject::connectSlotsByName(PanelItem_Pol);
    } // setupUi

    void retranslateUi(QWidget *PanelItem_Pol)
    {
        PanelItem_Pol->setWindowTitle(QApplication::translate("PanelItem_Pol", "Form", Q_NULLPTR));
        label->setText(QApplication::translate("PanelItem_Pol", "Integration time:", Q_NULLPTR));
        label_2->setText(QApplication::translate("PanelItem_Pol", "Number of averages:", Q_NULLPTR));
        label_saturatedPixels->setText(QApplication::translate("PanelItem_Pol", "<saturated pixels>", Q_NULLPTR));
        label_timeBase->setText(QApplication::translate("PanelItem_Pol", "ms", Q_NULLPTR));
        label_integrationTime->setText(QApplication::translate("PanelItem_Pol", "<value>", Q_NULLPTR));
        label_numberOfAverages->setText(QApplication::translate("PanelItem_Pol", "<value>", Q_NULLPTR));
        lineEdit_name->setText(QApplication::translate("PanelItem_Pol", "<name>", Q_NULLPTR));
        label_autoAdjust->setText(QApplication::translate("PanelItem_Pol", "Auto Adjust", Q_NULLPTR));
        label_ActiveSpec_Pol->setText(QApplication::translate("PanelItem_Pol", "Active", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class PanelItem_Pol: public Ui_PanelItem_Pol {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PANEL_ITEM_POL_H
