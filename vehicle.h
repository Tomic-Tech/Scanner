#ifndef VEHICLE_H
#define VEHICLE_H

#include <QtXml>

class Vehicle {
public:
    Vehicle();
    Vehicle(const QString &imagePath,
        const QString &brief,
        const QString &longText,
        const QString &VehicleName,
        const QString &VehiclePath);
    Vehicle(const QString &xmlFileName);
    Vehicle(const Vehicle &other);
    Vehicle& operator=(const Vehicle &other);
    QString imagePath() const;
    void setImagePath(const QString &imagePath);
    QString brief() const;
    void setBrief(const QString &brief);
    QString longText() const;
    void setLongText(const QString &longText);
    QString vehicleName() const;
    void setVehicleName(const QString &VehicleName);
    QString vehiclePath() const;
    void setVehiclePath(const QString &VehiclePath);
private:
    void setVehicleName(const QDomElement &root);
    void setBrief(const QDomElement &root);
    void setLongText(const QDomElement &root);
private:
    QString _imagePath;
    QString _briefText;
    QString _longText;
    QString _vehicleName;
    QString _vehiclePath;
};

Q_DECLARE_METATYPE(Vehicle)

#endif