#include "peerrelacionado.h"

#include <cstdlib>

#include <QDebug>

GP::PeerRelacionado::PeerRelacionado(QObject* _parent)
    : QObject(_parent)
{
}

const GP::Processo*
GP::PeerRelacionado::getProcesso(const Q_PID& _pid)
{
    if( this->processos.contains(_pid) )
    {
        return static_cast<const GP::Processo*>(this->processos.value(_pid));
    }
    else
    {
        qDebug() << Q_FUNC_INFO << "Processo não encontrado!!";
        exit(1);
    }
}

void
GP::PeerRelacionado::insereProcesso(const Q_PID& _pid, const Processo* _processo)
{
    this->processos.insert(_pid, _processo);
}

