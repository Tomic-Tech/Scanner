#ifndef LIVE_DATA_H
#define LIVE_DATA_H

#include <QtCore>
#include <QWidget>
#include "dynamicbuttons.h"
#include "livedatamodel.h"
#include "livedatadelegate.h"
#include "ui_livedata.h"

class LiveData : public QWidget
{
    Q_OBJECT

public:
    explicit LiveData(QWidget *parent = 0);
    ~LiveData();
    DynamicButtons* dynamicButtons();
public slots:
    void setValue(int index, const QString &value);
protected:
    void changeEvent(QEvent *event);
    void showEvent(QShowEvent *event);
    void hideEvent(QHideEvent *event);
private:
    Ui::LiveDataClass _ui;
    DynamicButtons _dynamicButtons;
    LiveDataModel *_model;
    LiveDataDelegate _delegate;
};

#endif