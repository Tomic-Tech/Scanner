#ifndef MENU_H
#define MENU_H

#include <QWidget>
#include "dynamicbuttons.h"
#include "menumodel.h"
#include "ui_menu.h"

class Menu : public QWidget
{
    Q_OBJECT

public:
    explicit Menu(QWidget *parent = 0);
    DynamicButtons *dynamicButtons();

public slots:
    void addItem(const QString &text);
    void itemClr();
    void btnClked(int index);
protected:
    void changeEvent(QEvent *event);
private slots:
    void on_menuList_doubleClicked(const QModelIndex &index);

private:
    Ui::MenuClass _ui;
    DynamicButtons _dynamicButtons;
    MenuModel _model;
};


#endif