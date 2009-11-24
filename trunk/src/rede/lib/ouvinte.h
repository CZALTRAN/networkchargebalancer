#ifndef OUVINTE_H
#define OUVINTE_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QList>

#include "conexao.h"

namespace Rede
{
    class Ouvinte : public QTcpServer
    {
        Q_OBJECT
    public:
        Ouvinte( QObject* _parent = NULL );

        ~Ouvinte();

        bool
        startListen( const quint16& _porta = 6969 );

    signals:

        void
        novaConn( int _socket_descriptor );

    protected:

        void
        incomingConnection ( int _socket_descriptor );

        int
        porta;
    };
}
#endif // OUVINTE_H
