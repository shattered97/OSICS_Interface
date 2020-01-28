#include "EXFO_T100_PM_Power_Step_Test_Worker.h"

EXFO_T100_PM_Power_Step_Test_Worker::EXFO_T100_PM_Power_Step_Test_Worker(double startPowerDBM,
                                                                         double endPowerDBM,
                                                                         double powerStepDBM,
                                                                         double dwellInSeconds,
                                                                         double wavelengthNM,
                                                                         QObject *parent) :
    QObject(parent)
{
    this->startPowerDBM = startPowerDBM;
    this->endPowerDBM = endPowerDBM;
    this->powerStepDBM = powerStepDBM;
    this->dwellInSeconds = dwellInSeconds;
    this->wavelengthNM = wavelengthNM;
}

void EXFO_T100_PM_Power_Step_Test_Worker::runTest()
{
    //#TODO set
}

void EXFO_T100_PM_Power_Step_Test_Worker::executeTest()
{

}

void EXFO_T100_PM_Power_Step_Test_Worker::executeTestStep()
{

}
