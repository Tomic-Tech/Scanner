#ifndef SERIAL_PORT_THREAD
#define SERIAL_PORT_THREAD

#include <QThread>
#include <jm/jmserialport.h>
#include <jm/jmcommboxport.h>
#include "serialportreadthread.h"
#include "serialportwritethread.h"

class SerialPortThread
{
public:
    explicit SerialPortThread();
    ~SerialPortThread();
    void start();
    void stop();
private:
    JMSerialPort *_serial_port;
    SerialPortWriteThread _write;
    SerialPortReadThread _read;
};

#endif