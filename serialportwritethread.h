#ifndef SERIAL_PORT_WRITE_THREAD_H
#define SERIAL_PORT_WRITE_THREAD_H

#include <QThread>
#include <jm/jmserialport.h>

class SerialPortWriteThread : public QThread
{
public:
    SerialPortWriteThread(JMSerialPort *port, QObject *parent = 0);
    void stop();
protected:
    void run();
private:
    JMSerialPort *_serial_port;
    bool _stopped;
};

#endif