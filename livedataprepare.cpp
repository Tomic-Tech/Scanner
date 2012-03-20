#include "livedataprepare.h"
#include <jm/jmlib.h>

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
            size_t size = jm_ld_array_size();
            for (size_t i = 0; i < size; i++)
            {
                if (jm_ld_array_get_enabled(i))
                {
                    atLeastOne = true;
                    break;
                }
            }
            if (atLeastOne)
            {
                jm_ui_set_btn_clicked(".");
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
        jm_ui_set_btn_clicked("..");
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
    jm_ld_array_deploy_enabled_index();
    LiveDataModel *model = _model;
    _model = new LiveDataModel(LiveDataModel::PrepareMode);
    _ui.tableView->setModel(_model);
    if (model != NULL)
        delete model;
    QWidget::showEvent(event);
}

