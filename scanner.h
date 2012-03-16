#ifndef SCANNER_H
#define SCANNER_H

#include <QtGui/QMainWindow>
#include <QtCore/QSettings>
#include "ui_scanner.h"
#include "setting.h"
#include "vehicle.h"
#include "vehicledelegate.h"
#include "vehiclemodel.h"
#include "vehiclethread.h"
#include "dynamicbuttons.h"

class Scanner : public QMainWindow
{
	Q_OBJECT

public:
	Scanner(QWidget *parent = 0, Qt::WFlags flags = 0);
	~Scanner();
    VehicleThread* thread();
protected:
    void changeEvent(QEvent *event);
private slots:
    void showSetting();
    void showRegister();
    void on_vehicleList_clicked(const QModelIndex &index);
    void on_vehicleList_doubleClicked(const QModelIndex &index);
    void btnClked(int index);
private:
    void scanVehicles();
private:
	Ui::ScannerClass _ui;
    VehicleModel _model;
    VehicleDelegate _delegate;
    DynamicButtons _dynamicButtons;
    VehicleThread _thread;
    Setting _setting;
};

#endif // SCANNER_H
