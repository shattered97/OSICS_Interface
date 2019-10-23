/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QLabel *powerStatusIndicator;
    QPushButton *searchForDevTypeBtn;
    QListWidget *foundDevicesListWidget;
    QPushButton *addSelectedDeviceBtn;
    QListWidget *selectedDevicesListWidget;
    QLabel *label_6;
    QPushButton *startTestPushButton;
    QLabel *label_7;
    QComboBox *testTypeComboBox;
    QLabel *label_8;
    QComboBox *devicetypeComboBox;
    QPushButton *clearSelectedListButton;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1024, 768);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setMinimumSize(QSize(1024, 768));
        MainWindow->setMaximumSize(QSize(1024, 768));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        powerStatusIndicator = new QLabel(centralWidget);
        powerStatusIndicator->setObjectName(QString::fromUtf8("powerStatusIndicator"));
        powerStatusIndicator->setGeometry(QRect(590, 10, 55, 51));
        searchForDevTypeBtn = new QPushButton(centralWidget);
        searchForDevTypeBtn->setObjectName(QString::fromUtf8("searchForDevTypeBtn"));
        searchForDevTypeBtn->setEnabled(true);
        searchForDevTypeBtn->setGeometry(QRect(680, 120, 121, 41));
        QFont font;
        font.setPointSize(14);
        searchForDevTypeBtn->setFont(font);
        foundDevicesListWidget = new QListWidget(centralWidget);
        foundDevicesListWidget->setObjectName(QString::fromUtf8("foundDevicesListWidget"));
        foundDevicesListWidget->setEnabled(true);
        foundDevicesListWidget->setGeometry(QRect(30, 160, 651, 221));
        foundDevicesListWidget->setFont(font);
        addSelectedDeviceBtn = new QPushButton(centralWidget);
        addSelectedDeviceBtn->setObjectName(QString::fromUtf8("addSelectedDeviceBtn"));
        addSelectedDeviceBtn->setEnabled(false);
        addSelectedDeviceBtn->setGeometry(QRect(430, 380, 251, 41));
        QFont font1;
        font1.setFamily(QString::fromUtf8("MS Shell Dlg 2"));
        font1.setPointSize(14);
        addSelectedDeviceBtn->setFont(font1);
        selectedDevicesListWidget = new QListWidget(centralWidget);
        selectedDevicesListWidget->setObjectName(QString::fromUtf8("selectedDevicesListWidget"));
        selectedDevicesListWidget->setEnabled(true);
        selectedDevicesListWidget->setGeometry(QRect(30, 440, 641, 221));
        selectedDevicesListWidget->setFont(font);
        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(30, 410, 391, 31));
        label_6->setFont(font);
        startTestPushButton = new QPushButton(centralWidget);
        startTestPushButton->setObjectName(QString::fromUtf8("startTestPushButton"));
        startTestPushButton->setEnabled(true);
        startTestPushButton->setGeometry(QRect(760, 520, 221, 101));
        startTestPushButton->setFont(font);
        label_7 = new QLabel(centralWidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(30, 10, 461, 31));
        label_7->setFont(font);
        testTypeComboBox = new QComboBox(centralWidget);
        testTypeComboBox->setObjectName(QString::fromUtf8("testTypeComboBox"));
        testTypeComboBox->setGeometry(QRect(30, 40, 651, 41));
        QFont font2;
        font2.setPointSize(12);
        testTypeComboBox->setFont(font2);
        label_8 = new QLabel(centralWidget);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(30, 90, 181, 31));
        label_8->setFont(font);
        devicetypeComboBox = new QComboBox(centralWidget);
        devicetypeComboBox->setObjectName(QString::fromUtf8("devicetypeComboBox"));
        devicetypeComboBox->setGeometry(QRect(30, 120, 651, 41));
        devicetypeComboBox->setFont(font);
        clearSelectedListButton = new QPushButton(centralWidget);
        clearSelectedListButton->setObjectName(QString::fromUtf8("clearSelectedListButton"));
        clearSelectedListButton->setEnabled(true);
        clearSelectedListButton->setGeometry(QRect(430, 660, 241, 41));
        clearSelectedListButton->setFont(font);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1024, 21));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        powerStatusIndicator->setText(QString());
        searchForDevTypeBtn->setText(QCoreApplication::translate("MainWindow", "Search", nullptr));
        addSelectedDeviceBtn->setText(QCoreApplication::translate("MainWindow", "Add To Selected Devices", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "Selected Devices", nullptr));
        startTestPushButton->setText(QCoreApplication::translate("MainWindow", "Start Test", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "Select Test Type:", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "Device Type:", nullptr));
        clearSelectedListButton->setText(QCoreApplication::translate("MainWindow", "Clear List", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
