#ifndef MENU_PRESENTER_H
#define MENU_PRESENTER_H

#include "presenter.h"

class MenuPresenter : public Presenter
{
    Q_OBJECT
public:
    explicit MenuPresenter(QObject *parent = 0);

signals:
    void sendAddItem(const QString &text);
    void sendItemClr();
public slots:
    void addItem(const QString &text);
    void itemClr();
    void show();
};

#endif