#ifndef REDEINTERFACE_H
#define REDEINTERFACE_H

#include <QDBusInterface>
#include <QObject>

class RedeInterface : public QObject
{
Q_OBJECT
public:
    RedeInterface( QObject* _parent = 0 );

    ~RedeInterface();

    QStringList
    getListPeers();

    int
    getServerId();

signals:

    void
    novoPeer(int _novo_id, QString _novo_host );

    void
    peerCaiu( int _id_caido );

protected slots:

    void
    slotPeerCaiu( int _id_caido );

    void
    slotNovoPeer(int _novo_id, QString _novo_host);

private:

    QDBusInterface*
    interface_rede;

    QList<QVariant>
    getArguments( const QString& _metodo ) const;
};

#endif // REDEINTERFACE_H
