#include "processoexportado.h"

GP::ProcessoExportado::ProcessoExportado()
{
}

int
GP::ProcessoExportado::getIdHost()
{
    return this->id_host;
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
