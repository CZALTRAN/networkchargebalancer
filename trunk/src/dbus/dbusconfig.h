#ifndef DBUSCONFIG_H
#define DBUSCONFIG_H

#include <QString>

namespace DBus
{
    class DBusConfig
    {
    public:

        QString
        name_service;

        static DBus::DBusConfig&
        getInstance();

    private:

        DBusConfig();

        DBusConfig( const DBusConfig& );

        DBus::DBusConfig&
        operator= ( DBus::DBusConfig const& );
    };
}


#endif // DBUSCONFIG_H
