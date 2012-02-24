#include "livedatapresenter.h"

LiveDataPresenter::LiveDataPresenter(QObject *parent /* = 0 */)
    : Presenter(parent)
{

}

void LiveDataPresenter::show()
{
    emit switchWindow();
}

void LiveDataPresenter::addBtn(const QString &text)
{
    emit sendAddBtn(text);
}

void LiveDataPresenter::setValue(int index, const QString &value)
{
    emit sendSetValue(index, value);
}

void LiveDataPresenter::btnClr()
{
    emit sendBtnClr();
}
