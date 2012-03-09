#ifndef SETTING_H
#define SETTING_H

#include <jm/jmserialport.h>
#include <QtGui/QDialog>
#include <QtCore/QSettings>
#include <QtCore/QTimer>
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
    void spRead();
    void spWrite();
private:
	Ui::SettingClass _ui;
    QSettings _setting;
    JMCommboxVersion _commboxVer;
    JMCommboxPortType _portType;
    QTimer *_spReadTimer;
    QTimer *_spWriteTimer;
    JMSerialPort *_serial_port;
};

#endif // SETTING_H