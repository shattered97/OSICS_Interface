#include "N7714A.h"

N7714A::N7714A( QByteArray theIdentity, QByteArray theInstrLoc) : DefaultInstrument(theIdentity, theInstrLoc)
{
    this->theIdentity = theIdentity;
    this->theInstrLoc = theInstrLoc;
}


void N7714A::queryPowerUnit(int module, QByteArray &response){

    QByteArray baseCmd = N7714A_POW_UNIT_QUERY;
    int paramPosition = baseCmd.indexOf(':');
    QString param = QString("%1").arg(module);

    QByteArray command = QString(baseCmd.insert(paramPosition, param)).toLatin1();

    // send command
    emit signalSendCmdRsp(theInstrLoc, command, response);
    qDebug() << "response" << response;
}

void N7714A::execPowerUnit(int module, QByteArray unit){
    QByteArray baseCmd = N7714A_POW_UNIT_CMD;

    // outp1:pow:un w
    int paramPosition = baseCmd.indexOf(':');
    QString param = QString("%1").arg(module);

    QByteArray command = QString(baseCmd.insert(paramPosition, param)).toLatin1();

    command.insert(command.indexOf('\n'), " " + unit);

    qDebug() << command;

    // send command
    emit signalSendCmdNoRsp(theInstrLoc, command);
}

void N7714A::queryPowerStatus(int module, QByteArray &response){

    QByteArray baseCmd = N7714A_POW_STAT_QUERY;
    int paramPosition = baseCmd.indexOf(':');
    QString param = QString("%1").arg(module);

    QByteArray command = QString(baseCmd.insert(paramPosition, param)).toLatin1();

    // send command
    emit signalSendCmdRsp(theInstrLoc, command, response);

}

void N7714A::execPowerOnModule(int module){

    QByteArray baseCmd = N7714A_POW_ON_CMD;
    int paramPosition = baseCmd.indexOf(':');
    QString param = QString("%1").arg(module);

    QByteArray command = QString(baseCmd.insert(paramPosition, param)).toLatin1();

    emit signalSendCmdNoRsp(theInstrLoc, command);
}

void N7714A::execPowerOffModule(int module){
    QByteArray baseCmd = N7714A_POW_OFF_CMD;
    int paramPosition = baseCmd.indexOf(':');
    QString param = QString("%1").arg(module);

    QByteArray command = QString(baseCmd.insert(paramPosition, param)).toLatin1();

    emit signalSendCmdNoRsp(theInstrLoc, command);
}

void N7714A::queryPowerLevel(int module, QByteArray &response, QByteArray value){
    QByteArray baseCmd = N7714A_POW_LEVEL_QUERY;
    int modulePos = baseCmd.indexOf(':');

    QString moduleString = QString("%1").arg(module);
    QByteArray command = QString(baseCmd.insert(modulePos, moduleString)).toLatin1();

    int valuePos = command.indexOf('\n');
    command = QString(command.insert(valuePos, " " + value)).toLatin1();

    // send command
    emit signalSendCmdRsp(theInstrLoc, command, response);
}

void N7714A::execPowerLevel(int module, QByteArray value, QByteArray unit){
    QByteArray baseCmd = N7714A_POW_LEVEL_CMD;
    int modulePos = baseCmd.indexOf(':');

    QString moduleString = QString("%1").arg(module);
    QByteArray command = QString(baseCmd.insert(modulePos, moduleString)).toLatin1();

    int valuePos = command.indexOf('\n');
    command = QString(command.insert(valuePos, " " + value)).toLatin1();

    valuePos = command.indexOf('\n');
    command = QString(command.insert(valuePos, unit)).toLatin1();
    // send command
    emit signalSendCmdNoRsp(theInstrLoc, command);
}

void N7714A::queryWavelength(int module, QByteArray &response, QByteArray value){
    QByteArray baseCmd = N7714A_WAV_QUERY;

    int modulePos = baseCmd.indexOf(':');

    QString moduleString = QString("%1").arg(module);
    QByteArray command = QString(baseCmd.insert(modulePos, moduleString)).toLatin1();

    int valuePos = command.indexOf('\n');
    command = QString(command.insert(valuePos, " " + value)).toLatin1();

    // send command
    emit signalSendCmdRsp(theInstrLoc, command, response);
}

