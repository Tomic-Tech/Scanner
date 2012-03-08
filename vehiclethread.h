#ifndef VEHICLE_THREAD_H
#define VEHICLE_THREAD_H

#include <jm/jmserialport.h>
#include <QTimer>
#include <QThread>
#include <QSettings>
//#include "serialportthread.h"

class VehicleThread : public QThread
{
    Q_OBJECT
public:
    explicit VehicleThread(QObject *parent = 0);
    ~VehicleThread();

    void init(const QString &name, const QString &path, 
        const QString &dbName);
protected:
    void run();
private slots:
    void spRead();
    void spWrite();
private:
    QString _name;
    QString _path;
    QString _dbName;
    //SerialPortThread _serialPortThread;
    QSettings _setting;
    QTimer *_spReadTimer;
    QTimer *_spWriteTimer;
    JMSerialPort *_serial_port;
};

#endif