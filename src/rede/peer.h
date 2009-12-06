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
        Peer( const int& _socket_descriptor, QObject* _parent = 0 );

        Peer(QObject* _parent = 0);

        Peer( const QString& host );

        virtual
        ~Peer();

        void
        setHost( const QString& _host );

        QString
        getHost() const;

        int
        getId() const;

        void
        conectar( const QString& _host );

        void
        conectar();

        void
        sendInit( const int _total_conn );

        void
        sendGP( const int& _id, const QString& _message );

        void
        setId( const int _id );

    public slots:

        void
        incommingMessage(const QString& _message );

        void
        conectado();

        void
        erro( QAbstractSocket::SocketError _erro );

    //slots de envio de mensagem

        void
        enviaNovoPeer( const QString& _host, const int& _id );

        void
        enviaMensagemGenerica( const QString& _mensagem );

    signals:

        void
        incommingMessage( const int& _id, const QString& _message );

        void
        perdiConexao( Rede::Peer* const _peer );

    private:

        void
        constroiSocket();
    };
}

#endif // PEER_H