void N7714A::execWavelength(int module, QByteArray value, QByteArray unit){
    QByteArray baseCmd = N7714A_WAV_CMD;
    int modulePos = baseCmd.indexOf(':');

    QString moduleString = QString("%1").arg(module);
    QByteArray command = QString(baseCmd.insert(modulePos, moduleString)).toLatin1();

    int valuePos = command.indexOf('\n');
    command = QString(command.insert(valuePos, " " + value)).toLatin1();

    command.insert(command.indexOf('\n'), unit);

    // send command
    emit signalSendCmdNoRsp(theInstrLoc, command);
}

void N7714A::queryFrequency(int module, QByteArray &response, QByteArray value){
    QByteArray baseCmd = N7714A_FREQ_QUERY;
    int modulePos = baseCmd.indexOf(':');

    QString moduleString = QString("%1").arg(module);
    QByteArray command = QString(baseCmd.insert(modulePos, moduleString)).toLatin1();

    int valuePos = command.indexOf('\n');
    command = QString(command.insert(valuePos, " " + value)).toLatin1();

    // send command
    emit signalSendCmdRsp(theInstrLoc, command, response);
}

void N7714A::execFrequency(int module, QByteArray value, QByteArray unit){
    QByteArray baseCmd = N7714A_FREQ_CMD;
    int modulePos = baseCmd.indexOf(':');

    QString moduleString = QString("%1").arg(module);
    QByteArray command = QString(baseCmd.insert(modulePos, moduleString)).toLatin1();

    int valuePos = command.indexOf('\n');
    command = QString(command.insert(valuePos, " " + value)).toLatin1();

    command.insert(command.indexOf('\n'), unit);

    // send command
    emit signalSendCmdNoRsp(theInstrLoc, command);
}

void N7714A::testCommand(QByteArray cmd, QByteArray &response){
    cmd = cmd + '\n';
    emit signalSendCmdRsp(theInstrLoc, cmd, response);
}

void N7714A::queryAutoWavMode(int module, QByteArray &response){
    QByteArray baseCmd = "sour:wav:auto?";
    baseCmd.insert(baseCmd.indexOf(':'), QByteArray::number(module));

    emit signalSendCmdRsp(theInstrLoc, baseCmd, response);
}

void N7714A::turnOnAutoWavMode(int module){
    QByteArray baseCmd = "sour:wav:auto on\n";

    baseCmd.insert(baseCmd.indexOf(':'), QByteArray::number(module));

    emit signalSendCmdNoRsp(theInstrLoc, baseCmd);
}

void N7714A::updateConfig(QSettings &configSettings){
    qDebug() << "n7714a update config";

    updatePowerSettings(configSettings);
    updateWavelengthSettings(configSettings);
    updateFrequencySettings(configSettings);
}

void N7714A::applyConfigSettings(QSettings &configSettings){
    // apply power settings to device
    QList<QByteArray> powerSettings = configSettings.value(N7714A_POWER_SETTINGS).value<QList<QByteArray>>();
    for(int i = 0; i <= N7714A_NUM_SLOTS; i++){
        int slot = i + 1;
        QByteArray unit = "Watt";
        execPowerLevel(slot, powerSettings[i], unit);
    }

    // apply wavelength settings to device
    QList<QByteArray> wavelengthSettings = configSettings.value(N7714A_WAVELENGTH_SETTINGS).value<QList<QByteArray>>();
    for(int i = 0; i <= N7714A_NUM_SLOTS; i++){
        int slot = i + 1;
        QByteArray unit = "m";
        execWavelength(slot, wavelengthSettings[i], unit);
    }

    // apply frequency settings to device
    QList<QByteArray> frequencySettings = configSettings.value(N7714A_FREQUENCY_SETTINGS).value<QList<QByteArray>>();
    for(int i = 0; i <= N7714A_NUM_SLOTS; i++){
        int slot = i + 1;
        QByteArray unit = "Hz";
        execFrequency(slot, frequencySettings[i], unit);
    }

    // update values
    updateConfig(configSettings);
}

