#include "livedatadelegate.h"
#include <jm/system/app.h>

LiveDataDelegate::LiveDataDelegate(Mode mode, QObject *parent)
    : QItemDelegate(parent)
    , _mode(mode)
{

}

void LiveDataDelegate::updateEditorGeometry(QWidget *editor,
    const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (_mode == PrepareMode)
    {
        if (JM::System::app().ldVectorPtr->at(index.row())->enabled())
        {
            editor->setGeometry(option.rect);
        }
        else
        {
            editor->setGeometry(QRect(0, 0, 0, 0));
        }
    }
    else
    {
        if (JM::System::app().ldVectorPtr->at(index.row())->enabled() &&
            JM::System::app().ldVectorPtr->at(index.row())->showed())
        {
            editor->setGeometry(option.rect);
        }
        else
        {
            editor->setGeometry(QRect(0, 0, 0, 0));
        }
    }
}