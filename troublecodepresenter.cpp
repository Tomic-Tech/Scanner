#include "troublecodepresenter.h"

TroubleCodePresenter::TroubleCodePresenter(QObject *parent /* = 0 */)
    : Presenter(parent)
{

}

void TroubleCodePresenter::itemClr()
{
    emit sendItemClr();
}

void TroubleCodePresenter::addItem(const QString &code, const QString &text)
{
    emit sendAddItem(code, text);
}

void TroubleCodePresenter::addBtn(const QString &text)
{
    emit sendAddBtn(text);
}

void TroubleCodePresenter::btnClr()
{
    emit sendBtnClr();
}

void TroubleCodePresenter::show()
{
    emit switchWindow();
}


