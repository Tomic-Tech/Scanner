#include "utils.h"

Utils::Utils()
    : _localeSupport()
{
    _localeSupport.append("en-US");
    _localeSupport.append("zh-CN");
}

QString Utils::getTheSystemLang()
{
    QString lang = QLocale::system().name();
    lang.replace('_', '-');
    int index = _localeSupport.indexOf(lang);
    if (index == -1)
        return _localeSupport[0];
    return lang;
}

Utils& Utils::instance()
{
    static Utils inst;
    return inst;
}