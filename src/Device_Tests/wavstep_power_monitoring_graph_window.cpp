#include "wavstep_power_monitoring_graph_window.h"
#include "ui_wavstep_power_monitoring_graph_window.h"


WavStep_Power_Monitoring_Graph_Window::WavStep_Power_Monitoring_Graph_Window(QList<QByteArray> seriesNames,
                                                                             int maxSeriesSize, double refreshTimeMsec,
                                                                             QWidget *parent) : QMainWindow(parent),
    ui(new Ui::wavstep_power_monitoring_graph_window)
{
    ui->setupUi(this);

    this->seriesNames = seriesNames;
    this->refreshTimeMsec = refreshTimeMsec;
    this->maxSeriesSize = maxSeriesSize;

    setupGraphing();

    // needed for using signals/slots with parameters of this type
    qRegisterMetaType<QList<WavStepPowerMonitoringDataPoint>>();
}

WavStep_Power_Monitoring_Graph_Window::~WavStep_Power_Monitoring_Graph_Window()
{
    delete chart;
    delete chartView;
    delete ui;
}

void WavStep_Power_Monitoring_Graph_Window::setupGraphing(){


    // set up keys for map of series names to QPoint lists
    for(auto name : seriesNames){
        name = name.replace(",", "");
        QList<QPointF> placeholder;
        pointsLists.append(placeholder);
        pointsListIndexPerSeries.insert(name, pointsLists.size() - 1);
    }



    // begin refresh timer
    timer.start();
}

void WavStep_Power_Monitoring_Graph_Window::processDataPoint(WavStepPowerMonitoringDataPoint dataPoint){
    QByteArray seriesName = dataPoint.powerMeterChannelName;
    QByteArray powerReading = dataPoint.powerReading;
    QByteArray readingTime = dataPoint.readingTime;
    QByteArray wavelength = dataPoint.wavelength;

    // get list of QPoints from map
    if(pointsListIndexPerSeries.keys().contains(seriesName)){
        int index = pointsListIndexPerSeries.value(seriesName);
        QList<QPointF> points = pointsLists[index];

        maintainSeriesSize(points);

        // construct data point and add to points list
        double timeInSeconds = readingTime.toDouble();
        double powerInDBm = ConversionUtilities::convertWattToDBm(powerReading.toDouble());

        // append data point to list of points
        points.append({timeInSeconds, powerInDBm});

        pointsLists[index] = points;
   }


}

void WavStep_Power_Monitoring_Graph_Window::maintainSeriesSize(QList<QPointF> &points){
    // if the list contains >= maxSeriesSize, knock off the first value
//    qDebug() << points.size();
    if(points.size() >= maxSeriesSize){
        points.removeFirst();
    }

}

void WavStep_Power_Monitoring_Graph_Window::slotAddReadingsToGraph(QList<WavStepPowerMonitoringDataPoint> dataPoints)
{

    mutex.lock();

    for(int i = 0; i < dataPoints.size(); i++){
        processDataPoint(dataPoints[i]);
    }


    // set wavelength to the last data point's wavelength
    wavelength = dataPoints.last().wavelength.toDouble();

    // update graph display
    drawGraph();


    mutex.unlock();

}

void WavStep_Power_Monitoring_Graph_Window::drawGraph()
{

    // re-draw graph if refresh rate time has been reached
    if(timer.elapsed() >= refreshTimeMsec){

        chart = new QtCharts::QChart();

        for(auto seriesName : pointsListIndexPerSeries.keys()){
            QLineSeries *series = new QLineSeries();
            series->setName(seriesName);
            int index = pointsListIndexPerSeries.value(seriesName);
            series->append(pointsLists[index]);
            chart->addSeries(series);
        }

        chart->createDefaultAxes();
        chart->axes(Qt::Horizontal).first()->setTitleText("Test Runtime (s)");
        chart->axes(Qt::Vertical).first()->setTitleText("Power Reading (dBm)");

        // set remaining chart settings
        chart->legend()->setAlignment(Qt::AlignRight);
        chart->legend()->setVisible(true);

        // change title to include wavelength
        QString title = QString("Power Reading vs Time.  Current Wavelength = " + QString::number(wavelength));
        chart->setTitle(title);

        chartView = new QtCharts::QChartView(chart);
        this->setCentralWidget(chartView);

        // reset timer
        timer.restart();
    }
}
