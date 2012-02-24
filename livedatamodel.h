#ifndef LIVE_DATA_MODEL_H
#define LIVE_DATA_MODEL_H

#include <QAbstractTableModel>

class LiveDataModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    enum Mode {
        PrepareMode,
        LiveDataMode
    };
public:
    explicit LiveDataModel(Mode mode, QObject *parent = 0);
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
    //bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex());
    //bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex());
    Qt::ItemFlags flags(const QModelIndex &index) const;
    //void addItem(const QString &shortName, const QString &content, const QString &unit,
    //    const QString &defValue, bool enabled);
    void setData(int index, const QString &value);
    //void itemClear();
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

private:
    Mode _mode;
};

#endif