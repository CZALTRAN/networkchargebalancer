#include "processoexportado.h"

GP::ProcessoExportado::ProcessoExportado()
{
}

Q_PID
GP::ProcessoExportado::getPid()
{
    return this->pid;
}

int
GP::ProcessoExportado::getIdHost()
{
    return this->id_host;
}

void
GP::ProcessoExportado::setPid( const Q_PID& _pid )
{
    this->pid = _pid;
}

void
GP::ProcessoExportado::setIdHost( const int& _id_host )
{
    this->id_host = _id_host;
}

void
GP::ProcessoExportado::stdIn(const QString& _entrada)
{

}
