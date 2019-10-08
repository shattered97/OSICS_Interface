#include "wavstep_power_monitoring_graph_window.h"
#include "ui_wavstep_power_monitoring_graph_window.h"
#include <QDebug>
#include <QtCharts/QLineSeries>
#include <QtCharts/QChartView>
#include "ConversionUtilities.h"


WavStep_Power_Monitoring_Graph_Window::WavStep_Power_Monitoring_Graph_Window(QList<QByteArray> seriesNames, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::wavstep_power_monitoring_graph_window)
{
    ui->setupUi(this);
    this->seriesNames = seriesNames;

}

WavStep_Power_Monitoring_Graph_Window::~WavStep_Power_Monitoring_Graph_Window()
{
    delete ui;
}

void WavStep_Power_Monitoring_Graph_Window::slotGraphPowerMeterReadings(WavStepPowerTestData allData){
    QtCharts::QChart *chart = new QtCharts::QChart();

    // match each series name
    for(auto e : seriesNames){

        // make new graph series
        QtCharts::QLineSeries *series = new QtCharts::QLineSeries();
        series->setName(e);
        for(auto dataPoint : *allData.value(e)){

            double powerInDBm = ConversionUtilities::convertWattToDBm(dataPoint.second.toDouble());
            series->append(dataPoint.first.toDouble(),  powerInDBm);
        }

        chart->addSeries(series);
        chart->createDefaultAxes();
        chart->legend()->setVisible(true);
        QtCharts::QChartView *chartView = new QtCharts::QChartView(chart);
        this->setCentralWidget(chartView);
    }

}
