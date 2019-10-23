/********************************************************************************
** Form generated from reading UI file 'exfo_operationaltest_t100_swt_atn_window.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EXFO_OPERATIONALTEST_T100_SWT_ATN_WINDOW_H
#define UI_EXFO_OPERATIONALTEST_T100_SWT_ATN_WINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_EXFO_OperationalTest_T100_SWT_ATN_Window
{
public:
    QWidget *centralwidget;
    QPushButton *runTestButton;
    QLineEdit *outuptFilenameLineEdit;
    QPushButton *outputFileButton;
    QLabel *directionsTextField;
    QLabel *directionsImageLabel;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *EXFO_OperationalTest_T100_SWT_ATN_Window)
    {
        if (EXFO_OperationalTest_T100_SWT_ATN_Window->objectName().isEmpty())
            EXFO_OperationalTest_T100_SWT_ATN_Window->setObjectName(QString::fromUtf8("EXFO_OperationalTest_T100_SWT_ATN_Window"));
        EXFO_OperationalTest_T100_SWT_ATN_Window->resize(1024, 786);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(EXFO_OperationalTest_T100_SWT_ATN_Window->sizePolicy().hasHeightForWidth());
        EXFO_OperationalTest_T100_SWT_ATN_Window->setSizePolicy(sizePolicy);
        centralwidget = new QWidget(EXFO_OperationalTest_T100_SWT_ATN_Window);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        runTestButton = new QPushButton(centralwidget);
        runTestButton->setObjectName(QString::fromUtf8("runTestButton"));
        runTestButton->setGeometry(QRect(430, 620, 161, 61));
        QFont font;
        font.setPointSize(14);
        runTestButton->setFont(font);
        outuptFilenameLineEdit = new QLineEdit(centralwidget);
        outuptFilenameLineEdit->setObjectName(QString::fromUtf8("outuptFilenameLineEdit"));
        outuptFilenameLineEdit->setEnabled(false);
        outuptFilenameLineEdit->setGeometry(QRect(30, 530, 711, 41));
        outuptFilenameLineEdit->setReadOnly(true);
        outputFileButton = new QPushButton(centralwidget);
        outputFileButton->setObjectName(QString::fromUtf8("outputFileButton"));
        outputFileButton->setGeometry(QRect(750, 530, 221, 41));
        outputFileButton->setFont(font);
        directionsTextField = new QLabel(centralwidget);
        directionsTextField->setObjectName(QString::fromUtf8("directionsTextField"));
        directionsTextField->setGeometry(QRect(640, 40, 341, 401));
        directionsTextField->setFont(font);
        directionsTextField->setAlignment(Qt::AlignCenter);
        directionsTextField->setWordWrap(true);
        directionsImageLabel = new QLabel(centralwidget);
        directionsImageLabel->setObjectName(QString::fromUtf8("directionsImageLabel"));
        directionsImageLabel->setGeometry(QRect(30, 20, 551, 461));
        directionsImageLabel->setPixmap(QPixmap(QString::fromUtf8("../img/EXFO_DRAWING_OPTEST1_SETUP_T100_POWER_STEP_TEST.PNG")));
        directionsImageLabel->setScaledContents(true);
        EXFO_OperationalTest_T100_SWT_ATN_Window->setCentralWidget(centralwidget);
        runTestButton->raise();
        outuptFilenameLineEdit->raise();
        outputFileButton->raise();
        directionsImageLabel->raise();
        directionsTextField->raise();
        menubar = new QMenuBar(EXFO_OperationalTest_T100_SWT_ATN_Window);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1024, 17));
        EXFO_OperationalTest_T100_SWT_ATN_Window->setMenuBar(menubar);
        statusbar = new QStatusBar(EXFO_OperationalTest_T100_SWT_ATN_Window);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        EXFO_OperationalTest_T100_SWT_ATN_Window->setStatusBar(statusbar);

        retranslateUi(EXFO_OperationalTest_T100_SWT_ATN_Window);

        QMetaObject::connectSlotsByName(EXFO_OperationalTest_T100_SWT_ATN_Window);
    } // setupUi

    void retranslateUi(QMainWindow *EXFO_OperationalTest_T100_SWT_ATN_Window)
    {
        EXFO_OperationalTest_T100_SWT_ATN_Window->setWindowTitle(QCoreApplication::translate("EXFO_OperationalTest_T100_SWT_ATN_Window", "MainWindow", nullptr));
        runTestButton->setText(QCoreApplication::translate("EXFO_OperationalTest_T100_SWT_ATN_Window", "Run", nullptr));
        outputFileButton->setText(QCoreApplication::translate("EXFO_OperationalTest_T100_SWT_ATN_Window", "Choose Output File", nullptr));
        directionsTextField->setText(QCoreApplication::translate("EXFO_OperationalTest_T100_SWT_ATN_Window", "PLACEHOLDER TEXT", nullptr));
        directionsImageLabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class EXFO_OperationalTest_T100_SWT_ATN_Window: public Ui_EXFO_OperationalTest_T100_SWT_ATN_Window {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EXFO_OPERATIONALTEST_T100_SWT_ATN_WINDOW_H
