#include "N7714A.h"

N7714A::N7714A( QByteArray theIdentity, QByteArray theInstrLoc) : DefaultInstrument(theIdentity, theInstrLoc)
{
    this->theIdentity = theIdentity;
    this->theInstrLoc = theInstrLoc;
}

QByteArray N7714A::queryPowerUnit(int module){

    QByteArray baseCmd = N7714A_POW_UNIT_QUERY;
    int paramPosition = baseCmd.indexOf(':');
    QString param = QString("%1").arg(module);

    baseCmd = QString(baseCmd.insert(paramPosition, param)).toLatin1();
    QByteArray response = "";

    sendCommandAndWaitForResponse(theInstrLoc, baseCmd, &response);
    return response;
}

void N7714A::execPowerUnit(int module, QByteArray unit){
    QByteArray baseCmd = N7714A_POW_UNIT_CMD;

    // outp1:pow:un w
    int paramPosition = baseCmd.indexOf(':');
    QString param = QString("%1").arg(module);

    baseCmd = QString(baseCmd.insert(paramPosition, param)).toLatin1();

    baseCmd.insert(baseCmd.indexOf('\n'), " " + unit);

    // send command
    emit signalSendCmdNoRsp(theInstrLoc, baseCmd);

}

QByteArray N7714A::queryPowerStatus(int module){

    QByteArray baseCmd = N7714A_POW_STAT_QUERY;
    int paramPosition = baseCmd.indexOf(':');
    QString param = QString("%1").arg(module);

    baseCmd = QString(baseCmd.insert(paramPosition, param)).toLatin1();
    QByteArray response = "";

    sendCommandAndWaitForResponse(theInstrLoc, baseCmd, &response);
    return response;
}

void N7714A::execPowerOnModule(int module){

    QByteArray baseCmd = N7714A_POW_ON_CMD;
    int paramPosition = baseCmd.indexOf(':');
    QString param = QString("%1").arg(module);

    baseCmd = QString(baseCmd.insert(paramPosition, param)).toLatin1();

    emit signalSendCmdNoRsp(theInstrLoc, baseCmd);
}

void N7714A::execPowerOffModule(int module){
    QByteArray baseCmd = N7714A_POW_OFF_CMD;
    int paramPosition = baseCmd.indexOf(':');
    QString param = QString("%1").arg(module);

    baseCmd = QString(baseCmd.insert(paramPosition, param)).toLatin1();

    emit signalSendCmdNoRsp(theInstrLoc, baseCmd);
}

QByteArray N7714A::queryPowerLevel(int module, QByteArray value){
    QByteArray baseCmd = N7714A_POW_LEVEL_QUERY;
    int modulePos = baseCmd.indexOf(':');

    QString moduleString = QString("%1").arg(module);
    baseCmd = QString(baseCmd.insert(modulePos, moduleString)).toLatin1();

    int valuePos = baseCmd.indexOf('\n');
    baseCmd = QString(baseCmd.insert(valuePos, " " + value)).toLatin1();
    QByteArray response = "";

    sendCommandAndWaitForResponse(theInstrLoc, baseCmd, &response);
    return response;
}

void N7714A::execPowerLevel(int module, QByteArray value, QByteArray unit){
    QByteArray baseCmd = N7714A_POW_LEVEL_CMD;
    int modulePos = baseCmd.indexOf(':');

    QString moduleString = QString("%1").arg(module);
    baseCmd = QString(baseCmd.insert(modulePos, moduleString)).toLatin1();

    int valuePos = baseCmd.indexOf('\n');
    baseCmd = QString(baseCmd.insert(valuePos, " " + value)).toLatin1();

    valuePos = baseCmd.indexOf('\n');
    baseCmd = QString(baseCmd.insert(valuePos, unit)).toLatin1();

    emit signalSendCmdNoRsp(theInstrLoc, baseCmd);
}

QByteArray N7714A::queryWavelength(int module, QByteArray value){
    QByteArray baseCmd = N7714A_WAV_QUERY;

    int modulePos = baseCmd.indexOf(':');

    QString moduleString = QString("%1").arg(module);
    baseCmd = QString(baseCmd.insert(modulePos, moduleString)).toLatin1();

    int valuePos = baseCmd.indexOf('\n');
    baseCmd = QString(baseCmd.insert(valuePos, " " + value)).toLatin1();
    QByteArray response = "";
    // send command
    sendCommandAndWaitForResponse(theInstrLoc, baseCmd, &response);
    return response;
}

