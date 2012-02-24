#ifndef UI_THREAD_H
#define UI_THREAD_H

#include <QThread>
#include "manager.h"

class UIThread : public QThread
{
    Q_OBJECT
public:
    explicit UIThread(Manager *manager, QObject *parent = 0);
    void stop();
protected:
    void run();
private:
    bool _isStop;
    Manager *_manager;
};

#endif