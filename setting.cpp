#include "setting.h"
#include <jm/jmlib.h>

Setting::Setting(QWidget *parent, Qt::WFlags flags)
	: QDialog(parent, flags)
    , _setting("Tomic", "C168 II")
{
	_ui.setupUi(this);
    _commboxVer = (JMCommboxVersion)_setting.value("CommboxVer", QVariant(int(JM_COMMBOX_V1))).toInt();
    _ui.commboxVersion->setCurrentIndex(_commboxVer);
    _portType = (JMCommboxPortType)_setting.value("PortType", QVariant(int(JM_COMMBOX_PORT_SERIAL_PORT))).toInt();
    _ui.commboxPort->setCurrentIndex(_portType);

    jm_commbox_factory_set_commbox_version(_commboxVer);
    jm_commbox_port_set_type(_portType);

    connect(_ui.okButton, SIGNAL(clicked()), this, SLOT(onOk()));
}

Setting::~Setting()
{

}

void Setting::onOk() 
{
    _commboxVer = (JMCommboxVersion)_ui.commboxVersion->currentIndex();
    _portType = (JMCommboxPortType)_ui.commboxPort->currentIndex();

    _setting.setValue("CommboxVer", QVariant(int(_commboxVer)));
    _setting.setValue("PortType", QVariant(int(_portType)));

    jm_commbox_factory_set_commbox_version(_commboxVer);
    jm_commbox_port_set_type(_portType);
}