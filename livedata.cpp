#include "livedata.h"

LiveData::LiveData(QWidget *parent /* = 0 */)
    : QWidget(parent)
    , _ui()
    , _dynamicButtons(Qt::Vertical, this)
    , _model(LiveDataModel::LiveDataMode)
    , _delegate(LiveDataDelegate::LiveDataMode)
{
    _ui.setupUi(this);
    _ui.horizontalLayout->addWidget(&_dynamicButtons);

    _ui.liveDataTable->setModel(&_model);
    _ui.liveDataTable->setItemDelegate(&_delegate);
    _ui.liveDataTable->horizontalHeader()->setResizeMode(1, QHeaderView::ResizeToContents);
    _ui.liveDataTable->horizontalHeader()->setResizeMode(2, QHeaderView::ResizeToContents);
}

DynamicButtons* LiveData::dynamicButtons()
{
    return &_dynamicButtons;
}

void LiveData::setValue(int index, const QString &value)
{
    _model.setData(index, value);
}

void LiveData::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::LanguageChange)
    {
        _ui.retranslateUi(this);
    }
    else
    {
        QWidget::changeEvent(event);
    }
}
