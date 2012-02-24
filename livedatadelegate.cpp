#include "livedatadelegate.h"
#include <jm/jmldarray.h>

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
        if (jm_ld_array_get_enabled(index.row()))
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
        if (jm_ld_array_get_enabled(index.row()) &&
            jm_ld_array_get_show(index.row()))
        {
            editor->setGeometry(option.rect);
        }
        else
        {
            editor->setGeometry(QRect(0, 0, 0, 0));
        }
    }
}