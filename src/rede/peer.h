#ifndef PEER_H
#define PEER_H

#include <QAbstractSocket>
#include <QObject>
#include <QString>

namespace Rede
{
    class Conexao;

    class Peer : public QObject
    {
    Q_OBJECT
        Rede::Conexao*
        conexao;

        QString
        host;

        unsigned int
        id;

    public:
        Peer( const int& _socket_descriptor );

        Peer();

        virtual
        ~Peer();

        void
        setHost( const QString& _host );

        const QString
        getHost();

        void
        conectar( const QString& _host );

        void
        conectar();

        void
        sendInit( const int _total_conn );

    public slots:

        void
        incommingMessage(const QString& _message );

        void
        conectado();

        void
        erro( QAbstractSocket::SocketError _erro );

    signals:

        void
        incommingMessage( const int& _id, const QString& _message );
    };
}

#endif // PEER_H
