#include "gerenciadorrede.h"

//#include <cstdlib>

#include "redeconfig.h"

GerenciadorRede::GerenciadorRede( Rede::Peer* _primeiro_peer )
{
    this->gerenciador_conexoes = new Rede::GerenciadorConexao::GerenciadorConexao();
    this->ouvinte = new Rede::Ouvinte(this);

    QObject::connect(this->ouvinte, SIGNAL(novaConn(int)),
                     this->gerenciador_conexoes, SLOT(novaConexao(int)));

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

    //conectar na porta 6969 e perguntar pelo servidor
    _primeiro_peer->conectar();
}
