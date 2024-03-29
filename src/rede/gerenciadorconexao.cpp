#include "gerenciadorconexao.h"

#include <QStringList>

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
    novo_peer = new Rede::Peer( _socket_descriptor, this );

    novo_peer->setId( this->getNextId() );

    this->indexaPeer( novo_peer->getId(), novo_peer );

    return novo_peer;
}

void
Rede::GerenciadorConexao::addConexao( Rede::Peer* _novo_peer )
{
    if ( this->peers.size() == Rede::RedeConfig::getInstance().qtdePeers &&
         Rede::RedeConfig::getInstance().estado_atual != Rede::SERVER)
    {
        Rede::RedeConfig::getInstance().estado_atual = Rede::CONECTADO;
    }

    this->indexaPeer( _novo_peer->getId(), _novo_peer );
}

Rede::Peer*
Rede::GerenciadorConexao::getPeerById( const int& _id) const
{
    for ( QList<Rede::Peer*>::const_iterator it = this->peers.begin();
          it != this->peers.end();
          it++)
    {
        if ( (*it)->getId() == _id )
        {
            return (*it);
        }
    }

    return NULL;
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
    }

    -- Rede::RedeConfig::getInstance().qtdePeers;

    int
    index = this->peers.indexOf( _peer );

    this->peers.removeAt( index );

    emit this->peerCaiu(_peer->getId() );
}

void
Rede::GerenciadorConexao::indexaPeer( const int _id, Rede::Peer* const _peer )
{
    Q_UNUSED(_id)

    this->peers.push_back(_peer);
    ++ Rede::RedeConfig::getInstance().qtdePeers;

    QObject::connect( _peer, SIGNAL( perdiConexao(Rede::Peer* )),
                      this, SLOT( peerCaiu( Rede::Peer* ) ));

    QObject::connect( this, SIGNAL(signalBroadCast(QString)),
                      _peer, SLOT(enviaMensagemGenerica(QString)));
}

int
Rede::GerenciadorConexao::getNextId() const
{
    int max_id = Rede::RedeConfig::getInstance().meu_id;

    Rede::Peer*
    tmp_peer;

    foreach( tmp_peer, this->peers )
    {
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
Rede::GerenciadorConexao::emitSignalBroadCast( const QString& _message )
{
    emit this->signalBroadCast(_message);
}

QString
Rede::GerenciadorConexao::getCSVAllPeers() const
{
    QStringList
    all_peers;

    Rede::Peer*
    tmp_peer;

    foreach( tmp_peer, this->peers )
    {
        all_peers.push_back( QString::number( tmp_peer->getId() ) +
                             ";" +
                             tmp_peer->getHost() );
    }

    return all_peers.join(":");
}

void
Rede::GerenciadorConexao::setNextServer() const
{
//    this->debug();
    Rede::Peer*
    proximo_server = this->getPeerById( Rede::RedeConfig::getInstance().meu_id );

    Rede::Peer*
    tmp_server;

    foreach( tmp_server, this->peers)
    {
        if ( tmp_server->getId() < proximo_server->getId() &&
             tmp_server != Rede::RedeConfig::getInstance().server_host )
        {
            proximo_server = tmp_server;
        }
    }

    if ( proximo_server->getId() == Rede::RedeConfig::getInstance().meu_id )
    {
//        qDebug() << Q_FUNC_INFO << ": fui eleito server";
        Rede::RedeConfig::getInstance().estado_atual = Rede::SERVER;
    }
    else
    {
//        qDebug() << "O server agora eh o host " << proximo_server->getHost()
//                 << " com o id: " << proximo_server->getId();
    }

    Rede::RedeConfig::getInstance().server_host = proximo_server;
}
