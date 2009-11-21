#ifndef REDE_H
#define REDE_H

#include <QMap>
#include <QObject>

#include "gerenciadorconexao.h"
#include "peer.h"
#include "rede_global.h"

class REDESHARED_EXPORT GerenciadorRede : public QObject
{
Q_OBJECT

    Rede::GerenciadorConexao*
    gerenciador_conexoes;

    Rede::Ouvinte*
    ouvinte;

public:

    enum PEER_ESTADO
    {
        FORA,
        PROCURANDO_SERVER,
        CONECTADO
    };

    /**
     *  @param _primeiro_peer Indica em qual peer o xboga deve iniciar sua busca
     *        pelo servidor. Caso este parametro seja nulo, ele não tentará se
     *        conectar em ninguem iniciando uma nova rede.
     */
    GerenciadorRede( Rede::Peer* _primeiro_peer = 0 );

    virtual
    ~GerenciadorRede();

private:

    void
    startComoServer();

    void
    buscaPorServer( Rede::Peer* _primeiro_peer );
};

#endif // REDE_H
