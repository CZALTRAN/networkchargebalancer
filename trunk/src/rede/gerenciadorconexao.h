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
        GerenciadorConexao();

        virtual
        ~GerenciadorConexao();

    public slots:

        void
        novaConexao( int _socket_descriptor);
    };
}

#endif // GERENCIADORCONEXAO_H
