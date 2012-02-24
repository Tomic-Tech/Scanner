#include "serialportthread.h"

SerialPortThread::SerialPortThread()
    : _serial_port(jm_serial_port_new())
    , _write(_serial_port)
    , _read(_serial_port)
{
    jm_commbox_port_set_pointer((gpointer)_serial_port);
}

SerialPortThread::~SerialPortThread()
{
    stop();
    jm_serial_port_free(_serial_port);
    jm_commbox_port_set_pointer(NULL);
}

void SerialPortThread::start()
{
    _write.start();
    _read.start();
}

void SerialPortThread::stop()
{
    _write.stop();
    _read.stop();
}
