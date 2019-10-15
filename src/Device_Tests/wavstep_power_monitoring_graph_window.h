#ifndef WAVSTEP_POWER_MONITORING_GRAPH_WINDOW_H
#define WAVSTEP_POWER_MONITORING_GRAPH_WINDOW_H

#include <QMainWindow>
#include "constants.h"
#include <QtCharts/QLineSeries>
#include <QtCharts/QChartView>
#include <QChartView>
#include <QtCharts>
#include "wavstep_power_monitoring_data_point.h"
#include <QMetaType>
namespace Ui {
class wavstep_power_monitoring_graph_window;
}

Q_DECLARE_METATYPE(QList<WavStep_Power_Monitoring_Data_Point>)

class WavStep_Power_Monitoring_Graph_Window : public QMainWindow
{
    Q_OBJECT

public:
    explicit WavStep_Power_Monitoring_Graph_Window(QList<QByteArray> seriesNames, int maxSeriesSize,
                                                   int refreshTimeMsec, QWidget *parent = nullptr);
    ~WavStep_Power_Monitoring_Graph_Window();

signals:
    void signalStopWorkerThreads();
public slots:
    void slotAddReadingsToGraph(QList<WavStep_Power_Monitoring_Data_Point> dataPoints);

private:
    Ui::wavstep_power_monitoring_graph_window *ui;

    QList<QByteArray> seriesNames;
    QList<QLineSeries*> chartSeries;
    QChart *chart;
    QChartView *chartView;
    int dataPointCount = 0;
    int maxSeriesSize = 0;
    int maxPointsPerSeries = 0;
    QElapsedTimer *timer;
    int refreshTimeMsec = 0;

};

#endif // WAVSTEP_POWER_MONITORING_GRAPH_WINDOW_H
