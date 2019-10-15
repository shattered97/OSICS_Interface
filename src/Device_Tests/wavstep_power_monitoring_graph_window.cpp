#include "wavstep_power_monitoring_graph_window.h"
#include "ui_wavstep_power_monitoring_graph_window.h"
#include <QDebug>
#include <QtCharts/QLineSeries>
#include <QtCharts/QChartView>
#include "ConversionUtilities.h"


WavStep_Power_Monitoring_Graph_Window::WavStep_Power_Monitoring_Graph_Window(QList<QByteArray> seriesNames,
                                                                             int maxSeriesSize, int refreshTimeMsec,
                                                                             QWidget *parent) : QMainWindow(parent),
    ui(new Ui::wavstep_power_monitoring_graph_window)
{
    ui->setupUi(this);

    qRegisterMetaType<QList<WavStep_Power_Monitoring_Data_Point>>();

    this->seriesNames = seriesNames;
    this->maxSeriesSize = maxSeriesSize;
    this->refreshTimeMsec = refreshTimeMsec;

    // set value of max number of points per series
    maxPointsPerSeries = maxSeriesSize * seriesNames.size();

    qDebug() << "initializng chart";
    // initialize chart
    chart = new QtCharts::QChart();

    qDebug() << "creating series";
    // create a series for each power meter / channel combination
    for(auto name : seriesNames){
        name = name.replace(",", "");

        QtCharts::QLineSeries *series = new QtCharts::QLineSeries();
        series->setName(name);

        chart->addSeries(series);
        chartSeries.append(series);
    }

    qDebug() << "initializing axes";
    // initialize axes
    chart->createDefaultAxes();
    chart->axes(Qt::Horizontal).first()->setTitleText("Test Runtime (s)");
    chart->axes(Qt::Vertical).first()->setTitleText("Power Reading (dBm)");

    // set remaining chart settings
    chart->legend()->setAlignment(Qt::AlignRight);
    chart->legend()->setVisible(true);
    chartView = new QtCharts::QChartView(chart);
    this->setCentralWidget(chartView);

    timer = new QElapsedTimer();
    timer->start();

    qDebug() << "done with setup";
}

WavStep_Power_Monitoring_Graph_Window::~WavStep_Power_Monitoring_Graph_Window()
{
    // signal to the test class --> power power meter polling worker to emit finished()
    emit signalStopWorkerThreads();

    delete chart;
    delete chartView;

    for(auto item : chartSeries){
        delete item;
    }

    delete ui;
}

void WavStep_Power_Monitoring_Graph_Window::slotAddReadingsToGraph(QList<WavStep_Power_Monitoring_Data_Point> dataPoints)
{
    for(auto dataPoint : dataPoints){
        // get data from dataPoint
        QByteArray seriesName = dataPoint.getPowerMeterChannelName();
        QByteArray powerReading = dataPoint.getPowerReading();
        QByteArray readingTime = dataPoint.getReadingTime();
        QByteArray wavelength = dataPoint.getWavelength();
        qDebug() << "======================================";
        qDebug() << seriesName;
        qDebug() << powerReading;
        qDebug() << readingTime;
        qDebug() << wavelength;

        // change title to include wavelength
        QString title = QString("Power Reading vs Time.  Current Wavelength = " + wavelength);
        chart->setTitle(title);

        // get series that matches the series name in dataPoint
        for(auto series : chartSeries){
            QString firstName = series->name();
            QString secondName = seriesName;

            if(firstName == secondName){
                // we found the match, now construct and add data point to series

                if(dataPointCount >= maxPointsPerSeries){
                    // remove datapoint from beginning if the max size has been reached
                    series->remove(0);
                }

                double timeInSeconds = dataPoint.getReadingTime().toDouble();
                double powerInDBm = ConversionUtilities::convertWattToDBm(dataPoint.getPowerReading().toDouble());

                qDebug() << "ADDING DATA POINT: " << timeInSeconds << " , " << powerInDBm << " , " << series->name();
                // append data point to series
                series->append({timeInSeconds, powerInDBm});

                dataPointCount++;
           }
        }
    }

    qDebug() << timer->elapsed() << "   >=  " << refreshTimeMsec;
    if(timer->elapsed() >= refreshTimeMsec){
        for(auto series : chartSeries){
            chart->removeSeries(series);
            chart->addSeries(series);
        }

        chart->createDefaultAxes();

        chartView = new QtCharts::QChartView(chart);
        this->setCentralWidget(chartView);

        // reset timer
        timer->start();
    }
}
