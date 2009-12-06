#ifndef GERENCIADORCONEXAO_H
#define GERENCIADORCONEXAO_H

#include <QList>
#include <QObject>

#include "lib/conexao.h"
#include "lib/ouvinte.h"

#include "peer.h"

namespace Rede
{
    class GerenciadorConexao : public QObject
    {
    Q_OBJECT

        QList<Rede::Peer*>
        peers;

    public:

        Rede::Peer*
        tmp_peer;

        GerenciadorConexao();

        virtual
        ~GerenciadorConexao();

        Rede::Peer*
        novaConexao( int _socket_descriptor);

        void
        addConexao( Rede::Peer* _novo_peer );

        Rede::Peer*
        getPeerById( const int& _id) const;

        int
        getTotalConn() const;

        void
        indexaPeer( const int _id, Rede::Peer* const _peer );

        int
        getNextId() const;
        
        void
        debug() const;

        void
        emitSignalBroadCast( const QString& _message );

    public slots:

        void
        peerCaiu( Rede::Peer* const _peer );

    signals:

        void
        peerCaiu( const int& _id );

        void
        signalBroadCast( const QString& _message );

    private:

        void
        setNextServer() const;
    };
}

#endif // GERENCIADORCONEXAO_H
