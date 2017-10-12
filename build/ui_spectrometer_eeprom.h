/********************************************************************************
** Form generated from reading UI file 'spectrometer_eeprom.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SPECTROMETER_EEPROM_H
#define UI_SPECTROMETER_EEPROM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SpectrometerEEPROM
{
public:
    QPushButton *button_close;
    QPushButton *button_read;
    QPushButton *button_write;
    QPushButton *button_backupCreate;
    QPushButton *button_backupRestore;
    QLabel *label_9;
    QLabel *label_10;
    QLineEdit *lineEdit_structureLength;
    QLineEdit *lineEdit_structureVersion;
    QLabel *label_43;
    QLineEdit *lineEdit_information;
    QLabel *label_44;
    QTabWidget *tabWidget_2;
    QWidget *tab_3;
    QLineEdit *detectorType;
    QLabel *label_11;
    QLabel *label_4;
    QLineEdit *a_pNumPixels;
    QLabel *label_21;
    QLabel *label_22;
    QLineEdit *lineEdit_wavelengthCalibration_intercept;
    QLineEdit *lineEdit_wavelengthCalibration_X1;
    QLabel *label_23;
    QLineEdit *lineEdit_wavelengthCalibration_X2;
    QLabel *label_24;
    QLabel *label_25;
    QLineEdit *lineEdit_wavelengthCalibration_X3;
    QLineEdit *lineEdit_wavelengthCalibration_X4;
    QLabel *label_26;
    QLabel *label_27;
    QLabel *label_28;
    QLabel *label_29;
    QLineEdit *lineEdit_nonlinearityCalibration_X2;
    QLineEdit *lineEdit_nonlinearityCalibration_X4;
    QLineEdit *lineEdit_nonlinearityCalibration_intercept;
    QLineEdit *lineEdit_nonlinearityCalibration_X3;
    QLineEdit *lineEdit_nonlinearityCalibration_X1;
    QLabel *label_30;
    QLabel *label_31;
    QLabel *label_32;
    QLabel *label_33;
    QLineEdit *lineEdit_nonlinearityCalibration_X5;
    QLabel *label_34;
    QLineEdit *lineEdit_nonlinearityCalibration_X6;
    QLabel *label_35;
    QLineEdit *lineEdit_nonlinearityCalibration_X7;
    QLineEdit *lineEdit_nonlinearityCalibration_lowCounts;
    QLabel *label_36;
    QLineEdit *lineEdit_nonlinearityCalibration_highCounts;
    QLabel *label_37;
    QCheckBox *checkBox_nonlinearityCorrection_enabled;
    QLabel *label_38;
    QListWidget *listWidget_defectivePixels;
    QLabel *label_12;
    QLabel *label_13;
    QLabel *label_39;
    QLabel *label_40;
    QLabel *label_41;
    QDoubleSpinBox *doubleSpinBox_extOffset;
    QDoubleSpinBox *doubleSpinBox_offset2;
    QDoubleSpinBox *doubleSpinBox_offset1;
    QDoubleSpinBox *doubleSpinBox_gain2;
    QDoubleSpinBox *doubleSpinBox_gain1;
    QLabel *label_42;
    QLabel *label_45;
    QWidget *tab_5;
    QLabel *label_8;
    QLineEdit *m_IpAddr;
    QLineEdit *m_NetMask;
    QLabel *label_7;
    QLabel *label_6;
    QLineEdit *m_TcpPort;
    QLineEdit *m_Gateway;
    QCheckBox *m_DhcpEnabled;
    QLabel *label_5;
    QWidget *tab_4;
    QLineEdit *a_pFPGAVersion;
    QLabel *label;
    QLabel *label_2;
    QLineEdit *a_pDLLVersion;
    QLabel *label_3;
    QLineEdit *a_pFirmwareVersion;
    QFrame *line;
    QLabel *label_14;

    void setupUi(QDialog *SpectrometerEEPROM)
    {
        if (SpectrometerEEPROM->objectName().isEmpty())
            SpectrometerEEPROM->setObjectName(QStringLiteral("SpectrometerEEPROM"));
        SpectrometerEEPROM->resize(640, 485);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(SpectrometerEEPROM->sizePolicy().hasHeightForWidth());
        SpectrometerEEPROM->setSizePolicy(sizePolicy);
        button_close = new QPushButton(SpectrometerEEPROM);
        button_close->setObjectName(QStringLiteral("button_close"));
        button_close->setGeometry(QRect(565, 450, 60, 23));
        button_read = new QPushButton(SpectrometerEEPROM);
        button_read->setObjectName(QStringLiteral("button_read"));
        button_read->setGeometry(QRect(15, 450, 60, 23));
        button_write = new QPushButton(SpectrometerEEPROM);
        button_write->setObjectName(QStringLiteral("button_write"));
        button_write->setGeometry(QRect(80, 450, 60, 23));
        button_backupCreate = new QPushButton(SpectrometerEEPROM);
        button_backupCreate->setObjectName(QStringLiteral("button_backupCreate"));
        button_backupCreate->setGeometry(QRect(200, 450, 60, 23));
        button_backupRestore = new QPushButton(SpectrometerEEPROM);
        button_backupRestore->setObjectName(QStringLiteral("button_backupRestore"));
        button_backupRestore->setGeometry(QRect(265, 450, 60, 23));
        label_9 = new QLabel(SpectrometerEEPROM);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(10, 5, 80, 20));
        label_10 = new QLabel(SpectrometerEEPROM);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(420, 5, 90, 20));
        lineEdit_structureLength = new QLineEdit(SpectrometerEEPROM);
        lineEdit_structureLength->setObjectName(QStringLiteral("lineEdit_structureLength"));
        lineEdit_structureLength->setGeometry(QRect(110, 5, 110, 20));
        lineEdit_structureLength->setMaxLength(16);
        lineEdit_structureLength->setReadOnly(true);
        lineEdit_structureVersion = new QLineEdit(SpectrometerEEPROM);
        lineEdit_structureVersion->setObjectName(QStringLiteral("lineEdit_structureVersion"));
        lineEdit_structureVersion->setGeometry(QRect(520, 5, 110, 20));
        lineEdit_structureVersion->setMaxLength(8);
        lineEdit_structureVersion->setReadOnly(true);
        label_43 = new QLabel(SpectrometerEEPROM);
        label_43->setObjectName(QStringLiteral("label_43"));
        label_43->setGeometry(QRect(10, 35, 90, 20));
        lineEdit_information = new QLineEdit(SpectrometerEEPROM);
        lineEdit_information->setObjectName(QStringLiteral("lineEdit_information"));
        lineEdit_information->setGeometry(QRect(110, 35, 520, 20));
        lineEdit_information->setMaxLength(64);
        lineEdit_information->setReadOnly(true);
        label_44 = new QLabel(SpectrometerEEPROM);
        label_44->setObjectName(QStringLiteral("label_44"));
        label_44->setGeometry(QRect(230, 5, 40, 20));
        tabWidget_2 = new QTabWidget(SpectrometerEEPROM);
        tabWidget_2->setObjectName(QStringLiteral("tabWidget_2"));
        tabWidget_2->setGeometry(QRect(10, 70, 620, 370));
        tab_3 = new QWidget();
        tab_3->setObjectName(QStringLiteral("tab_3"));
        detectorType = new QLineEdit(tab_3);
        detectorType->setObjectName(QStringLiteral("detectorType"));
        detectorType->setGeometry(QRect(100, 40, 111, 21));
        detectorType->setReadOnly(true);
        label_11 = new QLabel(tab_3);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setGeometry(QRect(10, 40, 91, 21));
        label_4 = new QLabel(tab_3);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(10, 65, 91, 21));
        a_pNumPixels = new QLineEdit(tab_3);
        a_pNumPixels->setObjectName(QStringLiteral("a_pNumPixels"));
        a_pNumPixels->setGeometry(QRect(100, 65, 111, 21));
        a_pNumPixels->setReadOnly(true);
        label_21 = new QLabel(tab_3);
        label_21->setObjectName(QStringLiteral("label_21"));
        label_21->setGeometry(QRect(10, 135, 81, 21));
        label_22 = new QLabel(tab_3);
        label_22->setObjectName(QStringLiteral("label_22"));
        label_22->setGeometry(QRect(10, 160, 81, 21));
        lineEdit_wavelengthCalibration_intercept = new QLineEdit(tab_3);
        lineEdit_wavelengthCalibration_intercept->setObjectName(QStringLiteral("lineEdit_wavelengthCalibration_intercept"));
        lineEdit_wavelengthCalibration_intercept->setGeometry(QRect(100, 135, 111, 21));
        lineEdit_wavelengthCalibration_X1 = new QLineEdit(tab_3);
        lineEdit_wavelengthCalibration_X1->setObjectName(QStringLiteral("lineEdit_wavelengthCalibration_X1"));
        lineEdit_wavelengthCalibration_X1->setGeometry(QRect(100, 160, 111, 21));
        label_23 = new QLabel(tab_3);
        label_23->setObjectName(QStringLiteral("label_23"));
        label_23->setGeometry(QRect(10, 185, 81, 21));
        lineEdit_wavelengthCalibration_X2 = new QLineEdit(tab_3);
        lineEdit_wavelengthCalibration_X2->setObjectName(QStringLiteral("lineEdit_wavelengthCalibration_X2"));
        lineEdit_wavelengthCalibration_X2->setGeometry(QRect(100, 185, 111, 21));
        label_24 = new QLabel(tab_3);
        label_24->setObjectName(QStringLiteral("label_24"));
        label_24->setGeometry(QRect(10, 210, 81, 21));
        label_25 = new QLabel(tab_3);
        label_25->setObjectName(QStringLiteral("label_25"));
        label_25->setGeometry(QRect(10, 235, 81, 21));
        lineEdit_wavelengthCalibration_X3 = new QLineEdit(tab_3);
        lineEdit_wavelengthCalibration_X3->setObjectName(QStringLiteral("lineEdit_wavelengthCalibration_X3"));
        lineEdit_wavelengthCalibration_X3->setGeometry(QRect(100, 210, 111, 21));
        lineEdit_wavelengthCalibration_X4 = new QLineEdit(tab_3);
        lineEdit_wavelengthCalibration_X4->setObjectName(QStringLiteral("lineEdit_wavelengthCalibration_X4"));
        lineEdit_wavelengthCalibration_X4->setGeometry(QRect(100, 235, 111, 21));
        label_26 = new QLabel(tab_3);
        label_26->setObjectName(QStringLiteral("label_26"));
        label_26->setGeometry(QRect(10, 105, 201, 21));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        label_26->setFont(font);
        label_27 = new QLabel(tab_3);
        label_27->setObjectName(QStringLiteral("label_27"));
        label_27->setGeometry(QRect(410, 10, 181, 21));
        label_27->setFont(font);
        label_28 = new QLabel(tab_3);
        label_28->setObjectName(QStringLiteral("label_28"));
        label_28->setGeometry(QRect(410, 140, 61, 21));
        label_29 = new QLabel(tab_3);
        label_29->setObjectName(QStringLiteral("label_29"));
        label_29->setGeometry(QRect(410, 90, 61, 21));
        lineEdit_nonlinearityCalibration_X2 = new QLineEdit(tab_3);
        lineEdit_nonlinearityCalibration_X2->setObjectName(QStringLiteral("lineEdit_nonlinearityCalibration_X2"));
        lineEdit_nonlinearityCalibration_X2->setGeometry(QRect(480, 90, 111, 21));
        lineEdit_nonlinearityCalibration_X4 = new QLineEdit(tab_3);
        lineEdit_nonlinearityCalibration_X4->setObjectName(QStringLiteral("lineEdit_nonlinearityCalibration_X4"));
        lineEdit_nonlinearityCalibration_X4->setGeometry(QRect(480, 140, 111, 21));
        lineEdit_nonlinearityCalibration_intercept = new QLineEdit(tab_3);
        lineEdit_nonlinearityCalibration_intercept->setObjectName(QStringLiteral("lineEdit_nonlinearityCalibration_intercept"));
        lineEdit_nonlinearityCalibration_intercept->setGeometry(QRect(480, 40, 111, 21));
        lineEdit_nonlinearityCalibration_X3 = new QLineEdit(tab_3);
        lineEdit_nonlinearityCalibration_X3->setObjectName(QStringLiteral("lineEdit_nonlinearityCalibration_X3"));
        lineEdit_nonlinearityCalibration_X3->setGeometry(QRect(480, 115, 111, 21));
        lineEdit_nonlinearityCalibration_X1 = new QLineEdit(tab_3);
        lineEdit_nonlinearityCalibration_X1->setObjectName(QStringLiteral("lineEdit_nonlinearityCalibration_X1"));
        lineEdit_nonlinearityCalibration_X1->setGeometry(QRect(480, 65, 111, 21));
        label_30 = new QLabel(tab_3);
        label_30->setObjectName(QStringLiteral("label_30"));
        label_30->setGeometry(QRect(410, 65, 61, 21));
        label_31 = new QLabel(tab_3);
        label_31->setObjectName(QStringLiteral("label_31"));
        label_31->setGeometry(QRect(410, 40, 61, 21));
        label_32 = new QLabel(tab_3);
        label_32->setObjectName(QStringLiteral("label_32"));
        label_32->setGeometry(QRect(410, 115, 61, 21));
        label_33 = new QLabel(tab_3);
        label_33->setObjectName(QStringLiteral("label_33"));
        label_33->setGeometry(QRect(410, 165, 61, 21));
        lineEdit_nonlinearityCalibration_X5 = new QLineEdit(tab_3);
        lineEdit_nonlinearityCalibration_X5->setObjectName(QStringLiteral("lineEdit_nonlinearityCalibration_X5"));
        lineEdit_nonlinearityCalibration_X5->setGeometry(QRect(480, 165, 111, 21));
        label_34 = new QLabel(tab_3);
        label_34->setObjectName(QStringLiteral("label_34"));
        label_34->setGeometry(QRect(410, 190, 61, 21));
        lineEdit_nonlinearityCalibration_X6 = new QLineEdit(tab_3);
        lineEdit_nonlinearityCalibration_X6->setObjectName(QStringLiteral("lineEdit_nonlinearityCalibration_X6"));
        lineEdit_nonlinearityCalibration_X6->setGeometry(QRect(480, 190, 111, 21));
        label_35 = new QLabel(tab_3);
        label_35->setObjectName(QStringLiteral("label_35"));
        label_35->setGeometry(QRect(410, 215, 61, 21));
        lineEdit_nonlinearityCalibration_X7 = new QLineEdit(tab_3);
        lineEdit_nonlinearityCalibration_X7->setObjectName(QStringLiteral("lineEdit_nonlinearityCalibration_X7"));
        lineEdit_nonlinearityCalibration_X7->setGeometry(QRect(480, 215, 111, 21));
        lineEdit_nonlinearityCalibration_lowCounts = new QLineEdit(tab_3);
        lineEdit_nonlinearityCalibration_lowCounts->setObjectName(QStringLiteral("lineEdit_nonlinearityCalibration_lowCounts"));
        lineEdit_nonlinearityCalibration_lowCounts->setGeometry(QRect(480, 250, 111, 21));
        label_36 = new QLabel(tab_3);
        label_36->setObjectName(QStringLiteral("label_36"));
        label_36->setGeometry(QRect(410, 250, 61, 21));
        lineEdit_nonlinearityCalibration_highCounts = new QLineEdit(tab_3);
        lineEdit_nonlinearityCalibration_highCounts->setObjectName(QStringLiteral("lineEdit_nonlinearityCalibration_highCounts"));
        lineEdit_nonlinearityCalibration_highCounts->setGeometry(QRect(480, 275, 111, 21));
        label_37 = new QLabel(tab_3);
        label_37->setObjectName(QStringLiteral("label_37"));
        label_37->setGeometry(QRect(410, 275, 61, 21));
        checkBox_nonlinearityCorrection_enabled = new QCheckBox(tab_3);
        checkBox_nonlinearityCorrection_enabled->setObjectName(QStringLiteral("checkBox_nonlinearityCorrection_enabled"));
        checkBox_nonlinearityCorrection_enabled->setGeometry(QRect(410, 310, 181, 21));
        label_38 = new QLabel(tab_3);
        label_38->setObjectName(QStringLiteral("label_38"));
        label_38->setGeometry(QRect(240, 200, 141, 21));
        label_38->setFont(font);
        listWidget_defectivePixels = new QListWidget(tab_3);
        listWidget_defectivePixels->setObjectName(QStringLiteral("listWidget_defectivePixels"));
        listWidget_defectivePixels->setGeometry(QRect(240, 230, 141, 96));
        label_12 = new QLabel(tab_3);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setGeometry(QRect(240, 40, 51, 21));
        label_13 = new QLabel(tab_3);
        label_13->setObjectName(QStringLiteral("label_13"));
        label_13->setGeometry(QRect(240, 65, 51, 21));
        label_39 = new QLabel(tab_3);
        label_39->setObjectName(QStringLiteral("label_39"));
        label_39->setGeometry(QRect(240, 100, 51, 21));
        label_40 = new QLabel(tab_3);
        label_40->setObjectName(QStringLiteral("label_40"));
        label_40->setGeometry(QRect(240, 125, 51, 21));
        label_41 = new QLabel(tab_3);
        label_41->setObjectName(QStringLiteral("label_41"));
        label_41->setGeometry(QRect(240, 160, 61, 21));
        doubleSpinBox_extOffset = new QDoubleSpinBox(tab_3);
        doubleSpinBox_extOffset->setObjectName(QStringLiteral("doubleSpinBox_extOffset"));
        doubleSpinBox_extOffset->setGeometry(QRect(310, 160, 71, 21));
        doubleSpinBox_offset2 = new QDoubleSpinBox(tab_3);
        doubleSpinBox_offset2->setObjectName(QStringLiteral("doubleSpinBox_offset2"));
        doubleSpinBox_offset2->setGeometry(QRect(310, 125, 71, 21));
        doubleSpinBox_offset1 = new QDoubleSpinBox(tab_3);
        doubleSpinBox_offset1->setObjectName(QStringLiteral("doubleSpinBox_offset1"));
        doubleSpinBox_offset1->setGeometry(QRect(310, 100, 71, 21));
        doubleSpinBox_gain2 = new QDoubleSpinBox(tab_3);
        doubleSpinBox_gain2->setObjectName(QStringLiteral("doubleSpinBox_gain2"));
        doubleSpinBox_gain2->setGeometry(QRect(310, 65, 71, 21));
        doubleSpinBox_gain1 = new QDoubleSpinBox(tab_3);
        doubleSpinBox_gain1->setObjectName(QStringLiteral("doubleSpinBox_gain1"));
        doubleSpinBox_gain1->setGeometry(QRect(310, 40, 71, 21));
        label_42 = new QLabel(tab_3);
        label_42->setObjectName(QStringLiteral("label_42"));
        label_42->setGeometry(QRect(240, 10, 141, 21));
        label_42->setFont(font);
        label_45 = new QLabel(tab_3);
        label_45->setObjectName(QStringLiteral("label_45"));
        label_45->setGeometry(QRect(10, 10, 141, 21));
        label_45->setFont(font);
        tabWidget_2->addTab(tab_3, QString());
        tab_5 = new QWidget();
        tab_5->setObjectName(QStringLiteral("tab_5"));
        label_8 = new QLabel(tab_5);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(10, 85, 61, 21));
        m_IpAddr = new QLineEdit(tab_5);
        m_IpAddr->setObjectName(QStringLiteral("m_IpAddr"));
        m_IpAddr->setGeometry(QRect(80, 10, 111, 21));
        m_IpAddr->setMaxLength(16);
        m_IpAddr->setFrame(true);
        m_IpAddr->setReadOnly(true);
        m_NetMask = new QLineEdit(tab_5);
        m_NetMask->setObjectName(QStringLiteral("m_NetMask"));
        m_NetMask->setGeometry(QRect(80, 35, 111, 21));
        m_NetMask->setMaxLength(16);
        m_NetMask->setReadOnly(true);
        label_7 = new QLabel(tab_5);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(10, 60, 61, 21));
        label_6 = new QLabel(tab_5);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(10, 35, 61, 21));
        m_TcpPort = new QLineEdit(tab_5);
        m_TcpPort->setObjectName(QStringLiteral("m_TcpPort"));
        m_TcpPort->setGeometry(QRect(80, 85, 111, 21));
        m_TcpPort->setMaxLength(5);
        m_TcpPort->setReadOnly(true);
        m_Gateway = new QLineEdit(tab_5);
        m_Gateway->setObjectName(QStringLiteral("m_Gateway"));
        m_Gateway->setGeometry(QRect(80, 60, 111, 21));
        m_Gateway->setMaxLength(16);
        m_Gateway->setReadOnly(true);
        m_DhcpEnabled = new QCheckBox(tab_5);
        m_DhcpEnabled->setObjectName(QStringLiteral("m_DhcpEnabled"));
        m_DhcpEnabled->setGeometry(QRect(10, 110, 181, 21));
        m_DhcpEnabled->setCheckable(false);
        label_5 = new QLabel(tab_5);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(10, 10, 61, 21));
        tabWidget_2->addTab(tab_5, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName(QStringLiteral("tab_4"));
        a_pFPGAVersion = new QLineEdit(tab_4);
        a_pFPGAVersion->setObjectName(QStringLiteral("a_pFPGAVersion"));
        a_pFPGAVersion->setGeometry(QRect(110, 10, 111, 21));
        a_pFPGAVersion->setReadOnly(true);
        label = new QLabel(tab_4);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 10, 91, 21));
        label_2 = new QLabel(tab_4);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(10, 35, 91, 21));
        a_pDLLVersion = new QLineEdit(tab_4);
        a_pDLLVersion->setObjectName(QStringLiteral("a_pDLLVersion"));
        a_pDLLVersion->setGeometry(QRect(110, 60, 111, 21));
        a_pDLLVersion->setReadOnly(true);
        label_3 = new QLabel(tab_4);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(10, 60, 91, 21));
        a_pFirmwareVersion = new QLineEdit(tab_4);
        a_pFirmwareVersion->setObjectName(QStringLiteral("a_pFirmwareVersion"));
        a_pFirmwareVersion->setGeometry(QRect(110, 35, 111, 21));
        a_pFirmwareVersion->setReadOnly(true);
        tabWidget_2->addTab(tab_4, QString());
        line = new QFrame(SpectrometerEEPROM);
        line->setObjectName(QStringLiteral("line"));
        line->setGeometry(QRect(140, 450, 20, 23));
        line->setFrameShadow(QFrame::Sunken);
        line->setFrameShape(QFrame::VLine);
        label_14 = new QLabel(SpectrometerEEPROM);
        label_14->setObjectName(QStringLiteral("label_14"));
        label_14->setGeometry(QRect(160, 450, 40, 23));

        retranslateUi(SpectrometerEEPROM);

        tabWidget_2->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(SpectrometerEEPROM);
    } // setupUi

    void retranslateUi(QDialog *SpectrometerEEPROM)
    {
        SpectrometerEEPROM->setWindowTitle(QApplication::translate("SpectrometerEEPROM", "EEPROM", Q_NULLPTR));
        button_close->setText(QApplication::translate("SpectrometerEEPROM", "Close", Q_NULLPTR));
        button_read->setText(QApplication::translate("SpectrometerEEPROM", "Read", Q_NULLPTR));
        button_write->setText(QApplication::translate("SpectrometerEEPROM", "Write", Q_NULLPTR));
        button_backupCreate->setText(QApplication::translate("SpectrometerEEPROM", "Create", Q_NULLPTR));
        button_backupRestore->setText(QApplication::translate("SpectrometerEEPROM", "Restore", Q_NULLPTR));
        label_9->setText(QApplication::translate("SpectrometerEEPROM", "Structure length", Q_NULLPTR));
        label_10->setText(QApplication::translate("SpectrometerEEPROM", "Structure version", Q_NULLPTR));
        label_43->setText(QApplication::translate("SpectrometerEEPROM", "Information", Q_NULLPTR));
        label_44->setText(QApplication::translate("SpectrometerEEPROM", "bytes", Q_NULLPTR));
        label_11->setText(QApplication::translate("SpectrometerEEPROM", "Detector type", Q_NULLPTR));
        label_4->setText(QApplication::translate("SpectrometerEEPROM", "Number of pixels", Q_NULLPTR));
        label_21->setText(QApplication::translate("SpectrometerEEPROM", "Intercept", Q_NULLPTR));
        label_22->setText(QApplication::translate("SpectrometerEEPROM", "X1", Q_NULLPTR));
        label_23->setText(QApplication::translate("SpectrometerEEPROM", "X2", Q_NULLPTR));
        label_24->setText(QApplication::translate("SpectrometerEEPROM", "X3", Q_NULLPTR));
        label_25->setText(QApplication::translate("SpectrometerEEPROM", "X4", Q_NULLPTR));
        label_26->setText(QApplication::translate("SpectrometerEEPROM", "Wavelength calibration", Q_NULLPTR));
        label_27->setText(QApplication::translate("SpectrometerEEPROM", "Non-linearity calibration", Q_NULLPTR));
        label_28->setText(QApplication::translate("SpectrometerEEPROM", "X4", Q_NULLPTR));
        label_29->setText(QApplication::translate("SpectrometerEEPROM", "X2", Q_NULLPTR));
        label_30->setText(QApplication::translate("SpectrometerEEPROM", "X1", Q_NULLPTR));
        label_31->setText(QApplication::translate("SpectrometerEEPROM", "Intercept", Q_NULLPTR));
        label_32->setText(QApplication::translate("SpectrometerEEPROM", "X3", Q_NULLPTR));
        label_33->setText(QApplication::translate("SpectrometerEEPROM", "X5", Q_NULLPTR));
        label_34->setText(QApplication::translate("SpectrometerEEPROM", "X6", Q_NULLPTR));
        label_35->setText(QApplication::translate("SpectrometerEEPROM", "X7", Q_NULLPTR));
        lineEdit_nonlinearityCalibration_lowCounts->setText(QString());
        label_36->setText(QApplication::translate("SpectrometerEEPROM", "Low counts", Q_NULLPTR));
        lineEdit_nonlinearityCalibration_highCounts->setText(QString());
        label_37->setText(QApplication::translate("SpectrometerEEPROM", "High counts", Q_NULLPTR));
        checkBox_nonlinearityCorrection_enabled->setText(QApplication::translate("SpectrometerEEPROM", "Enable non-linearity correction", Q_NULLPTR));
        label_38->setText(QApplication::translate("SpectrometerEEPROM", "Defective pixels", Q_NULLPTR));
        label_12->setText(QApplication::translate("SpectrometerEEPROM", "Gain 1", Q_NULLPTR));
        label_13->setText(QApplication::translate("SpectrometerEEPROM", "Gain 2", Q_NULLPTR));
        label_39->setText(QApplication::translate("SpectrometerEEPROM", "Offset 1", Q_NULLPTR));
        label_40->setText(QApplication::translate("SpectrometerEEPROM", "Offset 2", Q_NULLPTR));
        label_41->setText(QApplication::translate("SpectrometerEEPROM", "Ext. Offset", Q_NULLPTR));
        label_42->setText(QApplication::translate("SpectrometerEEPROM", "Gain and offset", Q_NULLPTR));
        label_45->setText(QApplication::translate("SpectrometerEEPROM", "Sensor", Q_NULLPTR));
        tabWidget_2->setTabText(tabWidget_2->indexOf(tab_3), QApplication::translate("SpectrometerEEPROM", "Detector", Q_NULLPTR));
        label_8->setText(QApplication::translate("SpectrometerEEPROM", "TCP port", Q_NULLPTR));
        label_7->setText(QApplication::translate("SpectrometerEEPROM", "Gateway", Q_NULLPTR));
        label_6->setText(QApplication::translate("SpectrometerEEPROM", "Net mask", Q_NULLPTR));
        m_DhcpEnabled->setText(QApplication::translate("SpectrometerEEPROM", "DHCP enabled", Q_NULLPTR));
        label_5->setText(QApplication::translate("SpectrometerEEPROM", "IP address", Q_NULLPTR));
        tabWidget_2->setTabText(tabWidget_2->indexOf(tab_5), QApplication::translate("SpectrometerEEPROM", "Ethernet", Q_NULLPTR));
        label->setText(QApplication::translate("SpectrometerEEPROM", "FPGA version", Q_NULLPTR));
        label_2->setText(QApplication::translate("SpectrometerEEPROM", "Firmware version", Q_NULLPTR));
        label_3->setText(QApplication::translate("SpectrometerEEPROM", "DLL version", Q_NULLPTR));
        tabWidget_2->setTabText(tabWidget_2->indexOf(tab_4), QApplication::translate("SpectrometerEEPROM", "Software", Q_NULLPTR));
        label_14->setText(QApplication::translate("SpectrometerEEPROM", "Backup", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class SpectrometerEEPROM: public Ui_SpectrometerEEPROM {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SPECTROMETER_EEPROM_H
