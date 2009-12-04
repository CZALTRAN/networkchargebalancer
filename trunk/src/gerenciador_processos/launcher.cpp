#include "launcher.h"

GP::Launcher::Launcher(QObject *parent) :
    QObject(parent)
{


}

GP::Launcher::~Launcher()
{


}

void
GP::Launcher::processoStart( const int& _id_host, const int& _id_dono, const QString&, const QStringList& _parametros )
{

    // se o _id_host for o igual ao meu_id, starta um ProcessoLocalOuImportado
    // senao, envia mensagem através da rede para o _id_host startar um processo

}

void
GP::Launcher::incommingMessage( const int& _id, const GP::PacoteBase& _parametros )
{

}

