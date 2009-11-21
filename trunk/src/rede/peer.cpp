#include "peer.h"

#include <QDebug>
#include <QHostAddress>
#include <QRegExp>

#include "lib/conexao.h"

Rede::Peer::Peer( const int& _socket_descriptor )
{
    this->conexao = new Rede::Conexao(this);
    this->conexao->setSocketDescriptor( _socket_descriptor );

    if( this->conexao->state() == QAbstractSocket::ConnectedState )
    {
        this->host = this->conexao->peerAddress().toString();
    }
    else
    {
        qDebug() << Q_FUNC_INFO << " naum estah em connected state";
    }
}

Rede::Peer::Peer()
{
    this->conexao = NULL;
}

Rede::Peer::~Peer()
{
    this->conexao->close();
}

void
Rede::Peer::setHost( const QString& _host )
{

}

const QString
Rede::Peer::getHost()
{
    return this->host;
}

void
Rede::Peer::conectar( const QString& _host )
{
    this->setHost( _host );

    this->conectar();
}

void
Rede::Peer::conectar()
{
}

void
Rede::Peer::incommingMessage(const QString& _message )
{
    emit this->incommingMessage( this->id, _message );
}
