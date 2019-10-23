/********************************************************************************
** Form generated from reading UI file 'ConfigOSICS_ATN.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONFIGOSICS_ATN_H
#define UI_CONFIGOSICS_ATN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ConfigOSICS_ATN
{
public:
    QWidget *centralwidget;
    QGroupBox *groupBox_3;
    QPushButton *saveSettingsButton;
    QPushButton *loadSettingsButton;
    QLabel *instrumentAddressLabel;
    QLabel *instrumentInfoLabel;
    QPushButton *saveChangesButton;
    QGroupBox *groupBox_2;
    QLabel *refWavelengthUnitLabel;
    QLabel *label_8;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QRadioButton *refWavelengthRadioButton1;
    QRadioButton *refWavelengthRadioButton2;
    QLabel *powerUnitEditLabel_2;
    QLabel *label_29;
    QLabel *label_28;
    QLineEdit *maxAttenuationOffsetDisplay;
    QLineEdit *attenuationOffsetEdit;
    QLabel *maxPowerDisplayUnitLabel_2;
    QLineEdit *minAttenuationOffsetDisplay;
    QLineEdit *attenuationOffsetDisplay;
    QLabel *minPowerDisplayUnitLabel_2;
    QLabel *powerDisplayUnitLabel_2;
    QLabel *label_27;
    QLabel *powerUnitEditLabel;
    QLineEdit *attenuationDisplay;
    QLabel *minPowerDisplayUnitLabel;
    QLabel *powerDisplayUnitLabel;
    QLabel *label_25;
    QLabel *label_26;
    QLineEdit *maxAttenuationDisplay;
    QLineEdit *attenuationEdit;
    QLabel *label_3;
    QLabel *maxPowerDisplayUnitLabel;
    QLineEdit *minAttenuationDisplay;
    QMenuBar *menubar;
    QStatusBar *statusbar;
    QButtonGroup *buttonGroup;

    void setupUi(QMainWindow *ConfigOSICS_ATN)
    {
        if (ConfigOSICS_ATN->objectName().isEmpty())
            ConfigOSICS_ATN->setObjectName(QString::fromUtf8("ConfigOSICS_ATN"));
        ConfigOSICS_ATN->resize(1024, 786);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(ConfigOSICS_ATN->sizePolicy().hasHeightForWidth());
        ConfigOSICS_ATN->setSizePolicy(sizePolicy);
        centralwidget = new QWidget(ConfigOSICS_ATN);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        groupBox_3 = new QGroupBox(centralwidget);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setGeometry(QRect(780, 0, 221, 81));
        QFont font;
        font.setPointSize(12);
        groupBox_3->setFont(font);
        saveSettingsButton = new QPushButton(groupBox_3);
        saveSettingsButton->setObjectName(QString::fromUtf8("saveSettingsButton"));
        saveSettingsButton->setGeometry(QRect(120, 30, 80, 41));
        loadSettingsButton = new QPushButton(groupBox_3);
        loadSettingsButton->setObjectName(QString::fromUtf8("loadSettingsButton"));
        loadSettingsButton->setGeometry(QRect(20, 30, 80, 41));
        instrumentAddressLabel = new QLabel(centralwidget);
        instrumentAddressLabel->setObjectName(QString::fromUtf8("instrumentAddressLabel"));
        instrumentAddressLabel->setGeometry(QRect(10, 30, 751, 31));
        instrumentAddressLabel->setFont(font);
        instrumentInfoLabel = new QLabel(centralwidget);
        instrumentInfoLabel->setObjectName(QString::fromUtf8("instrumentInfoLabel"));
        instrumentInfoLabel->setGeometry(QRect(10, 10, 751, 21));
        instrumentInfoLabel->setFont(font);
        saveChangesButton = new QPushButton(centralwidget);
        saveChangesButton->setObjectName(QString::fromUtf8("saveChangesButton"));
        saveChangesButton->setGeometry(QRect(810, 660, 191, 41));
        saveChangesButton->setFont(font);
        groupBox_2 = new QGroupBox(centralwidget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(10, 100, 1001, 471));
        groupBox_2->setFont(font);
        refWavelengthUnitLabel = new QLabel(groupBox_2);
        refWavelengthUnitLabel->setObjectName(QString::fromUtf8("refWavelengthUnitLabel"));
        refWavelengthUnitLabel->setGeometry(QRect(250, 70, 181, 21));
        refWavelengthUnitLabel->setFont(font);
        label_8 = new QLabel(groupBox_2);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(30, 70, 201, 21));
        label_8->setFont(font);
        layoutWidget = new QWidget(groupBox_2);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(60, 100, 411, 28));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        refWavelengthRadioButton1 = new QRadioButton(layoutWidget);
        buttonGroup = new QButtonGroup(ConfigOSICS_ATN);
        buttonGroup->setObjectName(QString::fromUtf8("buttonGroup"));
        buttonGroup->addButton(refWavelengthRadioButton1);
        refWavelengthRadioButton1->setObjectName(QString::fromUtf8("refWavelengthRadioButton1"));
        refWavelengthRadioButton1->setFont(font);
        refWavelengthRadioButton1->setChecked(true);

        horizontalLayout->addWidget(refWavelengthRadioButton1);

        refWavelengthRadioButton2 = new QRadioButton(layoutWidget);
        buttonGroup->addButton(refWavelengthRadioButton2);
        refWavelengthRadioButton2->setObjectName(QString::fromUtf8("refWavelengthRadioButton2"));
        refWavelengthRadioButton2->setFont(font);

        horizontalLayout->addWidget(refWavelengthRadioButton2);

        powerUnitEditLabel_2 = new QLabel(groupBox_2);
        powerUnitEditLabel_2->setObjectName(QString::fromUtf8("powerUnitEditLabel_2"));
        powerUnitEditLabel_2->setGeometry(QRect(720, 320, 81, 21));
        powerUnitEditLabel_2->setFont(font);
        label_29 = new QLabel(groupBox_2);
        label_29->setObjectName(QString::fromUtf8("label_29"));
        label_29->setGeometry(QRect(30, 370, 201, 21));
        label_29->setFont(font);
        label_29->setStyleSheet(QString::fromUtf8(""));
        label_28 = new QLabel(groupBox_2);
        label_28->setObjectName(QString::fromUtf8("label_28"));
        label_28->setGeometry(QRect(30, 340, 201, 21));
        label_28->setFont(font);
        label_28->setStyleSheet(QString::fromUtf8(""));
        maxAttenuationOffsetDisplay = new QLineEdit(groupBox_2);
        maxAttenuationOffsetDisplay->setObjectName(QString::fromUtf8("maxAttenuationOffsetDisplay"));
        maxAttenuationOffsetDisplay->setEnabled(false);
        maxAttenuationOffsetDisplay->setGeometry(QRect(230, 370, 211, 31));
        maxAttenuationOffsetDisplay->setFont(font);
        attenuationOffsetEdit = new QLineEdit(groupBox_2);
        attenuationOffsetEdit->setObjectName(QString::fromUtf8("attenuationOffsetEdit"));
        attenuationOffsetEdit->setEnabled(true);
        attenuationOffsetEdit->setGeometry(QRect(500, 310, 211, 31));
        attenuationOffsetEdit->setFont(font);
        maxPowerDisplayUnitLabel_2 = new QLabel(groupBox_2);
        maxPowerDisplayUnitLabel_2->setObjectName(QString::fromUtf8("maxPowerDisplayUnitLabel_2"));
        maxPowerDisplayUnitLabel_2->setGeometry(QRect(450, 380, 61, 21));
        maxPowerDisplayUnitLabel_2->setFont(font);
        minAttenuationOffsetDisplay = new QLineEdit(groupBox_2);
        minAttenuationOffsetDisplay->setObjectName(QString::fromUtf8("minAttenuationOffsetDisplay"));
        minAttenuationOffsetDisplay->setEnabled(false);
        minAttenuationOffsetDisplay->setGeometry(QRect(230, 340, 211, 31));
        minAttenuationOffsetDisplay->setFont(font);
        attenuationOffsetDisplay = new QLineEdit(groupBox_2);
        attenuationOffsetDisplay->setObjectName(QString::fromUtf8("attenuationOffsetDisplay"));
        attenuationOffsetDisplay->setEnabled(false);
        attenuationOffsetDisplay->setGeometry(QRect(230, 310, 211, 31));
        attenuationOffsetDisplay->setFont(font);
        minPowerDisplayUnitLabel_2 = new QLabel(groupBox_2);
        minPowerDisplayUnitLabel_2->setObjectName(QString::fromUtf8("minPowerDisplayUnitLabel_2"));
        minPowerDisplayUnitLabel_2->setGeometry(QRect(450, 350, 61, 21));
        minPowerDisplayUnitLabel_2->setFont(font);
        powerDisplayUnitLabel_2 = new QLabel(groupBox_2);
        powerDisplayUnitLabel_2->setObjectName(QString::fromUtf8("powerDisplayUnitLabel_2"));
        powerDisplayUnitLabel_2->setGeometry(QRect(450, 320, 61, 21));
        powerDisplayUnitLabel_2->setFont(font);
        label_27 = new QLabel(groupBox_2);
        label_27->setObjectName(QString::fromUtf8("label_27"));
        label_27->setGeometry(QRect(30, 310, 201, 21));
        label_27->setFont(font);
        label_27->setStyleSheet(QString::fromUtf8(""));
        powerUnitEditLabel = new QLabel(groupBox_2);
        powerUnitEditLabel->setObjectName(QString::fromUtf8("powerUnitEditLabel"));
        powerUnitEditLabel->setGeometry(QRect(720, 180, 81, 21));
        powerUnitEditLabel->setFont(font);
        attenuationDisplay = new QLineEdit(groupBox_2);
        attenuationDisplay->setObjectName(QString::fromUtf8("attenuationDisplay"));
        attenuationDisplay->setEnabled(false);
        attenuationDisplay->setGeometry(QRect(230, 170, 211, 31));
        attenuationDisplay->setFont(font);
        attenuationDisplay->setStyleSheet(QString::fromUtf8(""));
        minPowerDisplayUnitLabel = new QLabel(groupBox_2);
        minPowerDisplayUnitLabel->setObjectName(QString::fromUtf8("minPowerDisplayUnitLabel"));
        minPowerDisplayUnitLabel->setGeometry(QRect(450, 210, 61, 21));
        minPowerDisplayUnitLabel->setFont(font);
        powerDisplayUnitLabel = new QLabel(groupBox_2);
        powerDisplayUnitLabel->setObjectName(QString::fromUtf8("powerDisplayUnitLabel"));
        powerDisplayUnitLabel->setGeometry(QRect(450, 180, 61, 21));
        powerDisplayUnitLabel->setFont(font);
        label_25 = new QLabel(groupBox_2);
        label_25->setObjectName(QString::fromUtf8("label_25"));
        label_25->setGeometry(QRect(30, 235, 201, 21));
        label_25->setFont(font);
        label_25->setStyleSheet(QString::fromUtf8(""));
        label_26 = new QLabel(groupBox_2);
        label_26->setObjectName(QString::fromUtf8("label_26"));
        label_26->setGeometry(QRect(30, 205, 201, 21));
        label_26->setFont(font);
        maxAttenuationDisplay = new QLineEdit(groupBox_2);
        maxAttenuationDisplay->setObjectName(QString::fromUtf8("maxAttenuationDisplay"));
        maxAttenuationDisplay->setEnabled(false);
        maxAttenuationDisplay->setGeometry(QRect(230, 230, 211, 31));
        maxAttenuationDisplay->setFont(font);
        attenuationEdit = new QLineEdit(groupBox_2);
        attenuationEdit->setObjectName(QString::fromUtf8("attenuationEdit"));
        attenuationEdit->setEnabled(true);
        attenuationEdit->setGeometry(QRect(500, 170, 211, 31));
        attenuationEdit->setFont(font);
        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(30, 175, 201, 21));
        label_3->setFont(font);
        maxPowerDisplayUnitLabel = new QLabel(groupBox_2);
        maxPowerDisplayUnitLabel->setObjectName(QString::fromUtf8("maxPowerDisplayUnitLabel"));
        maxPowerDisplayUnitLabel->setGeometry(QRect(450, 240, 61, 21));
        maxPowerDisplayUnitLabel->setFont(font);
        minAttenuationDisplay = new QLineEdit(groupBox_2);
        minAttenuationDisplay->setObjectName(QString::fromUtf8("minAttenuationDisplay"));
        minAttenuationDisplay->setEnabled(false);
        minAttenuationDisplay->setGeometry(QRect(230, 200, 211, 31));
        minAttenuationDisplay->setFont(font);
        ConfigOSICS_ATN->setCentralWidget(centralwidget);
        menubar = new QMenuBar(ConfigOSICS_ATN);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1024, 17));
        ConfigOSICS_ATN->setMenuBar(menubar);
        statusbar = new QStatusBar(ConfigOSICS_ATN);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        ConfigOSICS_ATN->setStatusBar(statusbar);

        retranslateUi(ConfigOSICS_ATN);

        QMetaObject::connectSlotsByName(ConfigOSICS_ATN);
    } // setupUi

    void retranslateUi(QMainWindow *ConfigOSICS_ATN)
    {
        ConfigOSICS_ATN->setWindowTitle(QCoreApplication::translate("ConfigOSICS_ATN", "MainWindow", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("ConfigOSICS_ATN", "Configuration", nullptr));
        saveSettingsButton->setText(QCoreApplication::translate("ConfigOSICS_ATN", "Save", nullptr));
        loadSettingsButton->setText(QCoreApplication::translate("ConfigOSICS_ATN", "Load", nullptr));
        instrumentAddressLabel->setText(QCoreApplication::translate("ConfigOSICS_ATN", "Address: ", nullptr));
        instrumentInfoLabel->setText(QCoreApplication::translate("ConfigOSICS_ATN", "Instrument: ", nullptr));
        saveChangesButton->setText(QCoreApplication::translate("ConfigOSICS_ATN", "Submit Changes", nullptr));
        groupBox_2->setTitle(QString());
        refWavelengthUnitLabel->setText(QCoreApplication::translate("ConfigOSICS_ATN", "(nm)", nullptr));
        label_8->setText(QCoreApplication::translate("ConfigOSICS_ATN", "Reference Wavelength", nullptr));
        refWavelengthRadioButton1->setText(QCoreApplication::translate("ConfigOSICS_ATN", "<ref wavelength 1>", nullptr));
        refWavelengthRadioButton2->setText(QCoreApplication::translate("ConfigOSICS_ATN", "<ref wavelength 2>", nullptr));
        powerUnitEditLabel_2->setText(QCoreApplication::translate("ConfigOSICS_ATN", "db", nullptr));
        label_29->setText(QCoreApplication::translate("ConfigOSICS_ATN", "Max Offset", nullptr));
        label_28->setText(QCoreApplication::translate("ConfigOSICS_ATN", "Min Offset", nullptr));
        maxAttenuationOffsetDisplay->setText(QCoreApplication::translate("ConfigOSICS_ATN", "10", nullptr));
        maxPowerDisplayUnitLabel_2->setText(QCoreApplication::translate("ConfigOSICS_ATN", "db", nullptr));
        minAttenuationOffsetDisplay->setText(QCoreApplication::translate("ConfigOSICS_ATN", "-10", nullptr));
        minPowerDisplayUnitLabel_2->setText(QCoreApplication::translate("ConfigOSICS_ATN", "db", nullptr));
        powerDisplayUnitLabel_2->setText(QCoreApplication::translate("ConfigOSICS_ATN", "db", nullptr));
        label_27->setText(QCoreApplication::translate("ConfigOSICS_ATN", "Attenuation Offset", nullptr));
        powerUnitEditLabel->setText(QCoreApplication::translate("ConfigOSICS_ATN", "db", nullptr));
        minPowerDisplayUnitLabel->setText(QCoreApplication::translate("ConfigOSICS_ATN", "db", nullptr));
        powerDisplayUnitLabel->setText(QCoreApplication::translate("ConfigOSICS_ATN", "db", nullptr));
        label_25->setText(QCoreApplication::translate("ConfigOSICS_ATN", "Max Attenuation", nullptr));
        label_26->setText(QCoreApplication::translate("ConfigOSICS_ATN", "Min Attenuation", nullptr));
        label_3->setText(QCoreApplication::translate("ConfigOSICS_ATN", "Attenuation", nullptr));
        maxPowerDisplayUnitLabel->setText(QCoreApplication::translate("ConfigOSICS_ATN", "db", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ConfigOSICS_ATN: public Ui_ConfigOSICS_ATN {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONFIGOSICS_ATN_H
