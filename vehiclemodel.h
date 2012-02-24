#ifndef VEHICLE_MODEL_H
#define VEHICLE_MODEL_H

#include <QList>
#include <QAbstractListModel>
#include "vehicle.h"

class VehicleModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit VehicleModel(QObject *parent = 0);
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
    bool insertRows(int position, int rows, const QModelIndex &parent = QModelIndex());
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex());
signals:

    public slots:
private:
    QList<Vehicle> _vehicles;
};

#endif