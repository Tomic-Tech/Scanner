#include "vehiclethread.h"
#include <jm/jmlib.h>
#include <jm/jmcommboxport.h>

VehicleThread::VehicleThread(QObject *parent /* = 0 */)
    : QThread(parent)
    , _setting("Tomic", "C168 II")
{
    
}

void VehicleThread::init(const QString &name, const QString &path, const QString &dbName)
{
    _name = name;
    _path = path;
    _dbName = dbName;
}

void VehicleThread::run()
{
    JMCommboxPortType portType = (JMCommboxPortType)_setting.value("PortType", QVariant(int(JM_COMMBOX_PORT_SERIAL_PORT))).toInt();
    if (portType == JM_COMMBOX_PORT_SERIAL_PORT)
    {
        _serialPortThread.start();
    }
    
    jm_load_vehicle_script(_name.toUtf8().data(),
        _path.toUtf8().data(),
        _dbName.toUtf8().data());
    if (portType == JM_COMMBOX_PORT_SERIAL_PORT)
    {
        _serialPortThread.stop();
    }
}