#include <QtCore/QCoreApplication>
#include <QDebug>

#include "gerenciadorprocessos.h"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    GerenciadorProcessos
    gerenciador;

    qDebug() << Q_FUNC_INFO << "setando meuId";

    gerenciador.meuId(3);

    qDebug() << Q_FUNC_INFO << "startando processo";

//    gerenciador.peerNovo(3);
//    gerenciador.peerNovo(5);
//    gerenciador.peerNovo(6);

/*    gerenciador.incommingMessage(4, "GP:BALANCER:STATUS_PEER:0:1");
    gerenciador.incommingMessage(5, "GP:BALANCER:STATUS_PEER:0:1");
    gerenciador.incommingMessage(6, "GP:BALANCER:STATUS_PEER:0:1");
*/
 /*   gerenciador.incommingMessage(4, "GP:LAUNCHER:START_PROCESS:456:firefox:www.sandrinha.com.br");
    gerenciador.incommingMessage(4, "GP:LAUNCHER:START_PROCESS:456:firefox:www.mundocanibal.com.br");
    gerenciador.incommingMessage(4, "GP:LAUNCHER:START_PROCESS:456:firefox:www.terra.com.br");
    gerenciador.incommingMessage(4, "GP:LAUNCHER:START_PROCESS:456:firefox:www.vivo.com.br");
    gerenciador.incommingMessage(4, "GP:LAUNCHER:START_PROCESS:456:firefox:www.twitter.com");
    gerenciador.incommingMessage(4, "GP:LAUNCHER:START_PROCESS:456:firefox:www.twitter.com");*/

    gerenciador.processoStart(1, "firefox", "www.google.com");
/*    gerenciador.processoStart(2, "firefox", "www.youtube.com");
    gerenciador.processoStart(3, "firefox", "www.uol.com.br");
    gerenciador.processoStart(3, "firefox", "www.redtube.com");
    gerenciador.processoStart(3, "firefox", "www.tube8.com");
*/

    return a.exec();
}
