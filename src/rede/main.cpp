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
    for ( int i = 0; i < argc ; i++)
    {
        qDebug() << argv[i];
    }

    QCoreApplication
    app(argc,argv);

    Rede::Peer*
    primeiro_peer;

    if ( argc == 2 )
    {
        primeiro_peer = new Rede::Peer();
        primeiro_peer->setHost( QString(argv[1]) );
    }
    else
    {
        primeiro_peer = 0;
    }

    GerenciadorRede*
    gerente_rede = new GerenciadorRede( primeiro_peer );

    app.exec();
}
