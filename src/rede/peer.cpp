#include "peer.h"

#include <QDebug>
#include <QHostAddress>
#include <QRegExp>

#include "construtordepacotes.h"
#include "lib/conexao.h"
#include "redeconfig.h"

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

    QObject::connect( this->conexao, SIGNAL(connected()),
                      this, SLOT(conectado()));
    
    QObject::connect(this->conexao, SIGNAL(error(QAbstractSocket::SocketError)),
                     this, SLOT(erro(QAbstractSocket::SocketError)));
}

Rede::Peer::Peer()
{
    this->conexao = new Rede::Conexao(this);
}

Rede::Peer::~Peer()
{
    this->conexao->close();
}

void
Rede::Peer::setHost( const QString& _host )
{
    this->host = _host;
}

QString
Rede::Peer::getHost() const
{
    return this->host;
}

int
Rede::Peer::getId() const
{
    return this->id;
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
    const quint16
    porta = 6969;

    this->conexao->connectToHost("localhost", porta);
}

void
Rede::Peer::sendInit( const int _total_conn )
{
    QString
    mensagem = Rede::ConstrutorDePacotes::getInstance().montaInit( this->id,
                                                                   _total_conn );

    this->conexao->enviaDado( mensagem );
}

void
Rede::Peer::incommingMessage(const QString& _message )
{
    emit this->incommingMessage( this->id, _message );
}

void
Rede::Peer::conectado()
{
    switch ( Rede::RedeConfig::getInstance().estado_atual )
    {
    case Rede::CONECTADO:
        qDebug() << Q_FUNC_INFO << " : " << Rede::CONECTADO;
        break;

    case Rede::PROCURANDO_SERVER:
        qDebug() << Q_FUNC_INFO << " : " << Rede::PROCURANDO_SERVER;
        break;
    }
}

void
Rede::Peer::erro( QAbstractSocket::SocketError _erro )
{
    Q_UNUSED(_erro)
    qDebug() << Q_FUNC_INFO << this->conexao->errorString();
}

void
Rede::Peer::setId( const int _id )
{
    this->id = _id;
}
