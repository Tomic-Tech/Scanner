#ifndef VEHICLE_DELEGATE_H
#define VEHICLE_DELEGATE_H

#include <QtGui>

class VehicleDelegate : public QItemDelegate
{
Q_OBJECT
public:
    explicit VehicleDelegate(QObject *parent = 0);
    //basic function for a read-only delegate, you can draw anything with the painter
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;

    //for a editable delegate
    QWidget* createEditor(QWidget *parent, const QStyleOptionViewItem &option,
        const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model,
        const QModelIndex &index) const;
    void updateEditorGeometry(QWidget *editor,
        const QStyleOptionViewItem &option,
        const QModelIndex &index) const;
signals:

    public slots:
};

#endif