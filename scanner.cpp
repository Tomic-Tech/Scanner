#include "scanner.h"
#include <jm/jmlib.h>
#include "register.h"

Scanner::Scanner(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
    , _model(this)
    , _delegate(this)
    , _dynamicButtons(Qt::Vertical, this)
    , _thread(this)
    , _setting(this)
{
	_ui.setupUi(this);

    _ui.horizontalLayout->addWidget(&_dynamicButtons);
    _ui.vehicleList->setModel(&_model);
    _ui.vehicleList->setItemDelegate(&_delegate);
    _dynamicButtons.addBtn(trUtf8("Enter"));
    _dynamicButtons.addBtn(trUtf8("Quit"));

    connect(&_dynamicButtons, SIGNAL(sendBtnClkByInx(int)), this, SLOT(btnClked(int)));
    connect(_ui.actionSettings, SIGNAL(triggered()), this, SLOT(showSetting()));
    connect(_ui.actionRegister, SIGNAL(triggered()), this, SLOT(showRegister()));

    showSetting();
    scanVehicles();
}

Scanner::~Scanner()
{

}

void Scanner::showSetting()
{
    _setting.exec();
}

void Scanner::showRegister()
{
    Register r;
    r.exec();
}

void Scanner::scanVehicles()
{
    _model.removeRows(0, _model.rowCount());
    QDir dir(QString::fromUtf8(jm_vehicles_dir()));
    if (dir.exists())
    {
        dir.setFilter(QDir::Dirs | QDir::NoSymLinks);

        QStringList dirList = dir.entryList();
        dirList.removeFirst();
        dirList.removeFirst();
        foreach (QString dirName, dirList)
        {
            // check dirName.xml
            dir.cd(dirName);
            if (dir.exists(dirName + ".xml"))
            {
                _model.insertRow(_model.rowCount());
                _model.setData(_model.index(_model.rowCount() - 1),
                    QVariant::fromValue(Vehicle(dir.absoluteFilePath(dirName + ".xml"))));
            }
            dir.cdUp();
        }
    }
}

void Scanner::on_vehicleList_clicked(const QModelIndex &index)
{
    if (index.isValid())
    {
        if (qVariantCanConvert<Vehicle>(_model.data(index)))
        {
            Vehicle v = qVariantValue<Vehicle>(_model.data(index));
            _ui.vehicleDetail->setPlainText(v.longText());
        }
    }
}

void Scanner::on_vehicleList_doubleClicked(const QModelIndex &index)
{
    if (index.isValid())
    {
        if (qVariantCanConvert<Vehicle>(_model.data(index)))
        {
            Vehicle v = qVariantValue<Vehicle>(_model.data(index));
            _thread.init(v.vehiclePath(),
                v.vehiclePath(),
                v.vehiclePath());
            _thread.start(QThread::IdlePriority);
			jm_log_write("Vehicle", v.vehicleName().toUtf8().data());
        }
    }
}

void Scanner::btnClked(int index)
{
    switch (index)
    {
    case 0:
        on_vehicleList_doubleClicked(_ui.vehicleList->currentIndex());
        break;
    case 1:
        qApp->quit();
        break;
    }
}

void Scanner::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::LanguageChange)
    {
        _dynamicButtons.btnClr();
        _dynamicButtons.addBtn(trUtf8("Enter"));
        _dynamicButtons.addBtn(trUtf8("Quit"));
        _ui.retranslateUi(this);
        scanVehicles();
    }
    else
    {
        QWidget::changeEvent(event);
    }
}

VehicleThread* Scanner::thread()
{
    return &_thread;
}
