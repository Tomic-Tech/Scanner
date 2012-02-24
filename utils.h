#ifndef UTILS_H
#define UTILS_H

#include <QStringList>
#include <QLocale>

class Utils
{
public:
    static Utils& instance();
    QString getTheSystemLang();
private:
    Utils();
    QStringList _localeSupport;
};

inline Utils& UtilsInst()
{
    return Utils::instance();
}

#endif