void N7714A::updatePowerSettings(QSettings &configSettings){
    // query device for power values
    QList<QByteArray> powerSettings;
    QList<QByteArray> minPowerSettings;
    QList<QByteArray> maxPowerSettings;
    QList<QByteArray> laserStates;
    for(int i = 1; i <= N7714A_NUM_SLOTS; i++){
        QByteArray power;
        QByteArray minPower;
        QByteArray maxPower;
        QByteArray laserState;

        queryPowerLevel(i, power);
        powerSettings.append(QByteArray::number(power.toDouble()));

        queryPowerLevel(i, minPower, "MIN");
        minPowerSettings.append(QByteArray::number(minPower.toDouble()));

        queryPowerLevel(i, maxPower, "MAX");
        maxPowerSettings.append(QByteArray::number(maxPower.toDouble()));

        queryPowerStatus(i, laserState);
        laserStates.append(laserState);
    }

    // save to config
    configSettings.setValue(N7714A_POWER_SETTINGS, QVariant::fromValue(powerSettings));
    qDebug() << configSettings.value(N7714A_POWER_SETTINGS).value<QList<QByteArray>>();
    configSettings.setValue(N7714A_MIN_POWER, QVariant::fromValue(minPowerSettings));
    qDebug() << configSettings.value(N7714A_MIN_POWER).value<QList<QByteArray>>();
    configSettings.setValue(N7714A_MAX_POWER, QVariant::fromValue(maxPowerSettings));
    qDebug() << configSettings.value(N7714A_MAX_POWER).value<QList<QByteArray>>();
    configSettings.setValue(N7714A_LASER_STATE, QVariant::fromValue(laserStates));
    qDebug() << configSettings.value(N7714A_LASER_STATE).value<QList<QByteArray>>();
    configSettings.sync();
}

void N7714A::updateWavelengthSettings(QSettings &configSettings){
    QList<QByteArray> wavelengthSettings;
    QList<QByteArray> minWavelength;
    QList<QByteArray> maxWavelength;

    for(int i = 1; i <= N7714A_NUM_SLOTS; i++){
        QByteArray wavelength;
        queryWavelength(i, wavelength);
        wavelengthSettings.append(QByteArray::number(wavelength.toDouble()));

        queryWavelength(i, wavelength, "MIN");
        minWavelength.append(QByteArray::number(wavelength.toDouble()));

        queryWavelength(i, wavelength, "MAX");
        maxWavelength.append(QByteArray::number(wavelength.toDouble()));
    }

    // save to config
    configSettings.setValue(N7714A_WAVELENGTH_SETTINGS, QVariant::fromValue(wavelengthSettings));
    qDebug() << configSettings.value(N7714A_WAVELENGTH_SETTINGS).value<QList<QByteArray>>();
    configSettings.setValue(N7714A_MIN_WAVELENGTH, QVariant::fromValue(minWavelength));
    qDebug() << configSettings.value(N7714A_MIN_WAVELENGTH).value<QList<QByteArray>>();
    configSettings.setValue(N7714A_MAX_WAVELENGTH, QVariant::fromValue(maxWavelength));
    qDebug() << configSettings.value(N7714A_MAX_WAVELENGTH).value<QList<QByteArray>>();
    configSettings.sync();
}

void N7714A::updateFrequencySettings(QSettings &configSettings){

    QList<QByteArray> frequencySettings;
    QList<QByteArray> minFrequency;
    QList<QByteArray> maxFrequency;
    for(int i = 1; i <= N7714A_NUM_SLOTS; i++){
        QByteArray frequency;
        queryFrequency(i, frequency);
        frequencySettings.append(QByteArray::number(frequency.toDouble()));

        queryFrequency(i, frequency, "MIN");
        minFrequency.append(QByteArray::number(frequency.toDouble()));

        queryFrequency(i, frequency, "MAX");
        maxFrequency.append(QByteArray::number(frequency.toDouble()));
    }

    // save to config
    configSettings.setValue(N7714A_FREQUENCY_SETTINGS, QVariant::fromValue(frequencySettings));
    qDebug() << configSettings.value(N7714A_FREQUENCY_SETTINGS).value<QList<QByteArray>>();
    configSettings.setValue(N7714A_MIN_FREQUENCY, QVariant::fromValue(minFrequency));
    qDebug() << configSettings.value(N7714A_MIN_FREQUENCY).value<QList<QByteArray>>();
    configSettings.setValue(N7714A_MAX_FREQUENCY, QVariant::fromValue(maxFrequency));
    qDebug() << configSettings.value(N7714A_MAX_FREQUENCY).value<QList<QByteArray>>();
    configSettings.sync();

}

