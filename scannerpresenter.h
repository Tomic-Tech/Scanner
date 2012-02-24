#ifndef SCANNER_PRESENTER_H
#define SCANNER_PRESENTER_H

#include "presenter.h"

class ScannerPresenter : public Presenter
{
    Q_OBJECT
public:
    explicit ScannerPresenter(QObject *parent = 0);

public slots:
    void show();
};

#endif