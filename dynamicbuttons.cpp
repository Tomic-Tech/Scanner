#include "dynamicbuttons.h"
#include <jm/system/app.hpp>

DynamicButtons::DynamicButtons(Qt::Orientations orientation,
    QWidget *parent)
    : QWidget(parent)
    , _layout(0)
{
    if (orientation == Qt::Horizontal)
    {
        _layout = new QHBoxLayout(this);
        setMaximumHeight(100);
    }
    else
    {
        _layout = new QVBoxLayout(this);
        setMaximumWidth(200);
    }
    setLayout(_layout);
}

DynamicButtons::~DynamicButtons()
{
    for (QList<QPushButton *>::iterator i = _buttonList.begin(); i != _buttonList.end(); i++)
    {
        delete *i;
    }
    delete _layout;
}

void DynamicButtons::addBtn(const QString &text)
{
    QPushButton *button = new QPushButton(text, this);
    QFont font = QFont(QString::fromUtf8("微软雅黑"), 16);
    button->setFont(font);
    _buttonList.append(button);
    _layout->addWidget(button);
    connect(button, SIGNAL(clicked()),
        this, SLOT(btnClked()));
}

void DynamicButtons::btnClr()
{
    for (QList<QPushButton *>::iterator i = _buttonList.begin(); i != _buttonList.end(); i++)
    {
        (*i)->hide();
        delete (*i);
    }
    _buttonList.clear();
}

void DynamicButtons::btnClked()
{
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    emit sendBtnClk(button->text());
    for (int i = 0; i < _buttonList.size(); i++)
    {
        if (button == _buttonList[i])
        {
            emit sendBtnClkByInx(i);
        }
    }
}

void DynamicButtons::defaultBtnClked(const QString &text)
{
    JM::System::app().ui().setBtnClicked(text.toUtf8().data());
}
