#include "gerenciadorconexao.h"

#include "redeconfig.h"

Rede::GerenciadorConexao::GerenciadorConexao()
{

    Rede::Peer*
    eu_mesmo = new Rede::Peer();

    eu_mesmo->setId( Rede::RedeConfig::getInstance().meu_id );
    eu_mesmo->setHost( Rede::RedeConfig::getInstance().host );

    this->peers.insert( this->peers.size(), eu_mesmo );
}


Rede::GerenciadorConexao::~GerenciadorConexao()
{


}

Rede::Peer*
Rede::GerenciadorConexao::novaConexao( int _socket_descriptor)
{


}

Rede::Peer*
Rede::GerenciadorConexao::getPeerById( const int& _id)
{
    return this->peers[_id];
}

int
Rede::GerenciadorConexao::getTotalConn() const
{
    return this->peers.size();
}
