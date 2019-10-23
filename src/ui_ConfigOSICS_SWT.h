/********************************************************************************
** Form generated from reading UI file 'ConfigOSICS_SWT.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONFIGOSICS_SWT_H
#define UI_CONFIGOSICS_SWT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ConfigOSICS_SWT
{
public:
    QWidget *centralwidget;
    QLabel *instrumentAddressLabel;
    QGroupBox *groupBox_3;
    QPushButton *saveSettingsButton;
    QPushButton *loadSettingsButton;
    QLabel *instrumentInfoLabel;
    QPushButton *saveChangesButton;
    QGroupBox *powerSettingsGroup;
    QLabel *label;
    QComboBox *powerUnitComboBox;
    QLineEdit *powerDisplay;
    QLineEdit *minPowerDisplay;
    QLineEdit *maxPowerDisplay;
    QLineEdit *powerEdit;
    QLabel *label_11;
    QLabel *label_5;
    QLabel *label_10;
    QLabel *powerEditUnitLabel;
    QLabel *powerDisplayUnitLabel;
    QLabel *minPowerDisplayUnitLabel;
    QLabel *maxPowerDisplayUnitLabel;
    QLabel *label_2;
    QLineEdit *outputStatusDisplay;
    QPushButton *toggleOutputButton;
    QGroupBox *wavelengthSettingsGroup;
    QLineEdit *wavelengthDisplay;
    QLineEdit *minWavelengthDisplay;
    QLineEdit *maxWavelengthDisplay;
    QLineEdit *wavelengthEdit;
    QLabel *label_13;
    QLabel *label_14;
    QLabel *label_15;
    QLabel *wavelengthEditUnitLabel;
    QLabel *wavelengthDisplayUnitLabel;
    QLabel *minWavelengthDisplayUnitLabel;
    QLabel *maxWavelengthDisplayUnitLabel;
    QGroupBox *groupBox_4;
    QRadioButton *opModeRadioBtnSwitch;
    QRadioButton *opModeRadioBtnFullBand;
    QGroupBox *groupBox_5;
    QSplitter *splitter;
    QRadioButton *ch1Radio;
    QRadioButton *ch2Radio;
    QRadioButton *ch3Radio;
    QRadioButton *ch4Radio;
    QGroupBox *frequencySettingsGroup;
    QLabel *label_16;
    QLineEdit *frequencyDisplay;
    QLineEdit *minFrequencyDisplay;
    QLineEdit *maxFrequencyDisplay;
    QLineEdit *frequencyEdit;
    QLabel *label_17;
    QLabel *label_18;
    QLabel *label_19;
    QLabel *frequencyEditUnitLabel;
    QLabel *frequencyDisplayUnitLabel;
    QLabel *minFrequencyDisplayUnitLabel;
    QLabel *maxFrequencyDisplayUnitLabel;
    QComboBox *frequencyUnitComboBox;
    QMenuBar *menubar;
    QStatusBar *statusbar;
    QButtonGroup *buttonGroup_2;
    QButtonGroup *buttonGroup_3;

    void setupUi(QMainWindow *ConfigOSICS_SWT)
    {
        if (ConfigOSICS_SWT->objectName().isEmpty())
            ConfigOSICS_SWT->setObjectName(QString::fromUtf8("ConfigOSICS_SWT"));
        ConfigOSICS_SWT->resize(1024, 768);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(ConfigOSICS_SWT->sizePolicy().hasHeightForWidth());
        ConfigOSICS_SWT->setSizePolicy(sizePolicy);
        centralwidget = new QWidget(ConfigOSICS_SWT);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        instrumentAddressLabel = new QLabel(centralwidget);
        instrumentAddressLabel->setObjectName(QString::fromUtf8("instrumentAddressLabel"));
        instrumentAddressLabel->setGeometry(QRect(10, 30, 981, 31));
        QFont font;
        font.setPointSize(12);
        instrumentAddressLabel->setFont(font);
        groupBox_3 = new QGroupBox(centralwidget);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setGeometry(QRect(780, 0, 221, 81));
        groupBox_3->setFont(font);
        saveSettingsButton = new QPushButton(groupBox_3);
        saveSettingsButton->setObjectName(QString::fromUtf8("saveSettingsButton"));
        saveSettingsButton->setGeometry(QRect(120, 30, 80, 41));
        loadSettingsButton = new QPushButton(groupBox_3);
        loadSettingsButton->setObjectName(QString::fromUtf8("loadSettingsButton"));
        loadSettingsButton->setGeometry(QRect(20, 30, 80, 41));
        instrumentInfoLabel = new QLabel(centralwidget);
        instrumentInfoLabel->setObjectName(QString::fromUtf8("instrumentInfoLabel"));
        instrumentInfoLabel->setGeometry(QRect(10, 10, 991, 21));
        instrumentInfoLabel->setFont(font);
        saveChangesButton = new QPushButton(centralwidget);
        saveChangesButton->setObjectName(QString::fromUtf8("saveChangesButton"));
        saveChangesButton->setGeometry(QRect(810, 660, 191, 41));
        saveChangesButton->setFont(font);
        powerSettingsGroup = new QGroupBox(centralwidget);
        powerSettingsGroup->setObjectName(QString::fromUtf8("powerSettingsGroup"));
        powerSettingsGroup->setGeometry(QRect(10, 240, 1001, 211));
        powerSettingsGroup->setFont(font);
        label = new QLabel(powerSettingsGroup);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 70, 201, 21));
        powerUnitComboBox = new QComboBox(powerSettingsGroup);
        powerUnitComboBox->addItem(QString());
        powerUnitComboBox->addItem(QString());
        powerUnitComboBox->setObjectName(QString::fromUtf8("powerUnitComboBox"));
        powerUnitComboBox->setGeometry(QRect(170, 60, 111, 31));
        powerDisplay = new QLineEdit(powerSettingsGroup);
        powerDisplay->setObjectName(QString::fromUtf8("powerDisplay"));
        powerDisplay->setEnabled(false);
        powerDisplay->setGeometry(QRect(170, 90, 211, 31));
        powerDisplay->setStyleSheet(QString::fromUtf8(""));
        minPowerDisplay = new QLineEdit(powerSettingsGroup);
        minPowerDisplay->setObjectName(QString::fromUtf8("minPowerDisplay"));
        minPowerDisplay->setEnabled(false);
        minPowerDisplay->setGeometry(QRect(170, 120, 211, 31));
        minPowerDisplay->setStyleSheet(QString::fromUtf8(""));
        maxPowerDisplay = new QLineEdit(powerSettingsGroup);
        maxPowerDisplay->setObjectName(QString::fromUtf8("maxPowerDisplay"));
        maxPowerDisplay->setEnabled(false);
        maxPowerDisplay->setGeometry(QRect(170, 150, 211, 31));
        maxPowerDisplay->setStyleSheet(QString::fromUtf8(""));
        powerEdit = new QLineEdit(powerSettingsGroup);
        powerEdit->setObjectName(QString::fromUtf8("powerEdit"));
        powerEdit->setEnabled(true);
        powerEdit->setGeometry(QRect(480, 90, 211, 31));
        label_11 = new QLabel(powerSettingsGroup);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(10, 100, 201, 21));
        label_11->setFont(font);
        label_5 = new QLabel(powerSettingsGroup);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(10, 160, 201, 21));
        label_5->setFont(font);
        label_10 = new QLabel(powerSettingsGroup);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(10, 130, 201, 21));
        label_10->setFont(font);
        powerEditUnitLabel = new QLabel(powerSettingsGroup);
        powerEditUnitLabel->setObjectName(QString::fromUtf8("powerEditUnitLabel"));
        powerEditUnitLabel->setGeometry(QRect(700, 100, 61, 21));
        powerDisplayUnitLabel = new QLabel(powerSettingsGroup);
        powerDisplayUnitLabel->setObjectName(QString::fromUtf8("powerDisplayUnitLabel"));
        powerDisplayUnitLabel->setGeometry(QRect(390, 100, 61, 21));
        minPowerDisplayUnitLabel = new QLabel(powerSettingsGroup);
        minPowerDisplayUnitLabel->setObjectName(QString::fromUtf8("minPowerDisplayUnitLabel"));
        minPowerDisplayUnitLabel->setGeometry(QRect(390, 130, 61, 21));
        maxPowerDisplayUnitLabel = new QLabel(powerSettingsGroup);
        maxPowerDisplayUnitLabel->setObjectName(QString::fromUtf8("maxPowerDisplayUnitLabel"));
        maxPowerDisplayUnitLabel->setGeometry(QRect(390, 160, 61, 21));
        label_2 = new QLabel(powerSettingsGroup);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(10, 30, 201, 21));
        outputStatusDisplay = new QLineEdit(powerSettingsGroup);
        outputStatusDisplay->setObjectName(QString::fromUtf8("outputStatusDisplay"));
        outputStatusDisplay->setEnabled(false);
        outputStatusDisplay->setGeometry(QRect(170, 30, 211, 31));
        outputStatusDisplay->setStyleSheet(QString::fromUtf8(""));
        toggleOutputButton = new QPushButton(powerSettingsGroup);
        toggleOutputButton->setObjectName(QString::fromUtf8("toggleOutputButton"));
        toggleOutputButton->setGeometry(QRect(480, 30, 191, 31));
        toggleOutputButton->setFont(font);
        wavelengthSettingsGroup = new QGroupBox(centralwidget);
        wavelengthSettingsGroup->setObjectName(QString::fromUtf8("wavelengthSettingsGroup"));
        wavelengthSettingsGroup->setGeometry(QRect(10, 470, 491, 171));
        wavelengthSettingsGroup->setFont(font);
        wavelengthDisplay = new QLineEdit(wavelengthSettingsGroup);
        wavelengthDisplay->setObjectName(QString::fromUtf8("wavelengthDisplay"));
        wavelengthDisplay->setEnabled(false);
        wavelengthDisplay->setGeometry(QRect(150, 30, 111, 31));
        wavelengthDisplay->setStyleSheet(QString::fromUtf8(""));
        minWavelengthDisplay = new QLineEdit(wavelengthSettingsGroup);
        minWavelengthDisplay->setObjectName(QString::fromUtf8("minWavelengthDisplay"));
        minWavelengthDisplay->setEnabled(false);
        minWavelengthDisplay->setGeometry(QRect(150, 60, 111, 31));
        minWavelengthDisplay->setStyleSheet(QString::fromUtf8(""));
        maxWavelengthDisplay = new QLineEdit(wavelengthSettingsGroup);
        maxWavelengthDisplay->setObjectName(QString::fromUtf8("maxWavelengthDisplay"));
        maxWavelengthDisplay->setEnabled(false);
        maxWavelengthDisplay->setGeometry(QRect(150, 90, 111, 31));
        maxWavelengthDisplay->setStyleSheet(QString::fromUtf8(""));
        wavelengthEdit = new QLineEdit(wavelengthSettingsGroup);
        wavelengthEdit->setObjectName(QString::fromUtf8("wavelengthEdit"));
        wavelengthEdit->setEnabled(true);
        wavelengthEdit->setGeometry(QRect(320, 30, 111, 31));
        label_13 = new QLabel(wavelengthSettingsGroup);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setGeometry(QRect(10, 40, 201, 21));
        label_13->setFont(font);
        label_14 = new QLabel(wavelengthSettingsGroup);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setGeometry(QRect(10, 100, 201, 21));
        label_14->setFont(font);
        label_15 = new QLabel(wavelengthSettingsGroup);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setGeometry(QRect(10, 70, 201, 21));
        label_15->setFont(font);
        wavelengthEditUnitLabel = new QLabel(wavelengthSettingsGroup);
        wavelengthEditUnitLabel->setObjectName(QString::fromUtf8("wavelengthEditUnitLabel"));
        wavelengthEditUnitLabel->setGeometry(QRect(440, 40, 61, 21));
        wavelengthDisplayUnitLabel = new QLabel(wavelengthSettingsGroup);
        wavelengthDisplayUnitLabel->setObjectName(QString::fromUtf8("wavelengthDisplayUnitLabel"));
        wavelengthDisplayUnitLabel->setGeometry(QRect(270, 40, 61, 21));
        minWavelengthDisplayUnitLabel = new QLabel(wavelengthSettingsGroup);
        minWavelengthDisplayUnitLabel->setObjectName(QString::fromUtf8("minWavelengthDisplayUnitLabel"));
        minWavelengthDisplayUnitLabel->setGeometry(QRect(270, 70, 61, 21));
        maxWavelengthDisplayUnitLabel = new QLabel(wavelengthSettingsGroup);
        maxWavelengthDisplayUnitLabel->setObjectName(QString::fromUtf8("maxWavelengthDisplayUnitLabel"));
        maxWavelengthDisplayUnitLabel->setGeometry(QRect(270, 100, 61, 21));
        groupBox_4 = new QGroupBox(centralwidget);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        groupBox_4->setGeometry(QRect(10, 80, 1001, 61));
        groupBox_4->setFont(font);
        opModeRadioBtnSwitch = new QRadioButton(groupBox_4);
        buttonGroup_3 = new QButtonGroup(ConfigOSICS_SWT);
        buttonGroup_3->setObjectName(QString::fromUtf8("buttonGroup_3"));
        buttonGroup_3->addButton(opModeRadioBtnSwitch);
        opModeRadioBtnSwitch->setObjectName(QString::fromUtf8("opModeRadioBtnSwitch"));
        opModeRadioBtnSwitch->setGeometry(QRect(260, 30, 459, 21));
        opModeRadioBtnSwitch->setFont(font);
        opModeRadioBtnFullBand = new QRadioButton(groupBox_4);
        buttonGroup_3->addButton(opModeRadioBtnFullBand);
        opModeRadioBtnFullBand->setObjectName(QString::fromUtf8("opModeRadioBtnFullBand"));
        opModeRadioBtnFullBand->setGeometry(QRect(20, 30, 228, 21));
        opModeRadioBtnFullBand->setFont(font);
        opModeRadioBtnFullBand->setChecked(true);
        groupBox_5 = new QGroupBox(centralwidget);
        groupBox_5->setObjectName(QString::fromUtf8("groupBox_5"));
        groupBox_5->setGeometry(QRect(10, 160, 1001, 61));
        groupBox_5->setFont(font);
        splitter = new QSplitter(groupBox_5);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setGeometry(QRect(10, 30, 571, 21));
        splitter->setOrientation(Qt::Horizontal);
        ch1Radio = new QRadioButton(splitter);
        buttonGroup_2 = new QButtonGroup(ConfigOSICS_SWT);
        buttonGroup_2->setObjectName(QString::fromUtf8("buttonGroup_2"));
        buttonGroup_2->addButton(ch1Radio);
        ch1Radio->setObjectName(QString::fromUtf8("ch1Radio"));
        ch1Radio->setFont(font);
        ch1Radio->setChecked(true);
        splitter->addWidget(ch1Radio);
        ch2Radio = new QRadioButton(splitter);
        buttonGroup_2->addButton(ch2Radio);
        ch2Radio->setObjectName(QString::fromUtf8("ch2Radio"));
        ch2Radio->setFont(font);
        splitter->addWidget(ch2Radio);
        ch3Radio = new QRadioButton(splitter);
        buttonGroup_2->addButton(ch3Radio);
        ch3Radio->setObjectName(QString::fromUtf8("ch3Radio"));
        ch3Radio->setFont(font);
        splitter->addWidget(ch3Radio);
        ch4Radio = new QRadioButton(splitter);
        buttonGroup_2->addButton(ch4Radio);
        ch4Radio->setObjectName(QString::fromUtf8("ch4Radio"));
        ch4Radio->setFont(font);
        splitter->addWidget(ch4Radio);
        frequencySettingsGroup = new QGroupBox(centralwidget);
        frequencySettingsGroup->setObjectName(QString::fromUtf8("frequencySettingsGroup"));
        frequencySettingsGroup->setGeometry(QRect(520, 470, 491, 171));
        frequencySettingsGroup->setFont(font);
        label_16 = new QLabel(frequencySettingsGroup);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        label_16->setGeometry(QRect(10, 40, 201, 21));
        frequencyDisplay = new QLineEdit(frequencySettingsGroup);
        frequencyDisplay->setObjectName(QString::fromUtf8("frequencyDisplay"));
        frequencyDisplay->setEnabled(false);
        frequencyDisplay->setGeometry(QRect(150, 60, 111, 31));
        frequencyDisplay->setStyleSheet(QString::fromUtf8(""));
        minFrequencyDisplay = new QLineEdit(frequencySettingsGroup);
        minFrequencyDisplay->setObjectName(QString::fromUtf8("minFrequencyDisplay"));
        minFrequencyDisplay->setEnabled(false);
        minFrequencyDisplay->setGeometry(QRect(150, 90, 111, 31));
        minFrequencyDisplay->setStyleSheet(QString::fromUtf8(""));
        maxFrequencyDisplay = new QLineEdit(frequencySettingsGroup);
        maxFrequencyDisplay->setObjectName(QString::fromUtf8("maxFrequencyDisplay"));
        maxFrequencyDisplay->setEnabled(false);
        maxFrequencyDisplay->setGeometry(QRect(150, 120, 111, 31));
        maxFrequencyDisplay->setStyleSheet(QString::fromUtf8(""));
        frequencyEdit = new QLineEdit(frequencySettingsGroup);
        frequencyEdit->setObjectName(QString::fromUtf8("frequencyEdit"));
        frequencyEdit->setEnabled(true);
        frequencyEdit->setGeometry(QRect(320, 60, 111, 31));
        label_17 = new QLabel(frequencySettingsGroup);
        label_17->setObjectName(QString::fromUtf8("label_17"));
        label_17->setGeometry(QRect(10, 70, 201, 21));
        label_17->setFont(font);
        label_18 = new QLabel(frequencySettingsGroup);
        label_18->setObjectName(QString::fromUtf8("label_18"));
        label_18->setGeometry(QRect(10, 130, 201, 21));
        label_18->setFont(font);
        label_19 = new QLabel(frequencySettingsGroup);
        label_19->setObjectName(QString::fromUtf8("label_19"));
        label_19->setGeometry(QRect(10, 100, 201, 21));
        label_19->setFont(font);
        frequencyEditUnitLabel = new QLabel(frequencySettingsGroup);
        frequencyEditUnitLabel->setObjectName(QString::fromUtf8("frequencyEditUnitLabel"));
        frequencyEditUnitLabel->setGeometry(QRect(440, 70, 61, 21));
        frequencyDisplayUnitLabel = new QLabel(frequencySettingsGroup);
        frequencyDisplayUnitLabel->setObjectName(QString::fromUtf8("frequencyDisplayUnitLabel"));
        frequencyDisplayUnitLabel->setGeometry(QRect(270, 70, 61, 21));
        minFrequencyDisplayUnitLabel = new QLabel(frequencySettingsGroup);
        minFrequencyDisplayUnitLabel->setObjectName(QString::fromUtf8("minFrequencyDisplayUnitLabel"));
        minFrequencyDisplayUnitLabel->setGeometry(QRect(270, 100, 61, 21));
        maxFrequencyDisplayUnitLabel = new QLabel(frequencySettingsGroup);
        maxFrequencyDisplayUnitLabel->setObjectName(QString::fromUtf8("maxFrequencyDisplayUnitLabel"));
        maxFrequencyDisplayUnitLabel->setGeometry(QRect(270, 130, 61, 21));
        frequencyUnitComboBox = new QComboBox(frequencySettingsGroup);
        frequencyUnitComboBox->addItem(QString());
        frequencyUnitComboBox->addItem(QString());
        frequencyUnitComboBox->addItem(QString());
        frequencyUnitComboBox->setObjectName(QString::fromUtf8("frequencyUnitComboBox"));
        frequencyUnitComboBox->setGeometry(QRect(150, 30, 111, 31));
        ConfigOSICS_SWT->setCentralWidget(centralwidget);
        menubar = new QMenuBar(ConfigOSICS_SWT);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1024, 17));
        ConfigOSICS_SWT->setMenuBar(menubar);
        statusbar = new QStatusBar(ConfigOSICS_SWT);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        ConfigOSICS_SWT->setStatusBar(statusbar);

        retranslateUi(ConfigOSICS_SWT);

        QMetaObject::connectSlotsByName(ConfigOSICS_SWT);
    } // setupUi

    void retranslateUi(QMainWindow *ConfigOSICS_SWT)
    {
        ConfigOSICS_SWT->setWindowTitle(QCoreApplication::translate("ConfigOSICS_SWT", "MainWindow", nullptr));
        instrumentAddressLabel->setText(QCoreApplication::translate("ConfigOSICS_SWT", "Address: ", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("ConfigOSICS_SWT", "Configuration", nullptr));
        saveSettingsButton->setText(QCoreApplication::translate("ConfigOSICS_SWT", "Save", nullptr));
        loadSettingsButton->setText(QCoreApplication::translate("ConfigOSICS_SWT", "Load", nullptr));
        instrumentInfoLabel->setText(QCoreApplication::translate("ConfigOSICS_SWT", "Instrument: ", nullptr));
        saveChangesButton->setText(QCoreApplication::translate("ConfigOSICS_SWT", "Submit Changes", nullptr));
        powerSettingsGroup->setTitle(QCoreApplication::translate("ConfigOSICS_SWT", "Power Settings", nullptr));
        label->setText(QCoreApplication::translate("ConfigOSICS_SWT", "Power Unit", nullptr));
        powerUnitComboBox->setItemText(0, QCoreApplication::translate("ConfigOSICS_SWT", "dBm", nullptr));
        powerUnitComboBox->setItemText(1, QCoreApplication::translate("ConfigOSICS_SWT", "Watt", nullptr));

        label_11->setText(QCoreApplication::translate("ConfigOSICS_SWT", "Output Power", nullptr));
        label_5->setText(QCoreApplication::translate("ConfigOSICS_SWT", "Max Output Power", nullptr));
        label_10->setText(QCoreApplication::translate("ConfigOSICS_SWT", "Min Output Power", nullptr));
        powerEditUnitLabel->setText(QCoreApplication::translate("ConfigOSICS_SWT", "(unit)", nullptr));
        powerDisplayUnitLabel->setText(QCoreApplication::translate("ConfigOSICS_SWT", "(unit)", nullptr));
        minPowerDisplayUnitLabel->setText(QCoreApplication::translate("ConfigOSICS_SWT", "(unit)", nullptr));
        maxPowerDisplayUnitLabel->setText(QCoreApplication::translate("ConfigOSICS_SWT", "(unit)", nullptr));
        label_2->setText(QCoreApplication::translate("ConfigOSICS_SWT", "Output Status", nullptr));
        toggleOutputButton->setText(QCoreApplication::translate("ConfigOSICS_SWT", "Toggle Switch Output", nullptr));
        wavelengthSettingsGroup->setTitle(QCoreApplication::translate("ConfigOSICS_SWT", "Wavelength Settings", nullptr));
        label_13->setText(QCoreApplication::translate("ConfigOSICS_SWT", "Wavelength", nullptr));
        label_14->setText(QCoreApplication::translate("ConfigOSICS_SWT", "Max Wavelength", nullptr));
        label_15->setText(QCoreApplication::translate("ConfigOSICS_SWT", "Min Wavelength", nullptr));
        wavelengthEditUnitLabel->setText(QCoreApplication::translate("ConfigOSICS_SWT", "nm", nullptr));
        wavelengthDisplayUnitLabel->setText(QCoreApplication::translate("ConfigOSICS_SWT", "nm", nullptr));
        minWavelengthDisplayUnitLabel->setText(QCoreApplication::translate("ConfigOSICS_SWT", "nm", nullptr));
        maxWavelengthDisplayUnitLabel->setText(QCoreApplication::translate("ConfigOSICS_SWT", "nm", nullptr));
        groupBox_4->setTitle(QCoreApplication::translate("ConfigOSICS_SWT", "Operating Mode", nullptr));
        opModeRadioBtnSwitch->setText(QCoreApplication::translate("ConfigOSICS_SWT", "Switch", nullptr));
        opModeRadioBtnFullBand->setText(QCoreApplication::translate("ConfigOSICS_SWT", "Full-band", nullptr));
        groupBox_5->setTitle(QCoreApplication::translate("ConfigOSICS_SWT", "Active Channel Settings", nullptr));
        ch1Radio->setText(QCoreApplication::translate("ConfigOSICS_SWT", "Channel 1", nullptr));
        ch2Radio->setText(QCoreApplication::translate("ConfigOSICS_SWT", "Channel 2", nullptr));
        ch3Radio->setText(QCoreApplication::translate("ConfigOSICS_SWT", "Channel 3", nullptr));
        ch4Radio->setText(QCoreApplication::translate("ConfigOSICS_SWT", "Channel 4", nullptr));
        frequencySettingsGroup->setTitle(QCoreApplication::translate("ConfigOSICS_SWT", "Frequency Settings", nullptr));
        label_16->setText(QCoreApplication::translate("ConfigOSICS_SWT", "Frequency Unit", nullptr));
        label_17->setText(QCoreApplication::translate("ConfigOSICS_SWT", "Frequency", nullptr));
        label_18->setText(QCoreApplication::translate("ConfigOSICS_SWT", "Max Frequency", nullptr));
        label_19->setText(QCoreApplication::translate("ConfigOSICS_SWT", "Min Frequency", nullptr));
        frequencyEditUnitLabel->setText(QCoreApplication::translate("ConfigOSICS_SWT", "(unit)", nullptr));
        frequencyDisplayUnitLabel->setText(QCoreApplication::translate("ConfigOSICS_SWT", "(unit)", nullptr));
        minFrequencyDisplayUnitLabel->setText(QCoreApplication::translate("ConfigOSICS_SWT", "(unit)", nullptr));
        maxFrequencyDisplayUnitLabel->setText(QCoreApplication::translate("ConfigOSICS_SWT", "(unit)", nullptr));
        frequencyUnitComboBox->setItemText(0, QCoreApplication::translate("ConfigOSICS_SWT", "THz", nullptr));
        frequencyUnitComboBox->setItemText(1, QCoreApplication::translate("ConfigOSICS_SWT", "GHz", nullptr));
        frequencyUnitComboBox->setItemText(2, QCoreApplication::translate("ConfigOSICS_SWT", "MHz", nullptr));

    } // retranslateUi

};

namespace Ui {
    class ConfigOSICS_SWT: public Ui_ConfigOSICS_SWT {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONFIGOSICS_SWT_H
