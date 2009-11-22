#ifndef GERENCIADORCONEXAO_H
#define GERENCIADORCONEXAO_H

#include <QMap>
#include <QObject>

#include "lib/conexao.h"
#include "lib/ouvinte.h"

#include "peer.h"

namespace Rede
{
    class GerenciadorConexao : public QObject
    {
    Q_OBJECT

        QMap<int, Rede::Peer*>
        peers;

    public:

        Rede::Peer*
        tmp_peer;

        GerenciadorConexao();

        virtual
        ~GerenciadorConexao();

        Rede::Peer*
        novaConexao( int _socket_descriptor);

        Rede::Peer*
        getPeerById( const int& _id);

        int
        getTotalConn() const;
    };
}

#endif // GERENCIADORCONEXAO_H
