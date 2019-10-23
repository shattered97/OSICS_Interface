/********************************************************************************
** Form generated from reading UI file 'ConfigOSICS_T100.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONFIGOSICS_T100_H
#define UI_CONFIGOSICS_T100_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ConfigOSICS_T100
{
public:
    QWidget *centralwidget;
    QGroupBox *groupBox_3;
    QPushButton *saveSettingsButton;
    QPushButton *loadSettingsButton;
    QSplitter *splitter;
    QLabel *instrumentAddressLabel;
    QLabel *instrumentInfoLabel;
    QPushButton *saveChangesButton;
    QGroupBox *groupBox;
    QLineEdit *laserOutputPowerEdit;
    QLineEdit *laserMinPowerDisplay;
    QLabel *minPowerDisplayUnitLabel;
    QLabel *label;
    QLabel *powerDisplayUnitLabel;
    QLabel *label_26;
    QLineEdit *laserMaxPowerDisplay;
    QLabel *label_25;
    QPushButton *togglePowerButton;
    QLabel *label_2;
    QComboBox *powerUnitComboBox;
    QLineEdit *laserStateDisplay;
    QLabel *label_3;
    QLineEdit *laserOutputPowerDisplay;
    QLabel *powerUnitEditLabel;
    QLabel *maxPowerDisplayUnitLabel;
    QGroupBox *groupBox_2;
    QLabel *wavelengthEditUnitLabel;
    QLineEdit *minWavelengthDisplay;
    QLineEdit *laserWavelengthEdit;
    QLabel *maxWavelengthUnitLabel;
    QLabel *label_11;
    QLabel *wavelengthDisplayUnitLabel;
    QLabel *label_10;
    QLineEdit *maxWavelengthDisplay;
    QLineEdit *laserWavelengthDisplay;
    QLabel *label_8;
    QLabel *minWavlengthUnitLabel;
    QGroupBox *groupBox_4;
    QLabel *frequencyEditUnitLabel;
    QLabel *minFrequencyUnitLabel;
    QLabel *laserFrequencyDisplayUnitLabel;
    QLabel *label_14;
    QLineEdit *laserFrequencyDisplay;
    QComboBox *frequencyUnitComboBox;
    QLineEdit *laserFrequencyEdit;
    QLabel *label_23;
    QLabel *label_16;
    QLabel *maxFrequencyUnitLabel;
    QLineEdit *minFrequencyDisplay;
    QLabel *label_24;
    QLineEdit *maxFrequencyDisplay;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *ConfigOSICS_T100)
    {
        if (ConfigOSICS_T100->objectName().isEmpty())
            ConfigOSICS_T100->setObjectName(QString::fromUtf8("ConfigOSICS_T100"));
        ConfigOSICS_T100->resize(1024, 786);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(ConfigOSICS_T100->sizePolicy().hasHeightForWidth());
        ConfigOSICS_T100->setSizePolicy(sizePolicy);
        centralwidget = new QWidget(ConfigOSICS_T100);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        groupBox_3 = new QGroupBox(centralwidget);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setGeometry(QRect(780, 10, 221, 81));
        QFont font;
        font.setPointSize(12);
        groupBox_3->setFont(font);
        saveSettingsButton = new QPushButton(groupBox_3);
        saveSettingsButton->setObjectName(QString::fromUtf8("saveSettingsButton"));
        saveSettingsButton->setGeometry(QRect(120, 30, 80, 41));
        loadSettingsButton = new QPushButton(groupBox_3);
        loadSettingsButton->setObjectName(QString::fromUtf8("loadSettingsButton"));
        loadSettingsButton->setGeometry(QRect(20, 30, 80, 41));
        splitter = new QSplitter(centralwidget);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setGeometry(QRect(90, 60, 661, 20));
        splitter->setOrientation(Qt::Horizontal);
        instrumentAddressLabel = new QLabel(centralwidget);
        instrumentAddressLabel->setObjectName(QString::fromUtf8("instrumentAddressLabel"));
        instrumentAddressLabel->setGeometry(QRect(20, 30, 981, 31));
        instrumentAddressLabel->setFont(font);
        instrumentInfoLabel = new QLabel(centralwidget);
        instrumentInfoLabel->setObjectName(QString::fromUtf8("instrumentInfoLabel"));
        instrumentInfoLabel->setGeometry(QRect(20, 10, 991, 21));
        instrumentInfoLabel->setFont(font);
        saveChangesButton = new QPushButton(centralwidget);
        saveChangesButton->setObjectName(QString::fromUtf8("saveChangesButton"));
        saveChangesButton->setGeometry(QRect(820, 690, 191, 41));
        saveChangesButton->setFont(font);
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(10, 80, 1001, 221));
        groupBox->setFont(font);
        laserOutputPowerEdit = new QLineEdit(groupBox);
        laserOutputPowerEdit->setObjectName(QString::fromUtf8("laserOutputPowerEdit"));
        laserOutputPowerEdit->setEnabled(true);
        laserOutputPowerEdit->setGeometry(QRect(520, 60, 211, 31));
        laserMinPowerDisplay = new QLineEdit(groupBox);
        laserMinPowerDisplay->setObjectName(QString::fromUtf8("laserMinPowerDisplay"));
        laserMinPowerDisplay->setEnabled(false);
        laserMinPowerDisplay->setGeometry(QRect(240, 90, 211, 31));
        minPowerDisplayUnitLabel = new QLabel(groupBox);
        minPowerDisplayUnitLabel->setObjectName(QString::fromUtf8("minPowerDisplayUnitLabel"));
        minPowerDisplayUnitLabel->setGeometry(QRect(460, 100, 61, 21));
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(30, 40, 201, 21));
        powerDisplayUnitLabel = new QLabel(groupBox);
        powerDisplayUnitLabel->setObjectName(QString::fromUtf8("powerDisplayUnitLabel"));
        powerDisplayUnitLabel->setGeometry(QRect(460, 70, 61, 21));
        label_26 = new QLabel(groupBox);
        label_26->setObjectName(QString::fromUtf8("label_26"));
        label_26->setGeometry(QRect(30, 95, 201, 21));
        laserMaxPowerDisplay = new QLineEdit(groupBox);
        laserMaxPowerDisplay->setObjectName(QString::fromUtf8("laserMaxPowerDisplay"));
        laserMaxPowerDisplay->setEnabled(false);
        laserMaxPowerDisplay->setGeometry(QRect(240, 120, 211, 31));
        label_25 = new QLabel(groupBox);
        label_25->setObjectName(QString::fromUtf8("label_25"));
        label_25->setGeometry(QRect(30, 125, 201, 21));
        label_25->setStyleSheet(QString::fromUtf8(""));
        togglePowerButton = new QPushButton(groupBox);
        togglePowerButton->setObjectName(QString::fromUtf8("togglePowerButton"));
        togglePowerButton->setGeometry(QRect(520, 150, 211, 31));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(30, 155, 201, 21));
        powerUnitComboBox = new QComboBox(groupBox);
        powerUnitComboBox->addItem(QString());
        powerUnitComboBox->addItem(QString());
        powerUnitComboBox->setObjectName(QString::fromUtf8("powerUnitComboBox"));
        powerUnitComboBox->setGeometry(QRect(240, 30, 111, 31));
        laserStateDisplay = new QLineEdit(groupBox);
        laserStateDisplay->setObjectName(QString::fromUtf8("laserStateDisplay"));
        laserStateDisplay->setEnabled(false);
        laserStateDisplay->setGeometry(QRect(240, 150, 211, 31));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(30, 65, 201, 21));
        laserOutputPowerDisplay = new QLineEdit(groupBox);
        laserOutputPowerDisplay->setObjectName(QString::fromUtf8("laserOutputPowerDisplay"));
        laserOutputPowerDisplay->setEnabled(false);
        laserOutputPowerDisplay->setGeometry(QRect(240, 60, 211, 31));
        laserOutputPowerDisplay->setStyleSheet(QString::fromUtf8(""));
        powerUnitEditLabel = new QLabel(groupBox);
        powerUnitEditLabel->setObjectName(QString::fromUtf8("powerUnitEditLabel"));
        powerUnitEditLabel->setGeometry(QRect(740, 70, 81, 21));
        maxPowerDisplayUnitLabel = new QLabel(groupBox);
        maxPowerDisplayUnitLabel->setObjectName(QString::fromUtf8("maxPowerDisplayUnitLabel"));
        maxPowerDisplayUnitLabel->setGeometry(QRect(460, 130, 61, 21));
        groupBox_2 = new QGroupBox(centralwidget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(10, 310, 1001, 191));
        groupBox_2->setFont(font);
        wavelengthEditUnitLabel = new QLabel(groupBox_2);
        wavelengthEditUnitLabel->setObjectName(QString::fromUtf8("wavelengthEditUnitLabel"));
        wavelengthEditUnitLabel->setGeometry(QRect(740, 80, 81, 16));
        minWavelengthDisplay = new QLineEdit(groupBox_2);
        minWavelengthDisplay->setObjectName(QString::fromUtf8("minWavelengthDisplay"));
        minWavelengthDisplay->setEnabled(false);
        minWavelengthDisplay->setGeometry(QRect(240, 100, 211, 31));
        laserWavelengthEdit = new QLineEdit(groupBox_2);
        laserWavelengthEdit->setObjectName(QString::fromUtf8("laserWavelengthEdit"));
        laserWavelengthEdit->setEnabled(true);
        laserWavelengthEdit->setGeometry(QRect(520, 70, 211, 31));
        maxWavelengthUnitLabel = new QLabel(groupBox_2);
        maxWavelengthUnitLabel->setObjectName(QString::fromUtf8("maxWavelengthUnitLabel"));
        maxWavelengthUnitLabel->setGeometry(QRect(460, 140, 51, 21));
        label_11 = new QLabel(groupBox_2);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(30, 130, 181, 21));
        wavelengthDisplayUnitLabel = new QLabel(groupBox_2);
        wavelengthDisplayUnitLabel->setObjectName(QString::fromUtf8("wavelengthDisplayUnitLabel"));
        wavelengthDisplayUnitLabel->setGeometry(QRect(460, 80, 31, 16));
        label_10 = new QLabel(groupBox_2);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(30, 100, 181, 21));
        maxWavelengthDisplay = new QLineEdit(groupBox_2);
        maxWavelengthDisplay->setObjectName(QString::fromUtf8("maxWavelengthDisplay"));
        maxWavelengthDisplay->setEnabled(false);
        maxWavelengthDisplay->setGeometry(QRect(240, 130, 211, 31));
        laserWavelengthDisplay = new QLineEdit(groupBox_2);
        laserWavelengthDisplay->setObjectName(QString::fromUtf8("laserWavelengthDisplay"));
        laserWavelengthDisplay->setEnabled(false);
        laserWavelengthDisplay->setGeometry(QRect(240, 70, 211, 31));
        label_8 = new QLabel(groupBox_2);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(30, 70, 181, 21));
        minWavlengthUnitLabel = new QLabel(groupBox_2);
        minWavlengthUnitLabel->setObjectName(QString::fromUtf8("minWavlengthUnitLabel"));
        minWavlengthUnitLabel->setGeometry(QRect(460, 110, 41, 21));
        groupBox_4 = new QGroupBox(centralwidget);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        groupBox_4->setGeometry(QRect(10, 510, 1001, 171));
        groupBox_4->setFont(font);
        frequencyEditUnitLabel = new QLabel(groupBox_4);
        frequencyEditUnitLabel->setObjectName(QString::fromUtf8("frequencyEditUnitLabel"));
        frequencyEditUnitLabel->setGeometry(QRect(740, 70, 51, 21));
        minFrequencyUnitLabel = new QLabel(groupBox_4);
        minFrequencyUnitLabel->setObjectName(QString::fromUtf8("minFrequencyUnitLabel"));
        minFrequencyUnitLabel->setGeometry(QRect(460, 100, 61, 21));
        laserFrequencyDisplayUnitLabel = new QLabel(groupBox_4);
        laserFrequencyDisplayUnitLabel->setObjectName(QString::fromUtf8("laserFrequencyDisplayUnitLabel"));
        laserFrequencyDisplayUnitLabel->setGeometry(QRect(460, 70, 51, 21));
        label_14 = new QLabel(groupBox_4);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setGeometry(QRect(50, 70, 201, 16));
        laserFrequencyDisplay = new QLineEdit(groupBox_4);
        laserFrequencyDisplay->setObjectName(QString::fromUtf8("laserFrequencyDisplay"));
        laserFrequencyDisplay->setEnabled(false);
        laserFrequencyDisplay->setGeometry(QRect(240, 60, 211, 31));
        frequencyUnitComboBox = new QComboBox(groupBox_4);
        frequencyUnitComboBox->addItem(QString());
        frequencyUnitComboBox->addItem(QString());
        frequencyUnitComboBox->addItem(QString());
        frequencyUnitComboBox->addItem(QString());
        frequencyUnitComboBox->addItem(QString());
        frequencyUnitComboBox->setObjectName(QString::fromUtf8("frequencyUnitComboBox"));
        frequencyUnitComboBox->setGeometry(QRect(240, 30, 121, 31));
        laserFrequencyEdit = new QLineEdit(groupBox_4);
        laserFrequencyEdit->setObjectName(QString::fromUtf8("laserFrequencyEdit"));
        laserFrequencyEdit->setEnabled(true);
        laserFrequencyEdit->setGeometry(QRect(520, 60, 211, 31));
        label_23 = new QLabel(groupBox_4);
        label_23->setObjectName(QString::fromUtf8("label_23"));
        label_23->setGeometry(QRect(50, 130, 191, 16));
        label_16 = new QLabel(groupBox_4);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        label_16->setGeometry(QRect(50, 40, 201, 16));
        maxFrequencyUnitLabel = new QLabel(groupBox_4);
        maxFrequencyUnitLabel->setObjectName(QString::fromUtf8("maxFrequencyUnitLabel"));
        maxFrequencyUnitLabel->setGeometry(QRect(460, 130, 61, 21));
        minFrequencyDisplay = new QLineEdit(groupBox_4);
        minFrequencyDisplay->setObjectName(QString::fromUtf8("minFrequencyDisplay"));
        minFrequencyDisplay->setEnabled(false);
        minFrequencyDisplay->setGeometry(QRect(240, 90, 211, 31));
        label_24 = new QLabel(groupBox_4);
        label_24->setObjectName(QString::fromUtf8("label_24"));
        label_24->setGeometry(QRect(50, 100, 201, 16));
        maxFrequencyDisplay = new QLineEdit(groupBox_4);
        maxFrequencyDisplay->setObjectName(QString::fromUtf8("maxFrequencyDisplay"));
        maxFrequencyDisplay->setEnabled(false);
        maxFrequencyDisplay->setGeometry(QRect(240, 120, 211, 31));
        ConfigOSICS_T100->setCentralWidget(centralwidget);
        menubar = new QMenuBar(ConfigOSICS_T100);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1024, 17));
        ConfigOSICS_T100->setMenuBar(menubar);
        statusbar = new QStatusBar(ConfigOSICS_T100);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        ConfigOSICS_T100->setStatusBar(statusbar);

        retranslateUi(ConfigOSICS_T100);

        QMetaObject::connectSlotsByName(ConfigOSICS_T100);
    } // setupUi

    void retranslateUi(QMainWindow *ConfigOSICS_T100)
    {
        ConfigOSICS_T100->setWindowTitle(QCoreApplication::translate("ConfigOSICS_T100", "MainWindow", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("ConfigOSICS_T100", "Configuration", nullptr));
        saveSettingsButton->setText(QCoreApplication::translate("ConfigOSICS_T100", "Save", nullptr));
        loadSettingsButton->setText(QCoreApplication::translate("ConfigOSICS_T100", "Load", nullptr));
        instrumentAddressLabel->setText(QCoreApplication::translate("ConfigOSICS_T100", "Address: ", nullptr));
        instrumentInfoLabel->setText(QCoreApplication::translate("ConfigOSICS_T100", "Instrument: ", nullptr));
        saveChangesButton->setText(QCoreApplication::translate("ConfigOSICS_T100", "Submit Changes", nullptr));
        groupBox->setTitle(QCoreApplication::translate("ConfigOSICS_T100", "Power Settings", nullptr));
        minPowerDisplayUnitLabel->setText(QCoreApplication::translate("ConfigOSICS_T100", "(unit)", nullptr));
        label->setText(QCoreApplication::translate("ConfigOSICS_T100", "Output Power Unit:", nullptr));
        powerDisplayUnitLabel->setText(QCoreApplication::translate("ConfigOSICS_T100", "(unit)", nullptr));
        label_26->setText(QCoreApplication::translate("ConfigOSICS_T100", "Min Laser Power:", nullptr));
        label_25->setText(QCoreApplication::translate("ConfigOSICS_T100", "Max Laser Power:", nullptr));
        togglePowerButton->setText(QCoreApplication::translate("ConfigOSICS_T100", "Toggle Power", nullptr));
        label_2->setText(QCoreApplication::translate("ConfigOSICS_T100", "Laser State", nullptr));
        powerUnitComboBox->setItemText(0, QCoreApplication::translate("ConfigOSICS_T100", "dBm", nullptr));
        powerUnitComboBox->setItemText(1, QCoreApplication::translate("ConfigOSICS_T100", "Watt", nullptr));

        label_3->setText(QCoreApplication::translate("ConfigOSICS_T100", "Laser Output Power:", nullptr));
        powerUnitEditLabel->setText(QCoreApplication::translate("ConfigOSICS_T100", "(unit)", nullptr));
        maxPowerDisplayUnitLabel->setText(QCoreApplication::translate("ConfigOSICS_T100", "(unit)", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("ConfigOSICS_T100", "Wavelength Settings", nullptr));
        wavelengthEditUnitLabel->setText(QCoreApplication::translate("ConfigOSICS_T100", "nm", nullptr));
        maxWavelengthUnitLabel->setText(QCoreApplication::translate("ConfigOSICS_T100", "nm", nullptr));
        label_11->setText(QCoreApplication::translate("ConfigOSICS_T100", "Max Wavelength", nullptr));
        wavelengthDisplayUnitLabel->setText(QCoreApplication::translate("ConfigOSICS_T100", "nm", nullptr));
        label_10->setText(QCoreApplication::translate("ConfigOSICS_T100", "Min Wavelength", nullptr));
        maxWavelengthDisplay->setText(QString());
        label_8->setText(QCoreApplication::translate("ConfigOSICS_T100", "Laser Wavelength", nullptr));
        minWavlengthUnitLabel->setText(QCoreApplication::translate("ConfigOSICS_T100", "nm", nullptr));
        groupBox_4->setTitle(QCoreApplication::translate("ConfigOSICS_T100", "Frequency Settings", nullptr));
        frequencyEditUnitLabel->setText(QCoreApplication::translate("ConfigOSICS_T100", "(unit)", nullptr));
        minFrequencyUnitLabel->setText(QCoreApplication::translate("ConfigOSICS_T100", "(unit)", nullptr));
        laserFrequencyDisplayUnitLabel->setText(QCoreApplication::translate("ConfigOSICS_T100", "(unit)", nullptr));
        label_14->setText(QCoreApplication::translate("ConfigOSICS_T100", "Laser Frequency", nullptr));
        laserFrequencyDisplay->setText(QString());
        frequencyUnitComboBox->setItemText(0, QCoreApplication::translate("ConfigOSICS_T100", "Hz", nullptr));
        frequencyUnitComboBox->setItemText(1, QCoreApplication::translate("ConfigOSICS_T100", "KHz", nullptr));
        frequencyUnitComboBox->setItemText(2, QCoreApplication::translate("ConfigOSICS_T100", "MHz", nullptr));
        frequencyUnitComboBox->setItemText(3, QCoreApplication::translate("ConfigOSICS_T100", "GHz", nullptr));
        frequencyUnitComboBox->setItemText(4, QCoreApplication::translate("ConfigOSICS_T100", "THz", nullptr));

        label_23->setText(QCoreApplication::translate("ConfigOSICS_T100", "Max Frequency", nullptr));
        label_16->setText(QCoreApplication::translate("ConfigOSICS_T100", "Laser Frequency Unit", nullptr));
        maxFrequencyUnitLabel->setText(QCoreApplication::translate("ConfigOSICS_T100", "(unit)", nullptr));
        label_24->setText(QCoreApplication::translate("ConfigOSICS_T100", "Min Frequency", nullptr));
        maxFrequencyDisplay->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class ConfigOSICS_T100: public Ui_ConfigOSICS_T100 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONFIGOSICS_T100_H
