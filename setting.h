#ifndef SETTING_H
#define SETTING_H

#include <jm/jmserialport.h>
#include <jm/jmlib.h>
#include <QtGui/QDialog>
#include <QtCore/QSettings>
#include <QtCore/QTimer>
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