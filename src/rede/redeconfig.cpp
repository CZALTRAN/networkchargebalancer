#include "redeconfig.h"

Rede::RedeConfig
Rede::RedeConfig::getInstance()
{
    static Rede::RedeConfig
    instance;

    return instance;
}

Rede::RedeConfig::RedeConfig()
{
}
