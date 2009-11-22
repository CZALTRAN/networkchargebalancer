#ifndef REDE_H
#define REDE_H

#include <QMap>
#include <QObject>

#include "gerenciadorconexao.h"
#include "peer.h"
#include "rede_global.h"

class GerenciadorRede : public QObject
{
Q_OBJECT

    Rede::GerenciadorConexao*
    gerenciador_conexoes;

    Rede::Ouvinte*
    ouvinte;

public:

    /**
     *  @param _primeiro_peer Indica em qual peer o xboga deve iniciar sua busca
     *        pelo servidor. Caso este parametro seja nulo, ele n�o tentar� se
     *        conectar em ninguem iniciando uma nova rede.
     */
    GerenciadorRede( Rede::Peer* _primeiro_peer = NULL );

    virtual
    ~GerenciadorRede();

private:

    void
    startComoServer();

    void
    buscaPorServer( Rede::Peer* _primeiro_peer );

    void
    informaServerInfo( const int& _socket_descriptor);

protected slots:

    void
    slotNovaConexao( int _socket_descriptor );

    void
    slotNovaMensagemFromPeer( const int& _id, const QString& _message );

signals:

    void
    novoPeer( const QString& _host, const int& id );
};

#endif // REDE_H
