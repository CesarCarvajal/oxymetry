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
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
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
    QWidget *tab_3;
    QGridLayout *gridLayout_4;
    QHBoxLayout *horizontalLayout_7;
    QVBoxLayout *verticalLayout_8;
    QSpacerItem *verticalSpacer_11;
    QLabel *label_5_Pol_settings;
    QHBoxLayout *horizontalLayout_9;
    QPushButton *button_Pol_Syringe;
    QPushButton *button_Conf_Setup_Pol;
    QSpacerItem *verticalSpacer_8;
    QLabel *label_Save_Pol;
    QHBoxLayout *horizontalLayout_12;
    QSpacerItem *horizontalSpacer_17;
    QCheckBox *checkBox_AutoSave_Pol;
    QCheckBox *checkBox_AutoSave_Pol_Raw;
    QSpacerItem *verticalSpacer_12;
    QLabel *label_Set_Spec_Pol;
    QListWidget *list_devices_Pol;
    QSpacerItem *verticalSpacer_9;
    QLabel *label_Measurements_Pol;
    QTableWidget *Table_Measurements_Pol;
    QLabel *label_3;
    QProgressBar *currentProgressBar_Pol;
    QLabel *label_5;
    QProgressBar *TotalProgressBar_Pol;
    QSpacerItem *verticalSpacer_10;
    QPushButton *button_Start_Meas_Pol;
    QSpacerItem *verticalSpacer_7;
    QSpacerItem *horizontalSpacer_2;
    QVBoxLayout *verticalLayout_7;
    QHBoxLayout *horizontalLayout_13;
    QSpacerItem *horizontalSpacer_10;
    QVBoxLayout *verticalLayout_10;
    QLabel *label_6;
    Plot *qwtPlot_Pol;
    QSpacerItem *horizontalSpacer_12;
    QVBoxLayout *verticalLayout_11;
    QLabel *label_7;
    Plot *qwtPlot_Pol_Compensation;
    QSpacerItem *horizontalSpacer_11;
    QVBoxLayout *verticalLayout_12;
    QLabel *FFT_label_Pol;
    Plot *qwtPlot_Pol_Prediction;
    QSpacerItem *horizontalSpacer_18;
    QHBoxLayout *horizontalLayout_10;
    QSpacerItem *horizontalSpacer_19;
    QVBoxLayout *verticalLayout_13;
    QLabel *label_9;
    Plot *qwtPlot_Pol_w_2w;
    QSpacerItem *verticalSpacer_13;
    QSpacerItem *horizontalSpacer_13;
    QVBoxLayout *verticalLayout_14;
    QLabel *label_10;
    Plot *qwtPlot_Pol_Average;
    QSpacerItem *verticalSpacer_14;
    QSpacerItem *horizontalSpacer_20;
    QHBoxLayout *horizontalLayout_15;
    QPushButton *Button_Save_Graphs_Pol;
    QPushButton *button_Load_FFTData;
    QPushButton *button_AnalyzeRawPolData;

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
        tab_3 = new QWidget();
        tab_3->setObjectName(QStringLiteral("tab_3"));
        gridLayout_4 = new QGridLayout(tab_3);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        verticalLayout_8 = new QVBoxLayout();
        verticalLayout_8->setSpacing(6);
        verticalLayout_8->setObjectName(QStringLiteral("verticalLayout_8"));
        verticalSpacer_11 = new QSpacerItem(5, 5, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_8->addItem(verticalSpacer_11);

        label_5_Pol_settings = new QLabel(tab_3);
        label_5_Pol_settings->setObjectName(QStringLiteral("label_5_Pol_settings"));
        label_5_Pol_settings->setFont(font);

        verticalLayout_8->addWidget(label_5_Pol_settings);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        button_Pol_Syringe = new QPushButton(tab_3);
        button_Pol_Syringe->setObjectName(QStringLiteral("button_Pol_Syringe"));
        button_Pol_Syringe->setMinimumSize(QSize(110, 28));
        button_Pol_Syringe->setMaximumSize(QSize(110, 28));

        horizontalLayout_9->addWidget(button_Pol_Syringe);

        button_Conf_Setup_Pol = new QPushButton(tab_3);
        button_Conf_Setup_Pol->setObjectName(QStringLiteral("button_Conf_Setup_Pol"));
        button_Conf_Setup_Pol->setMinimumSize(QSize(110, 28));
        button_Conf_Setup_Pol->setMaximumSize(QSize(110, 28));

        horizontalLayout_9->addWidget(button_Conf_Setup_Pol);


        verticalLayout_8->addLayout(horizontalLayout_9);

        verticalSpacer_8 = new QSpacerItem(10, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_8->addItem(verticalSpacer_8);

        label_Save_Pol = new QLabel(tab_3);
        label_Save_Pol->setObjectName(QStringLiteral("label_Save_Pol"));
        label_Save_Pol->setFont(font);

        verticalLayout_8->addWidget(label_Save_Pol);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setSpacing(6);
        horizontalLayout_12->setObjectName(QStringLiteral("horizontalLayout_12"));
        horizontalSpacer_17 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_12->addItem(horizontalSpacer_17);

        checkBox_AutoSave_Pol = new QCheckBox(tab_3);
        checkBox_AutoSave_Pol->setObjectName(QStringLiteral("checkBox_AutoSave_Pol"));
        checkBox_AutoSave_Pol->setMinimumSize(QSize(110, 28));
        checkBox_AutoSave_Pol->setMaximumSize(QSize(110, 28));
        checkBox_AutoSave_Pol->setIconSize(QSize(16, 16));

        horizontalLayout_12->addWidget(checkBox_AutoSave_Pol);

        checkBox_AutoSave_Pol_Raw = new QCheckBox(tab_3);
        checkBox_AutoSave_Pol_Raw->setObjectName(QStringLiteral("checkBox_AutoSave_Pol_Raw"));
        checkBox_AutoSave_Pol_Raw->setMinimumSize(QSize(110, 28));
        checkBox_AutoSave_Pol_Raw->setMaximumSize(QSize(110, 28));
        checkBox_AutoSave_Pol_Raw->setChecked(true);

        horizontalLayout_12->addWidget(checkBox_AutoSave_Pol_Raw);


        verticalLayout_8->addLayout(horizontalLayout_12);

        verticalSpacer_12 = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Minimum);

        verticalLayout_8->addItem(verticalSpacer_12);

        label_Set_Spec_Pol = new QLabel(tab_3);
        label_Set_Spec_Pol->setObjectName(QStringLiteral("label_Set_Spec_Pol"));
        label_Set_Spec_Pol->setFont(font);

        verticalLayout_8->addWidget(label_Set_Spec_Pol);

        list_devices_Pol = new QListWidget(tab_3);
        list_devices_Pol->setObjectName(QStringLiteral("list_devices_Pol"));
        list_devices_Pol->setMinimumSize(QSize(290, 100));
        list_devices_Pol->setMaximumSize(QSize(280, 150));
        list_devices_Pol->setAutoScroll(false);

        verticalLayout_8->addWidget(list_devices_Pol);

        verticalSpacer_9 = new QSpacerItem(15, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_8->addItem(verticalSpacer_9);

        label_Measurements_Pol = new QLabel(tab_3);
        label_Measurements_Pol->setObjectName(QStringLiteral("label_Measurements_Pol"));
        label_Measurements_Pol->setFont(font);

        verticalLayout_8->addWidget(label_Measurements_Pol);

        Table_Measurements_Pol = new QTableWidget(tab_3);
        if (Table_Measurements_Pol->columnCount() < 3)
            Table_Measurements_Pol->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        Table_Measurements_Pol->setHorizontalHeaderItem(0, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        Table_Measurements_Pol->setHorizontalHeaderItem(1, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        Table_Measurements_Pol->setHorizontalHeaderItem(2, __qtablewidgetitem7);
        Table_Measurements_Pol->setObjectName(QStringLiteral("Table_Measurements_Pol"));
        Table_Measurements_Pol->setMinimumSize(QSize(290, 250));
        Table_Measurements_Pol->setMaximumSize(QSize(280, 16777215));
        Table_Measurements_Pol->setAutoScroll(true);
        Table_Measurements_Pol->setAutoScrollMargin(18);
        Table_Measurements_Pol->setTextElideMode(Qt::ElideLeft);
        Table_Measurements_Pol->setRowCount(0);
        Table_Measurements_Pol->setColumnCount(3);
        Table_Measurements_Pol->horizontalHeader()->setCascadingSectionResizes(false);
        Table_Measurements_Pol->horizontalHeader()->setDefaultSectionSize(54);
        Table_Measurements_Pol->horizontalHeader()->setProperty("showSortIndicator", QVariant(false));
        Table_Measurements_Pol->horizontalHeader()->setStretchLastSection(true);
        Table_Measurements_Pol->verticalHeader()->setCascadingSectionResizes(false);
        Table_Measurements_Pol->verticalHeader()->setHighlightSections(true);
        Table_Measurements_Pol->verticalHeader()->setMinimumSectionSize(39);
        Table_Measurements_Pol->verticalHeader()->setProperty("showSortIndicator", QVariant(false));
        Table_Measurements_Pol->verticalHeader()->setStretchLastSection(false);

        verticalLayout_8->addWidget(Table_Measurements_Pol);

        label_3 = new QLabel(tab_3);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setFont(font);

        verticalLayout_8->addWidget(label_3);

        currentProgressBar_Pol = new QProgressBar(tab_3);
        currentProgressBar_Pol->setObjectName(QStringLiteral("currentProgressBar_Pol"));
        currentProgressBar_Pol->setMaximumSize(QSize(16777215, 15));
        currentProgressBar_Pol->setValue(0);
        currentProgressBar_Pol->setTextVisible(true);
        currentProgressBar_Pol->setOrientation(Qt::Horizontal);
        currentProgressBar_Pol->setInvertedAppearance(false);

        verticalLayout_8->addWidget(currentProgressBar_Pol);

        label_5 = new QLabel(tab_3);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setFont(font);

        verticalLayout_8->addWidget(label_5);

        TotalProgressBar_Pol = new QProgressBar(tab_3);
        TotalProgressBar_Pol->setObjectName(QStringLiteral("TotalProgressBar_Pol"));
        TotalProgressBar_Pol->setMaximumSize(QSize(16777215, 15));
        TotalProgressBar_Pol->setValue(0);

        verticalLayout_8->addWidget(TotalProgressBar_Pol);

        verticalSpacer_10 = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_8->addItem(verticalSpacer_10);

        button_Start_Meas_Pol = new QPushButton(tab_3);
        button_Start_Meas_Pol->setObjectName(QStringLiteral("button_Start_Meas_Pol"));
        button_Start_Meas_Pol->setMinimumSize(QSize(290, 55));
        button_Start_Meas_Pol->setMaximumSize(QSize(120, 55));
        button_Start_Meas_Pol->setFont(font);
        button_Start_Meas_Pol->setIconSize(QSize(16, 16));

        verticalLayout_8->addWidget(button_Start_Meas_Pol);

        verticalSpacer_7 = new QSpacerItem(5, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_8->addItem(verticalSpacer_7);


        horizontalLayout_7->addLayout(verticalLayout_8);

        horizontalSpacer_2 = new QSpacerItem(5, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_2);

        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setSpacing(6);
        horizontalLayout_13->setObjectName(QStringLiteral("horizontalLayout_13"));
        horizontalSpacer_10 = new QSpacerItem(5, 10, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_13->addItem(horizontalSpacer_10);

        verticalLayout_10 = new QVBoxLayout();
        verticalLayout_10->setSpacing(6);
        verticalLayout_10->setObjectName(QStringLiteral("verticalLayout_10"));
        label_6 = new QLabel(tab_3);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setFont(font);
        label_6->setAlignment(Qt::AlignCenter);

        verticalLayout_10->addWidget(label_6);

        qwtPlot_Pol = new Plot(tab_3);
        qwtPlot_Pol->setObjectName(QStringLiteral("qwtPlot_Pol"));
        qwtPlot_Pol->setMinimumSize(QSize(265, 300));
        qwtPlot_Pol->setFrameShape(QFrame::StyledPanel);
        qwtPlot_Pol->setFrameShadow(QFrame::Raised);

        verticalLayout_10->addWidget(qwtPlot_Pol);


        horizontalLayout_13->addLayout(verticalLayout_10);

        horizontalSpacer_12 = new QSpacerItem(5, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_13->addItem(horizontalSpacer_12);

        verticalLayout_11 = new QVBoxLayout();
        verticalLayout_11->setSpacing(6);
        verticalLayout_11->setObjectName(QStringLiteral("verticalLayout_11"));
        label_7 = new QLabel(tab_3);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setFont(font);
        label_7->setAlignment(Qt::AlignCenter);

        verticalLayout_11->addWidget(label_7);

        qwtPlot_Pol_Compensation = new Plot(tab_3);
        qwtPlot_Pol_Compensation->setObjectName(QStringLiteral("qwtPlot_Pol_Compensation"));
        qwtPlot_Pol_Compensation->setMinimumSize(QSize(265, 300));
        qwtPlot_Pol_Compensation->setMaximumSize(QSize(16777215, 16777215));
        qwtPlot_Pol_Compensation->setFrameShape(QFrame::StyledPanel);
        qwtPlot_Pol_Compensation->setFrameShadow(QFrame::Raised);

        verticalLayout_11->addWidget(qwtPlot_Pol_Compensation);


        horizontalLayout_13->addLayout(verticalLayout_11);

        horizontalSpacer_11 = new QSpacerItem(5, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_13->addItem(horizontalSpacer_11);

        verticalLayout_12 = new QVBoxLayout();
        verticalLayout_12->setSpacing(6);
        verticalLayout_12->setObjectName(QStringLiteral("verticalLayout_12"));
        FFT_label_Pol = new QLabel(tab_3);
        FFT_label_Pol->setObjectName(QStringLiteral("FFT_label_Pol"));
        FFT_label_Pol->setFont(font);
        FFT_label_Pol->setAlignment(Qt::AlignCenter);

        verticalLayout_12->addWidget(FFT_label_Pol);

        qwtPlot_Pol_Prediction = new Plot(tab_3);
        qwtPlot_Pol_Prediction->setObjectName(QStringLiteral("qwtPlot_Pol_Prediction"));
        qwtPlot_Pol_Prediction->setMinimumSize(QSize(265, 300));
        qwtPlot_Pol_Prediction->setMaximumSize(QSize(16777215, 16777215));
        qwtPlot_Pol_Prediction->setFrameShape(QFrame::StyledPanel);
        qwtPlot_Pol_Prediction->setFrameShadow(QFrame::Raised);

        verticalLayout_12->addWidget(qwtPlot_Pol_Prediction);


        horizontalLayout_13->addLayout(verticalLayout_12);

        horizontalSpacer_18 = new QSpacerItem(5, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_13->addItem(horizontalSpacer_18);


        verticalLayout_7->addLayout(horizontalLayout_13);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setSpacing(6);
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        horizontalSpacer_19 = new QSpacerItem(10, 10, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_10->addItem(horizontalSpacer_19);

        verticalLayout_13 = new QVBoxLayout();
        verticalLayout_13->setSpacing(6);
        verticalLayout_13->setObjectName(QStringLiteral("verticalLayout_13"));
        label_9 = new QLabel(tab_3);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setFont(font);
        label_9->setAlignment(Qt::AlignCenter);

        verticalLayout_13->addWidget(label_9);

        qwtPlot_Pol_w_2w = new Plot(tab_3);
        qwtPlot_Pol_w_2w->setObjectName(QStringLiteral("qwtPlot_Pol_w_2w"));
        qwtPlot_Pol_w_2w->setMinimumSize(QSize(380, 335));
        qwtPlot_Pol_w_2w->setFrameShape(QFrame::StyledPanel);
        qwtPlot_Pol_w_2w->setFrameShadow(QFrame::Raised);

        verticalLayout_13->addWidget(qwtPlot_Pol_w_2w);

        verticalSpacer_13 = new QSpacerItem(20, 5, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_13->addItem(verticalSpacer_13);


        horizontalLayout_10->addLayout(verticalLayout_13);

        horizontalSpacer_13 = new QSpacerItem(5, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_10->addItem(horizontalSpacer_13);

        verticalLayout_14 = new QVBoxLayout();
        verticalLayout_14->setSpacing(6);
        verticalLayout_14->setObjectName(QStringLiteral("verticalLayout_14"));
        label_10 = new QLabel(tab_3);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setFont(font);
        label_10->setAlignment(Qt::AlignCenter);

        verticalLayout_14->addWidget(label_10);

        qwtPlot_Pol_Average = new Plot(tab_3);
        qwtPlot_Pol_Average->setObjectName(QStringLiteral("qwtPlot_Pol_Average"));
        qwtPlot_Pol_Average->setMinimumSize(QSize(380, 335));
        qwtPlot_Pol_Average->setMaximumSize(QSize(16777215, 16777215));
        qwtPlot_Pol_Average->setFrameShape(QFrame::StyledPanel);
        qwtPlot_Pol_Average->setFrameShadow(QFrame::Raised);

        verticalLayout_14->addWidget(qwtPlot_Pol_Average);

        verticalSpacer_14 = new QSpacerItem(20, 5, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_14->addItem(verticalSpacer_14);


        horizontalLayout_10->addLayout(verticalLayout_14);

        horizontalSpacer_20 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_10->addItem(horizontalSpacer_20);


        verticalLayout_7->addLayout(horizontalLayout_10);

        horizontalLayout_15 = new QHBoxLayout();
        horizontalLayout_15->setSpacing(6);
        horizontalLayout_15->setObjectName(QStringLiteral("horizontalLayout_15"));
        Button_Save_Graphs_Pol = new QPushButton(tab_3);
        Button_Save_Graphs_Pol->setObjectName(QStringLiteral("Button_Save_Graphs_Pol"));
        Button_Save_Graphs_Pol->setMinimumSize(QSize(120, 28));
        Button_Save_Graphs_Pol->setMaximumSize(QSize(100, 16777215));

        horizontalLayout_15->addWidget(Button_Save_Graphs_Pol);

        button_Load_FFTData = new QPushButton(tab_3);
        button_Load_FFTData->setObjectName(QStringLiteral("button_Load_FFTData"));
        button_Load_FFTData->setMinimumSize(QSize(120, 28));
        button_Load_FFTData->setMaximumSize(QSize(100, 28));

        horizontalLayout_15->addWidget(button_Load_FFTData);

        button_AnalyzeRawPolData = new QPushButton(tab_3);
        button_AnalyzeRawPolData->setObjectName(QStringLiteral("button_AnalyzeRawPolData"));
        button_AnalyzeRawPolData->setMinimumSize(QSize(120, 28));
        button_AnalyzeRawPolData->setMaximumSize(QSize(120, 28));

        horizontalLayout_15->addWidget(button_AnalyzeRawPolData);


        verticalLayout_7->addLayout(horizontalLayout_15);


        horizontalLayout_7->addLayout(verticalLayout_7);


        gridLayout_4->addLayout(horizontalLayout_7, 0, 0, 1, 1);

        tabWidget->addTab(tab_3, QString());

        verticalLayout->addWidget(tabWidget);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);


        retranslateUi(Panel);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(Panel);
    } // setupUi

    void retranslateUi(QDialog *Panel)
    {
        Panel->setWindowTitle(QApplication::translate("Panel", "Oxymetry in non-hemolyzed human whole blood", Q_NULLPTR));
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
        label_5_Pol_settings->setText(QApplication::translate("Panel", "Configuration", Q_NULLPTR));
        button_Pol_Syringe->setText(QApplication::translate("Panel", "Measurement", Q_NULLPTR));
        button_Conf_Setup_Pol->setText(QApplication::translate("Panel", "F-Rotator", Q_NULLPTR));
        label_Save_Pol->setText(QApplication::translate("Panel", "Save Options", Q_NULLPTR));
        checkBox_AutoSave_Pol->setText(QApplication::translate("Panel", "FFT Profiles", Q_NULLPTR));
        checkBox_AutoSave_Pol_Raw->setText(QApplication::translate("Panel", "Raw Data", Q_NULLPTR));
        label_Set_Spec_Pol->setText(QApplication::translate("Panel", "Spectrometer:", Q_NULLPTR));
        label_Measurements_Pol->setText(QApplication::translate("Panel", "Measurement Progress:", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem4 = Table_Measurements_Pol->horizontalHeaderItem(0);
        ___qtablewidgetitem4->setText(QApplication::translate("Panel", "No.", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem5 = Table_Measurements_Pol->horizontalHeaderItem(1);
        ___qtablewidgetitem5->setText(QApplication::translate("Panel", "Time", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem6 = Table_Measurements_Pol->horizontalHeaderItem(2);
        ___qtablewidgetitem6->setText(QApplication::translate("Panel", "File Name", Q_NULLPTR));
        label_3->setText(QApplication::translate("Panel", "Current Measurement:", Q_NULLPTR));
        label_5->setText(QApplication::translate("Panel", "Total measurement:", Q_NULLPTR));
        button_Start_Meas_Pol->setText(QApplication::translate("Panel", "Start Measurement", Q_NULLPTR));
        label_6->setText(QApplication::translate("Panel", "Raw Signal", Q_NULLPTR));
        label_7->setText(QApplication::translate("Panel", "Compensation Signal W/2W", Q_NULLPTR));
        FFT_label_Pol->setText(QApplication::translate("Panel", "FFT", Q_NULLPTR));
        label_9->setText(QApplication::translate("Panel", "FFT Amplitudes For All Wavelengths", Q_NULLPTR));
        label_10->setText(QApplication::translate("Panel", "Average Signal", Q_NULLPTR));
        Button_Save_Graphs_Pol->setText(QApplication::translate("Panel", "Save Graphs as PDF", Q_NULLPTR));
        button_Load_FFTData->setText(QApplication::translate("Panel", "Load FFT Data", Q_NULLPTR));
        button_AnalyzeRawPolData->setText(QApplication::translate("Panel", "Analyze Raw Data", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("Panel", "Polarimeter", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Panel: public Ui_Panel {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PANEL_H
