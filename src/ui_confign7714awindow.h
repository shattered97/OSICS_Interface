/********************************************************************************
** Form generated from reading UI file 'confign7714awindow.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONFIGN7714AWINDOW_H
#define UI_CONFIGN7714AWINDOW_H

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

class Ui_ConfigN7714AWindow
{
public:
    QWidget *centralwidget;
    QLabel *label;
    QLabel *label_2;
    QComboBox *powerUnitComboBox;
    QLineEdit *laserStateDisplay;
    QPushButton *togglePowerButton;
    QLabel *label_3;
    QLineEdit *laserOutputPowerDisplay;
    QLabel *powerDisplayUnitLabel;
    QLineEdit *laserOutputPowerEdit;
    QLabel *powerUnitEditLabel;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QLineEdit *laserWavelengthDisplay;
    QLabel *label_9;
    QComboBox *wavelengthUnitComboBox;
    QLineEdit *minWavelengthDisplay;
    QLabel *label_10;
    QLineEdit *maxWavelengthDisplay;
    QLabel *label_11;
    QLabel *wavelengthEditUnitLabel;
    QLineEdit *laserWavelengthEdit;
    QLabel *label_13;
    QLineEdit *laserFrequencyDisplay;
    QLabel *label_14;
    QLineEdit *laserFrequencyEdit;
    QLabel *frequencyEditUnitLabel;
    QLabel *label_16;
    QComboBox *frequencyUnitComboBox;
    QLabel *wavelengthDisplayUnitLabel;
    QLabel *minWavlengthUnitLabel;
    QLabel *maxWavelengthUnitLabel;
    QLabel *laserFrequencyDisplayUnitLabel;
    QLabel *minFrequencyUnitLabel;
    QLineEdit *minFrequencyDisplay;
    QLabel *maxFrequencyUnitLabel;
    QLabel *label_23;
    QLabel *label_24;
    QLineEdit *maxFrequencyDisplay;
    QLineEdit *laserMaxPowerDisplay;
    QLabel *label_25;
    QLineEdit *laserMinPowerDisplay;
    QLabel *label_26;
    QLabel *minPowerDisplayUnitLabel;
    QLabel *maxPowerDisplayUnitLabel;
    QLabel *instrumentInfoLabel;
    QLabel *instrumentAddressLabel;
    QSplitter *splitter;
    QRadioButton *slot1RadioBtn;
    QRadioButton *slot2RadioBtn;
    QRadioButton *slot3RadioBtn;
    QRadioButton *slot4RadioBtn;
    QPushButton *saveChangesButton;
    QGroupBox *groupBox_3;
    QPushButton *saveSettingsButton;
    QPushButton *loadSettingsButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;
    QButtonGroup *slotRadioButtonGroup;

    void setupUi(QMainWindow *ConfigN7714AWindow)
    {
        if (ConfigN7714AWindow->objectName().isEmpty())
            ConfigN7714AWindow->setObjectName(QString::fromUtf8("ConfigN7714AWindow"));
        ConfigN7714AWindow->resize(1024, 768);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(ConfigN7714AWindow->sizePolicy().hasHeightForWidth());
        ConfigN7714AWindow->setSizePolicy(sizePolicy);
        centralwidget = new QWidget(ConfigN7714AWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(40, 150, 201, 21));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(40, 265, 201, 21));
        powerUnitComboBox = new QComboBox(centralwidget);
        powerUnitComboBox->addItem(QString());
        powerUnitComboBox->addItem(QString());
        powerUnitComboBox->setObjectName(QString::fromUtf8("powerUnitComboBox"));
        powerUnitComboBox->setGeometry(QRect(240, 140, 111, 31));
        laserStateDisplay = new QLineEdit(centralwidget);
        laserStateDisplay->setObjectName(QString::fromUtf8("laserStateDisplay"));
        laserStateDisplay->setEnabled(false);
        laserStateDisplay->setGeometry(QRect(240, 260, 211, 31));
        togglePowerButton = new QPushButton(centralwidget);
        togglePowerButton->setObjectName(QString::fromUtf8("togglePowerButton"));
        togglePowerButton->setGeometry(QRect(660, 260, 211, 31));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(40, 175, 201, 21));
        laserOutputPowerDisplay = new QLineEdit(centralwidget);
        laserOutputPowerDisplay->setObjectName(QString::fromUtf8("laserOutputPowerDisplay"));
        laserOutputPowerDisplay->setEnabled(false);
        laserOutputPowerDisplay->setGeometry(QRect(240, 170, 211, 31));
        laserOutputPowerDisplay->setStyleSheet(QString::fromUtf8(""));
        powerDisplayUnitLabel = new QLabel(centralwidget);
        powerDisplayUnitLabel->setObjectName(QString::fromUtf8("powerDisplayUnitLabel"));
        powerDisplayUnitLabel->setGeometry(QRect(460, 180, 61, 21));
        laserOutputPowerEdit = new QLineEdit(centralwidget);
        laserOutputPowerEdit->setObjectName(QString::fromUtf8("laserOutputPowerEdit"));
        laserOutputPowerEdit->setEnabled(true);
        laserOutputPowerEdit->setGeometry(QRect(660, 170, 211, 31));
        powerUnitEditLabel = new QLabel(centralwidget);
        powerUnitEditLabel->setObjectName(QString::fromUtf8("powerUnitEditLabel"));
        powerUnitEditLabel->setGeometry(QRect(880, 180, 81, 21));
        label_6 = new QLabel(centralwidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(10, 90, 201, 31));
        QFont font;
        font.setPointSize(12);
        label_6->setFont(font);
        label_7 = new QLabel(centralwidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(10, 340, 261, 16));
        label_7->setFont(font);
        label_8 = new QLabel(centralwidget);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(30, 400, 181, 21));
        laserWavelengthDisplay = new QLineEdit(centralwidget);
        laserWavelengthDisplay->setObjectName(QString::fromUtf8("laserWavelengthDisplay"));
        laserWavelengthDisplay->setEnabled(false);
        laserWavelengthDisplay->setGeometry(QRect(240, 400, 211, 31));
        label_9 = new QLabel(centralwidget);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(30, 370, 181, 21));
        wavelengthUnitComboBox = new QComboBox(centralwidget);
        wavelengthUnitComboBox->addItem(QString());
        wavelengthUnitComboBox->addItem(QString());
        wavelengthUnitComboBox->addItem(QString());
        wavelengthUnitComboBox->addItem(QString());
        wavelengthUnitComboBox->addItem(QString());
        wavelengthUnitComboBox->setObjectName(QString::fromUtf8("wavelengthUnitComboBox"));
        wavelengthUnitComboBox->setGeometry(QRect(240, 370, 121, 31));
        minWavelengthDisplay = new QLineEdit(centralwidget);
        minWavelengthDisplay->setObjectName(QString::fromUtf8("minWavelengthDisplay"));
        minWavelengthDisplay->setEnabled(false);
        minWavelengthDisplay->setGeometry(QRect(240, 430, 211, 31));
        label_10 = new QLabel(centralwidget);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(30, 430, 181, 21));
        maxWavelengthDisplay = new QLineEdit(centralwidget);
        maxWavelengthDisplay->setObjectName(QString::fromUtf8("maxWavelengthDisplay"));
        maxWavelengthDisplay->setEnabled(false);
        maxWavelengthDisplay->setGeometry(QRect(240, 460, 211, 31));
        label_11 = new QLabel(centralwidget);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(30, 460, 181, 21));
        wavelengthEditUnitLabel = new QLabel(centralwidget);
        wavelengthEditUnitLabel->setObjectName(QString::fromUtf8("wavelengthEditUnitLabel"));
        wavelengthEditUnitLabel->setGeometry(QRect(870, 410, 81, 16));
        laserWavelengthEdit = new QLineEdit(centralwidget);
        laserWavelengthEdit->setObjectName(QString::fromUtf8("laserWavelengthEdit"));
        laserWavelengthEdit->setEnabled(true);
        laserWavelengthEdit->setGeometry(QRect(650, 400, 211, 31));
        label_13 = new QLabel(centralwidget);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setGeometry(QRect(10, 540, 331, 16));
        label_13->setFont(font);
        laserFrequencyDisplay = new QLineEdit(centralwidget);
        laserFrequencyDisplay->setObjectName(QString::fromUtf8("laserFrequencyDisplay"));
        laserFrequencyDisplay->setEnabled(false);
        laserFrequencyDisplay->setGeometry(QRect(240, 600, 211, 31));
        label_14 = new QLabel(centralwidget);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setGeometry(QRect(40, 610, 201, 16));
        laserFrequencyEdit = new QLineEdit(centralwidget);
        laserFrequencyEdit->setObjectName(QString::fromUtf8("laserFrequencyEdit"));
        laserFrequencyEdit->setEnabled(true);
        laserFrequencyEdit->setGeometry(QRect(660, 600, 211, 31));
        frequencyEditUnitLabel = new QLabel(centralwidget);
        frequencyEditUnitLabel->setObjectName(QString::fromUtf8("frequencyEditUnitLabel"));
        frequencyEditUnitLabel->setGeometry(QRect(880, 610, 51, 21));
        label_16 = new QLabel(centralwidget);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        label_16->setGeometry(QRect(40, 580, 201, 16));
        frequencyUnitComboBox = new QComboBox(centralwidget);
        frequencyUnitComboBox->addItem(QString());
        frequencyUnitComboBox->addItem(QString());
        frequencyUnitComboBox->addItem(QString());
        frequencyUnitComboBox->addItem(QString());
        frequencyUnitComboBox->addItem(QString());
        frequencyUnitComboBox->setObjectName(QString::fromUtf8("frequencyUnitComboBox"));
        frequencyUnitComboBox->setGeometry(QRect(240, 570, 121, 31));
        wavelengthDisplayUnitLabel = new QLabel(centralwidget);
        wavelengthDisplayUnitLabel->setObjectName(QString::fromUtf8("wavelengthDisplayUnitLabel"));
        wavelengthDisplayUnitLabel->setGeometry(QRect(460, 410, 31, 16));
        minWavlengthUnitLabel = new QLabel(centralwidget);
        minWavlengthUnitLabel->setObjectName(QString::fromUtf8("minWavlengthUnitLabel"));
        minWavlengthUnitLabel->setGeometry(QRect(460, 440, 41, 21));
        maxWavelengthUnitLabel = new QLabel(centralwidget);
        maxWavelengthUnitLabel->setObjectName(QString::fromUtf8("maxWavelengthUnitLabel"));
        maxWavelengthUnitLabel->setGeometry(QRect(460, 470, 51, 21));
        laserFrequencyDisplayUnitLabel = new QLabel(centralwidget);
        laserFrequencyDisplayUnitLabel->setObjectName(QString::fromUtf8("laserFrequencyDisplayUnitLabel"));
        laserFrequencyDisplayUnitLabel->setGeometry(QRect(460, 610, 51, 21));
        minFrequencyUnitLabel = new QLabel(centralwidget);
        minFrequencyUnitLabel->setObjectName(QString::fromUtf8("minFrequencyUnitLabel"));
        minFrequencyUnitLabel->setGeometry(QRect(460, 640, 61, 21));
        minFrequencyDisplay = new QLineEdit(centralwidget);
        minFrequencyDisplay->setObjectName(QString::fromUtf8("minFrequencyDisplay"));
        minFrequencyDisplay->setEnabled(false);
        minFrequencyDisplay->setGeometry(QRect(240, 630, 211, 31));
        maxFrequencyUnitLabel = new QLabel(centralwidget);
        maxFrequencyUnitLabel->setObjectName(QString::fromUtf8("maxFrequencyUnitLabel"));
        maxFrequencyUnitLabel->setGeometry(QRect(460, 670, 61, 21));
        label_23 = new QLabel(centralwidget);
        label_23->setObjectName(QString::fromUtf8("label_23"));
        label_23->setGeometry(QRect(40, 670, 191, 16));
        label_24 = new QLabel(centralwidget);
        label_24->setObjectName(QString::fromUtf8("label_24"));
        label_24->setGeometry(QRect(40, 640, 201, 16));
        maxFrequencyDisplay = new QLineEdit(centralwidget);
        maxFrequencyDisplay->setObjectName(QString::fromUtf8("maxFrequencyDisplay"));
        maxFrequencyDisplay->setEnabled(false);
        maxFrequencyDisplay->setGeometry(QRect(240, 660, 211, 31));
        laserMaxPowerDisplay = new QLineEdit(centralwidget);
        laserMaxPowerDisplay->setObjectName(QString::fromUtf8("laserMaxPowerDisplay"));
        laserMaxPowerDisplay->setEnabled(false);
        laserMaxPowerDisplay->setGeometry(QRect(240, 230, 211, 31));
        label_25 = new QLabel(centralwidget);
        label_25->setObjectName(QString::fromUtf8("label_25"));
        label_25->setGeometry(QRect(40, 235, 201, 21));
        label_25->setStyleSheet(QString::fromUtf8(""));
        laserMinPowerDisplay = new QLineEdit(centralwidget);
        laserMinPowerDisplay->setObjectName(QString::fromUtf8("laserMinPowerDisplay"));
        laserMinPowerDisplay->setEnabled(false);
        laserMinPowerDisplay->setGeometry(QRect(240, 200, 211, 31));
        label_26 = new QLabel(centralwidget);
        label_26->setObjectName(QString::fromUtf8("label_26"));
        label_26->setGeometry(QRect(40, 205, 201, 21));
        minPowerDisplayUnitLabel = new QLabel(centralwidget);
        minPowerDisplayUnitLabel->setObjectName(QString::fromUtf8("minPowerDisplayUnitLabel"));
        minPowerDisplayUnitLabel->setGeometry(QRect(460, 210, 61, 21));
        maxPowerDisplayUnitLabel = new QLabel(centralwidget);
        maxPowerDisplayUnitLabel->setObjectName(QString::fromUtf8("maxPowerDisplayUnitLabel"));
        maxPowerDisplayUnitLabel->setGeometry(QRect(460, 240, 61, 21));
        instrumentInfoLabel = new QLabel(centralwidget);
        instrumentInfoLabel->setObjectName(QString::fromUtf8("instrumentInfoLabel"));
        instrumentInfoLabel->setGeometry(QRect(20, 10, 991, 21));
        instrumentInfoLabel->setFont(font);
        instrumentAddressLabel = new QLabel(centralwidget);
        instrumentAddressLabel->setObjectName(QString::fromUtf8("instrumentAddressLabel"));
        instrumentAddressLabel->setGeometry(QRect(20, 30, 981, 31));
        instrumentAddressLabel->setFont(font);
        splitter = new QSplitter(centralwidget);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setGeometry(QRect(70, 60, 661, 20));
        splitter->setOrientation(Qt::Horizontal);
        slot1RadioBtn = new QRadioButton(splitter);
        slotRadioButtonGroup = new QButtonGroup(ConfigN7714AWindow);
        slotRadioButtonGroup->setObjectName(QString::fromUtf8("slotRadioButtonGroup"));
        slotRadioButtonGroup->addButton(slot1RadioBtn);
        slot1RadioBtn->setObjectName(QString::fromUtf8("slot1RadioBtn"));
        slot1RadioBtn->setChecked(true);
        splitter->addWidget(slot1RadioBtn);
        slot2RadioBtn = new QRadioButton(splitter);
        slotRadioButtonGroup->addButton(slot2RadioBtn);
        slot2RadioBtn->setObjectName(QString::fromUtf8("slot2RadioBtn"));
        splitter->addWidget(slot2RadioBtn);
        slot3RadioBtn = new QRadioButton(splitter);
        slotRadioButtonGroup->addButton(slot3RadioBtn);
        slot3RadioBtn->setObjectName(QString::fromUtf8("slot3RadioBtn"));
        splitter->addWidget(slot3RadioBtn);
        slot4RadioBtn = new QRadioButton(splitter);
        slotRadioButtonGroup->addButton(slot4RadioBtn);
        slot4RadioBtn->setObjectName(QString::fromUtf8("slot4RadioBtn"));
        splitter->addWidget(slot4RadioBtn);
        saveChangesButton = new QPushButton(centralwidget);
        saveChangesButton->setObjectName(QString::fromUtf8("saveChangesButton"));
        saveChangesButton->setGeometry(QRect(810, 670, 191, 41));
        saveChangesButton->setFont(font);
        groupBox_3 = new QGroupBox(centralwidget);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setGeometry(QRect(780, 10, 221, 81));
        groupBox_3->setFont(font);
        saveSettingsButton = new QPushButton(groupBox_3);
        saveSettingsButton->setObjectName(QString::fromUtf8("saveSettingsButton"));
        saveSettingsButton->setGeometry(QRect(120, 30, 80, 41));
        loadSettingsButton = new QPushButton(groupBox_3);
        loadSettingsButton->setObjectName(QString::fromUtf8("loadSettingsButton"));
        loadSettingsButton->setGeometry(QRect(20, 30, 80, 41));
        ConfigN7714AWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(ConfigN7714AWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1024, 17));
        ConfigN7714AWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(ConfigN7714AWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        ConfigN7714AWindow->setStatusBar(statusbar);

        retranslateUi(ConfigN7714AWindow);

        QMetaObject::connectSlotsByName(ConfigN7714AWindow);
    } // setupUi

    void retranslateUi(QMainWindow *ConfigN7714AWindow)
    {
        ConfigN7714AWindow->setWindowTitle(QCoreApplication::translate("ConfigN7714AWindow", "MainWindow", nullptr));
        label->setText(QCoreApplication::translate("ConfigN7714AWindow", "Output Power Unit:", nullptr));
        label_2->setText(QCoreApplication::translate("ConfigN7714AWindow", "Laser State", nullptr));
        powerUnitComboBox->setItemText(0, QCoreApplication::translate("ConfigN7714AWindow", "dBm", nullptr));
        powerUnitComboBox->setItemText(1, QCoreApplication::translate("ConfigN7714AWindow", "Watt", nullptr));

        togglePowerButton->setText(QCoreApplication::translate("ConfigN7714AWindow", "Toggle Power", nullptr));
        label_3->setText(QCoreApplication::translate("ConfigN7714AWindow", "Laser Output Power:", nullptr));
        powerDisplayUnitLabel->setText(QCoreApplication::translate("ConfigN7714AWindow", "(unit)", nullptr));
        powerUnitEditLabel->setText(QCoreApplication::translate("ConfigN7714AWindow", "(unit)", nullptr));
        label_6->setText(QCoreApplication::translate("ConfigN7714AWindow", "Power Settings", nullptr));
        label_7->setText(QCoreApplication::translate("ConfigN7714AWindow", "Wavelength Settings", nullptr));
        label_8->setText(QCoreApplication::translate("ConfigN7714AWindow", "Laser Wavelength", nullptr));
        label_9->setText(QCoreApplication::translate("ConfigN7714AWindow", "Laser Wavelength Unit", nullptr));
        wavelengthUnitComboBox->setItemText(0, QCoreApplication::translate("ConfigN7714AWindow", "m", nullptr));
        wavelengthUnitComboBox->setItemText(1, QCoreApplication::translate("ConfigN7714AWindow", "mm", nullptr));
        wavelengthUnitComboBox->setItemText(2, QCoreApplication::translate("ConfigN7714AWindow", "um", nullptr));
        wavelengthUnitComboBox->setItemText(3, QCoreApplication::translate("ConfigN7714AWindow", "nm", nullptr));
        wavelengthUnitComboBox->setItemText(4, QCoreApplication::translate("ConfigN7714AWindow", "pm", nullptr));

        label_10->setText(QCoreApplication::translate("ConfigN7714AWindow", "Min Wavelength", nullptr));
        maxWavelengthDisplay->setText(QString());
        label_11->setText(QCoreApplication::translate("ConfigN7714AWindow", "Max Wavelength", nullptr));
        wavelengthEditUnitLabel->setText(QCoreApplication::translate("ConfigN7714AWindow", "(unit)", nullptr));
        label_13->setText(QCoreApplication::translate("ConfigN7714AWindow", "Frequency Settings", nullptr));
        laserFrequencyDisplay->setText(QString());
        label_14->setText(QCoreApplication::translate("ConfigN7714AWindow", "Laser Frequency", nullptr));
        frequencyEditUnitLabel->setText(QCoreApplication::translate("ConfigN7714AWindow", "(unit)", nullptr));
        label_16->setText(QCoreApplication::translate("ConfigN7714AWindow", "Laser Frequency Unit", nullptr));
        frequencyUnitComboBox->setItemText(0, QCoreApplication::translate("ConfigN7714AWindow", "Hz", nullptr));
        frequencyUnitComboBox->setItemText(1, QCoreApplication::translate("ConfigN7714AWindow", "KHz", nullptr));
        frequencyUnitComboBox->setItemText(2, QCoreApplication::translate("ConfigN7714AWindow", "MHz", nullptr));
        frequencyUnitComboBox->setItemText(3, QCoreApplication::translate("ConfigN7714AWindow", "GHz", nullptr));
        frequencyUnitComboBox->setItemText(4, QCoreApplication::translate("ConfigN7714AWindow", "THz", nullptr));

        wavelengthDisplayUnitLabel->setText(QCoreApplication::translate("ConfigN7714AWindow", "(unit)", nullptr));
        minWavlengthUnitLabel->setText(QCoreApplication::translate("ConfigN7714AWindow", "(unit)", nullptr));
        maxWavelengthUnitLabel->setText(QCoreApplication::translate("ConfigN7714AWindow", "(unit)", nullptr));
        laserFrequencyDisplayUnitLabel->setText(QCoreApplication::translate("ConfigN7714AWindow", "(unit)", nullptr));
        minFrequencyUnitLabel->setText(QCoreApplication::translate("ConfigN7714AWindow", "(unit)", nullptr));
        maxFrequencyUnitLabel->setText(QCoreApplication::translate("ConfigN7714AWindow", "(unit)", nullptr));
        label_23->setText(QCoreApplication::translate("ConfigN7714AWindow", "Max Frequency", nullptr));
        label_24->setText(QCoreApplication::translate("ConfigN7714AWindow", "Min Frequency", nullptr));
        maxFrequencyDisplay->setText(QString());
        label_25->setText(QCoreApplication::translate("ConfigN7714AWindow", "Max Laser Power:", nullptr));
        label_26->setText(QCoreApplication::translate("ConfigN7714AWindow", "Min Laser Power:", nullptr));
        minPowerDisplayUnitLabel->setText(QCoreApplication::translate("ConfigN7714AWindow", "(unit)", nullptr));
        maxPowerDisplayUnitLabel->setText(QCoreApplication::translate("ConfigN7714AWindow", "(unit)", nullptr));
        instrumentInfoLabel->setText(QCoreApplication::translate("ConfigN7714AWindow", "Instrument: ", nullptr));
        instrumentAddressLabel->setText(QCoreApplication::translate("ConfigN7714AWindow", "Address: ", nullptr));
        slot1RadioBtn->setText(QCoreApplication::translate("ConfigN7714AWindow", "Slot 1", nullptr));
        slot2RadioBtn->setText(QCoreApplication::translate("ConfigN7714AWindow", "Slot 2", nullptr));
        slot3RadioBtn->setText(QCoreApplication::translate("ConfigN7714AWindow", "Slot 3", nullptr));
        slot4RadioBtn->setText(QCoreApplication::translate("ConfigN7714AWindow", "Slot 4", nullptr));
        saveChangesButton->setText(QCoreApplication::translate("ConfigN7714AWindow", "Submit Changes", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("ConfigN7714AWindow", "Configuration", nullptr));
        saveSettingsButton->setText(QCoreApplication::translate("ConfigN7714AWindow", "Save", nullptr));
        loadSettingsButton->setText(QCoreApplication::translate("ConfigN7714AWindow", "Load", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ConfigN7714AWindow: public Ui_ConfigN7714AWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONFIGN7714AWINDOW_H
