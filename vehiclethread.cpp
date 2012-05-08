#include "vehiclethread.h"
#include <jm/system/app.h>

VehicleThread::VehicleThread(QObject *parent /* = 0 */)
    : QThread(parent)
{

}

VehicleThread::~VehicleThread()
{

}

void VehicleThread::init(const QString &name, const QString &path, 
    const QString &dbName)
{
    _name = name;
    _path = path;
    _dbName = dbName;
}

void VehicleThread::run()
{    
    JM::System::app().vldr().run(_name.toUtf8().data(),
        _path.toUtf8().data(),
        _dbName.toUtf8().data());
}