/********************************************************************************
** Form generated from reading UI file 'iad_configure_page01.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IAD_CONFIGURE_PAGE01_H
#define UI_IAD_CONFIGURE_PAGE01_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_ConfigureIADPage01
{
public:
    QLabel *label_caption1;
    QLabel *label_step1;
    QLabel *label_diffuseTransmission;
    QComboBox *combo_unscatteredTransmission;
    QLabel *label_diffuseReflection;
    QComboBox *combo_diffuseTransmission;
    QLabel *label_unscatteredTransmission;
    QComboBox *combo_diffuseReflection;
    QPushButton *button_next;
    QPushButton *button_cancel;
    QLabel *label_opticalParameters;
    QCheckBox *checkBox_absorptionCoefficient;
    QCheckBox *checkBox_scatteringCoefficient;
    QCheckBox *checkBox_reducedScatteringCoefficient;
    QCheckBox *checkBox_anisotropy;
    QLabel *label_step2;
    QLabel *label_caption2;
    QSpinBox *spinBox_incidentLightAngle;
    QLabel *label_incidentLightAngle;
    QLabel *label_incidentLightAngleUnit;
    QLabel *label_errorTolerance;
    QDoubleSpinBox *doubleSpinBox_errorTolerance;
    QLabel *label_errorToleranceUnit;
    QLabel *label_quadraturePoints;
    QSpinBox *spinBox_quadraturePoints;

    void setupUi(QDialog *ConfigureIADPage01)
    {
        if (ConfigureIADPage01->objectName().isEmpty())
            ConfigureIADPage01->setObjectName(QStringLiteral("ConfigureIADPage01"));
        ConfigureIADPage01->resize(640, 480);
        label_caption1 = new QLabel(ConfigureIADPage01);
        label_caption1->setObjectName(QStringLiteral("label_caption1"));
        label_caption1->setGeometry(QRect(60, 10, 571, 20));
        QFont font;
        font.setBold(false);
        font.setWeight(50);
        label_caption1->setFont(font);
        label_step1 = new QLabel(ConfigureIADPage01);
        label_step1->setObjectName(QStringLiteral("label_step1"));
        label_step1->setGeometry(QRect(10, 10, 41, 20));
        QFont font1;
        font1.setBold(true);
        font1.setWeight(75);
        label_step1->setFont(font1);
        label_diffuseTransmission = new QLabel(ConfigureIADPage01);
        label_diffuseTransmission->setObjectName(QStringLiteral("label_diffuseTransmission"));
        label_diffuseTransmission->setGeometry(QRect(180, 40, 150, 20));
        combo_unscatteredTransmission = new QComboBox(ConfigureIADPage01);
        combo_unscatteredTransmission->setObjectName(QStringLiteral("combo_unscatteredTransmission"));
        combo_unscatteredTransmission->setEnabled(false);
        combo_unscatteredTransmission->setGeometry(QRect(350, 60, 150, 22));
        label_diffuseReflection = new QLabel(ConfigureIADPage01);
        label_diffuseReflection->setObjectName(QStringLiteral("label_diffuseReflection"));
        label_diffuseReflection->setGeometry(QRect(10, 40, 150, 20));
        combo_diffuseTransmission = new QComboBox(ConfigureIADPage01);
        combo_diffuseTransmission->setObjectName(QStringLiteral("combo_diffuseTransmission"));
        combo_diffuseTransmission->setEnabled(false);
        combo_diffuseTransmission->setGeometry(QRect(180, 60, 150, 22));
        label_unscatteredTransmission = new QLabel(ConfigureIADPage01);
        label_unscatteredTransmission->setObjectName(QStringLiteral("label_unscatteredTransmission"));
        label_unscatteredTransmission->setGeometry(QRect(350, 40, 150, 20));
        combo_diffuseReflection = new QComboBox(ConfigureIADPage01);
        combo_diffuseReflection->setObjectName(QStringLiteral("combo_diffuseReflection"));
        combo_diffuseReflection->setGeometry(QRect(10, 60, 150, 22));
        button_next = new QPushButton(ConfigureIADPage01);
        button_next->setObjectName(QStringLiteral("button_next"));
        button_next->setEnabled(false);
        button_next->setGeometry(QRect(470, 440, 75, 23));
        button_cancel = new QPushButton(ConfigureIADPage01);
        button_cancel->setObjectName(QStringLiteral("button_cancel"));
        button_cancel->setGeometry(QRect(550, 440, 75, 23));
        label_opticalParameters = new QLabel(ConfigureIADPage01);
        label_opticalParameters->setObjectName(QStringLiteral("label_opticalParameters"));
        label_opticalParameters->setGeometry(QRect(10, 100, 100, 20));
        QFont font2;
        font2.setBold(false);
        font2.setItalic(false);
        font2.setWeight(50);
        label_opticalParameters->setFont(font2);
        checkBox_absorptionCoefficient = new QCheckBox(ConfigureIADPage01);
        checkBox_absorptionCoefficient->setObjectName(QStringLiteral("checkBox_absorptionCoefficient"));
        checkBox_absorptionCoefficient->setEnabled(true);
        checkBox_absorptionCoefficient->setGeometry(QRect(120, 100, 41, 21));
        checkBox_absorptionCoefficient->setCheckable(true);
        checkBox_absorptionCoefficient->setAutoExclusive(false);
        checkBox_scatteringCoefficient = new QCheckBox(ConfigureIADPage01);
        checkBox_scatteringCoefficient->setObjectName(QStringLiteral("checkBox_scatteringCoefficient"));
        checkBox_scatteringCoefficient->setEnabled(true);
        checkBox_scatteringCoefficient->setGeometry(QRect(160, 100, 41, 21));
        checkBox_scatteringCoefficient->setCheckable(true);
        checkBox_scatteringCoefficient->setAutoExclusive(false);
        checkBox_reducedScatteringCoefficient = new QCheckBox(ConfigureIADPage01);
        checkBox_reducedScatteringCoefficient->setObjectName(QStringLiteral("checkBox_reducedScatteringCoefficient"));
        checkBox_reducedScatteringCoefficient->setEnabled(true);
        checkBox_reducedScatteringCoefficient->setGeometry(QRect(200, 100, 41, 21));
        checkBox_reducedScatteringCoefficient->setCheckable(true);
        checkBox_anisotropy = new QCheckBox(ConfigureIADPage01);
        checkBox_anisotropy->setObjectName(QStringLiteral("checkBox_anisotropy"));
        checkBox_anisotropy->setEnabled(true);
        checkBox_anisotropy->setGeometry(QRect(240, 100, 41, 21));
        checkBox_anisotropy->setCheckable(true);
        label_step2 = new QLabel(ConfigureIADPage01);
        label_step2->setObjectName(QStringLiteral("label_step2"));
        label_step2->setGeometry(QRect(10, 150, 41, 20));
        label_step2->setFont(font1);
        label_caption2 = new QLabel(ConfigureIADPage01);
        label_caption2->setObjectName(QStringLiteral("label_caption2"));
        label_caption2->setGeometry(QRect(60, 150, 571, 20));
        label_caption2->setFont(font);
        spinBox_incidentLightAngle = new QSpinBox(ConfigureIADPage01);
        spinBox_incidentLightAngle->setObjectName(QStringLiteral("spinBox_incidentLightAngle"));
        spinBox_incidentLightAngle->setGeometry(QRect(120, 185, 60, 22));
        spinBox_incidentLightAngle->setMinimum(0);
        spinBox_incidentLightAngle->setMaximum(90);
        spinBox_incidentLightAngle->setValue(8);
        label_incidentLightAngle = new QLabel(ConfigureIADPage01);
        label_incidentLightAngle->setObjectName(QStringLiteral("label_incidentLightAngle"));
        label_incidentLightAngle->setGeometry(QRect(10, 185, 105, 20));
        label_incidentLightAngle->setFont(font2);
        label_incidentLightAngleUnit = new QLabel(ConfigureIADPage01);
        label_incidentLightAngleUnit->setObjectName(QStringLiteral("label_incidentLightAngleUnit"));
        label_incidentLightAngleUnit->setGeometry(QRect(190, 185, 26, 21));
        label_errorTolerance = new QLabel(ConfigureIADPage01);
        label_errorTolerance->setObjectName(QStringLiteral("label_errorTolerance"));
        label_errorTolerance->setGeometry(QRect(10, 210, 105, 20));
        label_errorTolerance->setFont(font2);
        doubleSpinBox_errorTolerance = new QDoubleSpinBox(ConfigureIADPage01);
        doubleSpinBox_errorTolerance->setObjectName(QStringLiteral("doubleSpinBox_errorTolerance"));
        doubleSpinBox_errorTolerance->setGeometry(QRect(120, 210, 60, 22));
        doubleSpinBox_errorTolerance->setDecimals(3);
        doubleSpinBox_errorTolerance->setMinimum(0.001);
        doubleSpinBox_errorTolerance->setMaximum(10);
        doubleSpinBox_errorTolerance->setSingleStep(0.001);
        doubleSpinBox_errorTolerance->setValue(0.001);
        label_errorToleranceUnit = new QLabel(ConfigureIADPage01);
        label_errorToleranceUnit->setObjectName(QStringLiteral("label_errorToleranceUnit"));
        label_errorToleranceUnit->setGeometry(QRect(190, 210, 26, 22));
        label_quadraturePoints = new QLabel(ConfigureIADPage01);
        label_quadraturePoints->setObjectName(QStringLiteral("label_quadraturePoints"));
        label_quadraturePoints->setGeometry(QRect(10, 235, 105, 20));
        label_quadraturePoints->setFont(font2);
        spinBox_quadraturePoints = new QSpinBox(ConfigureIADPage01);
        spinBox_quadraturePoints->setObjectName(QStringLiteral("spinBox_quadraturePoints"));
        spinBox_quadraturePoints->setGeometry(QRect(120, 235, 60, 22));
        spinBox_quadraturePoints->setMinimum(1);
        spinBox_quadraturePoints->setMaximum(64);
        spinBox_quadraturePoints->setValue(8);
        spinBox_quadraturePoints->setDisplayIntegerBase(10);

        retranslateUi(ConfigureIADPage01);

        QMetaObject::connectSlotsByName(ConfigureIADPage01);
    } // setupUi

    void retranslateUi(QDialog *ConfigureIADPage01)
    {
        ConfigureIADPage01->setWindowTitle(QApplication::translate("ConfigureIADPage01", "Assistant", Q_NULLPTR));
        label_caption1->setText(QApplication::translate("ConfigureIADPage01", "Assign the activated spectrometer(s) to the measured variables.", Q_NULLPTR));
        label_step1->setText(QApplication::translate("ConfigureIADPage01", "Step 1:", Q_NULLPTR));
        label_diffuseTransmission->setText(QApplication::translate("ConfigureIADPage01", "Diffuse transmission", Q_NULLPTR));
        combo_unscatteredTransmission->clear();
        combo_unscatteredTransmission->insertItems(0, QStringList()
         << QApplication::translate("ConfigureIADPage01", "Select spectrometer", Q_NULLPTR)
        );
        label_diffuseReflection->setText(QApplication::translate("ConfigureIADPage01", "Diffuse reflection", Q_NULLPTR));
        combo_diffuseTransmission->clear();
        combo_diffuseTransmission->insertItems(0, QStringList()
         << QApplication::translate("ConfigureIADPage01", "Select spectrometer", Q_NULLPTR)
        );
        label_unscatteredTransmission->setText(QApplication::translate("ConfigureIADPage01", "Unscattered transmission", Q_NULLPTR));
        combo_diffuseReflection->clear();
        combo_diffuseReflection->insertItems(0, QStringList()
         << QApplication::translate("ConfigureIADPage01", "Select spectrometer", Q_NULLPTR)
        );
        button_next->setText(QApplication::translate("ConfigureIADPage01", "Next", Q_NULLPTR));
        button_cancel->setText(QApplication::translate("ConfigureIADPage01", "Cancel", Q_NULLPTR));
        label_opticalParameters->setText(QApplication::translate("ConfigureIADPage01", "Calculation possible:", Q_NULLPTR));
        checkBox_absorptionCoefficient->setText(QApplication::translate("ConfigureIADPage01", "\302\265a", Q_NULLPTR));
        checkBox_scatteringCoefficient->setText(QApplication::translate("ConfigureIADPage01", "\302\265s", Q_NULLPTR));
        checkBox_reducedScatteringCoefficient->setText(QApplication::translate("ConfigureIADPage01", "\302\265s'", Q_NULLPTR));
        checkBox_anisotropy->setText(QApplication::translate("ConfigureIADPage01", "g", Q_NULLPTR));
        label_step2->setText(QApplication::translate("ConfigureIADPage01", "Step 2:", Q_NULLPTR));
        label_caption2->setText(QApplication::translate("ConfigureIADPage01", "IAD arguments", Q_NULLPTR));
        label_incidentLightAngle->setText(QApplication::translate("ConfigureIADPage01", "Incident light angle:", Q_NULLPTR));
        label_incidentLightAngleUnit->setText(QApplication::translate("ConfigureIADPage01", "deg", Q_NULLPTR));
        label_errorTolerance->setText(QApplication::translate("ConfigureIADPage01", "Error tolerance:", Q_NULLPTR));
        label_errorToleranceUnit->setText(QApplication::translate("ConfigureIADPage01", "%", Q_NULLPTR));
        label_quadraturePoints->setText(QApplication::translate("ConfigureIADPage01", "# Quadrature points:", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ConfigureIADPage01: public Ui_ConfigureIADPage01 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IAD_CONFIGURE_PAGE01_H
