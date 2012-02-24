#ifndef TROUBLE_CODE_PRESENTER_H
#define TROUBLE_CODE_PRESENTER_H

#include "presenter.h"

class TroubleCodePresenter : public Presenter
{
    Q_OBJECT
public:
    explicit TroubleCodePresenter(QObject *parent = 0);

signals:
    void sendAddBtn(const QString &text);
    void sendAddItem(const QString &code, const QString &text);
    void sendItemClr();
    void sendBtnClr();
public slots:
    void itemClr();
    void addBtn(const QString &text);
    void addItem(const QString &code, const QString &text);
    void btnClr();
    void show();
};

#endif