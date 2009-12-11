#include "kill.h"

#include <QDebug>

Kill::Kill(  const QStringList& _argumentos, QObject* _parent )
    : ProcessoNativoPai( _argumentos, _parent )
{
}

void
Kill::run()
{
    if ( this->args.indexOf("-help") != -1 )
    {
        this->printHelp();
    }
    else
    {
        this->gp_interface->matarProcesso(
                this->getIntArgument("-pid"),
                this->getIntArgument("-peer"),
                this->getIntArgument("-req")
                );
    }
    this->exit(0);
}

void
Kill::printHelp()
{
    qDebug() << "Modo de usar:";
    qDebug() << "      kill -pid <pid> -peer <peer solicitante> -req <id_requisicao>";
}
