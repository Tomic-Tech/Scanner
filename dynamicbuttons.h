#ifndef DYNAMIC_BUTTONS_H
#define DYNAMIC_BUTTONS_H

#include <QtGui>

class DynamicButtons : public QWidget
{
    Q_OBJECT
public:
    explicit DynamicButtons(Qt::Orientations orientation, QWidget *parent = 0);
    ~DynamicButtons();
signals:
    void sendBtnClk(const QString &text);
    void sendBtnClkByInx(int index);
public slots:
    void addBtn(const QString &text);
    void btnClr();
    void btnClked();
    void defaultBtnClked(const QString &text);
private:
    QList<QPushButton *>_buttonList;
    QLayout *_layout;
};

#endif