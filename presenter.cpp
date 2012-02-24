#include "presenter.h"

Presenter::Presenter(QObject *parent /* = 0 */)
    : QObject(parent)
{

}

Presenter::~Presenter()
{

}

void Presenter::show()
{
    emit switchWindow();
}