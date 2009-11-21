#ifndef OUVINTE_H
#define OUVINTE_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QThread>
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
        startListen();

    signals:

        void
        novaConn( int _socket_descriptor );

    protected:

        void
        incomingConnection ( int _socket_descriptor );
    };
}
#endif // OUVINTE_H
