#include "register.h"
#include <jm/system/app.hpp>

Register::Register(QWidget *parent /* = 0 */, Qt::WFlags flags /* = 0 */)
    : QDialog(parent, flags)
{
    _ui.setupUi(this);
    //connect(_ui.quitButton, SIGNAL(clicked()), qApp, SLOT(quit()));
    connect(_ui.okButton, SIGNAL(clicked()), this, SLOT(onOk()));

    _ui.idCode->setText(QString::fromStdString(JM::System::app().reg().queryIDCode()));
}

Register::~Register()
{

}

void Register::onOk()
{
    QString reg = _ui.regText->toPlainText();
    JM::System::app().reg().saveReg(reg.toStdString());
}