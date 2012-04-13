#include "vehicle.h"
#include <QFile>
#include <jm/system/app.hpp>
#include <QtDebug>
#include <QLocale>
#include "utils.h"

Vehicle::Vehicle()
    : _imagePath()
    , _briefText()
    , _longText()
    , _vehicleName()
    , _vehiclePath()
{

}

Vehicle::Vehicle(const QString &imagePath, 
    const QString &brief, 
    const QString &longText, 
    const QString &vehicleName, 
    const QString &vehiclePath)
    : _imagePath(imagePath)
    , _briefText(brief)
    , _longText(longText)
    , _vehicleName(vehicleName)
    , _vehiclePath(vehiclePath)
{

}

Vehicle::Vehicle(const QString &xmlFileName)
    : _imagePath("")
    , _briefText("")
    , _longText("")
    , _vehicleName("")
    , _vehiclePath("")
{
    if (!QFile::exists(xmlFileName))
        return;
    QFile file(xmlFileName);
    QDomDocument domDocument;
    QString errorStr;
    int errorLine;
    int errorColumn;

    if (!domDocument.setContent(&file, true, &errorStr, &errorLine, &errorColumn))
    {
        return;
    }

    QDomElement root = domDocument.documentElement();
    if (root.hasAttribute("version")
        && root.attribute("version") != "1.0")
    {
        return;
    }

    setVehiclePath(root.tagName());
    setVehicleName(root);
    setBrief(root);
    setLongText(root);
}

QString Vehicle::imagePath() const
{
    return _imagePath;
}

void Vehicle::setImagePath(const QString &imagePath)
{
    if (imagePath != _imagePath)
    {
        _imagePath = imagePath;
    }
}

QString Vehicle::brief() const
{
    return _briefText;
}

void Vehicle::setBrief(const QString &brief)
{
    if (brief != _briefText)
    {
        _briefText = brief;
    }
}

void Vehicle::setBrief(const QDomElement &root)
{
    QDomElement brief = root.firstChildElement("Brief");

    QDomElement briefChild = brief.firstChildElement(UtilsInst().getTheSystemLang());
    setBrief(briefChild.text());

}

QString Vehicle::longText() const
{
    return _longText;
}

void Vehicle::setLongText(const QString &longText)
{
    if (longText != _longText)
    {
        _longText = longText;
    }
}

void Vehicle::setLongText(const QDomElement &root)
{
    QString longTextString;
    QDomElement longText = root.firstChildElement("LongText");
    QDomElement longTextChild = longText.firstChildElement("Version");
    while (!longTextChild.isNull())
    {
        QString number = longTextChild.attribute("Number");
        QDomElement child = longTextChild.firstChildElement(UtilsInst().getTheSystemLang());

        longTextString.append(QObject::trUtf8("version"));
        longTextString.append(QString(" %1: %2\n").arg(number).arg(child.text()));
        longTextChild = longTextChild.nextSiblingElement();
    }
    setLongText(longTextString);
}

QString Vehicle::vehicleName() const
{
    return _vehicleName;
}

void Vehicle::setVehicleName(const QString &vehicleName)
{
    if (_vehicleName != vehicleName)
    {
        _vehicleName = vehicleName;
    }
}

void Vehicle::setVehicleName(const QDomElement &root)
{
    QDomElement name = root.firstChildElement("Name");
    QDomElement nameChild = name.firstChildElement(UtilsInst().getTheSystemLang());
    setVehicleName(nameChild.text());
}

QString Vehicle::vehiclePath() const
{
    return _vehiclePath;
}

void Vehicle::setVehiclePath(const QString &vehiclePath)
{
    if (_vehiclePath != vehiclePath)
    {
        _vehiclePath = vehiclePath;
    }
}

Vehicle::Vehicle(const Vehicle &other)
{
    _imagePath = other.imagePath();
    _briefText = other.brief();
    _longText = other.longText();
    _vehicleName = other.vehicleName();
    _vehiclePath = other.vehiclePath();
}

Vehicle& Vehicle::operator =(const Vehicle &other)
{
    _imagePath = other.imagePath();
    _briefText = other.brief();
    _longText = other.longText();
    _vehicleName = other.vehicleName();
    _vehiclePath = other.vehiclePath();
    return *this;
}
