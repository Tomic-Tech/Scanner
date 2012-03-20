#include "setting.h"
#include <jm/jmlib.h>

Setting::Setting(QWidget *parent, Qt::WFlags flags)
	: QDialog(parent, flags)
    , _setting("Tomic", "C168 II")
    , _spReadTimer(new QTimer(this))
    , _spWriteTimer(new QTimer(this))
    , _serial_port(jm_serial_port_new())
{
	_ui.setupUi(this);
    _commboxVer = (JMCommboxVersion)_setting.value("CommboxVer", QVariant(int(JM_COMMBOX_V1))).toInt();
    _ui.commboxVersion->setCurrentIndex(_commboxVer);
    _portType = (JMCommboxPortType)_setting.value("PortType", QVariant(int(JM_COMMBOX_PORT_SERIAL_PORT))).toInt();
    _ui.commboxPort->setCurrentIndex(_portType);

    jm_commbox_factory_set_commbox_version(_commboxVer);
    jm_commbox_port_set_type(_portType);

    connect(_ui.okButton, SIGNAL(clicked()), this, SLOT(onOk()));
    connect(_spReadTimer, SIGNAL(timeout()), this, SLOT(spRead()));
    connect(_spWriteTimer, SIGNAL(timeout()), this, SLOT(spWrite()));

    if (_portType == JM_COMMBOX_PORT_SERIAL_PORT)
    {
        jm_commbox_port_set_pointer(_serial_port);
        _spReadTimer->start(1);
        _spWriteTimer->start(1);
    }
    else
    {
        _spReadTimer->stop();
        _spWriteTimer->stop();
    }
}

Setting::~Setting()
{
    if (_portType == JM_COMMBOX_PORT_SERIAL_PORT)
    {
        _spReadTimer->stop();
        _spWriteTimer->stop();
    }
    delete _spReadTimer;
    delete _spWriteTimer;
}

void Setting::spRead()
{
    static guint8 buff[1024];
    static size_t avail = 0;
    avail = jm_serial_port_bytes_available(_serial_port);
    jm_serial_port_read(_serial_port, buff, avail);
    jm_commbox_port_push_in_deque(buff, avail);
}

void Setting::spWrite()
{
    static GByteArray *buff = NULL;
    if (jm_commbox_port_out_deque_available())
    {
        if (jm_commbox_port_pop_out_deque(&buff))
        {
            jm_serial_port_write(_serial_port, buff->data, buff->len);
        }
    }
}

void Setting::onOk() 
{
    _commboxVer = (JMCommboxVersion)_ui.commboxVersion->currentIndex();
    _portType = (JMCommboxPortType)_ui.commboxPort->currentIndex();

    _setting.setValue("CommboxVer", QVariant(int(_commboxVer)));
    _setting.setValue("PortType", QVariant(int(_portType)));

    jm_commbox_factory_set_commbox_version(_commboxVer);
    jm_commbox_port_set_type(_portType);

    if (_portType == JM_COMMBOX_PORT_SERIAL_PORT)
    {
        jm_commbox_port_set_pointer(_serial_port);
        _spReadTimer->start(1);
        _spWriteTimer->start(1);
    }
    else
    {
        _spReadTimer->stop();
        _spWriteTimer->stop();
    }
}