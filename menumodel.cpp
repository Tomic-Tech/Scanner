#include "menumodel.h"

MenuModel::MenuModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

int MenuModel::rowCount(const QModelIndex &parent) const
{
    return _menus.size();
}

QVariant MenuModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role == Qt::DisplayRole)
    {
        return QVariant(_menus[index.row()]);
    }
    return QVariant();
}

bool MenuModel::insertRows(int position, int rows, const QModelIndex &parent)
{
    beginInsertRows(QModelIndex(), position, position + rows - 1);
    for (int row = 0; row < rows; ++row)
    {
        _menus.insert(position, QString());
    }

    endInsertRows();
    return true;
}

bool MenuModel::removeRows(int row, int count, const QModelIndex &parent)
{
    if (count == 0)
        return true;
    beginRemoveRows(QModelIndex(), row, row + count - 1);
    for (int i = 0; i < count; i++)
    {
        _menus.removeAt(row);
    }
    endRemoveRows();
    return true;
}

bool MenuModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid() && role == Qt::EditRole)
    {
        _menus.replace(index.row(), value.toString());
        emit dataChanged(index, index);
        return true;
    }
    return false;
}
