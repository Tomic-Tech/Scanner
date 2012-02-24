#include "vehiclemodel.h"

VehicleModel::VehicleModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

int VehicleModel::rowCount(const QModelIndex &parent) const
{
    return _vehicles.size();
}

QVariant VehicleModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role == Qt::DisplayRole)
    {
        return QVariant::fromValue(_vehicles[index.row()]);
    }
    return QVariant();
}

bool VehicleModel::insertRows(int position, int rows, const QModelIndex &parent)
{
    beginInsertRows(QModelIndex(), position, position + rows - 1);
    for (int row = 0; row < rows; ++row)
    {
        _vehicles.insert(position, Vehicle());
    }

    endInsertRows();
    return true;
}

bool VehicleModel::setData(const QModelIndex &index,
    const QVariant &value,
    int role)
{
    if (index.isValid() && role == Qt::EditRole)
    {
        _vehicles.replace(index.row(), qVariantValue<Vehicle>(value));
        emit dataChanged(index, index);
        return true;
    }
    return false;
}

bool VehicleModel::removeRows(int row, int count, const QModelIndex &parent)
{
    if (count == 0)
        return true;
    beginRemoveRows(QModelIndex(), row, row + count - 1);
    for (int i = 0; i < count; i++)
    {
        _vehicles.removeAt(row);
    }
    endRemoveRows();
    return true;
}
