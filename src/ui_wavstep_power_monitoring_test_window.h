/********************************************************************************
** Form generated from reading UI file 'wavstep_power_monitoring_test_window.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WAVSTEP_POWER_MONITORING_TEST_WINDOW_H
#define UI_WAVSTEP_POWER_MONITORING_TEST_WINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WavStep_Power_Monitoring_Test_Window
{
public:
    QWidget *centralwidget;
    QLabel *testIDLabel;
    QTableWidget *powerMeterTable;
    QPushButton *beginTestPB;
    QLabel *csvLocLabel;
    QLineEdit *csvLocDisplay;
    QGroupBox *groupBox;
    QComboBox *swtChannel2ComboBox;
    QComboBox *swtChannel3ComboBox;
    QComboBox *swtChannel4ComboBox;
    QComboBox *swtChannel1ComboBox;
    QLabel *label;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_2;
    QGroupBox *groupBox_2;
    QLineEdit *maxWavDisplay;
    QLineEdit *endWavLineEdit;
    QLineEdit *startWavLineEdit;
    QLineEdit *minWavDisplay;
    QLabel *startWavLabel;
    QLabel *endWavLabel;
    QLabel *minWavelengthLabel;
    QLabel *maxWavLabel;
    QGroupBox *groupBox_3;
    QRadioButton *dwellMsecRadioButton;
    QLabel *dwellLabel;
    QRadioButton *dwellMinRadioButton;
    QLineEdit *stepSizeLineEdit;
    QRadioButton *dwellSRadioButton;
    QLineEdit *dwellLineEdit;
    QLabel *stepSizeLabel;
    QLabel *currentWavLabel;
    QLineEdit *currentWavDisplay;
    QLineEdit *estimatedTimeDisplay;
    QLabel *estimatedTimeLabel;
    QPushButton *openGraphWindowButton;
    QPushButton *selectCsvLocButton;
    QLineEdit *graphRefreshRateEdit;
    QLabel *graphRefreshLabel;
    QMenuBar *menubar;
    QStatusBar *statusbar;
    QButtonGroup *buttonGroup;

    void setupUi(QMainWindow *WavStep_Power_Monitoring_Test_Window)
    {
        if (WavStep_Power_Monitoring_Test_Window->objectName().isEmpty())
            WavStep_Power_Monitoring_Test_Window->setObjectName(QString::fromUtf8("WavStep_Power_Monitoring_Test_Window"));
        WavStep_Power_Monitoring_Test_Window->resize(1024, 768);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(WavStep_Power_Monitoring_Test_Window->sizePolicy().hasHeightForWidth());
        WavStep_Power_Monitoring_Test_Window->setSizePolicy(sizePolicy);
        WavStep_Power_Monitoring_Test_Window->setMinimumSize(QSize(1024, 768));
        WavStep_Power_Monitoring_Test_Window->setMaximumSize(QSize(1024, 768));
        centralwidget = new QWidget(WavStep_Power_Monitoring_Test_Window);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        testIDLabel = new QLabel(centralwidget);
        testIDLabel->setObjectName(QString::fromUtf8("testIDLabel"));
        testIDLabel->setGeometry(QRect(20, 0, 341, 21));
        QFont font;
        font.setPointSize(14);
        testIDLabel->setFont(font);
        powerMeterTable = new QTableWidget(centralwidget);
        if (powerMeterTable->columnCount() < 4)
            powerMeterTable->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        powerMeterTable->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        powerMeterTable->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        powerMeterTable->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        powerMeterTable->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        powerMeterTable->setObjectName(QString::fromUtf8("powerMeterTable"));
        powerMeterTable->setGeometry(QRect(10, 260, 1001, 351));
        QFont font1;
        font1.setPointSize(12);
        powerMeterTable->setFont(font1);
        powerMeterTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
        powerMeterTable->setTextElideMode(Qt::ElideMiddle);
        beginTestPB = new QPushButton(centralwidget);
        beginTestPB->setObjectName(QString::fromUtf8("beginTestPB"));
        beginTestPB->setEnabled(true);
        beginTestPB->setGeometry(QRect(870, 630, 141, 41));
        beginTestPB->setFont(font);
        beginTestPB->setCheckable(false);
        csvLocLabel = new QLabel(centralwidget);
        csvLocLabel->setObjectName(QString::fromUtf8("csvLocLabel"));
        csvLocLabel->setGeometry(QRect(20, 670, 261, 41));
        csvLocLabel->setFont(font1);
        csvLocDisplay = new QLineEdit(centralwidget);
        csvLocDisplay->setObjectName(QString::fromUtf8("csvLocDisplay"));
        csvLocDisplay->setEnabled(false);
        csvLocDisplay->setGeometry(QRect(210, 680, 501, 41));
        csvLocDisplay->setFont(font1);
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(10, 50, 331, 191));
        groupBox->setFont(font1);
        swtChannel2ComboBox = new QComboBox(groupBox);
        swtChannel2ComboBox->addItem(QString());
        swtChannel2ComboBox->setObjectName(QString::fromUtf8("swtChannel2ComboBox"));
        swtChannel2ComboBox->setGeometry(QRect(140, 70, 181, 31));
        swtChannel3ComboBox = new QComboBox(groupBox);
        swtChannel3ComboBox->addItem(QString());
        swtChannel3ComboBox->setObjectName(QString::fromUtf8("swtChannel3ComboBox"));
        swtChannel3ComboBox->setGeometry(QRect(140, 110, 181, 31));
        swtChannel4ComboBox = new QComboBox(groupBox);
        swtChannel4ComboBox->addItem(QString());
        swtChannel4ComboBox->setObjectName(QString::fromUtf8("swtChannel4ComboBox"));
        swtChannel4ComboBox->setGeometry(QRect(140, 150, 181, 31));
        swtChannel1ComboBox = new QComboBox(groupBox);
        swtChannel1ComboBox->addItem(QString());
        swtChannel1ComboBox->setObjectName(QString::fromUtf8("swtChannel1ComboBox"));
        swtChannel1ComboBox->setGeometry(QRect(140, 30, 181, 31));
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 40, 111, 16));
        label->setFont(font1);
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(10, 120, 111, 16));
        label_3->setFont(font1);
        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(10, 160, 111, 16));
        label_4->setFont(font1);
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(10, 80, 111, 16));
        label_2->setFont(font1);
        groupBox_2 = new QGroupBox(centralwidget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(350, 10, 331, 231));
        groupBox_2->setFont(font1);
        maxWavDisplay = new QLineEdit(groupBox_2);
        maxWavDisplay->setObjectName(QString::fromUtf8("maxWavDisplay"));
        maxWavDisplay->setEnabled(false);
        maxWavDisplay->setGeometry(QRect(10, 180, 141, 41));
        maxWavDisplay->setFont(font1);
        endWavLineEdit = new QLineEdit(groupBox_2);
        endWavLineEdit->setObjectName(QString::fromUtf8("endWavLineEdit"));
        endWavLineEdit->setEnabled(true);
        endWavLineEdit->setGeometry(QRect(10, 80, 141, 41));
        endWavLineEdit->setFont(font1);
        startWavLineEdit = new QLineEdit(groupBox_2);
        startWavLineEdit->setObjectName(QString::fromUtf8("startWavLineEdit"));
        startWavLineEdit->setEnabled(true);
        startWavLineEdit->setGeometry(QRect(10, 30, 141, 41));
        startWavLineEdit->setFont(font1);
        minWavDisplay = new QLineEdit(groupBox_2);
        minWavDisplay->setObjectName(QString::fromUtf8("minWavDisplay"));
        minWavDisplay->setEnabled(false);
        minWavDisplay->setGeometry(QRect(10, 130, 141, 41));
        minWavDisplay->setFont(font1);
        startWavLabel = new QLabel(groupBox_2);
        startWavLabel->setObjectName(QString::fromUtf8("startWavLabel"));
        startWavLabel->setGeometry(QRect(160, 30, 211, 41));
        startWavLabel->setFont(font1);
        endWavLabel = new QLabel(groupBox_2);
        endWavLabel->setObjectName(QString::fromUtf8("endWavLabel"));
        endWavLabel->setGeometry(QRect(160, 80, 211, 41));
        endWavLabel->setFont(font1);
        minWavelengthLabel = new QLabel(groupBox_2);
        minWavelengthLabel->setObjectName(QString::fromUtf8("minWavelengthLabel"));
        minWavelengthLabel->setGeometry(QRect(160, 130, 181, 41));
        minWavelengthLabel->setFont(font1);
        maxWavLabel = new QLabel(groupBox_2);
        maxWavLabel->setObjectName(QString::fromUtf8("maxWavLabel"));
        maxWavLabel->setGeometry(QRect(160, 180, 181, 41));
        maxWavLabel->setFont(font1);
        groupBox_3 = new QGroupBox(centralwidget);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setGeometry(QRect(690, 10, 321, 231));
        groupBox_3->setFont(font1);
        dwellMsecRadioButton = new QRadioButton(groupBox_3);
        buttonGroup = new QButtonGroup(WavStep_Power_Monitoring_Test_Window);
        buttonGroup->setObjectName(QString::fromUtf8("buttonGroup"));
        buttonGroup->addButton(dwellMsecRadioButton);
        dwellMsecRadioButton->setObjectName(QString::fromUtf8("dwellMsecRadioButton"));
        dwellMsecRadioButton->setGeometry(QRect(220, 60, 71, 20));
        QFont font2;
        font2.setPointSize(7);
        dwellMsecRadioButton->setFont(font2);
        dwellLabel = new QLabel(groupBox_3);
        dwellLabel->setObjectName(QString::fromUtf8("dwellLabel"));
        dwellLabel->setGeometry(QRect(160, 40, 211, 21));
        dwellLabel->setFont(font1);
        dwellMinRadioButton = new QRadioButton(groupBox_3);
        buttonGroup->addButton(dwellMinRadioButton);
        dwellMinRadioButton->setObjectName(QString::fromUtf8("dwellMinRadioButton"));
        dwellMinRadioButton->setGeometry(QRect(220, 20, 71, 20));
        dwellMinRadioButton->setFont(font2);
        stepSizeLineEdit = new QLineEdit(groupBox_3);
        stepSizeLineEdit->setObjectName(QString::fromUtf8("stepSizeLineEdit"));
        stepSizeLineEdit->setEnabled(true);
        stepSizeLineEdit->setGeometry(QRect(10, 80, 141, 41));
        stepSizeLineEdit->setFont(font1);
        dwellSRadioButton = new QRadioButton(groupBox_3);
        buttonGroup->addButton(dwellSRadioButton);
        dwellSRadioButton->setObjectName(QString::fromUtf8("dwellSRadioButton"));
        dwellSRadioButton->setGeometry(QRect(220, 40, 71, 20));
        dwellSRadioButton->setFont(font2);
        dwellSRadioButton->setChecked(true);
        dwellLineEdit = new QLineEdit(groupBox_3);
        dwellLineEdit->setObjectName(QString::fromUtf8("dwellLineEdit"));
        dwellLineEdit->setEnabled(true);
        dwellLineEdit->setGeometry(QRect(10, 30, 141, 41));
        dwellLineEdit->setFont(font1);
        stepSizeLabel = new QLabel(groupBox_3);
        stepSizeLabel->setObjectName(QString::fromUtf8("stepSizeLabel"));
        stepSizeLabel->setGeometry(QRect(160, 80, 211, 41));
        stepSizeLabel->setFont(font1);
        currentWavLabel = new QLabel(groupBox_3);
        currentWavLabel->setObjectName(QString::fromUtf8("currentWavLabel"));
        currentWavLabel->setGeometry(QRect(160, 180, 211, 41));
        currentWavLabel->setFont(font1);
        currentWavDisplay = new QLineEdit(groupBox_3);
        currentWavDisplay->setObjectName(QString::fromUtf8("currentWavDisplay"));
        currentWavDisplay->setEnabled(false);
        currentWavDisplay->setGeometry(QRect(10, 180, 141, 41));
        currentWavDisplay->setFont(font1);
        estimatedTimeDisplay = new QLineEdit(groupBox_3);
        estimatedTimeDisplay->setObjectName(QString::fromUtf8("estimatedTimeDisplay"));
        estimatedTimeDisplay->setEnabled(false);
        estimatedTimeDisplay->setGeometry(QRect(10, 130, 141, 41));
        estimatedTimeDisplay->setFont(font1);
        estimatedTimeLabel = new QLabel(groupBox_3);
        estimatedTimeLabel->setObjectName(QString::fromUtf8("estimatedTimeLabel"));
        estimatedTimeLabel->setGeometry(QRect(160, 130, 211, 41));
        estimatedTimeLabel->setFont(font1);
        openGraphWindowButton = new QPushButton(centralwidget);
        openGraphWindowButton->setObjectName(QString::fromUtf8("openGraphWindowButton"));
        openGraphWindowButton->setEnabled(false);
        openGraphWindowButton->setGeometry(QRect(870, 680, 141, 41));
        openGraphWindowButton->setFont(font);
        openGraphWindowButton->setCheckable(false);
        selectCsvLocButton = new QPushButton(centralwidget);
        selectCsvLocButton->setObjectName(QString::fromUtf8("selectCsvLocButton"));
        selectCsvLocButton->setEnabled(true);
        selectCsvLocButton->setGeometry(QRect(710, 680, 101, 41));
        selectCsvLocButton->setFont(font);
        selectCsvLocButton->setCheckable(false);
        graphRefreshRateEdit = new QLineEdit(centralwidget);
        graphRefreshRateEdit->setObjectName(QString::fromUtf8("graphRefreshRateEdit"));
        graphRefreshRateEdit->setEnabled(true);
        graphRefreshRateEdit->setGeometry(QRect(210, 620, 91, 41));
        graphRefreshRateEdit->setFont(font1);
        graphRefreshLabel = new QLabel(centralwidget);
        graphRefreshLabel->setObjectName(QString::fromUtf8("graphRefreshLabel"));
        graphRefreshLabel->setGeometry(QRect(20, 620, 211, 41));
        graphRefreshLabel->setFont(font1);
        WavStep_Power_Monitoring_Test_Window->setCentralWidget(centralwidget);
        groupBox->raise();
        testIDLabel->raise();
        powerMeterTable->raise();
        beginTestPB->raise();
        csvLocLabel->raise();
        csvLocDisplay->raise();
        groupBox_2->raise();
        groupBox_3->raise();
        openGraphWindowButton->raise();
        selectCsvLocButton->raise();
        graphRefreshRateEdit->raise();
        graphRefreshLabel->raise();
        menubar = new QMenuBar(WavStep_Power_Monitoring_Test_Window);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1024, 17));
        WavStep_Power_Monitoring_Test_Window->setMenuBar(menubar);
        statusbar = new QStatusBar(WavStep_Power_Monitoring_Test_Window);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        WavStep_Power_Monitoring_Test_Window->setStatusBar(statusbar);

        retranslateUi(WavStep_Power_Monitoring_Test_Window);

        QMetaObject::connectSlotsByName(WavStep_Power_Monitoring_Test_Window);
    } // setupUi

    void retranslateUi(QMainWindow *WavStep_Power_Monitoring_Test_Window)
    {
        WavStep_Power_Monitoring_Test_Window->setWindowTitle(QCoreApplication::translate("WavStep_Power_Monitoring_Test_Window", "MainWindow", nullptr));
        testIDLabel->setText(QCoreApplication::translate("WavStep_Power_Monitoring_Test_Window", "EXFO OSICS Wavelength Cycle Test", nullptr));
        QTableWidgetItem *___qtablewidgetitem = powerMeterTable->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("WavStep_Power_Monitoring_Test_Window", "Power Meter", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = powerMeterTable->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("WavStep_Power_Monitoring_Test_Window", "Channel", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = powerMeterTable->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("WavStep_Power_Monitoring_Test_Window", "Graph", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = powerMeterTable->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("WavStep_Power_Monitoring_Test_Window", "Power (dBm)", nullptr));
        beginTestPB->setText(QCoreApplication::translate("WavStep_Power_Monitoring_Test_Window", "Begin Test", nullptr));
        csvLocLabel->setText(QCoreApplication::translate("WavStep_Power_Monitoring_Test_Window", "Location of Graph .csv:", nullptr));
        csvLocDisplay->setText(QString());
        groupBox->setTitle(QCoreApplication::translate("WavStep_Power_Monitoring_Test_Window", "Select T100 Lasers for each Switch Channel", nullptr));
        swtChannel2ComboBox->setItemText(0, QCoreApplication::translate("WavStep_Power_Monitoring_Test_Window", "<None>", nullptr));

        swtChannel3ComboBox->setItemText(0, QCoreApplication::translate("WavStep_Power_Monitoring_Test_Window", "<None>", nullptr));

        swtChannel4ComboBox->setItemText(0, QCoreApplication::translate("WavStep_Power_Monitoring_Test_Window", "<None>", nullptr));

        swtChannel1ComboBox->setItemText(0, QCoreApplication::translate("WavStep_Power_Monitoring_Test_Window", "<None>", nullptr));

        swtChannel1ComboBox->setCurrentText(QCoreApplication::translate("WavStep_Power_Monitoring_Test_Window", "<None>", nullptr));
        label->setText(QCoreApplication::translate("WavStep_Power_Monitoring_Test_Window", "SWT Channel 1", nullptr));
        label_3->setText(QCoreApplication::translate("WavStep_Power_Monitoring_Test_Window", "SWT Channel 3", nullptr));
        label_4->setText(QCoreApplication::translate("WavStep_Power_Monitoring_Test_Window", "SWT Channel 4", nullptr));
        label_2->setText(QCoreApplication::translate("WavStep_Power_Monitoring_Test_Window", "SWT Channel 2", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("WavStep_Power_Monitoring_Test_Window", "Wavelength Settings", nullptr));
        maxWavDisplay->setText(QString());
        endWavLineEdit->setText(QString());
        startWavLineEdit->setText(QString());
        minWavDisplay->setText(QString());
        startWavLabel->setText(QCoreApplication::translate("WavStep_Power_Monitoring_Test_Window", "Start Wavelength (nm)", nullptr));
        endWavLabel->setText(QCoreApplication::translate("WavStep_Power_Monitoring_Test_Window", "End Wavelength (nm)", nullptr));
        minWavelengthLabel->setText(QCoreApplication::translate("WavStep_Power_Monitoring_Test_Window", "Min Wavelength (nm)", nullptr));
        maxWavLabel->setText(QCoreApplication::translate("WavStep_Power_Monitoring_Test_Window", "Max Wavelength (nm)", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("WavStep_Power_Monitoring_Test_Window", "Test Timing / Metrics", nullptr));
        dwellMsecRadioButton->setText(QCoreApplication::translate("WavStep_Power_Monitoring_Test_Window", "msec", nullptr));
        dwellLabel->setText(QCoreApplication::translate("WavStep_Power_Monitoring_Test_Window", "Dwell", nullptr));
        dwellMinRadioButton->setText(QCoreApplication::translate("WavStep_Power_Monitoring_Test_Window", "min", nullptr));
        stepSizeLineEdit->setText(QString());
        dwellSRadioButton->setText(QCoreApplication::translate("WavStep_Power_Monitoring_Test_Window", "sec", nullptr));
        dwellLineEdit->setText(QString());
        stepSizeLabel->setText(QCoreApplication::translate("WavStep_Power_Monitoring_Test_Window", "Step Size (nm)", nullptr));
        currentWavLabel->setText(QCoreApplication::translate("WavStep_Power_Monitoring_Test_Window", "Current Wavelength (nm)", nullptr));
        currentWavDisplay->setText(QString());
        estimatedTimeDisplay->setText(QString());
        estimatedTimeLabel->setText(QCoreApplication::translate("WavStep_Power_Monitoring_Test_Window", "Estimated Test Time", nullptr));
        openGraphWindowButton->setText(QCoreApplication::translate("WavStep_Power_Monitoring_Test_Window", "Display Graph", nullptr));
        selectCsvLocButton->setText(QCoreApplication::translate("WavStep_Power_Monitoring_Test_Window", "Select", nullptr));
        graphRefreshRateEdit->setText(QCoreApplication::translate("WavStep_Power_Monitoring_Test_Window", "1", nullptr));
        graphRefreshLabel->setText(QCoreApplication::translate("WavStep_Power_Monitoring_Test_Window", "Graph Refresh Speed (s)", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WavStep_Power_Monitoring_Test_Window: public Ui_WavStep_Power_Monitoring_Test_Window {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WAVSTEP_POWER_MONITORING_TEST_WINDOW_H
