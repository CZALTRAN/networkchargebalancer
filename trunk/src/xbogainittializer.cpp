#include "xbogainittializer.h"

#include <QDebug>

#include "rede/peer.h"

XBogaInittializer::XBogaInittializer( int argc, char* argv[], QObject *parent) :
    QObject(parent)
{

    this->grede = new GerenciadorRede( argv[1],this);
    this->gprocessos = new GerenciadorProcessos(this);
    this->dbus = new GerenciadorDBus(this);

    QObject::connect( this->grede, SIGNAL(meuId(int)),
                      this->gprocessos, SLOT(meuId(int)));

    QObject::connect( this->grede, SIGNAL( meuId(int)),
                      this, SLOT(teste(int)));

    QObject::connect( this->grede, SIGNAL(novoPeer(int)),
                      this->gprocessos, SLOT(peerNovo(int)));

    QObject::connect( this->grede, SIGNAL( novoPeer(int) ),
                      this, SLOT(teste(int)));

    QObject::connect( this->grede, SIGNAL(peerCaiu(int)),
                      this->gprocessos, SLOT(peerCaiu(int)));

    QObject::connect( this->grede, SIGNAL( peerCaiu(int) ),
                      this, SLOT(teste(int)));

    QObject::connect( this->dbus, SIGNAL(novaSolicitacaoDeProcesso(int,QString,QString)),
                      this->gprocessos, SLOT(processoStart(int,QString,QString)));

    QObject::connect( this->gprocessos,SIGNAL(sendMessage(int,QString)),
                      this->grede, SLOT(enviaPacoteGP(int,QString)));

    QObject::connect( this->grede, SIGNAL(recebePacoteGP(int,QString)),
                      this->gprocessos,SLOT(incommingMessage(int,QString)));

    QObject::connect( this->grede, SIGNAL(recebePacoteGP(int,QString)),
                      this, SLOT(incommingMessage(int,QString)));

    if (argc == 3)
    {
        Rede::Peer*
        primeiro_peer = new Rede::Peer();;

        primeiro_peer->setHost( argv[2] );

        this->grede->buscaPorServer(primeiro_peer);
    }
    else
    {
        this->grede->startComoServer();
    }
}

void
XBogaInittializer::teste(int bla)
{
    qDebug() << Q_FUNC_INFO << bla;
}

void
XBogaInittializer::incommingMessage(int bla ,QString ble)
{
    qDebug() << Q_FUNC_INFO << bla << ble;
}
