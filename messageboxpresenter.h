#ifndef MESSAGE_BOX_PRESENTER_H
#define MESSAGE_BOX_PRESENTER_H

#include <QObject>

class MessageBoxPresenter : public QObject
{
    Q_OBJECT
public:
    explicit MessageBoxPresenter(QObject *parent = 0);

signals:
    void sendBtnClr();
    void sendSetMsg(const QString &text);
    void sendSetTitle(const QString &text);
    void sendAddBtn(const QString &text);
    void sendShow();
    void sendHide();
public slots:
    void btnClr();
    void setMsg(const QString &text);
    void setTitle(const QString &text);
    void addBtn(const QString &text);
    void show();
    void hide();
};

#endif