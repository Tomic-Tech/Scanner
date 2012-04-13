#include "livedatamodel.h"
#include <jm/system/app.hpp>

LiveDataModel::LiveDataModel(Mode mode, QObject *parent /* = 0 */)
    : QAbstractTableModel(parent)
    , _mode(mode)
{
}

int LiveDataModel::rowCount(const QModelIndex &parent) const
{
    if (_mode == PrepareMode)
    {
        return JM::System::app().ldVecPtr->enabledSize();
    }
    else
    {
        return JM::System::app().ldVecPtr->showedSize();
    }
}

int LiveDataModel::columnCount(const QModelIndex &parent) const
{
    if (_mode == PrepareMode)
    {
        return 2;
    }
    else
    {
        return 5;
    }
}

QVariant LiveDataModel::data(const QModelIndex &index, int role) const
{
    using namespace JM::System;
    if (!index.isValid())
        return QVariant();

    if (_mode == PrepareMode)
    {
        switch (role)
        {
        case Qt::DisplayRole:
            if (index.column() == 0)
            {
                return QString::fromUtf8(
                    app().ldVecPtr->at(app().ldVecPtr->getEnabledIndex(index.row()))->shortName().c_str());
            }
            if (index.column() == 1)
            {
                return QString::fromUtf8(
                    app().ldVecPtr->at(app().ldVecPtr->getEnabledIndex(index.row()))->content().c_str());
            }
            break;
        case Qt::CheckStateRole:
            if (index.column() == 0)
            {
                return app().ldVecPtr->at(app().ldVecPtr->getEnabledIndex(index.row()))->showed() ? Qt::Checked : Qt::Unchecked;
            }
        }
    }
    else
    {
        if (role == Qt::DisplayRole)
        {
            if (index.column() == 0)
            {
                return QString::fromUtf8(
                    app().ldVecPtr->at(app().ldVecPtr->getShowedIndex(index.row()))->shortName().c_str());
            }
            else if (index.column() == 1)
            {
                return QString::fromUtf8(
                    app().ldVecPtr->at(app().ldVecPtr->getShowedIndex(index.row()))->content().c_str());
            }
            else if (index.column() == 2)
            {
                return QString::fromUtf8(
                    app().ldVecPtr->at(app().ldVecPtr->getShowedIndex(index.row()))->value().c_str());
            }
            else if (index.column() == 3)
            {
                return QString::fromUtf8(
                    app().ldVecPtr->at(app().ldVecPtr->getShowedIndex(index.row()))->unit().c_str());
            }
            else if (index.column() == 4)
            {
                return QString::fromUtf8(
                    app().ldVecPtr->at(app().ldVecPtr->getShowedIndex(index.row()))->defaultValue().c_str());
            }
        }
    }
    return QVariant();
}

void LiveDataModel::setData(int index, const QString &value)
{
    using namespace JM::System;
    if (_mode == PrepareMode)
        return;
    setData(this->index(app().ldVecPtr->queryShowedPosition(index), 2), QVariant(value));
}

bool LiveDataModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    using namespace JM::System;
    if (!index.isValid())
        return false;

    if (_mode == PrepareMode)
    {
        switch (role)
        {
        case Qt::EditRole:
            if (index.column() == 0)
            {
                if (value.type() == QVariant::String)
                {
                }
                else
                {
                    app().ldVecPtr->at(app().ldVecPtr->getEnabledIndex(index.row()))->setShowed(value.toBool());
                }
                emit dataChanged(index, index);
            }

            if (index.column() == 1)
            {
                emit dataChanged(index, index);
            }
            break;
        case Qt::CheckStateRole:
            if (index.column() == 0)
            {
                app().ldVecPtr->at(app().ldVecPtr->getEnabledIndex(index.row()))->setShowed(value.toBool());
                emit dataChanged(index, index);
            }
            break;
        }
        return true;
    }
    else
    {
        if (role == Qt::EditRole)
        {
            if (index.column() == 0)
            {
                emit dataChanged(index, index);
            }
            if (index.column() == 1)
            {
                emit dataChanged(index, index);
            }
            if (index.column() == 2)
            {
                // 
                emit dataChanged(index, index);
            }
            if (index.column() == 3)
            {
                emit dataChanged(index, index);
            }
            if (index.column() == 4)
            {
                emit dataChanged(index, index);
            }
            return true;
        }
    }
    return false;
}

//bool LiveDataModel::insertRows(int row, int count, const QModelIndex &parent)
//{
//    beginInsertRows(QModelIndex(), row, row + count - 1);
//    for (int i = 0; i < count; i++)
//    {
//        _liveDatas.insert(row, jmLiveData());
//    }
//    endInsertRows();
//    return true;
//}

//bool LiveDataModel::removeRows(int row, int count, const QModelIndex &parent)
//{
//    if (count == 0)
//        return true;
//    beginRemoveRows(QModelIndex(), row, row + count - 1);
//    for (int i = 0; i < count; i++)
//    {
//        _liveDatas.removeAt(row);
//    }
//    endRemoveRows();
//    return true;
//}

Qt::ItemFlags LiveDataModel::flags(const QModelIndex &index) const
{
    if (index.column() == 0)
        return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsUserCheckable;
    return QAbstractTableModel::flags(index);
}

//void LiveDataModel::addItem(const QString &shortName,
//    const QString &content,
//    const QString &unit,
//    const QString &defValue,
//    bool enabled)
//{
//    _realCount++;
//    if (enabled)
//    {
//        _indexMapper.insert(_realCount, rowCount());
//        if(_mode == PrepareMode)
//        {
//            insertRow(rowCount());
//            setData(index(rowCount() - 1, 0), QVariant(shortName));
//            setData(index(rowCount() - 1, 0), QVariant(false));
//            setData(index(rowCount() - 1, 1), QVariant(content));
//        }
//        else
//        {
//            insertRow(rowCount());
//            setData(index(rowCount() - 1, 0), QVariant(shortName));
//            setData(index(rowCount() - 1, 1), QVariant(content));
//            setData(index(rowCount() - 1, 2), QVariant(QString("")));
//            setData(index(rowCount() - 1, 3), QVariant(unit));
//            setData(index(rowCount() - 1, 4), QVariant(defValue));
//        }
//    }
//}

//void LiveDataModel::itemClear()
//{
//    _realCount = -1;
//    removeRows(0, rowCount());
//}

QVariant LiveDataModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (_mode == PrepareMode)
    {
        if (orientation == Qt::Horizontal)
        {
            if (section == 0)
            {
                return QVariant(trUtf8("Short Name"));
            }
            if (section == 1)
            {
                return QVariant(trUtf8("Content"));
            }
        }
    }
    else
    {
        if (orientation == Qt::Horizontal)
        {
            if (section == 0)
            {
                return QVariant(trUtf8("Short Name"));
            }
            if (section == 1)
            {
                return QVariant(trUtf8("Content"));
            }
            if (section == 2)
            {
                return QVariant(trUtf8("Value"));
            }
            if (section == 3)
            {
                return QVariant(trUtf8("Unit"));
            }
            if (section == 4)
            {
                return QVariant(trUtf8("Default Value"));
            }
        }
    }
    return QVariant();
}

