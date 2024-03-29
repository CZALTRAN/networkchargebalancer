//Qts includes
#include <QCoreApplication>
#include <QDebug>

//C includes
#include <cassert>

//project includes
#include "gerenciadorrede.h"
#include "peer.h"
#include "ping.h"

int main ( int argc, char* argv[])
{
    QCoreApplication
    app(argc,argv);

    Rede::Peer*
    primeiro_peer;

    GerenciadorRede*
    gerente_rede = new GerenciadorRede( "wlan0", 0);

    if ( argc == 2 )
    {
        qDebug() << Q_FUNC_INFO << "startando como host";
        primeiro_peer = new Rede::Peer();
        primeiro_peer->setHost( QString(argv[1]) );

        gerente_rede->buscaPorServer(primeiro_peer);
    }
    else
    {
        qDebug() << Q_FUNC_INFO << "startando como server";
        primeiro_peer = 0;

        gerente_rede->startComoServer();
    }



    //gerente_rede->pingPeer("192.168.1.100");

    Q_UNUSED(gerente_rede)
    return app.exec();
}
