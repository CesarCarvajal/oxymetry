/********************************************************************************
** Form generated from reading UI file 'panel_polarimeter.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PANEL_POLARIMETER_H
#define UI_PANEL_POLARIMETER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "clickablelabel.h"
#include "plot.h"

QT_BEGIN_NAMESPACE

class Ui_PanelPolarimeter
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizonalLayout_2;
    QVBoxLayout *verticalLayout_8;
    QSpacerItem *verticalSpacer_11;
    QLabel *label_Set_Spec_Pol;
    QSpacerItem *verticalSpacer_2;
    QListWidget *list_devices_Pol;
    QSpacerItem *verticalSpacer_9;
    QLabel *label_3;
    QProgressBar *currentProgressBar_Pol;
    QLabel *label_5;
    QProgressBar *TotalProgressBar_Pol;
    QSpacerItem *verticalSpacer_12;
    QLabel *label_Measurements_Pol;
    QSpacerItem *verticalSpacer_3;
    QTableWidget *Table_Measurements_Pol;
    QSpacerItem *verticalSpacer;
    QLabel *label_Save_Pol;
    QSpacerItem *verticalSpacer_5;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_17;
    QCheckBox *checkBox_AutoSave_Pol_Raw;
    QCheckBox *checkBox_AutoSave_Pol;
    QSpacerItem *verticalSpacer_10;
    QLabel *label_5_Pol_settings;
    QSpacerItem *verticalSpacer_4;
    QHBoxLayout *horizontalLayout_9;
    QPushButton *button_Pol_ConfigureMeasurement;
    QPushButton *button_Conf_Setup_Pol;
    QSpacerItem *verticalSpacer_8;
    QPushButton *button_Start_Meas_Pol;
    QSpacerItem *verticalSpacer_7;
    QSpacerItem *horizontalSpacer_2;
    QFrame *line_2;
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
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_3;
    QLabel *FFT_label_Pol;
    ClickableLabel *waveToPlotFFT;
    QLabel *label;
    QSpacerItem *horizontalSpacer;
    Plot *qwtPlot_Pol_Prediction;
    QSpacerItem *horizontalSpacer_18;
    QFrame *line;
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

    void setupUi(QWidget *PanelPolarimeter)
    {
        if (PanelPolarimeter->objectName().isEmpty())
            PanelPolarimeter->setObjectName(QStringLiteral("PanelPolarimeter"));
        PanelPolarimeter->resize(1190, 765);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(PanelPolarimeter->sizePolicy().hasHeightForWidth());
        PanelPolarimeter->setSizePolicy(sizePolicy);
        PanelPolarimeter->setMinimumSize(QSize(0, 0));
        gridLayout = new QGridLayout(PanelPolarimeter);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizonalLayout_2 = new QHBoxLayout();
        horizonalLayout_2->setObjectName(QStringLiteral("horizonalLayout_2"));
        verticalLayout_8 = new QVBoxLayout();
        verticalLayout_8->setObjectName(QStringLiteral("verticalLayout_8"));
        verticalSpacer_11 = new QSpacerItem(5, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_8->addItem(verticalSpacer_11);

        label_Set_Spec_Pol = new QLabel(PanelPolarimeter);
        label_Set_Spec_Pol->setObjectName(QStringLiteral("label_Set_Spec_Pol"));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        label_Set_Spec_Pol->setFont(font);

        verticalLayout_8->addWidget(label_Set_Spec_Pol);

        verticalSpacer_2 = new QSpacerItem(20, 5, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_8->addItem(verticalSpacer_2);

        list_devices_Pol = new QListWidget(PanelPolarimeter);
        list_devices_Pol->setObjectName(QStringLiteral("list_devices_Pol"));
        list_devices_Pol->setMinimumSize(QSize(290, 100));
        list_devices_Pol->setMaximumSize(QSize(280, 120));
        list_devices_Pol->setAutoScroll(false);

        verticalLayout_8->addWidget(list_devices_Pol);

        verticalSpacer_9 = new QSpacerItem(15, 15, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_8->addItem(verticalSpacer_9);

        label_3 = new QLabel(PanelPolarimeter);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setFont(font);

        verticalLayout_8->addWidget(label_3);

        currentProgressBar_Pol = new QProgressBar(PanelPolarimeter);
        currentProgressBar_Pol->setObjectName(QStringLiteral("currentProgressBar_Pol"));
        currentProgressBar_Pol->setMaximumSize(QSize(16777215, 15));
        currentProgressBar_Pol->setValue(0);
        currentProgressBar_Pol->setTextVisible(true);
        currentProgressBar_Pol->setOrientation(Qt::Horizontal);
        currentProgressBar_Pol->setInvertedAppearance(false);

        verticalLayout_8->addWidget(currentProgressBar_Pol);

        label_5 = new QLabel(PanelPolarimeter);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setFont(font);

        verticalLayout_8->addWidget(label_5);

        TotalProgressBar_Pol = new QProgressBar(PanelPolarimeter);
        TotalProgressBar_Pol->setObjectName(QStringLiteral("TotalProgressBar_Pol"));
        TotalProgressBar_Pol->setMaximumSize(QSize(16777215, 15));
        TotalProgressBar_Pol->setValue(0);

        verticalLayout_8->addWidget(TotalProgressBar_Pol);

        verticalSpacer_12 = new QSpacerItem(20, 15, QSizePolicy::Minimum, QSizePolicy::Minimum);

        verticalLayout_8->addItem(verticalSpacer_12);

        label_Measurements_Pol = new QLabel(PanelPolarimeter);
        label_Measurements_Pol->setObjectName(QStringLiteral("label_Measurements_Pol"));
        label_Measurements_Pol->setFont(font);

        verticalLayout_8->addWidget(label_Measurements_Pol);

        verticalSpacer_3 = new QSpacerItem(20, 5, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_8->addItem(verticalSpacer_3);

        Table_Measurements_Pol = new QTableWidget(PanelPolarimeter);
        if (Table_Measurements_Pol->columnCount() < 3)
            Table_Measurements_Pol->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        Table_Measurements_Pol->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        Table_Measurements_Pol->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        Table_Measurements_Pol->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        Table_Measurements_Pol->setObjectName(QStringLiteral("Table_Measurements_Pol"));
        Table_Measurements_Pol->setMinimumSize(QSize(290, 150));
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

        verticalSpacer = new QSpacerItem(20, 15, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_8->addItem(verticalSpacer);

        label_Save_Pol = new QLabel(PanelPolarimeter);
        label_Save_Pol->setObjectName(QStringLiteral("label_Save_Pol"));
        label_Save_Pol->setFont(font);

        verticalLayout_8->addWidget(label_Save_Pol);

        verticalSpacer_5 = new QSpacerItem(20, 5, QSizePolicy::Minimum, QSizePolicy::Minimum);

        verticalLayout_8->addItem(verticalSpacer_5);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer_17 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_17);

        checkBox_AutoSave_Pol_Raw = new QCheckBox(PanelPolarimeter);
        checkBox_AutoSave_Pol_Raw->setObjectName(QStringLiteral("checkBox_AutoSave_Pol_Raw"));
        checkBox_AutoSave_Pol_Raw->setMinimumSize(QSize(110, 28));
        checkBox_AutoSave_Pol_Raw->setMaximumSize(QSize(110, 28));
        checkBox_AutoSave_Pol_Raw->setChecked(true);

        horizontalLayout->addWidget(checkBox_AutoSave_Pol_Raw);

        checkBox_AutoSave_Pol = new QCheckBox(PanelPolarimeter);
        checkBox_AutoSave_Pol->setObjectName(QStringLiteral("checkBox_AutoSave_Pol"));
        checkBox_AutoSave_Pol->setMinimumSize(QSize(110, 28));
        checkBox_AutoSave_Pol->setMaximumSize(QSize(110, 28));
        checkBox_AutoSave_Pol->setIconSize(QSize(16, 16));

        horizontalLayout->addWidget(checkBox_AutoSave_Pol);


        verticalLayout_8->addLayout(horizontalLayout);

        verticalSpacer_10 = new QSpacerItem(20, 15, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_8->addItem(verticalSpacer_10);

        label_5_Pol_settings = new QLabel(PanelPolarimeter);
        label_5_Pol_settings->setObjectName(QStringLiteral("label_5_Pol_settings"));
        label_5_Pol_settings->setFont(font);

        verticalLayout_8->addWidget(label_5_Pol_settings);

        verticalSpacer_4 = new QSpacerItem(20, 5, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_8->addItem(verticalSpacer_4);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        button_Pol_ConfigureMeasurement = new QPushButton(PanelPolarimeter);
        button_Pol_ConfigureMeasurement->setObjectName(QStringLiteral("button_Pol_ConfigureMeasurement"));
        button_Pol_ConfigureMeasurement->setMinimumSize(QSize(110, 28));
        button_Pol_ConfigureMeasurement->setMaximumSize(QSize(110, 28));

        horizontalLayout_9->addWidget(button_Pol_ConfigureMeasurement);

        button_Conf_Setup_Pol = new QPushButton(PanelPolarimeter);
        button_Conf_Setup_Pol->setObjectName(QStringLiteral("button_Conf_Setup_Pol"));
        button_Conf_Setup_Pol->setMinimumSize(QSize(110, 28));
        button_Conf_Setup_Pol->setMaximumSize(QSize(110, 28));

        horizontalLayout_9->addWidget(button_Conf_Setup_Pol);


        verticalLayout_8->addLayout(horizontalLayout_9);

        verticalSpacer_8 = new QSpacerItem(10, 15, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_8->addItem(verticalSpacer_8);

        button_Start_Meas_Pol = new QPushButton(PanelPolarimeter);
        button_Start_Meas_Pol->setObjectName(QStringLiteral("button_Start_Meas_Pol"));
        button_Start_Meas_Pol->setMinimumSize(QSize(290, 55));
        button_Start_Meas_Pol->setMaximumSize(QSize(120, 55));
        button_Start_Meas_Pol->setFont(font);
        button_Start_Meas_Pol->setIconSize(QSize(16, 16));

        verticalLayout_8->addWidget(button_Start_Meas_Pol);

        verticalSpacer_7 = new QSpacerItem(5, 8, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_8->addItem(verticalSpacer_7);


        horizonalLayout_2->addLayout(verticalLayout_8);

        horizontalSpacer_2 = new QSpacerItem(5, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizonalLayout_2->addItem(horizontalSpacer_2);

        line_2 = new QFrame(PanelPolarimeter);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setFrameShape(QFrame::VLine);
        line_2->setFrameShadow(QFrame::Sunken);

        horizonalLayout_2->addWidget(line_2);

        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setObjectName(QStringLiteral("horizontalLayout_13"));
        horizontalSpacer_10 = new QSpacerItem(5, 10, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_13->addItem(horizontalSpacer_10);

        verticalLayout_10 = new QVBoxLayout();
        verticalLayout_10->setObjectName(QStringLiteral("verticalLayout_10"));
        label_6 = new QLabel(PanelPolarimeter);
        label_6->setObjectName(QStringLiteral("label_6"));
        QFont font1;
        font1.setPointSize(10);
        font1.setBold(true);
        font1.setWeight(75);
        label_6->setFont(font1);
        label_6->setAlignment(Qt::AlignCenter);

        verticalLayout_10->addWidget(label_6);

        qwtPlot_Pol = new Plot(PanelPolarimeter);
        qwtPlot_Pol->setObjectName(QStringLiteral("qwtPlot_Pol"));
        qwtPlot_Pol->setMinimumSize(QSize(265, 300));
        qwtPlot_Pol->setFrameShape(QFrame::StyledPanel);
        qwtPlot_Pol->setFrameShadow(QFrame::Raised);

        verticalLayout_10->addWidget(qwtPlot_Pol);


        horizontalLayout_13->addLayout(verticalLayout_10);

        horizontalSpacer_12 = new QSpacerItem(5, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_13->addItem(horizontalSpacer_12);

        verticalLayout_11 = new QVBoxLayout();
        verticalLayout_11->setObjectName(QStringLiteral("verticalLayout_11"));
        label_7 = new QLabel(PanelPolarimeter);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setFont(font1);
        label_7->setAlignment(Qt::AlignCenter);

        verticalLayout_11->addWidget(label_7);

        qwtPlot_Pol_Compensation = new Plot(PanelPolarimeter);
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
        verticalLayout_12->setObjectName(QStringLiteral("verticalLayout_12"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSpacer_3 = new QSpacerItem(50, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);

        FFT_label_Pol = new QLabel(PanelPolarimeter);
        FFT_label_Pol->setObjectName(QStringLiteral("FFT_label_Pol"));
        FFT_label_Pol->setMinimumSize(QSize(50, 0));
        FFT_label_Pol->setMaximumSize(QSize(50, 100));
        FFT_label_Pol->setFont(font1);
        FFT_label_Pol->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(FFT_label_Pol);

        waveToPlotFFT = new ClickableLabel(PanelPolarimeter);
        waveToPlotFFT->setObjectName(QStringLiteral("waveToPlotFFT"));
        waveToPlotFFT->setMinimumSize(QSize(50, 0));
        waveToPlotFFT->setMaximumSize(QSize(50, 100));
        QFont font2;
        font2.setPointSize(10);
        font2.setUnderline(true);
        waveToPlotFFT->setFont(font2);
        waveToPlotFFT->setCursor(QCursor(Qt::PointingHandCursor));

        horizontalLayout_2->addWidget(waveToPlotFFT);

        label = new QLabel(PanelPolarimeter);
        label->setObjectName(QStringLiteral("label"));
        label->setMinimumSize(QSize(20, 0));
        label->setMaximumSize(QSize(20, 16777215));
        label->setFont(font1);

        horizontalLayout_2->addWidget(label);

        horizontalSpacer = new QSpacerItem(70, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);


        verticalLayout_12->addLayout(horizontalLayout_2);

        qwtPlot_Pol_Prediction = new Plot(PanelPolarimeter);
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

        line = new QFrame(PanelPolarimeter);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout_7->addWidget(line);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        horizontalSpacer_19 = new QSpacerItem(10, 10, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_10->addItem(horizontalSpacer_19);

        verticalLayout_13 = new QVBoxLayout();
        verticalLayout_13->setObjectName(QStringLiteral("verticalLayout_13"));
        label_9 = new QLabel(PanelPolarimeter);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setFont(font1);
        label_9->setAlignment(Qt::AlignCenter);

        verticalLayout_13->addWidget(label_9);

        qwtPlot_Pol_w_2w = new Plot(PanelPolarimeter);
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
        verticalLayout_14->setObjectName(QStringLiteral("verticalLayout_14"));
        label_10 = new QLabel(PanelPolarimeter);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setFont(font1);
        label_10->setAlignment(Qt::AlignCenter);

        verticalLayout_14->addWidget(label_10);

        qwtPlot_Pol_Average = new Plot(PanelPolarimeter);
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
        horizontalLayout_15->setObjectName(QStringLiteral("horizontalLayout_15"));
        Button_Save_Graphs_Pol = new QPushButton(PanelPolarimeter);
        Button_Save_Graphs_Pol->setObjectName(QStringLiteral("Button_Save_Graphs_Pol"));
        Button_Save_Graphs_Pol->setMinimumSize(QSize(120, 28));
        Button_Save_Graphs_Pol->setMaximumSize(QSize(100, 16777215));

        horizontalLayout_15->addWidget(Button_Save_Graphs_Pol);

        button_Load_FFTData = new QPushButton(PanelPolarimeter);
        button_Load_FFTData->setObjectName(QStringLiteral("button_Load_FFTData"));
        button_Load_FFTData->setMinimumSize(QSize(120, 28));
        button_Load_FFTData->setMaximumSize(QSize(100, 28));

        horizontalLayout_15->addWidget(button_Load_FFTData);

        button_AnalyzeRawPolData = new QPushButton(PanelPolarimeter);
        button_AnalyzeRawPolData->setObjectName(QStringLiteral("button_AnalyzeRawPolData"));
        button_AnalyzeRawPolData->setMinimumSize(QSize(120, 28));
        button_AnalyzeRawPolData->setMaximumSize(QSize(120, 28));

        horizontalLayout_15->addWidget(button_AnalyzeRawPolData);


        verticalLayout_7->addLayout(horizontalLayout_15);


        horizonalLayout_2->addLayout(verticalLayout_7);


        gridLayout->addLayout(horizonalLayout_2, 0, 0, 1, 1);


        retranslateUi(PanelPolarimeter);

        QMetaObject::connectSlotsByName(PanelPolarimeter);
    } // setupUi

    void retranslateUi(QWidget *PanelPolarimeter)
    {
        PanelPolarimeter->setWindowTitle(QApplication::translate("PanelPolarimeter", "Form", Q_NULLPTR));
        label_Set_Spec_Pol->setText(QApplication::translate("PanelPolarimeter", "Spectrometer:", Q_NULLPTR));
        label_3->setText(QApplication::translate("PanelPolarimeter", "Current Measurement:", Q_NULLPTR));
        label_5->setText(QApplication::translate("PanelPolarimeter", "Total measurement:", Q_NULLPTR));
        label_Measurements_Pol->setText(QApplication::translate("PanelPolarimeter", "Measurement Progress:", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem = Table_Measurements_Pol->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("PanelPolarimeter", "No.", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem1 = Table_Measurements_Pol->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("PanelPolarimeter", "Time", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem2 = Table_Measurements_Pol->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("PanelPolarimeter", "File Name", Q_NULLPTR));
        label_Save_Pol->setText(QApplication::translate("PanelPolarimeter", "Save Options:", Q_NULLPTR));
        checkBox_AutoSave_Pol_Raw->setText(QApplication::translate("PanelPolarimeter", "Raw Data", Q_NULLPTR));
        checkBox_AutoSave_Pol->setText(QApplication::translate("PanelPolarimeter", "FFT Profiles", Q_NULLPTR));
        label_5_Pol_settings->setText(QApplication::translate("PanelPolarimeter", "Measurement Settings:", Q_NULLPTR));
        button_Pol_ConfigureMeasurement->setText(QApplication::translate("PanelPolarimeter", "Configure", Q_NULLPTR));
        button_Conf_Setup_Pol->setText(QApplication::translate("PanelPolarimeter", "Calibrate", Q_NULLPTR));
        button_Start_Meas_Pol->setText(QApplication::translate("PanelPolarimeter", "Start Measurement", Q_NULLPTR));
        label_6->setText(QApplication::translate("PanelPolarimeter", "Raw Signal", Q_NULLPTR));
        label_7->setText(QApplication::translate("PanelPolarimeter", "Compensation W/2W", Q_NULLPTR));
        FFT_label_Pol->setText(QApplication::translate("PanelPolarimeter", "FFT for", Q_NULLPTR));
        waveToPlotFFT->setText(QString());
        label->setText(QApplication::translate("PanelPolarimeter", "nm", Q_NULLPTR));
        label_9->setText(QApplication::translate("PanelPolarimeter", "FFT Wavelegth Profile", Q_NULLPTR));
        label_10->setText(QApplication::translate("PanelPolarimeter", "Average Signal", Q_NULLPTR));
        Button_Save_Graphs_Pol->setText(QApplication::translate("PanelPolarimeter", "Save Graphs as PDF", Q_NULLPTR));
        button_Load_FFTData->setText(QApplication::translate("PanelPolarimeter", "Load From FFT", Q_NULLPTR));
        button_AnalyzeRawPolData->setText(QApplication::translate("PanelPolarimeter", "Load From Raw Data", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class PanelPolarimeter: public Ui_PanelPolarimeter {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PANEL_POLARIMETER_H
