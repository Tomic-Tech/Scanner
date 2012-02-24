#ifndef MESSAGE_BOX_H
#define MESSAGE_BOX_H

#include <QDialog>
#include "ui_messagebox.h"
#include "dynamicbuttons.h"

class MessageBox : public QDialog
{
    Q_OBJECT
public:
    MessageBox(QWidget *parent = 0, Qt::WFlags flags = 0);
    DynamicButtons *dynamicButtons();
protected:
    void changeEvent(QEvent *event);
public slots:
    void setMsg(const QString &text);
    void setTitle(const QString &text);
private:
    Ui::MessageBoxClass _ui;
    DynamicButtons _dynamicButtons;
};

#endif