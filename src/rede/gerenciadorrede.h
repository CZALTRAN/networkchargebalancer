#ifndef REDE_H
#define REDE_H

#include <QMap>
#include <QObject>

#include "gerenciadorconexao.h"
#include "rede_global.h"
#include "parserdepacotes.h"

class GerenciadorRede : public QObject
{
Q_OBJECT

    Rede::GerenciadorConexao*
    gerenciador_conexoes;

    Rede::Ouvinte*
    ouvinte;

    Rede::Ouvinte*
    ouvinte_procura;

    QString
    interface;

public:

    /**
     *  @param _primeiro_peer Indica em qual peer o xboga deve iniciar sua busca
     *        pelo servidor. Caso este parametro seja nulo, ele não tentará se
     *        conectar em ninguem iniciando uma nova rede.
     */
    GerenciadorRede( QString _interface, Rede::Peer* _primeiro_peer = NULL );

    virtual
    ~GerenciadorRede();

    QStringList
    pingPeer( QString _host );

private:

    void
    startComoServer();

    void
    buscaPorServer( Rede::Peer* _primeiro_peer );

    void
    recebeInit( Rede::PacoteBase* const _pacote );

    void
    recebePacoteNovoPeer( Rede::PacoteBase* const _pacote );

    void
    recebeConexaoPeerVeterano( const int& _socket_descriptor );

public slots:

    void
    enviaPacoteGP( const int& _destinatario_id, const QString& _message );

protected slots:

    void
    slotNovaConexao( const int& _socket_descriptor );

    void
    slotNovaMensagemFromPeer( const int& _id, const QString& _message );

    void
    informaServerInfo( const int& _socket_descriptor);

    void
    serverEncontrado( const int& _id, const QString& _message );

    void
    slotPeerCaiu( const int& _id );

signals:

    void
    novoPeer( const QString& _host, const int& id );

    //sinais para outros modulos
    void
    novoPeer( const int& _id );

    void
    peerCaiu( const int& _id );

    void
    meuId( const int& _id );

    void
    recebePacoteGP( const int& _remetente, const QString& );
};

#endif // REDE_H
