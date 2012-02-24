#ifndef LIVE_DATA_DELEGATE_H
#define LIVE_DATA_DELEGATE_H

#include <QItemDelegate>

class LiveDataDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    enum Mode
    {
        PrepareMode,
        LiveDataMode
    };
public:
    explicit LiveDataDelegate(Mode mode, QObject *parent = 0);
    void updateEditorGeometry(QWidget *editor,
        const QStyleOptionViewItem &option, const QModelIndex &index) const;
private:
    Mode _mode;
};

#endif