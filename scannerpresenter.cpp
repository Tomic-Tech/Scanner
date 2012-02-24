#include "scannerpresenter.h"

ScannerPresenter::ScannerPresenter(QObject *parent /* = 0 */)
    : Presenter(parent)
{

}

void ScannerPresenter::show()
{
    emit switchWindow();
}