#include "troublecodemodel.h"

TroubleCodeModel::TroubleCodeModel(QObject *parent)
    : QAbstractTableModel(parent)
{
}

int TroubleCodeModel::rowCount(const QModelIndex &parent) const
{
    return _troubleCodes.size();
}

int TroubleCodeModel::columnCount(const QModelIndex &parent) const
{
    return 2;
}

QVariant TroubleCodeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role == Qt::DisplayRole)
    {
        if (index.column() == 0)
        {
            return _troubleCodes[index.row()].first;
        }

        if (index.column() == 1)
        {
            return _troubleCodes[index.row()].second;
        }
    }
    return QVariant();
}

bool TroubleCodeModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid())
        return false;
    if (role == Qt::EditRole)
    {
        if (index.column() == 0)
        {
            _troubleCodes[index.row()].first = value.toString();
            emit dataChanged(index, index);
        }

        if (index.column() == 1)
        {
            _troubleCodes[index.row()].second = value.toString();
            emit dataChanged(index, index);
        }
        return true;
    }
    else
    {
        return QAbstractTableModel::setData(index, value, role);
    }
}

bool TroubleCodeModel::insertRows(int row, int count, const QModelIndex &parent)
{
    beginInsertRows(QModelIndex(), row, row + count - 1);
    for (int i = 0; i < count; i++)
    {
        _troubleCodes.insert(row, QPair<QString, QString>());
    }
    endInsertRows();
    return true;
}

bool TroubleCodeModel::removeRows(int row, int count, const QModelIndex &parent)
{
    if (count == 0)
        return true;
    beginRemoveRows(QModelIndex(), row, row + count - 1);
    for (int i = 0; i < count; i++)
    {
        _troubleCodes.removeAt(row);
    }
    endRemoveRows();
    return true;
}

QVariant TroubleCodeModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal)
    {
        if (section == 0)
            return QVariant(trUtf8("Code"));
        if (section == 1)
            return QVariant(trUtf8("Content"));
    }

    return QVariant();
}
