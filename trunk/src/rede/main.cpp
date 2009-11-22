//Qts includes
#include <QCoreApplication>
#include <QDebug>

//C includes
#include <cassert>

//project includes
#include "gerenciadorrede.h"
#include "peer.h"

int main ( int argc, char* argv[])
{
    QCoreApplication
    app(argc,argv);

    Rede::Peer*
    primeiro_peer;

    if ( argc == 2 )
    {
        qDebug() << Q_FUNC_INFO << "startando como host";
        primeiro_peer = new Rede::Peer();
        primeiro_peer->setHost( QString(argv[1]) );
    }
    else
    {
        qDebug() << Q_FUNC_INFO << "startando como server";
        primeiro_peer = 0;
    }

    GerenciadorRede*
    gerente_rede = new GerenciadorRede( "wlan0", primeiro_peer );

    Q_UNUSED(gerente_rede)
    return app.exec();
}