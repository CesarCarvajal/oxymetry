/********************************************************************************
** Form generated from reading UI file 'configure_Polarimeter_Measure.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONFIGURE_POLARIMETER_MEASURE_H
#define UI_CONFIGURE_POLARIMETER_MEASURE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_configurePolMeasure
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer_11;
    QLabel *label_2;
    QSpacerItem *verticalSpacer_10;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_filename;
    QLineEdit *lineEdit_path;
    QPushButton *pushButton_select;
    QSpacerItem *verticalSpacer_9;
    QLabel *label;
    QSpacerItem *verticalSpacer_4;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_3;
    QLineEdit *lineEdit;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_4;
    QLineEdit *lineEdit_2;
    QLabel *label_13;
    QLabel *label_5;
    QLineEdit *lineEdit_3;
    QLabel *label_14;
    QSpacerItem *verticalSpacer_3;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_6;
    QLineEdit *lineEdit_4;
    QLabel *label_15;
    QLabel *label_7;
    QLineEdit *lineEdit_5;
    QLabel *label_16;
    QSpacerItem *verticalSpacer_5;
    QHBoxLayout *layou6;
    QLabel *label_8;
    QLineEdit *lineEdit_6;
    QSpacerItem *verticalSpacer_6;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_9;
    QLineEdit *lineEdit_7;
    QLabel *label_10;
    QLineEdit *lineEdit_8;
    QSpacerItem *verticalSpacer_7;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_11;
    QLineEdit *lineEdit_10;
    QLabel *label_12;
    QLineEdit *lineEdit_9;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_9;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton;
    QSpacerItem *verticalSpacer_8;

    void setupUi(QDialog *configurePolMeasure)
    {
        if (configurePolMeasure->objectName().isEmpty())
            configurePolMeasure->setObjectName(QStringLiteral("configurePolMeasure"));
        configurePolMeasure->resize(430, 468);
        gridLayout = new QGridLayout(configurePolMeasure);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalSpacer_11 = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer_11);

        label_2 = new QLabel(configurePolMeasure);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setMaximumSize(QSize(16777215, 20));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        label_2->setFont(font);

        verticalLayout->addWidget(label_2);

        verticalSpacer_10 = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer_10);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_filename = new QLabel(configurePolMeasure);
        label_filename->setObjectName(QStringLiteral("label_filename"));
        label_filename->setMaximumSize(QSize(16777215, 43));
        QFont font1;
        font1.setBold(false);
        font1.setWeight(50);
        label_filename->setFont(font1);

        horizontalLayout_2->addWidget(label_filename);

        lineEdit_path = new QLineEdit(configurePolMeasure);
        lineEdit_path->setObjectName(QStringLiteral("lineEdit_path"));
        lineEdit_path->setEnabled(false);
        lineEdit_path->setReadOnly(true);

        horizontalLayout_2->addWidget(lineEdit_path);

        pushButton_select = new QPushButton(configurePolMeasure);
        pushButton_select->setObjectName(QStringLiteral("pushButton_select"));
        pushButton_select->setMinimumSize(QSize(150, 0));

        horizontalLayout_2->addWidget(pushButton_select);


        verticalLayout->addLayout(horizontalLayout_2);

        verticalSpacer_9 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer_9);

        label = new QLabel(configurePolMeasure);
        label->setObjectName(QStringLiteral("label"));
        label->setMaximumSize(QSize(16777215, 20));
        label->setFont(font);

        verticalLayout->addWidget(label);

        verticalSpacer_4 = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer_4);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_3 = new QLabel(configurePolMeasure);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setMaximumSize(QSize(16777215, 43));

        horizontalLayout_4->addWidget(label_3);

        lineEdit = new QLineEdit(configurePolMeasure);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setEnabled(false);
        lineEdit->setMinimumSize(QSize(50, 0));
        lineEdit->setMaximumSize(QSize(50, 16777215));
        lineEdit->setLayoutDirection(Qt::LeftToRight);
        lineEdit->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_4->addWidget(lineEdit);


        verticalLayout->addLayout(horizontalLayout_4);

        verticalSpacer_2 = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_4 = new QLabel(configurePolMeasure);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout_3->addWidget(label_4);

        lineEdit_2 = new QLineEdit(configurePolMeasure);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));
        lineEdit_2->setEnabled(false);
        lineEdit_2->setMinimumSize(QSize(50, 0));
        lineEdit_2->setMaximumSize(QSize(50, 16777215));
        lineEdit_2->setLayoutDirection(Qt::LeftToRight);
        lineEdit_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_3->addWidget(lineEdit_2);

        label_13 = new QLabel(configurePolMeasure);
        label_13->setObjectName(QStringLiteral("label_13"));

        horizontalLayout_3->addWidget(label_13);

        label_5 = new QLabel(configurePolMeasure);
        label_5->setObjectName(QStringLiteral("label_5"));

        horizontalLayout_3->addWidget(label_5);

        lineEdit_3 = new QLineEdit(configurePolMeasure);
        lineEdit_3->setObjectName(QStringLiteral("lineEdit_3"));
        lineEdit_3->setEnabled(false);
        lineEdit_3->setMinimumSize(QSize(50, 0));
        lineEdit_3->setMaximumSize(QSize(50, 16777215));
        lineEdit_3->setLayoutDirection(Qt::LeftToRight);
        lineEdit_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_3->addWidget(lineEdit_3);

        label_14 = new QLabel(configurePolMeasure);
        label_14->setObjectName(QStringLiteral("label_14"));

        horizontalLayout_3->addWidget(label_14);


        verticalLayout->addLayout(horizontalLayout_3);

        verticalSpacer_3 = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer_3);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        label_6 = new QLabel(configurePolMeasure);
        label_6->setObjectName(QStringLiteral("label_6"));

        horizontalLayout_5->addWidget(label_6);

        lineEdit_4 = new QLineEdit(configurePolMeasure);
        lineEdit_4->setObjectName(QStringLiteral("lineEdit_4"));
        lineEdit_4->setEnabled(false);
        lineEdit_4->setMinimumSize(QSize(50, 0));
        lineEdit_4->setMaximumSize(QSize(50, 16777215));
        lineEdit_4->setLayoutDirection(Qt::LeftToRight);
        lineEdit_4->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_5->addWidget(lineEdit_4);

        label_15 = new QLabel(configurePolMeasure);
        label_15->setObjectName(QStringLiteral("label_15"));

        horizontalLayout_5->addWidget(label_15);

        label_7 = new QLabel(configurePolMeasure);
        label_7->setObjectName(QStringLiteral("label_7"));

        horizontalLayout_5->addWidget(label_7);

        lineEdit_5 = new QLineEdit(configurePolMeasure);
        lineEdit_5->setObjectName(QStringLiteral("lineEdit_5"));
        lineEdit_5->setEnabled(false);
        lineEdit_5->setMinimumSize(QSize(50, 0));
        lineEdit_5->setMaximumSize(QSize(50, 16777215));
        lineEdit_5->setLayoutDirection(Qt::LeftToRight);
        lineEdit_5->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_5->addWidget(lineEdit_5);

        label_16 = new QLabel(configurePolMeasure);
        label_16->setObjectName(QStringLiteral("label_16"));

        horizontalLayout_5->addWidget(label_16);


        verticalLayout->addLayout(horizontalLayout_5);

        verticalSpacer_5 = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer_5);

        layou6 = new QHBoxLayout();
        layou6->setObjectName(QStringLiteral("layou6"));
        label_8 = new QLabel(configurePolMeasure);
        label_8->setObjectName(QStringLiteral("label_8"));

        layou6->addWidget(label_8);

        lineEdit_6 = new QLineEdit(configurePolMeasure);
        lineEdit_6->setObjectName(QStringLiteral("lineEdit_6"));
        lineEdit_6->setEnabled(false);
        lineEdit_6->setMinimumSize(QSize(50, 0));
        lineEdit_6->setMaximumSize(QSize(50, 16777215));
        lineEdit_6->setLayoutDirection(Qt::LeftToRight);
        lineEdit_6->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        layou6->addWidget(lineEdit_6);


        verticalLayout->addLayout(layou6);

        verticalSpacer_6 = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer_6);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        label_9 = new QLabel(configurePolMeasure);
        label_9->setObjectName(QStringLiteral("label_9"));

        horizontalLayout_7->addWidget(label_9);

        lineEdit_7 = new QLineEdit(configurePolMeasure);
        lineEdit_7->setObjectName(QStringLiteral("lineEdit_7"));
        lineEdit_7->setEnabled(false);
        lineEdit_7->setMinimumSize(QSize(50, 0));
        lineEdit_7->setMaximumSize(QSize(50, 16777215));
        lineEdit_7->setLayoutDirection(Qt::LeftToRight);
        lineEdit_7->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_7->addWidget(lineEdit_7);

        label_10 = new QLabel(configurePolMeasure);
        label_10->setObjectName(QStringLiteral("label_10"));

        horizontalLayout_7->addWidget(label_10);

        lineEdit_8 = new QLineEdit(configurePolMeasure);
        lineEdit_8->setObjectName(QStringLiteral("lineEdit_8"));
        lineEdit_8->setEnabled(false);
        lineEdit_8->setMinimumSize(QSize(50, 0));
        lineEdit_8->setMaximumSize(QSize(50, 16777215));
        lineEdit_8->setLayoutDirection(Qt::LeftToRight);
        lineEdit_8->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_7->addWidget(lineEdit_8);


        verticalLayout->addLayout(horizontalLayout_7);

        verticalSpacer_7 = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer_7);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        label_11 = new QLabel(configurePolMeasure);
        label_11->setObjectName(QStringLiteral("label_11"));

        horizontalLayout_8->addWidget(label_11);

        lineEdit_10 = new QLineEdit(configurePolMeasure);
        lineEdit_10->setObjectName(QStringLiteral("lineEdit_10"));
        lineEdit_10->setEnabled(false);
        lineEdit_10->setMinimumSize(QSize(50, 0));
        lineEdit_10->setMaximumSize(QSize(50, 16777215));
        lineEdit_10->setLayoutDirection(Qt::LeftToRight);
        lineEdit_10->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_8->addWidget(lineEdit_10);

        label_12 = new QLabel(configurePolMeasure);
        label_12->setObjectName(QStringLiteral("label_12"));

        horizontalLayout_8->addWidget(label_12);

        lineEdit_9 = new QLineEdit(configurePolMeasure);
        lineEdit_9->setObjectName(QStringLiteral("lineEdit_9"));
        lineEdit_9->setEnabled(false);
        lineEdit_9->setMinimumSize(QSize(50, 0));
        lineEdit_9->setMaximumSize(QSize(50, 16777215));
        lineEdit_9->setLayoutDirection(Qt::LeftToRight);
        lineEdit_9->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_8->addWidget(lineEdit_9);


        verticalLayout->addLayout(horizontalLayout_8);

        verticalSpacer = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        horizontalSpacer = new QSpacerItem(252, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer);

        pushButton = new QPushButton(configurePolMeasure);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setMinimumSize(QSize(150, 0));

        horizontalLayout_9->addWidget(pushButton);


        verticalLayout->addLayout(horizontalLayout_9);

        verticalSpacer_8 = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer_8);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);


        retranslateUi(configurePolMeasure);

        QMetaObject::connectSlotsByName(configurePolMeasure);
    } // setupUi

    void retranslateUi(QDialog *configurePolMeasure)
    {
        configurePolMeasure->setWindowTitle(QApplication::translate("configurePolMeasure", "Time pattern", Q_NULLPTR));
        label_2->setText(QApplication::translate("configurePolMeasure", "Load a Spectrometer Configuration File:", Q_NULLPTR));
        label_filename->setText(QApplication::translate("configurePolMeasure", "Filename:", Q_NULLPTR));
        lineEdit_path->setText(QApplication::translate("configurePolMeasure", "Please select a configuration file", Q_NULLPTR));
        pushButton_select->setText(QApplication::translate("configurePolMeasure", "Load Configuration", Q_NULLPTR));
        label->setText(QApplication::translate("configurePolMeasure", "Generate a Spectrometer and Pump configuration Files:", Q_NULLPTR));
        label_3->setText(QApplication::translate("configurePolMeasure", "Number of Concentrations:", Q_NULLPTR));
        lineEdit->setText(QApplication::translate("configurePolMeasure", "50", Q_NULLPTR));
        label_4->setText(QApplication::translate("configurePolMeasure", "Range of Glucose:", Q_NULLPTR));
        lineEdit_2->setText(QApplication::translate("configurePolMeasure", "50", Q_NULLPTR));
        label_13->setText(QApplication::translate("configurePolMeasure", "mg/dL", Q_NULLPTR));
        label_5->setText(QApplication::translate("configurePolMeasure", "to", Q_NULLPTR));
        lineEdit_3->setText(QApplication::translate("configurePolMeasure", "50", Q_NULLPTR));
        label_14->setText(QApplication::translate("configurePolMeasure", "mg/dL", Q_NULLPTR));
        label_6->setText(QApplication::translate("configurePolMeasure", "Range of Proteins:", Q_NULLPTR));
        lineEdit_4->setText(QApplication::translate("configurePolMeasure", "50", Q_NULLPTR));
        label_15->setText(QApplication::translate("configurePolMeasure", "mg/dL", Q_NULLPTR));
        label_7->setText(QApplication::translate("configurePolMeasure", "to", Q_NULLPTR));
        lineEdit_5->setText(QApplication::translate("configurePolMeasure", "50", Q_NULLPTR));
        label_16->setText(QApplication::translate("configurePolMeasure", "mg/dL", Q_NULLPTR));
        label_8->setText(QApplication::translate("configurePolMeasure", "Absolute Flow:", Q_NULLPTR));
        lineEdit_6->setText(QApplication::translate("configurePolMeasure", "50", Q_NULLPTR));
        label_9->setText(QApplication::translate("configurePolMeasure", "Filling Time:", Q_NULLPTR));
        lineEdit_7->setText(QApplication::translate("configurePolMeasure", "50", Q_NULLPTR));
        label_10->setText(QApplication::translate("configurePolMeasure", "Break Time:", Q_NULLPTR));
        lineEdit_8->setText(QApplication::translate("configurePolMeasure", "50", Q_NULLPTR));
        label_11->setText(QApplication::translate("configurePolMeasure", "Stock Glucose:", Q_NULLPTR));
        lineEdit_10->setText(QApplication::translate("configurePolMeasure", "50", Q_NULLPTR));
        label_12->setText(QApplication::translate("configurePolMeasure", "Stock Proteins", Q_NULLPTR));
        lineEdit_9->setText(QApplication::translate("configurePolMeasure", "50", Q_NULLPTR));
        pushButton->setText(QApplication::translate("configurePolMeasure", "Generate Configuration", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class configurePolMeasure: public Ui_configurePolMeasure {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONFIGURE_POLARIMETER_MEASURE_H
