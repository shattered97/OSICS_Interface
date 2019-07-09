#include "N7714A.h"
#include "DefaultInstrument.h"

N7714A::N7714A(){

}
N7714A::N7714A(QByteArray theIdentity, QByteArray theInstrLoc){
    this->setInstrIdentity(theIdentity);
    qDebug() << this->getInstrIdentity();
    this->setInstrLocation(theInstrLoc);
    qDebug() << this->getInstrLocation();
}


bool N7714A::execPowerUnit(ViSession &defaultSession, ViSession &instrSession, int module, int unit){
}

bool N7714A::queryPowerUnit(ViSession &defaultSession, ViSession &instrSession, int module, QByteArray &response){
    QByteArray baseCmd = "SLOT:OPC?\n";
    int paramPosition = baseCmd.indexOf(':');
    QString param = QString("%1").arg(module);

    QByteArray command = QString(baseCmd.insert(paramPosition, param)).toLatin1();

    // send command
    return sendCmdRsp(defaultSession, instrSession, command, response);

}

bool N7714A::execPowerOnModule(ViSession &defaultSession, ViSession &instrSession, int module){
    QByteArray baseCmd = "sour:pow:stat on\n";
    baseCmd.insert(baseCmd.indexOf(':'), module);

    qDebug() << baseCmd;
}

bool N7714A::execPowerOffModule(ViSession &defaultSession, ViSession &instrSession, int module){
    QByteArray baseCmd = "sour:pow:stat off\n";
    baseCmd.insert(baseCmd.indexOf(':'), module);

    qDebug() << baseCmd;
}
