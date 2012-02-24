#include "troublecode.h"

TroubleCode::TroubleCode(QWidget *parent /* = 0 */)
    : QWidget(parent)
    , _ui()
    , _dynamicButtons(Qt::Vertical)
    , _model()
{
    _ui.setupUi(this);
    _ui.horizontalLayout->addWidget(&_dynamicButtons);
    _ui.troubleCodeTable->setModel(&_model);
}

DynamicButtons* TroubleCode::dynamicButtons()
{
    return &_dynamicButtons;
}

void TroubleCode::addItem(const QString &code, const QString &text)
{
    _model.insertRow(_model.rowCount());
    _model.setData(_model.index(_model.rowCount() - 1, 0), code);
    _model.setData(_model.index(_model.rowCount() - 1, 1), text);
}

void TroubleCode::itemClr()
{
    _model.removeRows(0, _model.rowCount());
}

void TroubleCode::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::LanguageChange)
        _ui.retranslateUi(this);
    else
        QWidget::changeEvent(event);
}
