#include "ps.h"

#include <QDebug>

Ps::Ps( const QStringList& _argumentos, QObject* _parent )
    : ProcessoNativoPai(_argumentos,_parent)
{
}

void
Ps::run()
{
    if (this->args.indexOf("-help") != -1)
    {

        this->printHelp();
    }
    else
    {
        qDebug() << "<nome processo>:<pid>:<peer solicitante>:<peer rodando>:<requisicao>";
        qDebug() << this->gp_interface->getAllProcesses();
    }
    this->exit(0);
}

void
Ps::printHelp()
{
    qDebug() << "Uso:";
    qDebug() << "       ps";
    qDebug() << "Saida:";
    qDebug() << "       <nome processo>:<pid>:<peer solicitante>:<peer rodando>:<requisicao>";
}
