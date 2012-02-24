#ifndef SETTING_H
#define SETTING_H

#include <QtGui/QDialog>
#include <QtCore/QSettings>
#include <jm/jmcommboxversion.h>
#include <jm/jmcommboxport.h>
#include "ui_setting.h"

class Setting : public QDialog
{
	Q_OBJECT

public:
	Setting(QWidget *parent = 0, Qt::WFlags flags = 0);
	~Setting();
private slots:
    void onOk();
private:
	Ui::SettingClass _ui;
    QSettings _setting;
    JMCommboxVersion _commboxVer;
    JMCommboxPortType _portType;
};

#endif // SETTING_H