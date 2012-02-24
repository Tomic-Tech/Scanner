#include "serialportwritethread.h"
#include <jm/jmcommboxport.h>

SerialPortWriteThread::SerialPortWriteThread(JMSerialPort *port, QObject *parent /* = 0 */)
    : QThread(parent)
    , _serial_port(port)
    , _stopped(false)
{

}

void SerialPortWriteThread::run()
{
    static GByteArray *buff = NULL;
    while (!_stopped)
    {
        if (jm_serial_port_is_open(_serial_port) &&
            jm_commbox_port_out_deque_available())
        {
            if (jm_commbox_port_pop_out_deque(&buff))
            {
                jm_serial_port_write(_serial_port, buff->data, buff->len);
            }
        }
        QThread::yieldCurrentThread();
    }
}

void SerialPortWriteThread::stop()
{
    _stopped = true;
    while(isRunning());
}
