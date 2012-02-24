#ifndef SERIAL_PORT_READ_THREAD_H
#define SERIAL_PORT_READ_THREAD_H

#include <QThread>
#include <jm/jmserialport.h>

class SerialPortReadThread : public QThread
{
public:
    SerialPortReadThread(JMSerialPort *port, QObject *parent = 0);
    void stop();
protected:
    void run();
private:
    JMSerialPort *_serial_port;
    bool _stopped;
};

#endif