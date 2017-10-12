/********************************************************************************
** Form generated from reading UI file 'panel.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PANEL_H
#define UI_PANEL_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "clickablelabel.h"
#include "measurementstable.h"
#include "plot.h"

QT_BEGIN_NAMESPACE

class Ui_Panel
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget;
    QWidget *tab;
    QGridLayout *gridLayout_3;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout_2;
    QLabel *label;
    QListWidget *list_devices;
    QSpacerItem *verticalSpacer_6;
    QLabel *label_2;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_preview;
    QVBoxLayout *verticalLayout_4;
    QPushButton *pushButton_storeToRam;
    QPushButton *pushButton_timePattern;
    QSpacerItem *horizontalSpacer_4;
    QVBoxLayout *verticalLayout_3;
    QSpacerItem *verticalSpacer_5;
    Plot *qwtPlot;
    QSpacerItem *verticalSpacer_4;
    QLabel *label_4;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *pushButton_legend;
    QPushButton *pushButton_exportData;
    QPushButton *pushButton_saveGraph;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_about;
    QWidget *tab_2;
    QGridLayout *gridLayout_2;
    QHBoxLayout *horizontalLayout_4;
    QVBoxLayout *verticalLayout_6;
    QLabel *label_iad_configuration;
    QHBoxLayout *horizontalLayout_6;
    QPushButton *button_iad_newConfiguration;
    QPushButton *button_iad_openConfiguration;
    QSpacerItem *horizontalSpacer_6;
    ClickableLabel *label_iad_configurationName;
    QSpacerItem *horizontalSpacer_5;
    QSpacerItem *verticalSpacer_3;
    QLabel *label_iad_calibration;
    QPushButton *button_iad_calibrate;
    QSpacerItem *verticalSpacer;
    QLabel *label_iad_measurement;
    QLabel *label_iad_name;
    QLineEdit *lineEdit_iad_name;
    QLabel *label_iad_description;
    QPlainTextEdit *plainTextEdit_iad_description;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *button_iad_measure;
    QCheckBox *checkBox_iad_liveView;
    QSpacerItem *horizontalSpacer_7;
    QSpacerItem *verticalSpacer_2;
    QLabel *label_iad_analysis;
    MeasurementsTable *table_iad_measurements;
    QSpacerItem *horizontalSpacer_3;
    QVBoxLayout *verticalLayout_5;
    Plot *qwtPlot_reflection;
    Plot *qwtPlot_transmission;

    void setupUi(QDialog *Panel)
    {
        if (Panel->objectName().isEmpty())
            Panel->setObjectName(QStringLiteral("Panel"));
        Panel->resize(1200, 800);
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Panel->sizePolicy().hasHeightForWidth());
        Panel->setSizePolicy(sizePolicy);
        Panel->setMinimumSize(QSize(1200, 800));
        gridLayout = new QGridLayout(Panel);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(5);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        tabWidget = new QTabWidget(Panel);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        gridLayout_3 = new QGridLayout(tab);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        label = new QLabel(tab);
        label->setObjectName(QStringLiteral("label"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy1);
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);
        label->setFrameShape(QFrame::NoFrame);
        label->setMidLineWidth(2);
        label->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);

        verticalLayout_2->addWidget(label);

        list_devices = new QListWidget(tab);
        list_devices->setObjectName(QStringLiteral("list_devices"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(list_devices->sizePolicy().hasHeightForWidth());
        list_devices->setSizePolicy(sizePolicy2);
        list_devices->setMinimumSize(QSize(230, 540));
        list_devices->setMaximumSize(QSize(230, 16777215));
        list_devices->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        list_devices->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        list_devices->setAutoScroll(false);

        verticalLayout_2->addWidget(list_devices);

        verticalSpacer_6 = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_2->addItem(verticalSpacer_6);

        label_2 = new QLabel(tab);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setFont(font);
        label_2->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);

        verticalLayout_2->addWidget(label_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        pushButton_preview = new QPushButton(tab);
        pushButton_preview->setObjectName(QStringLiteral("pushButton_preview"));
        QSizePolicy sizePolicy3(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(pushButton_preview->sizePolicy().hasHeightForWidth());
        pushButton_preview->setSizePolicy(sizePolicy3);
        pushButton_preview->setMinimumSize(QSize(110, 66));
        pushButton_preview->setMaximumSize(QSize(100, 66));

        horizontalLayout->addWidget(pushButton_preview);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        pushButton_storeToRam = new QPushButton(tab);
        pushButton_storeToRam->setObjectName(QStringLiteral("pushButton_storeToRam"));
        pushButton_storeToRam->setEnabled(true);
        sizePolicy3.setHeightForWidth(pushButton_storeToRam->sizePolicy().hasHeightForWidth());
        pushButton_storeToRam->setSizePolicy(sizePolicy3);
        pushButton_storeToRam->setMinimumSize(QSize(110, 30));
        pushButton_storeToRam->setMaximumSize(QSize(100, 30));

        verticalLayout_4->addWidget(pushButton_storeToRam);

        pushButton_timePattern = new QPushButton(tab);
        pushButton_timePattern->setObjectName(QStringLiteral("pushButton_timePattern"));
        pushButton_timePattern->setEnabled(true);
        sizePolicy3.setHeightForWidth(pushButton_timePattern->sizePolicy().hasHeightForWidth());
        pushButton_timePattern->setSizePolicy(sizePolicy3);
        pushButton_timePattern->setMinimumSize(QSize(110, 30));
        pushButton_timePattern->setMaximumSize(QSize(100, 30));

        verticalLayout_4->addWidget(pushButton_timePattern);


        horizontalLayout->addLayout(verticalLayout_4);


        verticalLayout_2->addLayout(horizontalLayout);


        horizontalLayout_2->addLayout(verticalLayout_2);

        horizontalSpacer_4 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_4);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalSpacer_5 = new QSpacerItem(20, 16, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_3->addItem(verticalSpacer_5);

        qwtPlot = new Plot(tab);
        qwtPlot->setObjectName(QStringLiteral("qwtPlot"));
        QSizePolicy sizePolicy4(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(qwtPlot->sizePolicy().hasHeightForWidth());
        qwtPlot->setSizePolicy(sizePolicy4);
        qwtPlot->setMinimumSize(QSize(0, 0));

        verticalLayout_3->addWidget(qwtPlot);

        verticalSpacer_4 = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_3->addItem(verticalSpacer_4);

        label_4 = new QLabel(tab);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setFont(font);

        verticalLayout_3->addWidget(label_4);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setSizeConstraint(QLayout::SetDefaultConstraint);
        pushButton_legend = new QPushButton(tab);
        pushButton_legend->setObjectName(QStringLiteral("pushButton_legend"));
        pushButton_legend->setMinimumSize(QSize(80, 30));
        pushButton_legend->setMaximumSize(QSize(80, 30));

        horizontalLayout_3->addWidget(pushButton_legend);

        pushButton_exportData = new QPushButton(tab);
        pushButton_exportData->setObjectName(QStringLiteral("pushButton_exportData"));
        QSizePolicy sizePolicy5(QSizePolicy::Maximum, QSizePolicy::Fixed);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(pushButton_exportData->sizePolicy().hasHeightForWidth());
        pushButton_exportData->setSizePolicy(sizePolicy5);
        pushButton_exportData->setMinimumSize(QSize(80, 30));
        pushButton_exportData->setMaximumSize(QSize(80, 30));

        horizontalLayout_3->addWidget(pushButton_exportData);

        pushButton_saveGraph = new QPushButton(tab);
        pushButton_saveGraph->setObjectName(QStringLiteral("pushButton_saveGraph"));
        sizePolicy5.setHeightForWidth(pushButton_saveGraph->sizePolicy().hasHeightForWidth());
        pushButton_saveGraph->setSizePolicy(sizePolicy5);
        pushButton_saveGraph->setMinimumSize(QSize(80, 30));
        pushButton_saveGraph->setMaximumSize(QSize(80, 30));

        horizontalLayout_3->addWidget(pushButton_saveGraph);

        horizontalSpacer = new QSpacerItem(100, 23, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        pushButton_about = new QPushButton(tab);
        pushButton_about->setObjectName(QStringLiteral("pushButton_about"));
        sizePolicy5.setHeightForWidth(pushButton_about->sizePolicy().hasHeightForWidth());
        pushButton_about->setSizePolicy(sizePolicy5);
        pushButton_about->setMinimumSize(QSize(80, 30));
        pushButton_about->setMaximumSize(QSize(80, 30));

        horizontalLayout_3->addWidget(pushButton_about);


        verticalLayout_3->addLayout(horizontalLayout_3);


        horizontalLayout_2->addLayout(verticalLayout_3);


        gridLayout_3->addLayout(horizontalLayout_2, 0, 0, 1, 1);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        gridLayout_2 = new QGridLayout(tab_2);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        label_iad_configuration = new QLabel(tab_2);
        label_iad_configuration->setObjectName(QStringLiteral("label_iad_configuration"));
        label_iad_configuration->setFont(font);

        verticalLayout_6->addWidget(label_iad_configuration);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        horizontalLayout_6->setContentsMargins(-1, 0, -1, -1);
        button_iad_newConfiguration = new QPushButton(tab_2);
        button_iad_newConfiguration->setObjectName(QStringLiteral("button_iad_newConfiguration"));
        sizePolicy3.setHeightForWidth(button_iad_newConfiguration->sizePolicy().hasHeightForWidth());
        button_iad_newConfiguration->setSizePolicy(sizePolicy3);

        horizontalLayout_6->addWidget(button_iad_newConfiguration);

        button_iad_openConfiguration = new QPushButton(tab_2);
        button_iad_openConfiguration->setObjectName(QStringLiteral("button_iad_openConfiguration"));
        sizePolicy3.setHeightForWidth(button_iad_openConfiguration->sizePolicy().hasHeightForWidth());
        button_iad_openConfiguration->setSizePolicy(sizePolicy3);

        horizontalLayout_6->addWidget(button_iad_openConfiguration);

        horizontalSpacer_6 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_6);

        label_iad_configurationName = new ClickableLabel(tab_2);
        label_iad_configurationName->setObjectName(QStringLiteral("label_iad_configurationName"));
        label_iad_configurationName->setMinimumSize(QSize(0, 0));
        label_iad_configurationName->setMaximumSize(QSize(340, 23));
        label_iad_configurationName->setTextInteractionFlags(Qt::NoTextInteraction);

        horizontalLayout_6->addWidget(label_iad_configurationName);

        horizontalSpacer_5 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_5);


        verticalLayout_6->addLayout(horizontalLayout_6);

        verticalSpacer_3 = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_6->addItem(verticalSpacer_3);

        label_iad_calibration = new QLabel(tab_2);
        label_iad_calibration->setObjectName(QStringLiteral("label_iad_calibration"));
        label_iad_calibration->setFont(font);
        label_iad_calibration->setMargin(0);

        verticalLayout_6->addWidget(label_iad_calibration);

        button_iad_calibrate = new QPushButton(tab_2);
        button_iad_calibrate->setObjectName(QStringLiteral("button_iad_calibrate"));
        button_iad_calibrate->setEnabled(false);
        sizePolicy3.setHeightForWidth(button_iad_calibrate->sizePolicy().hasHeightForWidth());
        button_iad_calibrate->setSizePolicy(sizePolicy3);

        verticalLayout_6->addWidget(button_iad_calibrate);

        verticalSpacer = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_6->addItem(verticalSpacer);

        label_iad_measurement = new QLabel(tab_2);
        label_iad_measurement->setObjectName(QStringLiteral("label_iad_measurement"));
        label_iad_measurement->setFont(font);

        verticalLayout_6->addWidget(label_iad_measurement);

        label_iad_name = new QLabel(tab_2);
        label_iad_name->setObjectName(QStringLiteral("label_iad_name"));

        verticalLayout_6->addWidget(label_iad_name);

        lineEdit_iad_name = new QLineEdit(tab_2);
        lineEdit_iad_name->setObjectName(QStringLiteral("lineEdit_iad_name"));
        lineEdit_iad_name->setEnabled(false);
        sizePolicy3.setHeightForWidth(lineEdit_iad_name->sizePolicy().hasHeightForWidth());
        lineEdit_iad_name->setSizePolicy(sizePolicy3);
        lineEdit_iad_name->setMinimumSize(QSize(540, 20));
        lineEdit_iad_name->setMaximumSize(QSize(16777215, 20));

        verticalLayout_6->addWidget(lineEdit_iad_name);

        label_iad_description = new QLabel(tab_2);
        label_iad_description->setObjectName(QStringLiteral("label_iad_description"));

        verticalLayout_6->addWidget(label_iad_description);

        plainTextEdit_iad_description = new QPlainTextEdit(tab_2);
        plainTextEdit_iad_description->setObjectName(QStringLiteral("plainTextEdit_iad_description"));
        plainTextEdit_iad_description->setEnabled(false);
        sizePolicy3.setHeightForWidth(plainTextEdit_iad_description->sizePolicy().hasHeightForWidth());
        plainTextEdit_iad_description->setSizePolicy(sizePolicy3);
        plainTextEdit_iad_description->setMinimumSize(QSize(540, 120));

        verticalLayout_6->addWidget(plainTextEdit_iad_description);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        button_iad_measure = new QPushButton(tab_2);
        button_iad_measure->setObjectName(QStringLiteral("button_iad_measure"));
        button_iad_measure->setEnabled(false);
        sizePolicy3.setHeightForWidth(button_iad_measure->sizePolicy().hasHeightForWidth());
        button_iad_measure->setSizePolicy(sizePolicy3);

        horizontalLayout_5->addWidget(button_iad_measure);

        checkBox_iad_liveView = new QCheckBox(tab_2);
        checkBox_iad_liveView->setObjectName(QStringLiteral("checkBox_iad_liveView"));
        checkBox_iad_liveView->setEnabled(false);
        QSizePolicy sizePolicy6(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy6.setHorizontalStretch(0);
        sizePolicy6.setVerticalStretch(0);
        sizePolicy6.setHeightForWidth(checkBox_iad_liveView->sizePolicy().hasHeightForWidth());
        checkBox_iad_liveView->setSizePolicy(sizePolicy6);

        horizontalLayout_5->addWidget(checkBox_iad_liveView);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_7);


        verticalLayout_6->addLayout(horizontalLayout_5);

        verticalSpacer_2 = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_6->addItem(verticalSpacer_2);

        label_iad_analysis = new QLabel(tab_2);
        label_iad_analysis->setObjectName(QStringLiteral("label_iad_analysis"));
        label_iad_analysis->setFont(font);

        verticalLayout_6->addWidget(label_iad_analysis);

        table_iad_measurements = new MeasurementsTable(tab_2);
        if (table_iad_measurements->columnCount() < 5)
            table_iad_measurements->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        table_iad_measurements->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        table_iad_measurements->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        table_iad_measurements->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        table_iad_measurements->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        table_iad_measurements->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        table_iad_measurements->setObjectName(QStringLiteral("table_iad_measurements"));
        sizePolicy2.setHeightForWidth(table_iad_measurements->sizePolicy().hasHeightForWidth());
        table_iad_measurements->setSizePolicy(sizePolicy2);
        table_iad_measurements->setMinimumSize(QSize(540, 320));
        table_iad_measurements->setMaximumSize(QSize(540, 16777215));
        table_iad_measurements->setFocusPolicy(Qt::NoFocus);
        table_iad_measurements->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        table_iad_measurements->setAutoScroll(false);
        table_iad_measurements->setEditTriggers(QAbstractItemView::NoEditTriggers);
        table_iad_measurements->setSelectionMode(QAbstractItemView::SingleSelection);
        table_iad_measurements->setSelectionBehavior(QAbstractItemView::SelectRows);
        table_iad_measurements->horizontalHeader()->setHighlightSections(false);
        table_iad_measurements->verticalHeader()->setVisible(false);
        table_iad_measurements->verticalHeader()->setHighlightSections(false);

        verticalLayout_6->addWidget(table_iad_measurements);


        horizontalLayout_4->addLayout(verticalLayout_6);

        horizontalSpacer_3 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_3);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        qwtPlot_reflection = new Plot(tab_2);
        qwtPlot_reflection->setObjectName(QStringLiteral("qwtPlot_reflection"));
        sizePolicy4.setHeightForWidth(qwtPlot_reflection->sizePolicy().hasHeightForWidth());
        qwtPlot_reflection->setSizePolicy(sizePolicy4);

        verticalLayout_5->addWidget(qwtPlot_reflection);

        qwtPlot_transmission = new Plot(tab_2);
        qwtPlot_transmission->setObjectName(QStringLiteral("qwtPlot_transmission"));
        sizePolicy4.setHeightForWidth(qwtPlot_transmission->sizePolicy().hasHeightForWidth());
        qwtPlot_transmission->setSizePolicy(sizePolicy4);

        verticalLayout_5->addWidget(qwtPlot_transmission);


        horizontalLayout_4->addLayout(verticalLayout_5);


        gridLayout_2->addLayout(horizontalLayout_4, 0, 0, 1, 1);

        tabWidget->addTab(tab_2, QString());

        verticalLayout->addWidget(tabWidget);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);


        retranslateUi(Panel);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(Panel);
    } // setupUi

    void retranslateUi(QDialog *Panel)
    {
        Panel->setWindowTitle(QApplication::translate("Panel", "Optical blood analysis toolkit", Q_NULLPTR));
        label->setText(QApplication::translate("Panel", "Spectrometers", Q_NULLPTR));
        label_2->setText(QApplication::translate("Panel", "Capture modes", Q_NULLPTR));
        pushButton_preview->setText(QApplication::translate("Panel", "Start preview", Q_NULLPTR));
        pushButton_storeToRam->setText(QApplication::translate("Panel", "Store to RAM", Q_NULLPTR));
        pushButton_timePattern->setText(QApplication::translate("Panel", "Time pattern", Q_NULLPTR));
        label_4->setText(QApplication::translate("Panel", "Display options", Q_NULLPTR));
        pushButton_legend->setText(QApplication::translate("Panel", "Legend", Q_NULLPTR));
        pushButton_exportData->setText(QApplication::translate("Panel", "Export data", Q_NULLPTR));
        pushButton_saveGraph->setText(QApplication::translate("Panel", "Save graph", Q_NULLPTR));
        pushButton_about->setText(QApplication::translate("Panel", "About", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("Panel", "Preview", Q_NULLPTR));
        label_iad_configuration->setText(QApplication::translate("Panel", "1. Configuration", Q_NULLPTR));
        button_iad_newConfiguration->setText(QApplication::translate("Panel", "New", Q_NULLPTR));
        button_iad_openConfiguration->setText(QApplication::translate("Panel", "Open", Q_NULLPTR));
        label_iad_configurationName->setText(QApplication::translate("Panel", "<configuration loaded>", Q_NULLPTR));
        label_iad_calibration->setText(QApplication::translate("Panel", "2. Calibration", Q_NULLPTR));
        button_iad_calibrate->setText(QApplication::translate("Panel", "Calibrate", Q_NULLPTR));
        label_iad_measurement->setText(QApplication::translate("Panel", "3. Measurement", Q_NULLPTR));
        label_iad_name->setText(QApplication::translate("Panel", "Name", Q_NULLPTR));
        label_iad_description->setText(QApplication::translate("Panel", "Description", Q_NULLPTR));
        button_iad_measure->setText(QApplication::translate("Panel", "Measure", Q_NULLPTR));
        checkBox_iad_liveView->setText(QApplication::translate("Panel", "Live view", Q_NULLPTR));
        label_iad_analysis->setText(QApplication::translate("Panel", "4. Analysis", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem = table_iad_measurements->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("Panel", "Name", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem1 = table_iad_measurements->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("Panel", "Date", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem2 = table_iad_measurements->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("Panel", "Time", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem3 = table_iad_measurements->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("Panel", "Status", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("Panel", "Inverse Adding-Doubling", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Panel: public Ui_Panel {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PANEL_H
