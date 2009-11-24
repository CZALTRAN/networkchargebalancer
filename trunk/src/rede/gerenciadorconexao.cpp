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

    this->indexaPeer( novo_peer->getId(), novo_peer );

    return novo_peer;
}

void
Rede::GerenciadorConexao::addConexao( Rede::Peer* _novo_peer )
{
    int
    id = _novo_peer->getId();

    if ( this->peers.size() == Rede::RedeConfig::getInstance().qtdePeers &&
         Rede::RedeConfig::getInstance().estado_atual != Rede::SERVER)
    {
        qDebug() << Q_FUNC_INFO << "em conectado!";
        Rede::RedeConfig::getInstance().estado_atual = Rede::CONECTADO;
    }

    this->indexaPeer( id, _novo_peer );
}

Rede::Peer*
Rede::GerenciadorConexao::getPeerById( const int& _id) const
{
    return this->peers[_id];
}

Rede::Peer*
Rede::GerenciadorConexao::getPeerByHost( const QString& _host) const
{

}

int
Rede::GerenciadorConexao::getTotalConn() const
{
    return this->peers.size();
}

void
Rede::GerenciadorConexao::peerCaiu( Rede::Peer* const _peer )
{
    if( _peer->getId() == Rede::RedeConfig::getInstance().server_host->getId() )
    {
        qDebug() << Q_FUNC_INFO << "Fudeu. Caiu o server. Vou notificar o GR";

        this->setNextServer();
        emit this->peerCaiu(true);
    }
    else
    {
        qDebug() << Q_FUNC_INFO << "O idiota " << _peer->getHost() << " caiu.";
        emit this->peerCaiu(false);
    }

    this->peers.remove(_peer->getId());
}

void
Rede::GerenciadorConexao::indexaPeer( const int _id, Rede::Peer* const _peer )
{
    this->peers.insert(_id, _peer);

    QObject::connect( _peer, SIGNAL(perdiConexao(Rede::Peer*const)),
                      this, SLOT(peerCaiu(Rede::Peer*const)));

    qDebug() << Q_FUNC_INFO << "Conectei meu slot no sinal do peer.";

}

void
Rede::GerenciadorConexao::setNextServer() const
{
    Rede::Peer*
    proximo_server = this->getPeerById( Rede::RedeConfig::getInstance().meu_id );

    Rede::Peer*
    tmp_server;

    foreach( tmp_server, this->peers)
    {
        if ( tmp_server->getId() < proximo_server->getId() )
        {
            proximo_server = tmp_server;
        }
    }

    if ( proximo_server->getId() == Rede::RedeConfig::getInstance().meu_id )
    {
        Rede::RedeConfig::getInstance().estado_atual = Rede::SERVER;
    }

    Rede::RedeConfig::getInstance().server_host = proximo_server;
}
