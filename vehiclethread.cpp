#include "vehiclethread.h"
#include <jm/jmlib.h>
#include <jm/jmcommboxport.h>

VehicleThread::VehicleThread(QObject *parent /* = 0 */)
    : QThread(parent)
    , _setting("Tomic", "C168 II")
    , _spReadTimer(new QTimer(this))
    , _spWriteTimer(new QTimer(this))
    , _serial_port(jm_serial_port_new())
{
    connect(_spReadTimer, SIGNAL(timeout()), this, SLOT(spRead()));
    connect(_spWriteTimer, SIGNAL(timeout()), this, SLOT(spWrite()));
}

VehicleThread::~VehicleThread()
{
    delete _spReadTimer;
    delete _spWriteTimer;
}

void VehicleThread::init(const QString &name, const QString &path, 
    const QString &dbName)
{
    _name = name;
    _path = path;
    _dbName = dbName;
}

void VehicleThread::spRead()
{
    static guint8 buff[1024];
    static size_t avail = 0;
    if (jm_serial_port_is_open(_serial_port))
    {
        avail = jm_serial_port_bytes_available(_serial_port);
        if (avail > 0)
        {
            jm_serial_port_read(_serial_port, buff, avail);
            jm_commbox_port_push_in_deque(buff, avail);
        }
    }
}

void VehicleThread::spWrite()
{
    static GByteArray *buff = NULL;
    if (jm_serial_port_is_open(_serial_port) && 
        jm_commbox_port_out_deque_available())
    {
        if (jm_commbox_port_pop_out_deque(&buff))
        {
            jm_serial_port_write(_serial_port, buff->data, buff->len);
        }
    }
}

void VehicleThread::run()
{
    JMCommboxPortType portType = (JMCommboxPortType)_setting.value("PortType", QVariant(int(JM_COMMBOX_PORT_SERIAL_PORT))).toInt();
    if (portType == JM_COMMBOX_PORT_SERIAL_PORT)
    {
        _spReadTimer->start(1);
        _spWriteTimer->start(1);
    }
    
    jm_load_vehicle_script(_name.toUtf8().data(),
        _path.toUtf8().data(),
        _dbName.toUtf8().data());
    if (portType == JM_COMMBOX_PORT_SERIAL_PORT)
    {
        _spReadTimer->stop();
        _spWriteTimer->stop();
    }
}