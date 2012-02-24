#ifndef TROUBLE_CODE_MODEL
#define TROUBLE_CODE_MODEL

#include <QAbstractTableModel>
#include <QList>
#include <QPair>

class TroubleCodeModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit TroubleCodeModel(QObject *parent = 0);
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex());
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex());
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

private:
    QList<QPair<QString, QString> > _troubleCodes;
};

#endif