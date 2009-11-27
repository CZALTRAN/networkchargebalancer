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

    novo_peer->setId( this->getNextId() );

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
        Rede::RedeConfig::getInstance().estado_atual = Rede::CONECTADO;
    }

    this->indexaPeer( id, _novo_peer );
}

Rede::Peer*
Rede::GerenciadorConexao::getPeerById( const int& _id) const
{
    return this->peers[_id];
}

int
Rede::GerenciadorConexao::getTotalConn() const
{
    return this->peers.size();
}

void
Rede::GerenciadorConexao::peerCaiu( Rede::Peer* const _peer )
{
    if( _peer == Rede::RedeConfig::getInstance().server_host )
    {
        this->setNextServer();
        emit this->peerCaiu(true);
    }
    else
    {
        emit this->peerCaiu(false);
    }

    -- Rede::RedeConfig::getInstance().qtdePeers;

    int
    removed = this->peers.remove(_peer->getId());

    if ( removed == 0)
    {
        for ( QMap<int, Rede::Peer*>::iterator it = this->peers.begin();
              it != this->peers.end();
              it++)
        {
            if ( it.value() == _peer )
            {
                it = this->peers.erase(it);
                if ( it.value() == _peer )
                {
                    qDebug() << Q_FUNC_INFO << " removi " << removed << "entradas."
                             << " Tentando remover a entrada numero: " << _peer->getId();

                    exit (1);
                }

            }
        }
    }
}

void
Rede::GerenciadorConexao::indexaPeer( const int _id, Rede::Peer* const _peer )
{
    this->peers.insert(_id, _peer);
    ++ Rede::RedeConfig::getInstance().qtdePeers;

    QObject::connect( _peer, SIGNAL(perdiConexao(Rede::Peer*const)),
                      this, SLOT(peerCaiu(Rede::Peer*const)));
}

int
Rede::GerenciadorConexao::getNextId() const
{
    int max_id = Rede::RedeConfig::getInstance().meu_id;

    Rede::Peer*
    tmp_peer;

    foreach( tmp_peer, this->peers )
    {
        qDebug () << Q_FUNC_INFO << ": teste novo id:" << tmp_peer->getId();
        if ( tmp_peer->getId() > max_id )
        {
            max_id = tmp_peer->getId();
        }
    }

    return max_id + 1;
}

void
Rede::GerenciadorConexao::debug() const
{
    Rede::Peer*
    tmp_peer;

    qDebug() << "********************************";
    qDebug() << "       Debugando peers          ";
    qDebug() << "********************************";
    foreach( tmp_peer, this->peers )
    {

        qDebug() << "Peer : " << tmp_peer->getId() << " host: " <<tmp_peer->getHost();

    }
    qDebug() << "********************************";
}

void
Rede::GerenciadorConexao::setNextServer() const
{
    this->debug();
    Rede::Peer*
    proximo_server = this->getPeerById( Rede::RedeConfig::getInstance().meu_id );

    Rede::Peer*
    tmp_server;

    foreach( tmp_server, this->peers)
    {
        qDebug() << Q_FUNC_INFO << ": testando ids cadastrados " << tmp_server->getId();
        if ( tmp_server->getId() < proximo_server->getId() &&
             tmp_server != Rede::RedeConfig::getInstance().server_host )
        {
            proximo_server = tmp_server;
        }
    }

    if ( proximo_server->getId() == Rede::RedeConfig::getInstance().meu_id )
    {
        qDebug() << Q_FUNC_INFO << ": fui eleito server";
        Rede::RedeConfig::getInstance().estado_atual = Rede::SERVER;
    }
    else
    {
        qDebug() << "O server agora eh o host " << proximo_server->getHost()
                 << " com o id: " << proximo_server->getId();
    }

    Rede::RedeConfig::getInstance().server_host = proximo_server;
}
