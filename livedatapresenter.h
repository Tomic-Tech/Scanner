#ifndef LIVE_DATA_PRESENTER_H
#define LIVE_DATA_PRESENTER_H

#include "presenter.h"

class LiveDataPresenter : public Presenter
{
    Q_OBJECT
public:
    explicit LiveDataPresenter(QObject *parent = 0);

signals:
    void sendAddBtn(const QString &text);
    void sendSetValue(int index, const QString &value);
    void sendBtnClr();
public slots:
    void show();
    void addBtn(const QString &text);
    void setValue(int index, const QString &value);
    void btnClr();
};

#endif