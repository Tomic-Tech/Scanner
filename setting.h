#ifndef SETTING_H
#define SETTING_H

#include <jm/system/app.h>
#include <jm/diag/boxfactory.h>
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
    JM::Diag::BoxFactory::Version _commboxVer;
    JM::Diag::BoxStream::RealType _portType;
};

#endif // SETTING_H