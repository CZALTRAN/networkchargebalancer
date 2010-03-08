#include "xbogainittializer.h"

#include <QDebug>

#include "rede/peer.h"

//adaptadores do dbus
#include "rede/redeadaptor.h"
#include "gerenciador_processos/gpadaptor.h"

XBogaInittializer::XBogaInittializer( int argc, char* argv[], QObject *parent) :
    QObject(parent)
{

    this->grede = new GerenciadorRede( argv[1],this);
    this->gprocessos = new GerenciadorProcessos(this);
    this->dbus = new GerenciadorDBus(this);

    QObject::connect( this->grede, SIGNAL(meuId(int)),
                      this->gprocessos, SLOT(meuId(int)));

    QObject::connect( this->grede, SIGNAL(novoPeer(int)),
                      this->gprocessos, SLOT(peerNovo(int)));

    QObject::connect( this->grede, SIGNAL(peerCaiu(int)),
                      this->gprocessos, SLOT(peerCaiu(int)));

    QObject::connect( this->gprocessos,SIGNAL(sendMessage(int,QString)),
                      this->grede, SLOT(enviaPacoteGP(int,QString)));

    QObject::connect( this->grede, SIGNAL(recebePacoteGP(int,QString)),
                      this->gprocessos,SLOT(incommingMessage(int,QString)));

    this->criarERegistrarGPAdaptor();
    this->criarERegistrarRedeAdaptor();

    if (argc == 3)
    {
        Rede::Peer*
        primeiro_peer = new Rede::Peer();

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
XBogaInittializer::criarERegistrarGPAdaptor()
{
    GPAdaptor*
    adaptador = new GPAdaptor(this->gprocessos);
    
    QObject::connect( adaptador, SIGNAL(signalStartProcesso(int,QString,QString)),
                      this->gprocessos, SLOT(processoStart(int,QString,QString)));

    QObject::connect( this->gprocessos, SIGNAL(resultadoProcessoStart(int,QString,qint64)),
                      adaptador,SLOT(slotResultStartProcesso(int,QString,qint64)));

    QObject::connect(this->gprocessos, SIGNAL(stdOut(qint64,int,QString)),
                     adaptador, SLOT(slotStandardOutput(qint64,int,QString)));

    QObject::connect(adaptador, SIGNAL(signalStandardInput(qint64,int,QString)),
                     this->gprocessos, SLOT(stdIn(qint64,int,QString)));

    QObject::connect(this->gprocessos, SIGNAL(terminoDeProcesso(qint64,int,int)),
                     adaptador,SLOT(slotProcessoTerminou(qint64,int,int)));

    QObject::connect(adaptador, SIGNAL(signalMatarProcesso(qint64,int,int)),
                     this->gprocessos, SLOT(mataProcesso(qint64,int,int)));

    if ( ! this->dbus->registrarNovoAdaptador(adaptador, "/gp") )
    {
        qDebug() << "nao consegui registrar o gp";
        exit(1);
    }
}

void
XBogaInittializer::criarERegistrarRedeAdaptor()
{
    RedeAdaptor*
    adaptador = new RedeAdaptor( this->grede );

    QObject::connect( this->grede, SIGNAL(novoPeerWithHost(QString,int)),
                      adaptador,SLOT(slotNovoPeer(QString,int)));

    QObject::connect( this->grede,SIGNAL(peerCaiu(int)),
                      adaptador,SLOT(slotPeerCaiu(int)));

    if (! this->dbus->registrarNovoAdaptador(adaptador,"/rede"))
    {
        qDebug() << "nao consegui registrar o rede";
        exit(1);
    }
}
