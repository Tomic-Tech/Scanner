#include "serialportreadthread.h"
#include <jm/jmcommboxport.h>

SerialPortReadThread::SerialPortReadThread(JMSerialPort *port, QObject *parent /* = 0 */)
    : QThread(parent)
    , _serial_port(port)
    , _stopped(false)
{

}

void SerialPortReadThread::run()
{
    static guint8 buff[1024];
    static size_t avail = 0;
    while (!_stopped)
    {
        if (jm_serial_port_is_open(_serial_port))
        {
            avail = jm_serial_port_bytes_available(_serial_port);
            if (avail > 0)
            {
                jm_serial_port_read(_serial_port, buff, avail);
                jm_commbox_port_push_in_deque(buff, avail);
            }
        }
        QThread::yieldCurrentThread();
    }
}

void SerialPortReadThread::stop()
{
    _stopped = true;
    while(isRunning());
}
