#include "processosconfig.h"

GP::ProcessosConfig::ProcessosConfig()
{
}

GP::ProcessosConfig::ProcessosConfig( ProcessosConfig const& )
{

}

void
GP::ProcessosConfig::insereProcesso( Processo& _processo )
{

}

GP::Processo
GP::ProcessosConfig::getProcesso( Q_PID _pid, int _id_dono )
{

}

GP::ProcessosConfig&
GP::ProcessosConfig::getInstance()
{
    static GP::ProcessosConfig
    instancia;

    return instancia;
}

GP::ProcessosConfig&
GP::ProcessosConfig::operator= ( GP::ProcessosConfig const& )
{

}


