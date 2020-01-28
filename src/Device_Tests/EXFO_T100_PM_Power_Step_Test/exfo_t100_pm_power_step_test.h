#ifndef EXFO_T100_PM_POWER_STEP_TEST_H
#define EXFO_T100_PM_POWER_STEP_TEST_H

#include "DeviceTest.h"
#include "EXFO_OSICS/EXFO_OSICS_T100.h"
#include "EXFO_T100_PM_Power_Step_Test_Worker.h"
#include "PowerMeter.h"

class EXFO_T100_PM_Power_Step_Test : public DeviceTest
{
    Q_OBJECT
public:
    EXFO_T100_PM_Power_Step_Test(QList<QVariant> &selectedDevices, QMainWindow &configWindow);

    /**
     * @brief areDevicesValidForTest Checks if the selected devices from the main menu are
     * valid for this particular test (Need one power meter and at least one T100 in an EXFO Mainframe).
     * Also initializes the pointers to the valid devices as it's checking them.
     * @return True if devices are valid, false otherwise.
     */
    bool areDevicesValidForTest();

    /**
     * @brief runDeviceTest Responsible for starting test execution (worker threads).
     */
    void runDeviceTest();

    /**
     * @brief runTestLoop Responsible for carrying out the test procedure commands and querying data.
     * @param filename Output filename for test data
     * @param startPow Beginning power value
     * @param endPow Ending power value
     * @param powStep Amount of power to increase each iteration
     * @param wavelength Wavelength value during test
     * @param dwell Amount of time to wait after setting the power and before reading the power.
     */
    void runTestLoop(QByteArray filename, double startPow, double endPow, double powStep, double wavelength,
                     double dwell, QMap<int, int> t100SlotNumToPMSlotNumMap);

    /**
     * @brief calculateNumberOfSteps Calculates the total number of steps that the test must take.
     */
    void calculateNumberOfSteps();

    /**
     * @brief calculateProgress Calculates the current test's progress based on the number of steps completed
     * divided by the total steps.
     * @return Progress percentage.
     */
    double calculateProgress();

    /**
     * @brief setStartPower Sets the test's Start Power value. Used by other tests (see operational test) that
     * execute this test as part of a sequence.
     * @param startPower Start Power to set.
     */
    void setStartPower(double startPower);

    /**
     * @brief setEndPower Sets the test's End Power value. Used by other tests (see operational test) that
     * execute this test as part of a sequence.
     * @param endPower End Power to set.
     */
    void setEndPower(double endPower);

    /**
     * @brief setPowerStep Sets the test's step size value. Used by other tests (see operational test) that
     * execute this test as part of a sequence.
     * @param powerStep Step size to set.
     */
    void setPowerStep(double powerStep);

    /**
     * @brief setWavelength Sets the test's wavelength value. Used by other tests (see operational test) that
     * execute this test as part of a sequence.
     * @param wavelength Wavelength to set.
     */
    void setWavelength(double wavelength);

//    /**
//     * @brief setPowerMeterSlotNum Sets the power meter slot number. Used by other tests (see operational test)
//     * that execute this test as part of a sequence.
//     * @param slotNum Slot Number to set.
//     */
//    void setPowerMeterSlotNum(int slotNum);

signals:

    /**
     * @brief signalSendTestProgressToGUI Sends the current test's progress (by percentage) for
     * display in the GUI's progress bar.
     * @param progressPercent Test progress percentage
     */
    void signalSendTestProgressToGUI(double progressPercent);

    void signalTestComplete();

    void signalGUIProcessEvents();

public slots:

    /**
     * @brief slotReturnT100DisplayNames Returns a list of formatted display names for all available
     * T100 modules in the EXFO chassis.
     * @param displayNames Display names so the user knows which T100 to select (type and slot number).
     */
    void slotReturnT100DisplayNames(QList<QByteArray> &displayNames);

    /**
     * @brief slotReturnPowerMeterChannels Returns the number of power meter slots to the GUI for display
     * @param numberOfSlots Number of slots/channels available on the power meter
     */
    void slotReturnPowerMeterChannels(int &numberOfSlots);

    /**
     * @brief slotBeginTest Initializes test (get settings, filename, etc.) then calls the
     * method responsible for running the test.
     * @param settings Settings returned from GUI input
     */
    void slotBeginTest(QSettings *settings);

private:

    // hardware variables
    QList<EXFO_OSICS_T100*> availableT100s;
    EXFO_OSICS_T100* selectedT100 = nullptr;
    PowerMeter *powerMeter = nullptr;
    QMap<int, int> t100SlotNumToPMSlotNumMap;

    // used to get test params from window
    QSettings *settings = nullptr;

    // test parameters
    double startPowerDBM = 0;
    double endPowerDBM = 0;
    double powerStepDBM = 0;
    double dwellInSeconds = 0;
    double wavelengthNM = 0;

    // progress variables
    int numberOfSteps = 0;
    int currentStep = 0;

    // data collection variables
    QList<QString> testData;
    QByteArray outputFilename;

    // multithreading variables
    QThread *workerThread;
    EXFO_T100_PM_Power_Step_Test_Worker *worker;

    /**
     * @brief constructOutputFilename Creates an output filename for the test data based on the type of
     * module being tested and the current timestamp
     * @return Ouptut filename for the test.
     */
    QByteArray constructOutputFilename();

    /**
     * @brief writeTestDataToFile Write out the single buffer containing all test data to the output file.
     * @param filename Output file name
     */
    void writeTestDataToFile(QByteArray filename);

    /**
     * @brief getTestValuesFromSettings Pulls any needed test parameter data from the QSettings object
     * and stores it in member vars.
     */
    void getTestValuesFromSettings();

    EXFO_OSICS_T100* getT100BySlotNum(int slotNum);

};

#endif // EXFO_T100_PM_POWER_STEP_TEST_H
