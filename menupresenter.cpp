#include "menupresenter.h"

MenuPresenter::MenuPresenter(QObject *parent /* = 0 */)
    : Presenter(parent)
{

}

void MenuPresenter::show()
{
    emit switchWindow();
}

void MenuPresenter::itemClr()
{
    emit sendItemClr();
}

void MenuPresenter::addItem(const QString &text)
{
    emit sendAddItem(text);
}
