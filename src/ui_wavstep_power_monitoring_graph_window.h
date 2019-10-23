/********************************************************************************
** Form generated from reading UI file 'wavstep_power_monitoring_graph_window.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WAVSTEP_POWER_MONITORING_GRAPH_WINDOW_H
#define UI_WAVSTEP_POWER_MONITORING_GRAPH_WINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_wavstep_power_monitoring_graph_window
{
public:
    QWidget *centralwidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *wavstep_power_monitoring_graph_window)
    {
        if (wavstep_power_monitoring_graph_window->objectName().isEmpty())
            wavstep_power_monitoring_graph_window->setObjectName(QString::fromUtf8("wavstep_power_monitoring_graph_window"));
        wavstep_power_monitoring_graph_window->resize(1024, 768);
        centralwidget = new QWidget(wavstep_power_monitoring_graph_window);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        wavstep_power_monitoring_graph_window->setCentralWidget(centralwidget);
        menubar = new QMenuBar(wavstep_power_monitoring_graph_window);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1024, 17));
        wavstep_power_monitoring_graph_window->setMenuBar(menubar);
        statusbar = new QStatusBar(wavstep_power_monitoring_graph_window);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        wavstep_power_monitoring_graph_window->setStatusBar(statusbar);

        retranslateUi(wavstep_power_monitoring_graph_window);

        QMetaObject::connectSlotsByName(wavstep_power_monitoring_graph_window);
    } // setupUi

    void retranslateUi(QMainWindow *wavstep_power_monitoring_graph_window)
    {
        wavstep_power_monitoring_graph_window->setWindowTitle(QCoreApplication::translate("wavstep_power_monitoring_graph_window", "MainWindow", nullptr));
    } // retranslateUi

};

namespace Ui {
    class wavstep_power_monitoring_graph_window: public Ui_wavstep_power_monitoring_graph_window {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WAVSTEP_POWER_MONITORING_GRAPH_WINDOW_H
