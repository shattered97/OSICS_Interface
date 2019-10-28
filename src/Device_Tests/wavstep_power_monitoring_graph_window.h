#ifndef WAVSTEP_POWER_MONITORING_GRAPH_WINDOW_H
#define WAVSTEP_POWER_MONITORING_GRAPH_WINDOW_H

#include "constants.h"
#include "ConversionUtilities.h"

#include <QMainWindow>
#include <QtCharts/QLineSeries>
#include <QtCharts/QChartView>
#include <QChartView>
#include <QtCharts>
#include <QMetaType>
#include <QDebug>

namespace Ui {
class wavstep_power_monitoring_graph_window;
}

Q_DECLARE_METATYPE(QList<WavStepPowerMonitoringDataPoint>)

class WavStep_Power_Monitoring_Graph_Window : public QMainWindow
{
    Q_OBJECT

public:
    explicit WavStep_Power_Monitoring_Graph_Window(QList<QByteArray> seriesNames, int maxSeriesSize,
                                                   double refreshTimeMsec, QWidget *parent = nullptr);
    ~WavStep_Power_Monitoring_Graph_Window();

public slots:
    /**
     * @brief slotAddReadingsToGraph Takes list of data points, formats each as a QPointF for use in the graph
     *                               then adds the QPointF to the appropriate list in a QMap.
     * @param dataPoints List of data points containing series name, power reading, time of reading and wavelength
     *                   for each power meter channel (even those not selected for graphing)
     */
    void slotAddReadingsToGraph(QList<WavStepPowerMonitoringDataPoint> dataPoints);

private:
    Ui::wavstep_power_monitoring_graph_window *ui;

    QList<QByteArray> seriesNames;                        /* List of series names selected for graphing */
    QList<QList<QPointF>> pointsLists;
    QMap<QByteArray, int> pointsListIndexPerSeries;       /* Map of series name to index of list of associated data points */
    QChart *chart;                                          /* Graphical represntation of chart to display */
    QChartView *chartView;                          /* Standalone widget to display the chart */
    int maxSeriesSize = 0;                                  /* Max number of data points displayed for each series */
    QElapsedTimer timer;                                   /* Running timer between visual graph updates */
    double refreshTimeMsec = 0;                                /* Min time between graph re-draws */
    QMutex mutex;
    double wavelength = 0;

    /**
     * @brief drawGraph Creates a new graph from the current data in the pointsPerSeries map and displays it.
     */
    void drawGraph();

    /**
     * @brief setupGraphing Misc setup activities such as initializing series names and starting the timer
     *                      for tracking graph re-draws.
     */
    void setupGraphing();

    void processDataPoint(WavStepPowerMonitoringDataPoint dataPoint);
    void maintainSeriesSize(QList<QPointF> &points);
};

#endif // WAVSTEP_POWER_MONITORING_GRAPH_WINDOW_H
