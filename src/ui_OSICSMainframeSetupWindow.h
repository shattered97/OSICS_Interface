/********************************************************************************
** Form generated from reading UI file 'OSICSMainframeSetupWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OSICSMAINFRAMESETUPWINDOW_H
#define UI_OSICSMAINFRAMESETUPWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_OSICSMainframeSetupWindow
{
public:
    QWidget *centralwidget;
    QLabel *instrumentAddressLabel;
    QLabel *instrumentInfoLabel;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QGroupBox *slot1GroupBox;
    QPushButton *configSlot1Btn;
    QGroupBox *slot2GroupBox;
    QPushButton *configSlot2Btn;
    QGroupBox *slot3GroupBox;
    QPushButton *configSlot3Btn;
    QGroupBox *slot4GroupBox;
    QPushButton *configSlot4Btn;
    QGroupBox *slot5GroupBox;
    QPushButton *configSlot5Btn;
    QGroupBox *slot6GroupBox;
    QPushButton *configSlot6Btn;
    QGroupBox *slot7GroupBox;
    QPushButton *configSlot7Btn;
    QGroupBox *slot8GroupBox;
    QPushButton *configSlot8Btn;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout_2;
    QWidget *layoutWidget2;
    QHBoxLayout *moduleNameLabelLayout;
    QMenuBar *menubar;
    QStatusBar *statusbar;
    QButtonGroup *configureButtonGroup;

    void setupUi(QMainWindow *OSICSMainframeSetupWindow)
    {
        if (OSICSMainframeSetupWindow->objectName().isEmpty())
            OSICSMainframeSetupWindow->setObjectName(QString::fromUtf8("OSICSMainframeSetupWindow"));
        OSICSMainframeSetupWindow->resize(1024, 768);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(OSICSMainframeSetupWindow->sizePolicy().hasHeightForWidth());
        OSICSMainframeSetupWindow->setSizePolicy(sizePolicy);
        centralwidget = new QWidget(OSICSMainframeSetupWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        instrumentAddressLabel = new QLabel(centralwidget);
        instrumentAddressLabel->setObjectName(QString::fromUtf8("instrumentAddressLabel"));
        instrumentAddressLabel->setGeometry(QRect(10, 40, 771, 41));
        QFont font;
        font.setPointSize(12);
        instrumentAddressLabel->setFont(font);
        instrumentInfoLabel = new QLabel(centralwidget);
        instrumentInfoLabel->setObjectName(QString::fromUtf8("instrumentInfoLabel"));
        instrumentInfoLabel->setGeometry(QRect(10, 10, 771, 31));
        instrumentInfoLabel->setFont(font);
        layoutWidget = new QWidget(centralwidget);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 90, 1001, 161));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        slot1GroupBox = new QGroupBox(layoutWidget);
        slot1GroupBox->setObjectName(QString::fromUtf8("slot1GroupBox"));
        slot1GroupBox->setFont(font);
        configSlot1Btn = new QPushButton(slot1GroupBox);
        configureButtonGroup = new QButtonGroup(OSICSMainframeSetupWindow);
        configureButtonGroup->setObjectName(QString::fromUtf8("configureButtonGroup"));
        configureButtonGroup->addButton(configSlot1Btn);
        configSlot1Btn->setObjectName(QString::fromUtf8("configSlot1Btn"));
        configSlot1Btn->setGeometry(QRect(20, 120, 81, 31));
        configSlot1Btn->setFont(font);

        horizontalLayout->addWidget(slot1GroupBox);

        slot2GroupBox = new QGroupBox(layoutWidget);
        slot2GroupBox->setObjectName(QString::fromUtf8("slot2GroupBox"));
        slot2GroupBox->setFont(font);
        configSlot2Btn = new QPushButton(slot2GroupBox);
        configureButtonGroup->addButton(configSlot2Btn);
        configSlot2Btn->setObjectName(QString::fromUtf8("configSlot2Btn"));
        configSlot2Btn->setGeometry(QRect(20, 120, 81, 31));
        configSlot2Btn->setFont(font);

        horizontalLayout->addWidget(slot2GroupBox);

        slot3GroupBox = new QGroupBox(layoutWidget);
        slot3GroupBox->setObjectName(QString::fromUtf8("slot3GroupBox"));
        slot3GroupBox->setFont(font);
        configSlot3Btn = new QPushButton(slot3GroupBox);
        configureButtonGroup->addButton(configSlot3Btn);
        configSlot3Btn->setObjectName(QString::fromUtf8("configSlot3Btn"));
        configSlot3Btn->setGeometry(QRect(20, 120, 81, 31));
        configSlot3Btn->setFont(font);

        horizontalLayout->addWidget(slot3GroupBox);

        slot4GroupBox = new QGroupBox(layoutWidget);
        slot4GroupBox->setObjectName(QString::fromUtf8("slot4GroupBox"));
        slot4GroupBox->setFont(font);
        configSlot4Btn = new QPushButton(slot4GroupBox);
        configureButtonGroup->addButton(configSlot4Btn);
        configSlot4Btn->setObjectName(QString::fromUtf8("configSlot4Btn"));
        configSlot4Btn->setGeometry(QRect(20, 120, 81, 31));
        configSlot4Btn->setFont(font);

        horizontalLayout->addWidget(slot4GroupBox);

        slot5GroupBox = new QGroupBox(layoutWidget);
        slot5GroupBox->setObjectName(QString::fromUtf8("slot5GroupBox"));
        slot5GroupBox->setFont(font);
        configSlot5Btn = new QPushButton(slot5GroupBox);
        configureButtonGroup->addButton(configSlot5Btn);
        configSlot5Btn->setObjectName(QString::fromUtf8("configSlot5Btn"));
        configSlot5Btn->setGeometry(QRect(20, 120, 81, 31));
        configSlot5Btn->setFont(font);

        horizontalLayout->addWidget(slot5GroupBox);

        slot6GroupBox = new QGroupBox(layoutWidget);
        slot6GroupBox->setObjectName(QString::fromUtf8("slot6GroupBox"));
        slot6GroupBox->setFont(font);
        configSlot6Btn = new QPushButton(slot6GroupBox);
        configureButtonGroup->addButton(configSlot6Btn);
        configSlot6Btn->setObjectName(QString::fromUtf8("configSlot6Btn"));
        configSlot6Btn->setGeometry(QRect(20, 120, 81, 31));
        configSlot6Btn->setFont(font);

        horizontalLayout->addWidget(slot6GroupBox);

        slot7GroupBox = new QGroupBox(layoutWidget);
        slot7GroupBox->setObjectName(QString::fromUtf8("slot7GroupBox"));
        slot7GroupBox->setFont(font);
        configSlot7Btn = new QPushButton(slot7GroupBox);
        configureButtonGroup->addButton(configSlot7Btn);
        configSlot7Btn->setObjectName(QString::fromUtf8("configSlot7Btn"));
        configSlot7Btn->setGeometry(QRect(20, 120, 81, 31));
        configSlot7Btn->setFont(font);

        horizontalLayout->addWidget(slot7GroupBox);

        slot8GroupBox = new QGroupBox(layoutWidget);
        slot8GroupBox->setObjectName(QString::fromUtf8("slot8GroupBox"));
        slot8GroupBox->setFont(font);
        configSlot8Btn = new QPushButton(slot8GroupBox);
        configureButtonGroup->addButton(configSlot8Btn);
        configSlot8Btn->setObjectName(QString::fromUtf8("configSlot8Btn"));
        configSlot8Btn->setGeometry(QRect(20, 120, 81, 31));
        configSlot8Btn->setFont(font);

        horizontalLayout->addWidget(slot8GroupBox);

        layoutWidget1 = new QWidget(centralwidget);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(0, 0, 2, 2));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget1);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        layoutWidget2 = new QWidget(centralwidget);
        layoutWidget2->setObjectName(QString::fromUtf8("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(10, 110, 1001, 101));
        moduleNameLabelLayout = new QHBoxLayout(layoutWidget2);
        moduleNameLabelLayout->setObjectName(QString::fromUtf8("moduleNameLabelLayout"));
        moduleNameLabelLayout->setContentsMargins(0, 0, 0, 0);
        OSICSMainframeSetupWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(OSICSMainframeSetupWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1024, 17));
        OSICSMainframeSetupWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(OSICSMainframeSetupWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        OSICSMainframeSetupWindow->setStatusBar(statusbar);

        retranslateUi(OSICSMainframeSetupWindow);

        QMetaObject::connectSlotsByName(OSICSMainframeSetupWindow);
    } // setupUi

    void retranslateUi(QMainWindow *OSICSMainframeSetupWindow)
    {
        OSICSMainframeSetupWindow->setWindowTitle(QCoreApplication::translate("OSICSMainframeSetupWindow", "MainWindow", nullptr));
        instrumentAddressLabel->setText(QCoreApplication::translate("OSICSMainframeSetupWindow", "Address: ", nullptr));
        instrumentInfoLabel->setText(QCoreApplication::translate("OSICSMainframeSetupWindow", "Instrument: ", nullptr));
        slot1GroupBox->setTitle(QCoreApplication::translate("OSICSMainframeSetupWindow", "Slot 1", nullptr));
        configSlot1Btn->setText(QCoreApplication::translate("OSICSMainframeSetupWindow", "Configure", nullptr));
        slot2GroupBox->setTitle(QCoreApplication::translate("OSICSMainframeSetupWindow", "Slot 2", nullptr));
        configSlot2Btn->setText(QCoreApplication::translate("OSICSMainframeSetupWindow", "Configure", nullptr));
        slot3GroupBox->setTitle(QCoreApplication::translate("OSICSMainframeSetupWindow", "Slot 3", nullptr));
        configSlot3Btn->setText(QCoreApplication::translate("OSICSMainframeSetupWindow", "Configure", nullptr));
        slot4GroupBox->setTitle(QCoreApplication::translate("OSICSMainframeSetupWindow", "Slot 4", nullptr));
        configSlot4Btn->setText(QCoreApplication::translate("OSICSMainframeSetupWindow", "Configure", nullptr));
        slot5GroupBox->setTitle(QCoreApplication::translate("OSICSMainframeSetupWindow", "Slot 5", nullptr));
        configSlot5Btn->setText(QCoreApplication::translate("OSICSMainframeSetupWindow", "Configure", nullptr));
        slot6GroupBox->setTitle(QCoreApplication::translate("OSICSMainframeSetupWindow", "Slot 6", nullptr));
        configSlot6Btn->setText(QCoreApplication::translate("OSICSMainframeSetupWindow", "Configure", nullptr));
        slot7GroupBox->setTitle(QCoreApplication::translate("OSICSMainframeSetupWindow", "Slot 7", nullptr));
        configSlot7Btn->setText(QCoreApplication::translate("OSICSMainframeSetupWindow", "Configure", nullptr));
        slot8GroupBox->setTitle(QCoreApplication::translate("OSICSMainframeSetupWindow", "Slot 8", nullptr));
        configSlot8Btn->setText(QCoreApplication::translate("OSICSMainframeSetupWindow", "Configure", nullptr));
    } // retranslateUi

};

namespace Ui {
    class OSICSMainframeSetupWindow: public Ui_OSICSMainframeSetupWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OSICSMAINFRAMESETUPWINDOW_H
