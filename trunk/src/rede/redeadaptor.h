#ifndef REDEADAPTOR_H
#define REDEADAPTOR_H

#include <QDBusAbstractAdaptor>

class GerenciadorRede;

class RedeAdaptor : public QDBusAbstractAdaptor
{
Q_OBJECT
Q_CLASSINFO("D-Bus Interface", "uel.computacao.xboga.rede")
public:

    RedeAdaptor( GerenciadorRede* _parent );

public slots:

    QString
    getAllPeers();

    int
    getServer();

    void
    pingPeer( int _id );

    Q_SCRIPTABLE void
    slotNovoPeer(  QString _novo_peer_host, int _novo_peer_id );

    Q_SCRIPTABLE void
    slotPeerCaiu( int _peer_caiu_id );

signals:

    void
    novoPeer(  QString _novo_peer_host, int _novo_peer_id );

    void
    peerCaiu( int _peer_caiu_id );
};

#endif // REDEADAPTOR_H
