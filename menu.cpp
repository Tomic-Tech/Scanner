#include "menu.h"
#include <jm/jmlib.h>

Menu::Menu(QWidget *parent /* = 0 */)
    : QWidget (parent)
    , _dynamicButtons(Qt::Vertical, this)
    , _model()
{
    _ui.setupUi(this);

    _ui.horizontalLayout->addWidget(&_dynamicButtons);

    _dynamicButtons.addBtn(trUtf8("Enter"));
    _dynamicButtons.addBtn(trUtf8("Back"));

    connect(&_dynamicButtons, SIGNAL(sendBtnClkByInx(int)), this, SLOT(btnClked(int)));
    _ui.menuList->setModel(&_model);
}

void Menu::btnClked(int index)
{
    switch (index)
    {
    case 0:
        on_menuList_doubleClicked(_ui.menuList->currentIndex());
        break;
    case 1:
        jm_ui_set_btn_clicked("..");
        break;
    }
}

DynamicButtons *Menu::dynamicButtons()
{
    return &_dynamicButtons;
}

void Menu::addItem(const QString &text)
{
    _model.insertRow(_model.rowCount());
    _model.setData(_model.index(_model.rowCount() - 1), QVariant(text));
}

void Menu::itemClr()
{
    _model.removeRows(0, _model.rowCount());
}

void Menu::on_menuList_doubleClicked(const QModelIndex &index)
{
    if (index.isValid())
    {
        QString item = _model.data(index).toString();
        jm_ui_set_btn_clicked(".");
        jm_ui_set_menu_selected(item.toUtf8().data());
		jm_log_write("Menu", item.toUtf8().data());
    }
}

void Menu::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::LanguageChange)
        _ui.retranslateUi(this);
    else
        QWidget::changeEvent(event);
}
