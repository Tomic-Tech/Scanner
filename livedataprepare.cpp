#include "livedataprepare.h"
#include <jm/system/app.hpp>

LiveDataPrepare::LiveDataPrepare(QWidget *parent /* = 0 */)
    : QWidget(parent)
    , _ui()
    , _dynamicButtons(Qt::Vertical, this)
    , _model(0)
    , _delegate(LiveDataDelegate::PrepareMode)
{
    _ui.setupUi(this);
    _ui.horizontalLayout->addWidget(&_dynamicButtons);
    _dynamicButtons.addBtn(trUtf8("Enter"));
    _dynamicButtons.addBtn(trUtf8("Select All"));
    _dynamicButtons.addBtn(trUtf8("Back"));

    connect(&_dynamicButtons, SIGNAL(sendBtnClkByInx(int)), this, SLOT(btnClked(int)));
    _ui.tableView->setModel(_model);
    _ui.tableView->setItemDelegate(&_delegate);
}

LiveDataPrepare::~LiveDataPrepare()
{
    if (_model != NULL)
        delete _model;
}

void LiveDataPrepare::btnClked(int index)
{
    switch(index)
    {
    case 0:
        {
            bool atLeastOne = false;
            size_t size = JM::System::app().ldVecPtr->size();
            for (size_t i = 0; i < size; i++)
            {
                if (JM::System::app().ldVecPtr->at(i)->enabled())
                {
                    atLeastOne = true;
                    break;
                }
            }
            if (atLeastOne)
            {
                JM::System::app().ui().setBtnClicked(".");
            }
        }
        break;
    case 1:
        for (int i = 0; i < _model->rowCount(); i++)
        {
            _model->setData(_model->index(i, 0), QVariant(true), Qt::CheckStateRole);
        }
        break;
    case 2:
        JM::System::app().ui().setBtnClicked("..");
        break;
    }
}

void LiveDataPrepare::changeEvent(QEvent *event)
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

void LiveDataPrepare::showEvent(QShowEvent *event)
{
    JM::System::app().ldVecPtr->deployEnabledIndex();
    LiveDataModel *model = _model;
    _model = new LiveDataModel(LiveDataModel::PrepareMode);
    _ui.tableView->setModel(_model);
    if (model != NULL)
        delete model;
    QWidget::showEvent(event);
}

