#ifndef LIVE_DATA_PREPARE_H
#define LIVE_DATA_PREPARE_H

#include <QWidget>
#include "dynamicbuttons.h"
#include "livedatamodel.h"
#include "livedatadelegate.h"
#include "ui_livedataprepare.h"

class LiveDataPrepare : public QWidget
{
    Q_OBJECT
public:
    explicit LiveDataPrepare(QWidget *parent = 0);
    ~LiveDataPrepare();
public slots:
protected:
    void changeEvent(QEvent *event);
    void showEvent(QShowEvent *event);
private slots:
    void btnClked(int index);
private:
    Ui::LiveDataPrepareClass _ui;
    DynamicButtons _dynamicButtons;
    LiveDataModel *_model;
    LiveDataDelegate _delegate;
};

#endif