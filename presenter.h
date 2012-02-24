#ifndef PRESENTER_H
#define PRESENTER_H

#include <QObject>

class Presenter : public QObject
{
    Q_OBJECT
public:
    explicit Presenter(QObject *parent = 0);
    virtual ~Presenter();
signals:
    void switchWindow();
public slots:
    virtual void show();
};

#endif