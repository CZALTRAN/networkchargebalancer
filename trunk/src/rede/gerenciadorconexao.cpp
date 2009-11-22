#include "gerenciadorconexao.h"

#include "redeconfig.h"

Rede::GerenciadorConexao::GerenciadorConexao()
{


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

void
Rede::GerenciadorConexao::addConexao( Rede::Peer* _novo_peer )
{
    int
    id = _novo_peer->getId();

    this->peers.insert(id, _novo_peer);
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
