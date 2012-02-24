#ifndef LIVE_DATA_PREPARE_PRESENTER_H
#define LIVE_DATA_PREPARE_PRESENTER_H

#include "presenter.h"

class LiveDataPreparePresenter : public Presenter
{
    Q_OBJECT
public:
    explicit LiveDataPreparePresenter(QObject *parent = 0);

signals:
    void sendShow();
public slots:
    void show();
};

#endif