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

    int
    getNovoProcId();

private:

    DBusConfig();

    DBusConfig( const DBusConfig& );

    DBusConfig&
    operator= ( DBusConfig const& );

    int
    indice_processo;
};


#endif // DBUSCONFIG_H
