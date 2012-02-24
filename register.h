#ifndef REGISTER_H
#define REGISTER_H

#include <QtGui/QDialog>
#include "ui_register.h"

class Register : public QDialog
{
    Q_OBJECT

public:
    Register(QWidget *parent = 0, Qt::WFlags flags = 0);
    ~Register();
private slots:
    void onOk();
private:
    Ui::RegisterClass _ui;
};

#endif