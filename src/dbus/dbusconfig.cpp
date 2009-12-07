#include "dbusconfig.h"

DBusConfig::DBusConfig()
{
    this->name_service = "uel.computacao.xboga";
    this->indice_processo = 0;
}

DBusConfig&
DBusConfig::getInstance()
{
    static DBusConfig
    instance;

    return instance;
}

int
DBusConfig::getNovoProcId()
{
    ++ this->indice_processo;

    return this->indice_processo;
}
