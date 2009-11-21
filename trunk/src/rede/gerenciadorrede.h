#ifndef REDE_H
#define REDE_H

#include <QMap>

#include "peer.h"
#include "rede_global.h"

class REDESHARED_EXPORT GerenciadorRede
{
    QMap<int, Rede::Peer*>
    Peers;

    bool
    server;

    unsigned int
    meu_id;

public:

    enum PEER_ESTADO
    {
        FORA,
        PROCURANDO_SERVER,
        CONECTADO
    };

    GerenciadorRede( Rede::Peer* _primeiro_peer = 0 );

};

#endif // REDE_H
