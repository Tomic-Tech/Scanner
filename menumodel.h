#ifndef MENU_MODEL_H
#define MENU_MODEL_H

#include <QAbstractListModel>
#include <QStringList>

class MenuModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit MenuModel(QObject *parent = 0);
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex());
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex());

private:
    QStringList _menus;
};

#endif