/********************************************************************************
** Form generated from reading UI file 'configpowermeter.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONFIGPOWERMETER_H
#define UI_CONFIGPOWERMETER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ConfigPowerMeter
{
public:
    QWidget *centralwidget;
    QLabel *instrumentInfoLabel;
    QLabel *instrumentAddressLabel;
    QGroupBox *radioButtonGroupBox;
    QGroupBox *groupBox;
    QLineEdit *powerDisplay;
    QLabel *powerDisplayUnit;
    QLabel *label_9;
    QLabel *label_11;
    QComboBox *powerUnitComboBox;
    QGroupBox *groupBox_2;
    QLineEdit *wavelengthDisplay;
    QLineEdit *minWavelengthDisplay;
    QLineEdit *maxWavelengthDisplay;
    QLabel *wavelengthDisplayUnitLabel;
    QLabel *minWavelengthUnitLabel;
    QLabel *maxWavelengthUnitLabel;
    QLabel *label_10;
    QLabel *wavelengthDisplay_2;
    QLabel *label_13;
    QLabel *label_14;
    QComboBox *wavelengthComboBox;
    QLineEdit *wavelengthEdit;
    QLabel *wavelengthEditUnitLabel;
    QGroupBox *groupBox_3;
    QPushButton *saveSettingsButton;
    QPushButton *loadSettingsButton;
    QPushButton *saveChangesButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *ConfigPowerMeter)
    {
        if (ConfigPowerMeter->objectName().isEmpty())
            ConfigPowerMeter->setObjectName(QString::fromUtf8("ConfigPowerMeter"));
        ConfigPowerMeter->resize(1024, 768);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(ConfigPowerMeter->sizePolicy().hasHeightForWidth());
        ConfigPowerMeter->setSizePolicy(sizePolicy);
        ConfigPowerMeter->setStyleSheet(QString::fromUtf8(""));
        centralwidget = new QWidget(ConfigPowerMeter);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        instrumentInfoLabel = new QLabel(centralwidget);
        instrumentInfoLabel->setObjectName(QString::fromUtf8("instrumentInfoLabel"));
        instrumentInfoLabel->setGeometry(QRect(10, 10, 771, 31));
        QFont font;
        font.setPointSize(12);
        instrumentInfoLabel->setFont(font);
        instrumentAddressLabel = new QLabel(centralwidget);
        instrumentAddressLabel->setObjectName(QString::fromUtf8("instrumentAddressLabel"));
        instrumentAddressLabel->setGeometry(QRect(10, 40, 771, 41));
        instrumentAddressLabel->setFont(font);
        radioButtonGroupBox = new QGroupBox(centralwidget);
        radioButtonGroupBox->setObjectName(QString::fromUtf8("radioButtonGroupBox"));
        radioButtonGroupBox->setGeometry(QRect(10, 100, 1001, 101));
        QFont font1;
        font1.setPointSize(14);
        radioButtonGroupBox->setFont(font1);
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(10, 230, 1001, 131));
        groupBox->setFont(font1);
        powerDisplay = new QLineEdit(groupBox);
        powerDisplay->setObjectName(QString::fromUtf8("powerDisplay"));
        powerDisplay->setEnabled(false);
        powerDisplay->setGeometry(QRect(350, 80, 211, 31));
        powerDisplay->setFont(font);
        powerDisplayUnit = new QLabel(groupBox);
        powerDisplayUnit->setObjectName(QString::fromUtf8("powerDisplayUnit"));
        powerDisplayUnit->setGeometry(QRect(580, 90, 51, 21));
        powerDisplayUnit->setFont(font);
        label_9 = new QLabel(groupBox);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(20, 30, 331, 31));
        label_9->setFont(font);
        label_11 = new QLabel(groupBox);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(20, 80, 331, 31));
        label_11->setFont(font);
        powerUnitComboBox = new QComboBox(groupBox);
        powerUnitComboBox->addItem(QString());
        powerUnitComboBox->addItem(QString());
        powerUnitComboBox->setObjectName(QString::fromUtf8("powerUnitComboBox"));
        powerUnitComboBox->setGeometry(QRect(350, 30, 121, 31));
        powerUnitComboBox->setFont(font);
        powerUnitComboBox->setStyleSheet(QString::fromUtf8(""));
        groupBox_2 = new QGroupBox(centralwidget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(10, 390, 1001, 281));
        groupBox_2->setFont(font1);
        wavelengthDisplay = new QLineEdit(groupBox_2);
        wavelengthDisplay->setObjectName(QString::fromUtf8("wavelengthDisplay"));
        wavelengthDisplay->setEnabled(false);
        wavelengthDisplay->setGeometry(QRect(350, 120, 211, 31));
        wavelengthDisplay->setFont(font);
        minWavelengthDisplay = new QLineEdit(groupBox_2);
        minWavelengthDisplay->setObjectName(QString::fromUtf8("minWavelengthDisplay"));
        minWavelengthDisplay->setEnabled(false);
        minWavelengthDisplay->setGeometry(QRect(350, 170, 211, 31));
        minWavelengthDisplay->setFont(font);
        maxWavelengthDisplay = new QLineEdit(groupBox_2);
        maxWavelengthDisplay->setObjectName(QString::fromUtf8("maxWavelengthDisplay"));
        maxWavelengthDisplay->setEnabled(false);
        maxWavelengthDisplay->setGeometry(QRect(350, 220, 211, 31));
        maxWavelengthDisplay->setFont(font);
        wavelengthDisplayUnitLabel = new QLabel(groupBox_2);
        wavelengthDisplayUnitLabel->setObjectName(QString::fromUtf8("wavelengthDisplayUnitLabel"));
        wavelengthDisplayUnitLabel->setGeometry(QRect(580, 130, 51, 21));
        wavelengthDisplayUnitLabel->setFont(font);
        minWavelengthUnitLabel = new QLabel(groupBox_2);
        minWavelengthUnitLabel->setObjectName(QString::fromUtf8("minWavelengthUnitLabel"));
        minWavelengthUnitLabel->setGeometry(QRect(580, 180, 51, 21));
        minWavelengthUnitLabel->setFont(font);
        maxWavelengthUnitLabel = new QLabel(groupBox_2);
        maxWavelengthUnitLabel->setObjectName(QString::fromUtf8("maxWavelengthUnitLabel"));
        maxWavelengthUnitLabel->setGeometry(QRect(580, 230, 51, 21));
        maxWavelengthUnitLabel->setFont(font);
        label_10 = new QLabel(groupBox_2);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(20, 70, 331, 31));
        label_10->setFont(font);
        wavelengthDisplay_2 = new QLabel(groupBox_2);
        wavelengthDisplay_2->setObjectName(QString::fromUtf8("wavelengthDisplay_2"));
        wavelengthDisplay_2->setGeometry(QRect(20, 120, 331, 31));
        wavelengthDisplay_2->setFont(font);
        label_13 = new QLabel(groupBox_2);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setGeometry(QRect(20, 170, 331, 31));
        label_13->setFont(font);
        label_14 = new QLabel(groupBox_2);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setGeometry(QRect(20, 220, 331, 31));
        label_14->setFont(font);
        wavelengthComboBox = new QComboBox(groupBox_2);
        wavelengthComboBox->addItem(QString());
        wavelengthComboBox->addItem(QString());
        wavelengthComboBox->addItem(QString());
        wavelengthComboBox->addItem(QString());
        wavelengthComboBox->addItem(QString());
        wavelengthComboBox->setObjectName(QString::fromUtf8("wavelengthComboBox"));
        wavelengthComboBox->setGeometry(QRect(350, 70, 121, 31));
        wavelengthComboBox->setFont(font);
        wavelengthEdit = new QLineEdit(groupBox_2);
        wavelengthEdit->setObjectName(QString::fromUtf8("wavelengthEdit"));
        wavelengthEdit->setEnabled(true);
        wavelengthEdit->setGeometry(QRect(660, 120, 211, 31));
        wavelengthEdit->setFont(font);
        wavelengthEditUnitLabel = new QLabel(groupBox_2);
        wavelengthEditUnitLabel->setObjectName(QString::fromUtf8("wavelengthEditUnitLabel"));
        wavelengthEditUnitLabel->setGeometry(QRect(890, 130, 81, 21));
        wavelengthEditUnitLabel->setFont(font);
        groupBox_3 = new QGroupBox(centralwidget);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setGeometry(QRect(790, 10, 221, 81));
        groupBox_3->setFont(font);
        saveSettingsButton = new QPushButton(groupBox_3);
        saveSettingsButton->setObjectName(QString::fromUtf8("saveSettingsButton"));
        saveSettingsButton->setGeometry(QRect(120, 30, 80, 41));
        loadSettingsButton = new QPushButton(groupBox_3);
        loadSettingsButton->setObjectName(QString::fromUtf8("loadSettingsButton"));
        loadSettingsButton->setGeometry(QRect(20, 30, 80, 41));
        saveChangesButton = new QPushButton(centralwidget);
        saveChangesButton->setObjectName(QString::fromUtf8("saveChangesButton"));
        saveChangesButton->setGeometry(QRect(820, 670, 191, 41));
        saveChangesButton->setFont(font);
        ConfigPowerMeter->setCentralWidget(centralwidget);
        groupBox_2->raise();
        groupBox->raise();
        instrumentInfoLabel->raise();
        instrumentAddressLabel->raise();
        radioButtonGroupBox->raise();
        groupBox_3->raise();
        saveChangesButton->raise();
        menubar = new QMenuBar(ConfigPowerMeter);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1024, 17));
        ConfigPowerMeter->setMenuBar(menubar);
        statusbar = new QStatusBar(ConfigPowerMeter);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        ConfigPowerMeter->setStatusBar(statusbar);

        retranslateUi(ConfigPowerMeter);

        wavelengthComboBox->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(ConfigPowerMeter);
    } // setupUi

    void retranslateUi(QMainWindow *ConfigPowerMeter)
    {
        ConfigPowerMeter->setWindowTitle(QCoreApplication::translate("ConfigPowerMeter", "MainWindow", nullptr));
        instrumentInfoLabel->setText(QCoreApplication::translate("ConfigPowerMeter", "Instrument: ", nullptr));
        instrumentAddressLabel->setText(QCoreApplication::translate("ConfigPowerMeter", "Address: ", nullptr));
        radioButtonGroupBox->setTitle(QCoreApplication::translate("ConfigPowerMeter", "Select Channel/Slot", nullptr));
        groupBox->setTitle(QCoreApplication::translate("ConfigPowerMeter", "Power Reading", nullptr));
        powerDisplay->setText(QString());
        powerDisplayUnit->setText(QCoreApplication::translate("ConfigPowerMeter", "(unit)", nullptr));
        label_9->setText(QCoreApplication::translate("ConfigPowerMeter", "Power Unit", nullptr));
        label_11->setText(QCoreApplication::translate("ConfigPowerMeter", "Power", nullptr));
        powerUnitComboBox->setItemText(0, QCoreApplication::translate("ConfigPowerMeter", "Watt", nullptr));
        powerUnitComboBox->setItemText(1, QCoreApplication::translate("ConfigPowerMeter", "dBm", nullptr));

        groupBox_2->setTitle(QCoreApplication::translate("ConfigPowerMeter", "Adjust Wavelength Settings", nullptr));
        wavelengthDisplay->setText(QString());
        minWavelengthDisplay->setText(QString());
        maxWavelengthDisplay->setText(QString());
        wavelengthDisplayUnitLabel->setText(QCoreApplication::translate("ConfigPowerMeter", "(unit)", nullptr));
        minWavelengthUnitLabel->setText(QCoreApplication::translate("ConfigPowerMeter", "(unit)", nullptr));
        maxWavelengthUnitLabel->setText(QCoreApplication::translate("ConfigPowerMeter", "(unit)", nullptr));
        label_10->setText(QCoreApplication::translate("ConfigPowerMeter", "Wavelength Unit", nullptr));
        wavelengthDisplay_2->setText(QCoreApplication::translate("ConfigPowerMeter", "Wavelength", nullptr));
        label_13->setText(QCoreApplication::translate("ConfigPowerMeter", "Min Wavelength", nullptr));
        label_14->setText(QCoreApplication::translate("ConfigPowerMeter", "Max Wavelength", nullptr));
        wavelengthComboBox->setItemText(0, QCoreApplication::translate("ConfigPowerMeter", "m", nullptr));
        wavelengthComboBox->setItemText(1, QCoreApplication::translate("ConfigPowerMeter", "mm", nullptr));
        wavelengthComboBox->setItemText(2, QCoreApplication::translate("ConfigPowerMeter", "um", nullptr));
        wavelengthComboBox->setItemText(3, QCoreApplication::translate("ConfigPowerMeter", "nm", nullptr));
        wavelengthComboBox->setItemText(4, QCoreApplication::translate("ConfigPowerMeter", "pm", nullptr));

        wavelengthEditUnitLabel->setText(QCoreApplication::translate("ConfigPowerMeter", "(unit)", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("ConfigPowerMeter", "Configuration", nullptr));
        saveSettingsButton->setText(QCoreApplication::translate("ConfigPowerMeter", "Save", nullptr));
        loadSettingsButton->setText(QCoreApplication::translate("ConfigPowerMeter", "Load", nullptr));
        saveChangesButton->setText(QCoreApplication::translate("ConfigPowerMeter", "Submit Changes", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ConfigPowerMeter: public Ui_ConfigPowerMeter {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONFIGPOWERMETER_H
