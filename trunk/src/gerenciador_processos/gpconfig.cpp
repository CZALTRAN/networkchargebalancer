#include "gpconfig.h"

GP::GPConfig::GPConfig()
{
}

GP::GPConfig::GPConfig( GPConfig const& )
{

}

int
GP::GPConfig::getMeuId()
{
    return this->meu_id;
}

GP::GPConfig&
GP::GPConfig::getInstance()
{
    static GP::GPConfig
    instancia;

    return instancia;
}

GP::GPConfig&
GP::GPConfig::operator= ( GP::GPConfig const& )
{

}


