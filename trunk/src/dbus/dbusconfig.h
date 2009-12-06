#ifndef DBUSCONFIG_H
#define DBUSCONFIG_H

#include <QString>

class DBusConfig
{
public:

    QString
    name_service;

    static DBusConfig&
    getInstance();

    quint64
    getNovoProcId();

private:

    DBusConfig();

    DBusConfig( const DBusConfig& );

    DBusConfig&
    operator= ( DBusConfig const& );

    quint64
    indice_processo;
};


#endif // DBUSCONFIG_H
