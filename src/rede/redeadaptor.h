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

signals:

    void
    novoPeer( int _novo_peer_id, QString _novo_peer_host );

    void
    peerCaiu( int _peer_caiu_id );
};

#endif // REDEADAPTOR_H
