#include "messageboxpresenter.h"

MessageBoxPresenter::MessageBoxPresenter(QObject *parent /* = 0 */)
    : QObject(parent)
{

}

void MessageBoxPresenter::addBtn(const QString &text)
{
    emit sendAddBtn(text);
}

void MessageBoxPresenter::setMsg(const QString &text)
{
    emit sendSetMsg(text);
}

void MessageBoxPresenter::setTitle(const QString &text)
{
    emit sendSetTitle(text);
}

void MessageBoxPresenter::show()
{
    emit sendShow();
}

void MessageBoxPresenter::btnClr()
{
    emit sendBtnClr();
}

void MessageBoxPresenter::hide()
{
    emit sendHide();
}
