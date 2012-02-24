#include "register.h"
#include <jm/jmauth.h>

Register::Register(QWidget *parent /* = 0 */, Qt::WFlags flags /* = 0 */)
    : QDialog(parent, flags)
{
    _ui.setupUi(this);
    connect(_ui.quitButton, SIGNAL(clicked()), qApp, SLOT(quit()));
    connect(_ui.okButton, SIGNAL(clicked()), this, SLOT(onOk()));

    gchar *idCode = jm_auth_get_id_code();
    _ui.idCode->setText(QString::fromUtf8(idCode));
    g_free(idCode);
}

Register::~Register()
{

}

void Register::onOk()
{
    QString reg = _ui.regText->toPlainText();
    jm_auth_write_register(reg.toUtf8().data());
}