#ifndef WAVSTEP_POWER_MONITORING_GRAPH_WINDOW_H
#define WAVSTEP_POWER_MONITORING_GRAPH_WINDOW_H

#include <QMainWindow>
#include "constants.h"
#include <QtCharts/QLineSeries>
#include <QtCharts/QChartView>

namespace Ui {
class wavstep_power_monitoring_graph_window;
}

class WavStep_Power_Monitoring_Graph_Window : public QMainWindow
{
    Q_OBJECT

public:
    explicit WavStep_Power_Monitoring_Graph_Window(QList<QByteArray> seriesNames, QWidget *parent = nullptr);
    ~WavStep_Power_Monitoring_Graph_Window();

signals:
    void signalStopWorkerThreads();
public slots:
    void slotGraphPowerMeterReadings(WavStepPowerTestData allData);

private:
    Ui::wavstep_power_monitoring_graph_window *ui;

    QList<QByteArray> seriesNames;
};

#endif // WAVSTEP_POWER_MONITORING_GRAPH_WINDOW_H
