#include "register.h"
#include <jm/jmlib.h>

Register::Register(QWidget *parent /* = 0 */, Qt::WFlags flags /* = 0 */)
    : QDialog(parent, flags)
{
    _ui.setupUi(this);
    //connect(_ui.quitButton, SIGNAL(clicked()), qApp, SLOT(quit()));
    connect(_ui.okButton, SIGNAL(clicked()), this, SLOT(onOk()));

    char *idCode = jm_auth_query_id_code();
    _ui.idCode->setText(QString::fromUtf8(idCode));
    free(idCode);
}

Register::~Register()
{

}

void Register::onOk()
{
    QString reg = _ui.regText->toPlainText();
    jm_auth_save_reg(reg.toUtf8().data());
}