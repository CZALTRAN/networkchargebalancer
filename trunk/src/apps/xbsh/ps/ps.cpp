#include "ps.h"

#include <QDebug>
#include <QStringList>

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
        QStringList
        processos = this->gp_interface->getAllProcesses();

        QString
        processo;

        qDebug() << "<nome processo>   <pid>   <peer solic>   <peer rod>   <req>";

        QStringList
        quebrado;

        if ( processos.size() > 0 )
        {
            foreach(processo, processos)
            {
                quebrado = processo.split(':');

                if ( quebrado.size() >= 5)
                {
                    qDebug() << quebrado.at(0) << "       "
                             << quebrado.at(1) << "       "
                             << quebrado.at(2) << "       "
                             << quebrado.at(3) << "       "
                             << quebrado.at(4) << "       ";
                }

            }
        }
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
