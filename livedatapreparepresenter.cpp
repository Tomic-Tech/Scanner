#include "livedatapreparepresenter.h"

LiveDataPreparePresenter::LiveDataPreparePresenter(QObject *parent /* = 0 */)
    : Presenter(parent)
{

}

void LiveDataPreparePresenter::show()
{
    emit switchWindow();
}