/********************************************************************************
** Form generated from reading UI file 'iad_configure_page02.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IAD_CONFIGURE_PAGE02_H
#define UI_IAD_CONFIGURE_PAGE02_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ConfigureIADPage02
{
public:
    QPushButton *button_finish;
    QPushButton *button_cancel;
    QLabel *label_caption3;
    QLabel *label_step3;
    QDoubleSpinBox *doubleSpinBox_indexOfRefractionOfSample;
    QLabel *label_2;
    QLabel *label_3;
    QDoubleSpinBox *doubleSpinBox_indexOfRefractionOfTopSlide;
    QLabel *label_4;
    QDoubleSpinBox *doubleSpinBox_thicknessOfSample;
    QLabel *label_6;
    QLabel *label_7;
    QDoubleSpinBox *doubleSpinBox_thicknessOfSlides;
    QLabel *label_8;
    QLabel *label_9;
    QDoubleSpinBox *doubleSpinBox_diameterOfIlluminationBeam;
    QLabel *label_10;
    QLabel *label_reflectionSphere;
    QLabel *label_12;
    QDoubleSpinBox *doubleSpinBox_rSphereDiameter;
    QLabel *label_13;
    QLabel *label_14;
    QDoubleSpinBox *doubleSpinBox_rSamplePortDiameter;
    QLabel *label_15;
    QLabel *label_16;
    QDoubleSpinBox *doubleSpinBox_rEntrancePortDiameter;
    QLabel *label_17;
    QLabel *label_18;
    QDoubleSpinBox *doubleSpinBox_rDetectorPortDiameter;
    QLabel *label_19;
    QComboBox *comboBox_rSphereWallMaterial;
    QLabel *label_20;
    QLabel *label_transmissionSphere;
    QLabel *label_22;
    QLabel *label_23;
    QComboBox *comboBox_tSphereWallMaterial;
    QDoubleSpinBox *doubleSpinBox_tDetectorPortDiameter;
    QLabel *label_24;
    QLabel *label_25;
    QLabel *label_26;
    QLabel *label_27;
    QLabel *label_28;
    QLabel *label_29;
    QDoubleSpinBox *doubleSpinBox_tEntrancePortDiameter;
    QLabel *label_30;
    QDoubleSpinBox *doubleSpinBox_tSphereDiameter;
    QDoubleSpinBox *doubleSpinBox_tSamplePortDiameter;
    QLabel *label_31;
    QComboBox *comboBox_calibrationStandard;

    void setupUi(QWidget *ConfigureIADPage02)
    {
        if (ConfigureIADPage02->objectName().isEmpty())
            ConfigureIADPage02->setObjectName(QStringLiteral("ConfigureIADPage02"));
        ConfigureIADPage02->resize(640, 480);
        button_finish = new QPushButton(ConfigureIADPage02);
        button_finish->setObjectName(QStringLiteral("button_finish"));
        button_finish->setEnabled(false);
        button_finish->setGeometry(QRect(470, 440, 75, 23));
        button_cancel = new QPushButton(ConfigureIADPage02);
        button_cancel->setObjectName(QStringLiteral("button_cancel"));
        button_cancel->setGeometry(QRect(550, 440, 75, 23));
        label_caption3 = new QLabel(ConfigureIADPage02);
        label_caption3->setObjectName(QStringLiteral("label_caption3"));
        label_caption3->setGeometry(QRect(60, 10, 401, 20));
        QFont font;
        font.setBold(false);
        font.setWeight(50);
        label_caption3->setFont(font);
        label_step3 = new QLabel(ConfigureIADPage02);
        label_step3->setObjectName(QStringLiteral("label_step3"));
        label_step3->setGeometry(QRect(10, 10, 41, 20));
        QFont font1;
        font1.setBold(true);
        font1.setWeight(75);
        label_step3->setFont(font1);
        doubleSpinBox_indexOfRefractionOfSample = new QDoubleSpinBox(ConfigureIADPage02);
        doubleSpinBox_indexOfRefractionOfSample->setObjectName(QStringLiteral("doubleSpinBox_indexOfRefractionOfSample"));
        doubleSpinBox_indexOfRefractionOfSample->setGeometry(QRect(170, 50, 81, 22));
        doubleSpinBox_indexOfRefractionOfSample->setMaximum(2);
        doubleSpinBox_indexOfRefractionOfSample->setSingleStep(0.01);
        doubleSpinBox_indexOfRefractionOfSample->setValue(1.35);
        label_2 = new QLabel(ConfigureIADPage02);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(10, 50, 151, 21));
        label_3 = new QLabel(ConfigureIADPage02);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(10, 80, 161, 21));
        doubleSpinBox_indexOfRefractionOfTopSlide = new QDoubleSpinBox(ConfigureIADPage02);
        doubleSpinBox_indexOfRefractionOfTopSlide->setObjectName(QStringLiteral("doubleSpinBox_indexOfRefractionOfTopSlide"));
        doubleSpinBox_indexOfRefractionOfTopSlide->setGeometry(QRect(170, 80, 81, 22));
        doubleSpinBox_indexOfRefractionOfTopSlide->setMaximum(2);
        doubleSpinBox_indexOfRefractionOfTopSlide->setSingleStep(0.01);
        doubleSpinBox_indexOfRefractionOfTopSlide->setValue(1.5);
        label_4 = new QLabel(ConfigureIADPage02);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(10, 109, 111, 21));
        doubleSpinBox_thicknessOfSample = new QDoubleSpinBox(ConfigureIADPage02);
        doubleSpinBox_thicknessOfSample->setObjectName(QStringLiteral("doubleSpinBox_thicknessOfSample"));
        doubleSpinBox_thicknessOfSample->setGeometry(QRect(170, 110, 81, 22));
        doubleSpinBox_thicknessOfSample->setMaximum(10);
        doubleSpinBox_thicknessOfSample->setSingleStep(0.01);
        doubleSpinBox_thicknessOfSample->setValue(0.1);
        label_6 = new QLabel(ConfigureIADPage02);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(260, 110, 21, 21));
        label_7 = new QLabel(ConfigureIADPage02);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(10, 140, 111, 21));
        doubleSpinBox_thicknessOfSlides = new QDoubleSpinBox(ConfigureIADPage02);
        doubleSpinBox_thicknessOfSlides->setObjectName(QStringLiteral("doubleSpinBox_thicknessOfSlides"));
        doubleSpinBox_thicknessOfSlides->setGeometry(QRect(170, 140, 81, 22));
        doubleSpinBox_thicknessOfSlides->setMaximum(10);
        doubleSpinBox_thicknessOfSlides->setSingleStep(0.01);
        doubleSpinBox_thicknessOfSlides->setValue(2);
        label_8 = new QLabel(ConfigureIADPage02);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(260, 140, 21, 21));
        label_9 = new QLabel(ConfigureIADPage02);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(10, 170, 151, 21));
        doubleSpinBox_diameterOfIlluminationBeam = new QDoubleSpinBox(ConfigureIADPage02);
        doubleSpinBox_diameterOfIlluminationBeam->setObjectName(QStringLiteral("doubleSpinBox_diameterOfIlluminationBeam"));
        doubleSpinBox_diameterOfIlluminationBeam->setGeometry(QRect(170, 170, 81, 22));
        doubleSpinBox_diameterOfIlluminationBeam->setMaximum(100);
        doubleSpinBox_diameterOfIlluminationBeam->setSingleStep(0.01);
        doubleSpinBox_diameterOfIlluminationBeam->setValue(8);
        label_10 = new QLabel(ConfigureIADPage02);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(260, 170, 21, 21));
        label_reflectionSphere = new QLabel(ConfigureIADPage02);
        label_reflectionSphere->setObjectName(QStringLiteral("label_reflectionSphere"));
        label_reflectionSphere->setGeometry(QRect(10, 240, 111, 21));
        QFont font2;
        font2.setBold(true);
        font2.setItalic(false);
        font2.setUnderline(false);
        font2.setWeight(75);
        label_reflectionSphere->setFont(font2);
        label_12 = new QLabel(ConfigureIADPage02);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setGeometry(QRect(10, 270, 151, 21));
        doubleSpinBox_rSphereDiameter = new QDoubleSpinBox(ConfigureIADPage02);
        doubleSpinBox_rSphereDiameter->setObjectName(QStringLiteral("doubleSpinBox_rSphereDiameter"));
        doubleSpinBox_rSphereDiameter->setGeometry(QRect(170, 270, 81, 22));
        doubleSpinBox_rSphereDiameter->setMaximum(1000);
        doubleSpinBox_rSphereDiameter->setSingleStep(0.01);
        doubleSpinBox_rSphereDiameter->setValue(50);
        label_13 = new QLabel(ConfigureIADPage02);
        label_13->setObjectName(QStringLiteral("label_13"));
        label_13->setGeometry(QRect(260, 270, 21, 21));
        label_14 = new QLabel(ConfigureIADPage02);
        label_14->setObjectName(QStringLiteral("label_14"));
        label_14->setGeometry(QRect(10, 300, 151, 21));
        doubleSpinBox_rSamplePortDiameter = new QDoubleSpinBox(ConfigureIADPage02);
        doubleSpinBox_rSamplePortDiameter->setObjectName(QStringLiteral("doubleSpinBox_rSamplePortDiameter"));
        doubleSpinBox_rSamplePortDiameter->setGeometry(QRect(170, 300, 81, 22));
        doubleSpinBox_rSamplePortDiameter->setMaximum(100);
        doubleSpinBox_rSamplePortDiameter->setSingleStep(0.01);
        doubleSpinBox_rSamplePortDiameter->setValue(10);
        label_15 = new QLabel(ConfigureIADPage02);
        label_15->setObjectName(QStringLiteral("label_15"));
        label_15->setGeometry(QRect(260, 300, 21, 21));
        label_16 = new QLabel(ConfigureIADPage02);
        label_16->setObjectName(QStringLiteral("label_16"));
        label_16->setGeometry(QRect(10, 330, 151, 21));
        doubleSpinBox_rEntrancePortDiameter = new QDoubleSpinBox(ConfigureIADPage02);
        doubleSpinBox_rEntrancePortDiameter->setObjectName(QStringLiteral("doubleSpinBox_rEntrancePortDiameter"));
        doubleSpinBox_rEntrancePortDiameter->setGeometry(QRect(170, 330, 81, 22));
        doubleSpinBox_rEntrancePortDiameter->setMaximum(100);
        doubleSpinBox_rEntrancePortDiameter->setSingleStep(0.01);
        doubleSpinBox_rEntrancePortDiameter->setValue(5);
        label_17 = new QLabel(ConfigureIADPage02);
        label_17->setObjectName(QStringLiteral("label_17"));
        label_17->setGeometry(QRect(260, 330, 21, 21));
        label_18 = new QLabel(ConfigureIADPage02);
        label_18->setObjectName(QStringLiteral("label_18"));
        label_18->setGeometry(QRect(10, 360, 151, 21));
        doubleSpinBox_rDetectorPortDiameter = new QDoubleSpinBox(ConfigureIADPage02);
        doubleSpinBox_rDetectorPortDiameter->setObjectName(QStringLiteral("doubleSpinBox_rDetectorPortDiameter"));
        doubleSpinBox_rDetectorPortDiameter->setGeometry(QRect(170, 360, 81, 22));
        doubleSpinBox_rDetectorPortDiameter->setMaximum(100);
        doubleSpinBox_rDetectorPortDiameter->setSingleStep(0.01);
        doubleSpinBox_rDetectorPortDiameter->setValue(3);
        label_19 = new QLabel(ConfigureIADPage02);
        label_19->setObjectName(QStringLiteral("label_19"));
        label_19->setGeometry(QRect(260, 360, 21, 21));
        comboBox_rSphereWallMaterial = new QComboBox(ConfigureIADPage02);
        comboBox_rSphereWallMaterial->setObjectName(QStringLiteral("comboBox_rSphereWallMaterial"));
        comboBox_rSphereWallMaterial->setGeometry(QRect(170, 390, 111, 22));
        label_20 = new QLabel(ConfigureIADPage02);
        label_20->setObjectName(QStringLiteral("label_20"));
        label_20->setGeometry(QRect(10, 390, 151, 21));
        label_transmissionSphere = new QLabel(ConfigureIADPage02);
        label_transmissionSphere->setObjectName(QStringLiteral("label_transmissionSphere"));
        label_transmissionSphere->setGeometry(QRect(350, 240, 121, 21));
        label_transmissionSphere->setFont(font1);
        label_22 = new QLabel(ConfigureIADPage02);
        label_22->setObjectName(QStringLiteral("label_22"));
        label_22->setGeometry(QRect(600, 270, 21, 21));
        label_23 = new QLabel(ConfigureIADPage02);
        label_23->setObjectName(QStringLiteral("label_23"));
        label_23->setGeometry(QRect(350, 330, 151, 21));
        comboBox_tSphereWallMaterial = new QComboBox(ConfigureIADPage02);
        comboBox_tSphereWallMaterial->setObjectName(QStringLiteral("comboBox_tSphereWallMaterial"));
        comboBox_tSphereWallMaterial->setGeometry(QRect(510, 390, 111, 22));
        doubleSpinBox_tDetectorPortDiameter = new QDoubleSpinBox(ConfigureIADPage02);
        doubleSpinBox_tDetectorPortDiameter->setObjectName(QStringLiteral("doubleSpinBox_tDetectorPortDiameter"));
        doubleSpinBox_tDetectorPortDiameter->setGeometry(QRect(510, 360, 81, 22));
        doubleSpinBox_tDetectorPortDiameter->setMaximum(100);
        doubleSpinBox_tDetectorPortDiameter->setSingleStep(0.01);
        doubleSpinBox_tDetectorPortDiameter->setValue(4.5);
        label_24 = new QLabel(ConfigureIADPage02);
        label_24->setObjectName(QStringLiteral("label_24"));
        label_24->setGeometry(QRect(600, 300, 21, 21));
        label_25 = new QLabel(ConfigureIADPage02);
        label_25->setObjectName(QStringLiteral("label_25"));
        label_25->setGeometry(QRect(350, 270, 151, 21));
        label_26 = new QLabel(ConfigureIADPage02);
        label_26->setObjectName(QStringLiteral("label_26"));
        label_26->setGeometry(QRect(350, 300, 151, 21));
        label_27 = new QLabel(ConfigureIADPage02);
        label_27->setObjectName(QStringLiteral("label_27"));
        label_27->setGeometry(QRect(600, 330, 21, 21));
        label_28 = new QLabel(ConfigureIADPage02);
        label_28->setObjectName(QStringLiteral("label_28"));
        label_28->setGeometry(QRect(350, 390, 151, 21));
        label_29 = new QLabel(ConfigureIADPage02);
        label_29->setObjectName(QStringLiteral("label_29"));
        label_29->setGeometry(QRect(600, 360, 21, 21));
        doubleSpinBox_tEntrancePortDiameter = new QDoubleSpinBox(ConfigureIADPage02);
        doubleSpinBox_tEntrancePortDiameter->setObjectName(QStringLiteral("doubleSpinBox_tEntrancePortDiameter"));
        doubleSpinBox_tEntrancePortDiameter->setGeometry(QRect(510, 330, 81, 22));
        doubleSpinBox_tEntrancePortDiameter->setMaximum(100);
        doubleSpinBox_tEntrancePortDiameter->setSingleStep(0.01);
        doubleSpinBox_tEntrancePortDiameter->setValue(0);
        label_30 = new QLabel(ConfigureIADPage02);
        label_30->setObjectName(QStringLiteral("label_30"));
        label_30->setGeometry(QRect(350, 360, 151, 21));
        doubleSpinBox_tSphereDiameter = new QDoubleSpinBox(ConfigureIADPage02);
        doubleSpinBox_tSphereDiameter->setObjectName(QStringLiteral("doubleSpinBox_tSphereDiameter"));
        doubleSpinBox_tSphereDiameter->setGeometry(QRect(510, 270, 81, 22));
        doubleSpinBox_tSphereDiameter->setMaximum(1000);
        doubleSpinBox_tSphereDiameter->setSingleStep(0.01);
        doubleSpinBox_tSphereDiameter->setValue(50);
        doubleSpinBox_tSamplePortDiameter = new QDoubleSpinBox(ConfigureIADPage02);
        doubleSpinBox_tSamplePortDiameter->setObjectName(QStringLiteral("doubleSpinBox_tSamplePortDiameter"));
        doubleSpinBox_tSamplePortDiameter->setGeometry(QRect(510, 300, 81, 22));
        doubleSpinBox_tSamplePortDiameter->setMaximum(100);
        doubleSpinBox_tSamplePortDiameter->setSingleStep(0.01);
        doubleSpinBox_tSamplePortDiameter->setValue(10);
        label_31 = new QLabel(ConfigureIADPage02);
        label_31->setObjectName(QStringLiteral("label_31"));
        label_31->setGeometry(QRect(10, 200, 151, 21));
        comboBox_calibrationStandard = new QComboBox(ConfigureIADPage02);
        comboBox_calibrationStandard->setObjectName(QStringLiteral("comboBox_calibrationStandard"));
        comboBox_calibrationStandard->setGeometry(QRect(170, 200, 111, 22));

        retranslateUi(ConfigureIADPage02);

        QMetaObject::connectSlotsByName(ConfigureIADPage02);
    } // setupUi

    void retranslateUi(QWidget *ConfigureIADPage02)
    {
        ConfigureIADPage02->setWindowTitle(QApplication::translate("ConfigureIADPage02", "Assistant", Q_NULLPTR));
        button_finish->setText(QApplication::translate("ConfigureIADPage02", "Finish", Q_NULLPTR));
        button_cancel->setText(QApplication::translate("ConfigureIADPage02", "Cancel", Q_NULLPTR));
        label_caption3->setText(QApplication::translate("ConfigureIADPage02", "Set the integrating spheres parameters for Inverse Adding-Doubling calculations.", Q_NULLPTR));
        label_step3->setText(QApplication::translate("ConfigureIADPage02", "Step 3:", Q_NULLPTR));
        label_2->setText(QApplication::translate("ConfigureIADPage02", "Index of refraction of sample:", Q_NULLPTR));
        label_3->setText(QApplication::translate("ConfigureIADPage02", "Index of refraction of top slide:", Q_NULLPTR));
        label_4->setText(QApplication::translate("ConfigureIADPage02", "Thickness of sample:", Q_NULLPTR));
        label_6->setText(QApplication::translate("ConfigureIADPage02", "mm", Q_NULLPTR));
        label_7->setText(QApplication::translate("ConfigureIADPage02", "Thickness of slides:", Q_NULLPTR));
        label_8->setText(QApplication::translate("ConfigureIADPage02", "mm", Q_NULLPTR));
        label_9->setText(QApplication::translate("ConfigureIADPage02", "Diameter of illumination beam:", Q_NULLPTR));
        label_10->setText(QApplication::translate("ConfigureIADPage02", "mm", Q_NULLPTR));
        label_reflectionSphere->setText(QApplication::translate("ConfigureIADPage02", "Reflection sphere", Q_NULLPTR));
        label_12->setText(QApplication::translate("ConfigureIADPage02", "Sphere diameter:", Q_NULLPTR));
        label_13->setText(QApplication::translate("ConfigureIADPage02", "mm", Q_NULLPTR));
        label_14->setText(QApplication::translate("ConfigureIADPage02", "Sample port diameter:", Q_NULLPTR));
        label_15->setText(QApplication::translate("ConfigureIADPage02", "mm", Q_NULLPTR));
        label_16->setText(QApplication::translate("ConfigureIADPage02", "Entrance port diameter:", Q_NULLPTR));
        label_17->setText(QApplication::translate("ConfigureIADPage02", "mm", Q_NULLPTR));
        label_18->setText(QApplication::translate("ConfigureIADPage02", "Detector port diameter:", Q_NULLPTR));
        label_19->setText(QApplication::translate("ConfigureIADPage02", "mm", Q_NULLPTR));
        comboBox_rSphereWallMaterial->clear();
        comboBox_rSphereWallMaterial->insertItems(0, QStringList()
         << QApplication::translate("ConfigureIADPage02", "Select material", Q_NULLPTR)
        );
        label_20->setText(QApplication::translate("ConfigureIADPage02", "Sphere wall material:", Q_NULLPTR));
        label_transmissionSphere->setText(QApplication::translate("ConfigureIADPage02", "Transmission sphere", Q_NULLPTR));
        label_22->setText(QApplication::translate("ConfigureIADPage02", "mm", Q_NULLPTR));
        label_23->setText(QApplication::translate("ConfigureIADPage02", "Entrance port diameter:", Q_NULLPTR));
        comboBox_tSphereWallMaterial->clear();
        comboBox_tSphereWallMaterial->insertItems(0, QStringList()
         << QApplication::translate("ConfigureIADPage02", "Select material", Q_NULLPTR)
        );
        label_24->setText(QApplication::translate("ConfigureIADPage02", "mm", Q_NULLPTR));
        label_25->setText(QApplication::translate("ConfigureIADPage02", "Sphere diameter:", Q_NULLPTR));
        label_26->setText(QApplication::translate("ConfigureIADPage02", "Sample port diameter:", Q_NULLPTR));
        label_27->setText(QApplication::translate("ConfigureIADPage02", "mm", Q_NULLPTR));
        label_28->setText(QApplication::translate("ConfigureIADPage02", "Sphere wall material:", Q_NULLPTR));
        label_29->setText(QApplication::translate("ConfigureIADPage02", "mm", Q_NULLPTR));
        label_30->setText(QApplication::translate("ConfigureIADPage02", "Detector port diameter:", Q_NULLPTR));
        label_31->setText(QApplication::translate("ConfigureIADPage02", "Calibration standard:", Q_NULLPTR));
        comboBox_calibrationStandard->clear();
        comboBox_calibrationStandard->insertItems(0, QStringList()
         << QApplication::translate("ConfigureIADPage02", "Select standard", Q_NULLPTR)
        );
    } // retranslateUi

};

namespace Ui {
    class ConfigureIADPage02: public Ui_ConfigureIADPage02 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IAD_CONFIGURE_PAGE02_H
