#ifndef VEHICLE_THREAD_H
#define VEHICLE_THREAD_H

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
private:
    QString _name;
    QString _path;
    QString _dbName;
};

#endif