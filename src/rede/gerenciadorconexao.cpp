#include "gerenciadorconexao.h"

#include "redeconfig.h"

Rede::GerenciadorConexao::GerenciadorConexao()
{

    if( Rede::RedeConfig::getInstance().estado_atual == Rede::SERVER )
    {
        Rede::Peer*
        eu_mesmo = new Rede::Peer();

        eu_mesmo->setId( Rede::RedeConfig::getInstance().meu_id );
        eu_mesmo->setHost( Rede::RedeConfig::getInstance().host );

        this->peers.insert( Rede::RedeConfig::getInstance().meu_id, eu_mesmo );
    }
}


Rede::GerenciadorConexao::~GerenciadorConexao()
{


}

Rede::Peer*
Rede::GerenciadorConexao::novaConexao( int _socket_descriptor)
{
    Rede::Peer*
    novo_peer = new Rede::Peer( _socket_descriptor );

    novo_peer->setId( this->peers.size()+1 );

    this->peers.insert( novo_peer->getId(), novo_peer );

    return novo_peer;
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