void N7714A::execWavelength(int module, QByteArray value, QByteArray unit){
    QByteArray baseCmd = N7714A_WAV_CMD;
    int modulePos = baseCmd.indexOf(':');

    QString moduleString = QString("%1").arg(module);
    baseCmd = QString(baseCmd.insert(modulePos, moduleString)).toLatin1();

    int valuePos = baseCmd.indexOf('\n');
    baseCmd = QString(baseCmd.insert(valuePos, " " + value)).toLatin1();

    baseCmd.insert(baseCmd.indexOf('\n'), unit);

    // send command
    emit signalSendCmdNoRsp(theInstrLoc, baseCmd);
}

QByteArray N7714A::queryFrequency(int module, QByteArray value){
    QByteArray baseCmd = N7714A_FREQ_QUERY;
    int modulePos = baseCmd.indexOf(':');

    QString moduleString = QString("%1").arg(module);
    baseCmd = QString(baseCmd.insert(modulePos, moduleString)).toLatin1();

    int valuePos = baseCmd.indexOf('\n');
    baseCmd = QString(baseCmd.insert(valuePos, " " + value)).toLatin1();
    QByteArray response = "";
    // send command
    sendCommandAndWaitForResponse(theInstrLoc, baseCmd, &response);
    return response;
}

void N7714A::execFrequency(int module, QByteArray value, QByteArray unit){
    QByteArray baseCmd = N7714A_FREQ_CMD;
    int modulePos = baseCmd.indexOf(':');

    QString moduleString = QString("%1").arg(module);
    baseCmd = QString(baseCmd.insert(modulePos, moduleString)).toLatin1();

    int valuePos = baseCmd.indexOf('\n');
    baseCmd = QString(baseCmd.insert(valuePos, " " + value)).toLatin1();

    baseCmd.insert(baseCmd.indexOf('\n'), unit);

    // send command
    emit signalSendCmdNoRsp(theInstrLoc, baseCmd);
}

QByteArray N7714A::testCommand(QByteArray baseCmd){
    baseCmd = baseCmd + '\n';
    QByteArray response = "";
    sendCommandAndWaitForResponse(theInstrLoc, baseCmd, &response);
    return response;
}

QByteArray N7714A::queryAutoWavMode(int module){
    QByteArray baseCmd = "sour:wav:auto?";
    baseCmd.insert(baseCmd.indexOf(':'), QByteArray::number(module));
    QByteArray response = "";
    sendCommandAndWaitForResponse(theInstrLoc, baseCmd, &response);
    return response;
}

void N7714A::turnOnAutoWavMode(int module){
    QByteArray baseCmd = "sour:wav:auto on\n";

    baseCmd.insert(baseCmd.indexOf(':'), QByteArray::number(module));

    emit signalSendCmdNoRsp(theInstrLoc, baseCmd);
}

void N7714A::updateConfig(QSettings *configSettings){

    configSettings->setValue(DEVICE_ADDRESS, QVariant::fromValue(theInstrLoc));
    configSettings->setValue(DEVICE_IDENTITY, QVariant::fromValue(theIdentity));
    configSettings->setValue(DEVICE_NICKNAME, QVariant::fromValue(getNickname()));

    // make sure auto mode is on
    for(int i = 1; i < N7714A_NUM_SLOTS; i++){
        turnOnAutoWavMode(i);
    }

    updatePowerSettings(*configSettings);
    updateWavelengthSettings(*configSettings);
    updateFrequencySettings(*configSettings);
}

