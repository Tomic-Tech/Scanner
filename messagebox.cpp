#include "messagebox.h"

MessageBox::MessageBox(QWidget *parent /* = 0 */, Qt::WFlags flags /* = 0 */)
    : QDialog(parent, flags)
    , _ui()
    , _dynamicButtons(Qt::Horizontal, this)
{
    _ui.setupUi(this);
    _ui.verticalLayout->addWidget(&_dynamicButtons);
    setWindowModality(Qt::ApplicationModal);
    setWindowFlags(Qt::CustomizeWindowHint);
}

DynamicButtons* MessageBox::dynamicButtons()
{
    return &_dynamicButtons;
}

void MessageBox::setMsg(const QString &text)
{
    _ui.message->setPlainText(text);
}

void MessageBox::setTitle(const QString &text)
{
    _ui.title->setText(text);
}

void MessageBox::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::LanguageChange)
    {
        _ui.retranslateUi(this);
    }
    else
    {
        QDialog::changeEvent(event);
    }
}
