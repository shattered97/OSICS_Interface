#include "wavstep_power_monitoring_graph_window.h"
#include "ui_wavstep_power_monitoring_graph_window.h"


WavStep_Power_Monitoring_Graph_Window::WavStep_Power_Monitoring_Graph_Window(QList<QByteArray> seriesNames,
                                                                             int maxSeriesSize, int refreshTimeMsec,
                                                                             QWidget *parent) : QMainWindow(parent),
    ui(new Ui::wavstep_power_monitoring_graph_window)
{
    ui->setupUi(this);

    this->seriesNames = seriesNames;
    this->maxSeriesSize = maxSeriesSize;
    this->refreshTimeMsec = refreshTimeMsec;

    // needed for using signals/slots with parameters of this type
    qRegisterMetaType<QList<WavStep_Power_Monitoring_Data_Point>>();
}


WavStep_Power_Monitoring_Graph_Window::~WavStep_Power_Monitoring_Graph_Window()
{
    delete chart;
    delete chartView;
    delete timer;
    delete ui;
}

void WavStep_Power_Monitoring_Graph_Window::setupGraphing(){
    // set up keys for map of series names to QPoint lists
    for(auto name : seriesNames){
        name = name.replace(",", "");
        QList<QPointF> placeholder;
        pointsPerSeries.insert(name, placeholder);
    }

    // begin refresh timer
    timer = new QElapsedTimer();
    timer->start();
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

        // get list of QPoints from map
        if(pointsPerSeries.contains(seriesName)){
            QList<QPointF> points = pointsPerSeries.value(seriesName);

            // if the list contains >= maxSeriesSize, knock off the first value
            if(points.size() >= maxSeriesSize){
                points.removeFirst();
            }

            // construct data point and add to points list
            double timeInSeconds = dataPoint.getReadingTime().toDouble();
            double powerInDBm = ConversionUtilities::convertWattToDBm(dataPoint.getPowerReading().toDouble());


            qDebug() << "ADDING DATA POINT: " << timeInSeconds << " , " << powerInDBm << " , " << seriesName;

            // append data point to list of points
            points.append({timeInSeconds, powerInDBm});
        }
    }

    // update graph display
    drawGraph();
}

void WavStep_Power_Monitoring_Graph_Window::drawGraph()
{
    qDebug() << timer->elapsed() << "   >=  " << refreshTimeMsec;

    // re-draw graph if refresh rate time has been reached
    if(timer->elapsed() >= refreshTimeMsec){

        chart = new QtCharts::QChart();
        for(auto seriesName : pointsPerSeries.keys()){
            QtCharts::QLineSeries *series = new QtCharts::QLineSeries();
            series->setName(seriesName);
            series->append(pointsPerSeries.value(seriesName));
            chart->addSeries(series);
        }

        // initialize axes
        chart->createDefaultAxes();
        chart->axes(Qt::Horizontal).first()->setTitleText("Test Runtime (s)");
        chart->axes(Qt::Vertical).first()->setTitleText("Power Reading (dBm)");

        // set remaining chart settings
        chart->legend()->setAlignment(Qt::AlignRight);
        chart->legend()->setVisible(true);
        QtCharts::QChartView *chartView = new QtCharts::QChartView(chart);
        this->setCentralWidget(chartView);

        // reset timer
        timer->restart();
    }
}
