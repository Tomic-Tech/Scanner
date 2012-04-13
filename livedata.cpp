#include "livedata.h"
#include <jm/system/app.hpp>

LiveData::LiveData(QWidget *parent /* = 0 */)
    : QWidget(parent)
    , _ui()
    , _dynamicButtons(Qt::Vertical, this)
    , _model(NULL)
    , _delegate(LiveDataDelegate::LiveDataMode)
{
    _ui.setupUi(this);
    _ui.horizontalLayout->addWidget(&_dynamicButtons);

    _ui.liveDataTable->setModel(_model);
    _ui.liveDataTable->setItemDelegate(&_delegate);
    _ui.liveDataTable->setWordWrap(true);
}

LiveData::~LiveData()
{
    if (_model != NULL)
        delete _model;
}

DynamicButtons* LiveData::dynamicButtons()
{
    return &_dynamicButtons;
}

void LiveData::setValue(int index, const QString &value)
{
    _model->setData(index, value);
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

void LiveData::showEvent(QShowEvent *event)
{
    JM::System::app().ldVecPtr->deployShowedIndex();
    _model = new LiveDataModel(LiveDataModel::LiveDataMode);
    _ui.liveDataTable->setModel(_model);
    //_ui.liveDataTable->horizontalHeader()->setResizeMode(1, QHeaderView::ResizeToContents);
    //_ui.liveDataTable->horizontalHeader()->setResizeMode(2, QHeaderView::ResizeToContents);
    QWidget::showEvent(event);
}

void LiveData::hideEvent(QHideEvent *event)
{
    if (_model != NULL)
        delete _model;
    _model = NULL;
    _ui.liveDataTable->setModel(_model);
    QWidget::hideEvent(event);
}