void N7714A::applyConfigSettings(QSettings *configSettings){

    // apply nickname
    QByteArray nicknameToSet = configSettings->value(DEVICE_NICKNAME).value<QByteArray>();
    setNickname(nicknameToSet);


    QList<QByteArray> powerSettings = configSettings->value(N7714A_POWER_SETTINGS).value<QList<QByteArray>>();
    QList<QByteArray> powerStates = configSettings->value(N7714A_LASER_STATE).value<QList<QByteArray>>();

    for(int i = 0; i < N7714A_NUM_SLOTS; i++){
        int slot = i + 1;
        QByteArray unit = "Watt";
        execPowerLevel(slot, powerSettings[i], unit);

        // change power if needed
        int powerOn = powerStates[i].toInt();
        if(!powerOn){
            execPowerOffModule(slot);
        }
        else{
            execPowerOnModule(slot);
        }
    }

    // apply wavelength settings to device
    QList<QByteArray> wavelengthSettings = configSettings->value(N7714A_WAVELENGTH_SETTINGS).value<QList<QByteArray>>();

    for(int i = 0; i < N7714A_NUM_SLOTS; i++){
        int slot = i + 1;
        QByteArray unit = "m";
        execWavelength(slot, wavelengthSettings[i], unit);
    }

    // apply frequency settings to device
    QList<QByteArray> frequencySettings = configSettings->value(N7714A_FREQUENCY_SETTINGS).value<QList<QByteArray>>();
    for(int i = 0; i < N7714A_NUM_SLOTS; i++){
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
        QByteArray power = queryPowerLevel(i);
        QByteArray minPower = queryPowerLevel(i, "MIN");
        QByteArray maxPower = queryPowerLevel(i, "MAX");
        QByteArray laserState = queryPowerStatus(i);


        powerSettings.append(QByteArray::number(power.toDouble()));
        minPowerSettings.append(QByteArray::number(minPower.toDouble()));
        maxPowerSettings.append(QByteArray::number(maxPower.toDouble()));
        laserStates.append(laserState);
    }

    // save to config
    configSettings.setValue(N7714A_POWER_SETTINGS, QVariant::fromValue(powerSettings));
    configSettings.setValue(N7714A_MIN_POWER, QVariant::fromValue(minPowerSettings));
    configSettings.setValue(N7714A_MAX_POWER, QVariant::fromValue(maxPowerSettings));
    configSettings.setValue(N7714A_LASER_STATE, QVariant::fromValue(laserStates));
    configSettings.sync();
}

void N7714A::updateWavelengthSettings(QSettings &configSettings){
    QList<QByteArray> wavelengthSettings;
    QList<QByteArray> minWavelengthSettings;
    QList<QByteArray> maxWavelengthSettings;

    for(int i = 1; i <= N7714A_NUM_SLOTS; i++){
        QByteArray wavelength = queryWavelength(i);
        QByteArray minWavelength = queryWavelength(i, "MIN");
        QByteArray maxWavelength = queryWavelength(i, "MAX");

        wavelengthSettings.append(QByteArray::number(wavelength.toDouble()));
        minWavelengthSettings.append(QByteArray::number(minWavelength.toDouble()));
        maxWavelengthSettings.append(QByteArray::number(maxWavelength.toDouble()));
    }

    // save to config
    configSettings.setValue(N7714A_WAVELENGTH_SETTINGS, QVariant::fromValue(wavelengthSettings));
    configSettings.setValue(N7714A_MIN_WAVELENGTH, QVariant::fromValue(minWavelengthSettings));
    configSettings.setValue(N7714A_MAX_WAVELENGTH, QVariant::fromValue(maxWavelengthSettings));
    configSettings.sync();
}

void N7714A::updateFrequencySettings(QSettings &configSettings){

    QList<QByteArray> frequencySettings;
    QList<QByteArray> minFrequencySettings;
    QList<QByteArray> maxFrequencySettings;
    for(int i = 1; i <= N7714A_NUM_SLOTS; i++){
        QByteArray frequency = queryFrequency(i);
        QByteArray minFrequency = queryFrequency(i, "MIN");
        QByteArray maxFrequency = queryFrequency(i, "MAX");

        frequencySettings.append(QByteArray::number(frequency.toDouble()));
        minFrequencySettings.append(QByteArray::number(minFrequency.toDouble()));
        maxFrequencySettings.append(QByteArray::number(maxFrequency.toDouble()));
    }

    // save to config
    configSettings.setValue(N7714A_FREQUENCY_SETTINGS, QVariant::fromValue(frequencySettings));
    configSettings.setValue(N7714A_MIN_FREQUENCY, QVariant::fromValue(minFrequencySettings));
    configSettings.setValue(N7714A_MAX_FREQUENCY, QVariant::fromValue(maxFrequencySettings));
    configSettings.sync();

}

