#include "redeadaptor.h"

#include <QDBusConnection>
#include <QDBusMessage>
#include <QDebug>

#include "gerenciadorrede.h"

RedeAdaptor::RedeAdaptor( GerenciadorRede* _parent )
    : QDBusAbstractAdaptor( _parent )
{

}

QString
RedeAdaptor::getAllPeers()
{
    return dynamic_cast<GerenciadorRede*>(this->parent())->getCSVPeers();
}

int
RedeAdaptor::getServer()
{
    return dynamic_cast<GerenciadorRede*>(this->parent())->getServer();
}

void
RedeAdaptor::pingPeer( int _id )
{
    //todo
}

void
RedeAdaptor::slotNovoPeer(  QString _novo_peer_host, int _novo_peer_id )
{
    QDBusMessage
    sinal_novo_peer;

    sinal_novo_peer = QDBusMessage::createSignal("/rede",
                                 "uel.computacao.xboga.rede",
                                 "novoPeer");

    QList<QVariant>
    argumentos;

    argumentos.push_back(_novo_peer_host);
    argumentos.push_back(_novo_peer_id);

    sinal_novo_peer.setArguments(argumentos);

    QDBusConnection::sessionBus().send(sinal_novo_peer);
}

void
RedeAdaptor::slotPeerCaiu( int _peer_caiu_id )
{
    QDBusMessage
    sinal_peer_caiu;

    sinal_peer_caiu = QDBusMessage::createSignal("/rede",
                                                 "uel.computacao.xboga.rede",
                                                 "peerCaiu");

    QList<QVariant>
    argumentos;

    argumentos.push_back(_peer_caiu_id);
    sinal_peer_caiu.setArguments(argumentos);

    QDBusConnection::sessionBus().send(sinal_peer_caiu);
}
