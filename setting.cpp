#include "setting.h"
#include <jm/system/app.h>

Setting::Setting(QWidget *parent, Qt::WFlags flags)
	: QDialog(parent, flags)
    , _setting("Tomic", "C168 II")
{
	_ui.setupUi(this);
    _commboxVer = (JM::Diag::BoxFactory::Version)_setting.value("CommboxVer", QVariant(int(JM::Diag::BoxFactory::V1))).toInt();
    _ui.commboxVersion->setCurrentIndex(_commboxVer);
    _portType = (JM::Diag::BoxStream::RealType)_setting.value("PortType", QVariant(int(JM::Diag::BoxStream::SerialPort))).toInt();
    _ui.commboxPort->setCurrentIndex(_portType);

    JM::System::app().box().set_version(_commboxVer);
    JM::System::app().stream().set_type(_portType);

    connect(_ui.okButton, SIGNAL(clicked()), this, SLOT(onOk()));
}

Setting::~Setting()
{

}

void Setting::onOk() 
{
    _commboxVer = (JM::Diag::BoxFactory::Version)_ui.commboxVersion->currentIndex();
    _portType = (JM::Diag::BoxStream::RealType)_ui.commboxPort->currentIndex();

    _setting.setValue("CommboxVer", QVariant(int(_commboxVer)));
    _setting.setValue("PortType", QVariant(int(_portType)));

    JM::System::app().box().set_version(_commboxVer);
    JM::System::app().stream().set_type(_portType);
}