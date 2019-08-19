#include "PowerMeterFactory.h"

PowerMeterFactory::PowerMeterFactory(QObject *parent) : QObject(parent)
{

}

PowerMeter *PowerMeterFactory::makePowerMeter(QString powerMeterType, QByteArray instrAddress, QByteArray instrIdentity)
{
  if (powerMeterType.contains("N7745A")){
      // create power meter
      KeysightPowerMeter *powerMeter = new KeysightPowerMeter(instrAddress, instrIdentity);

      // return power meter
      return powerMeter;
  }
  else{
      // device is not supported

      // #TODO signal to open "critical" error QMessageBox
      // display message "Selected Power Meter is not supported."

      return nullptr;
  }
}
