#include "ouvinte.h"

#include <QDebug>

Rede::Ouvinte::Ouvinte( QObject* _parent )
        : QTcpServer( _parent )
{

}

Rede::Ouvinte::~Ouvinte()
{

}

bool
Rede::Ouvinte::startListen()
{
    qint16
    porta = 2469;

    this->listen( QHostAddress::Any, porta );

    if ( this->isListening() )
    {
        qDebug() << Q_FUNC_INFO << " to ouvino fia!";
        return true;
    }
    else
    {
        qWarning() << Q_FUNC_INFO << " diabo de muieh surda!";
        return false;
    }
}

void
Rede::Ouvinte::incomingConnection( int _socket_descriptor )
{
    qDebug() << Q_FUNC_INFO << " nova conexao";

    emit this->novaConn( _socket_descriptor );
}
