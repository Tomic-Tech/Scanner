#include "vehicledelegate.h"
#include "vehicle.h"

VehicleDelegate::VehicleDelegate(QObject *parent)
    : QItemDelegate(parent)
{

}

void VehicleDelegate::paint(QPainter *painter,
    const QStyleOptionViewItem &option,
    const QModelIndex &index) const
{
    QStyleOptionViewItemV4 opt = setOptions(index, option);
    if (qVariantCanConvert<Vehicle>(index.data()))
    {
        Vehicle v = qVariantValue<Vehicle>(index.data());

        // prepare
        painter->save();
        QPixmap pixmap;

        if (option.state & QStyle::State_Selected)
        {
            painter->fillRect(option.rect, option.palette.highlight());
            pixmap.load(":/images/Selected.png");
        }
        else
        {
            pixmap.load(":/images/Unselected.png");
        }
        QRect decorationRect = QRect(opt.rect.topLeft(), QSize(64, 64));
        drawBackground(painter, opt, index);
        painter->drawPixmap(decorationRect, pixmap);

        QFont namefont(QString::fromUtf8("微软雅黑"), 16);
        QFontMetrics namefm(namefont);
        QRect nameRect = QRect(decorationRect.topRight() + QPoint(2, 2),
            QSize(namefm.width(v.vehicleName()),
            namefm.height()));




        painter->drawText(nameRect, v.vehicleName());

        drawFocus(painter, opt, opt.rect);

        // done
        painter->restore();

        painter->save();

        QFont brieffont(QString::fromUtf8("微软雅黑"), 16);
        QFontMetrics brieffm(brieffont);
        QRect briefRect = QRect(nameRect.bottomLeft() + QPoint(2, 2),
            QSize(brieffm.width(v.brief()), brieffm.height()));
        painter->drawText(briefRect, v.brief());
        painter->restore();
    }
    else
    {
        QItemDelegate::paint(painter, option, index);
    }
}

QSize VehicleDelegate::sizeHint(const QStyleOptionViewItem &option,
    const QModelIndex &index) const
{
    if (qVariantCanConvert<Vehicle>(index.data()))
    {
        Vehicle v = qVariantValue<Vehicle>(index.data());
        return QSize(240, 72);
    }
    else
    {
        return QItemDelegate::sizeHint(option, index);
    }
}

QWidget* VehicleDelegate::createEditor(QWidget *parent,
    const QStyleOptionViewItem &option,
    const QModelIndex &index) const
{
    if (qVariantCanConvert<Vehicle>(index.data()))
    {
        return 0;
    }
    else
    {
        return QItemDelegate::createEditor(parent, option, index);
    }
}

void VehicleDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    if (qVariantCanConvert<Vehicle>(index.data()))
    {
        Vehicle vehicle = qVariantValue<Vehicle>(index.data());
    }
    else
    {
        QItemDelegate::setEditorData(editor, index);
    }
}

void VehicleDelegate::setModelData(QWidget *editor,
    QAbstractItemModel *model,
    const QModelIndex &index) const
{
    if (qVariantCanConvert<Vehicle>(index.data()))
    {
        //        VehicleItem *item = qobject_cast<VehicleItem*>(editor);
        //        model->setData(index, qVariantFromValue(item->vehicle()));
    }
    else
    {
        QItemDelegate::setModelData(editor, model, index);
    }
}

void VehicleDelegate::updateEditorGeometry(QWidget *editor,
    const QStyleOptionViewItem &option,
    const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}

