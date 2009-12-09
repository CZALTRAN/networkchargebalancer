#include "redeinterface.h"

#include <QDBusConnection>
#include <QDBusMessage>
#include <QDebug>
#include <QStringList>

RedeInterface::RedeInterface( QObject* _parent )
    : QObject(_parent)
{
    this->interface_rede = new QDBusInterface(
            "uel.computacao.xboga",
            "/rede",
            "uel.computacao.xboga.rede",
            QDBusConnection::sessionBus(),
            this);

    if ( this->interface_rede->lastError().type() != QDBusError::NoError )
    {
        qDebug() << Q_FUNC_INFO <<"erro ao acessar a interface de rede do xboga";
        exit(1);
    }

    QObject::connect(this->interface_rede, SIGNAL(novoPeer( int,QString)),
                     this, SLOT(slotNovoPeer(int,QString)));

    QObject::connect(this->interface_rede, SIGNAL(peerCaiu( int )),
                     this,SLOT(slotPeerCaiu(int)));
}

RedeInterface::~RedeInterface()
{

}

QStringList
RedeInterface::getListPeers()
{
    QList<QVariant>
    message = this->getArguments("getAllPeers");

    if ( message.size() > 1 || message.size() == 0)
    {
        qDebug() << Q_FUNC_INFO << "erro ao receber retorno do getAllPeers";
        return QStringList();
    }
    else
    {
        QString
        csv_peers = message[0].toString();

        return csv_peers.split(':');
    }

}

int
RedeInterface::getServerId()
{
    QList<QVariant>
    message = this->getArguments("getServer");

    if ( message.size() > 1 || message.size() == 0)
    {
        qDebug() << Q_FUNC_INFO << "erro ao receber retorno do getAllPeers";
        return -1;
    }
    else
    {
        int
        server_id = message[0].toInt();

        return server_id;
    }
}

QList<QVariant>
RedeInterface::getArguments( const QString& _metodo ) const
{
    return this->interface_rede->call( _metodo ).arguments();
}

void
RedeInterface::slotPeerCaiu( int _id_caido )
{
    emit this->peerCaiu( _id_caido );
}

void
RedeInterface::slotNovoPeer(int _novo_id, QString _novo_host)
{
    emit this->novoPeer( _novo_id, _novo_host );
}

