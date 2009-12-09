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
    GerenciadorRede( const QString& _interface,
                     QObject* _parent = NULL);

    virtual
    ~GerenciadorRede();

    QStringList
    pingPeer( QString _host );

    void
    startComoServer();

    void
    buscaPorServer( Rede::Peer* _primeiro_peer );

    QString
    getCSVPeers() const;

    int
    getServer() const;

private:

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
    novoPeerWithHost( QString, int );

    void
    novoPeer( const int& _id );

    void
    peerCaiu( const int& _id );

    void
    meuId( int _id );

    void
    recebePacoteGP( int _remetente, const QString& );

protected:

    void
    broadcastGP( const QString& _message );
};

#endif // REDE_H
