#include "dbusconfig.h"

DBus::DBusConfig::DBusConfig()
{
    this->name_service = "uel.computacao.xboga";
}

DBus::DBusConfig&
DBus::DBusConfig::getInstance()
{
    static DBus::DBusConfig
    instance;

    return instance;
}
