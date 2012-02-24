#ifndef TROUBLE_CODE_H
#define TROUBLE_CODE_H

#include <QWidget>
#include "ui_troublecode.h"
#include "dynamicbuttons.h"
#include "troublecodemodel.h"

class TroubleCode : public QWidget
{
    Q_OBJECT

public:
    explicit TroubleCode(QWidget *parent = 0);
    DynamicButtons *dynamicButtons();
protected:
    void changeEvent(QEvent *event);
public slots:
    void addItem(const QString &code, const QString &text);
    void itemClr();
private:
    Ui::TroubleCodeClass _ui;
    DynamicButtons _dynamicButtons;
    TroubleCodeModel _model;
};

#endif