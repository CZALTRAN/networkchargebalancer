#include "gerenciadorrede.h"

//#include <cstdlib>

#include "redeconfig.h"

GerenciadorRede::GerenciadorRede( Rede::Peer* _primeiro_peer )
{
    this->gerenciador_conexoes = new Rede::GerenciadorConexao::GerenciadorConexao();
    this->ouvinte = new Rede::Ouvinte(this);

    QObject::connect(this->ouvinte, SIGNAL(novaConn(int)),
                     this, SLOT(slotIndicaServer(int)));

    if ( _primeiro_peer == NULL )
    {
        this->startComoServer();
    }
    else
    {
        this->buscaPorServer(_primeiro_peer);
    }

}

GerenciadorRede::~GerenciadorRede()
{

}

void
GerenciadorRede::startComoServer()
{
    Rede::RedeConfig::getInstance().meu_id = 1;
    Rede::RedeConfig::getInstance().server = true;
    Rede::RedeConfig::getInstance().estado_atual = Rede::SERVER;

    if (! this->ouvinte->startListen() )
    {
        exit(1);
    }
}

void
GerenciadorRede::buscaPorServer( Rede::Peer* _primeiro_peer )
{
    Rede::RedeConfig::getInstance().server = false;
    Rede::RedeConfig::getInstance().estado_atual = Rede::PROCURANDO_SERVER;

    _primeiro_peer->conectar();

}

void
GerenciadorRede::slotIndicaServer(int _socket_descriptor )
{
    qDebug() << Q_FUNC_INFO << "tenho que indicar o server para o socket "
             << _socket_descriptor;

    if ( Rede::RedeConfig::getInstance().server )
    { //sou o servidor e preciso indicar ao novo socket sobre todas as conexões.
        Rede::Peer*
        novo_peer = this->gerenciador_conexoes->novaConexao( _socket_descriptor );

        novo_peer->sendInit( this->gerenciador_conexoes->getTotalConn() );

        emit this->novoPeer( novo_peer->getHost() );

        QObject::connect(this,SIGNAL(novoPeer(QString)),
                         novo_peer,SLOT(enviaNovoPeer(QString)));
    }
    else
    { //não sou o servidor e preciso indicar quem é e fechar a conexão.


    }

}
