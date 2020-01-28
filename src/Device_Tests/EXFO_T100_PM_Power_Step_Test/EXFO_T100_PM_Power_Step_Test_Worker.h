#ifndef EXFO_T100_PM_POWER_STEP_TEST_WORKER_H
#define EXFO_T100_PM_POWER_STEP_TEST_WORKER_H

#include <QObject>
#include <QThread>
#include <EXFO_OSICS_T100.h>
#include <PowerMeter.h>

class EXFO_T100_PM_Power_Step_Test_Worker : public QObject
{
    Q_OBJECT

public:
    EXFO_T100_PM_Power_Step_Test_Worker(double startPowerDBM, double endPowerDBM, double powerStepDBM,
                                        double dwellInSeconds, double wavelengthNM, QObject *parent = nullptr);


signals:

    void signalTestCompleted();

public slots:

    void runTest();

private:

    void executeTest();

    void executeTestStep();

    // test parameters
    double startPowerDBM = 0;
    double endPowerDBM = 0;
    double powerStepDBM = 0;
    double dwellInSeconds = 0;
    double wavelengthNM = 0;

    // progress variables
    int numberOfSteps = 0;
    int currentStep = 0;

};

#endif // EXFO_T100_PM_POWER_STEP_TEST_WORKER_H
