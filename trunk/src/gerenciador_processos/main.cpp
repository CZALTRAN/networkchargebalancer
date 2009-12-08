#include <QtCore/QCoreApplication>
#include <QDebug>

#include "gerenciadorprocessos.h"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    GerenciadorProcessos
    gerenciador;

    qDebug() << Q_FUNC_INFO << "setando meuId";

    gerenciador.meuId(5);

    qDebug() << Q_FUNC_INFO << "startando processo";

    gerenciador.peerNovo(6);
    gerenciador.peerNovo(7);
    gerenciador.peerNovo(8);

    gerenciador.incommingMessage(6, "GP:BALANCER:STATUS_PEER:0:1:");
    gerenciador.incommingMessage(7, "GP:BALANCER:STATUS_PEER:0:1:");
    gerenciador.incommingMessage(8, "GP:BALANCER:STATUS_PEER:0:1:");

/*********************** teste1 **********************************/
//    gerenciador.processoStart(1, "firefox", "www.google.com");
//    gerenciador.processoStart(4, "firefox", "www.google.com");
//    gerenciador.incommingMessage(6, "GP:LAUNCHER:SUCCESS_START_PROCESS:4:123:firefox:");
//    gerenciador.incommingMessage(6, "GP:BALANCER:STATUS_PEER:1:1:");
//    gerenciador.processoStart(5, "firefox", "www.google.com");
//    gerenciador.incommingMessage(7, "GP:LAUNCHER:SUCCESS_START_PROCESS:5:123:firefox:");
//    gerenciador.incommingMessage(7, "GP:BALANCER:STATUS_PEER:1:1:");
//    gerenciador.processoStart(2, "firefox", "www.youtube.com");
//    gerenciador.incommingMessage(8, "GP:LAUNCHER:SUCCESS_START_PROCESS:2:123:firefox:");
//    gerenciador.incommingMessage(8, "GP:BALANCER:STATUS_PEER:1:1:");
//    gerenciador.processoStart(3, "firefox", "www.uol.com.br");
//    gerenciador.processoStart(3, "firefox", "www.redtube.com");
//    gerenciador.incommingMessage(6, "GP:BALANCER:STATUS_PEER:0:1:");
//    gerenciador.processoStart(3, "firefox", "www.tube8.com");
//    gerenciador.incommingMessage(6, "GP:LAUNCHER:SUCCESS_START_PROCESS:3:123:firefox:");

/*********************** teste2 **********************************/
//    gerenciador.incommingMessage(6, "GP:LAUNCHER:START_PROCESS:3:firefox:www.google.com");
//    gerenciador.incommingMessage(7, "GP:LAUNCHER:START_PROCESS:3:firefox:www.uel.br");
//    gerenciador.incommingMessage(8, "GP:LAUNCHER:START_PROCESS:3:firefox:docs.google.com");
//    gerenciador.incommingMessage(7, "GP:LAUNCHER:START_PROCESS:3:firefox:www.mundocanibal.com.br");

/*********************** teste3 *********************************/
//    gerenciador.processoStart(1, "firefox", "www.google.com");
//    gerenciador.processoStart(4, "firefox", "www.uol.com.br");
//    gerenciador.incommingMessage(6, "GP:LAUNCHER:FAIL_START_PROCESS:3:firefox:www.uol.com.br:");
//    gerenciador.incommingMessage(7, "GP:LAUNCHER:FAIL_START_PROCESS:3:firefox:www.uol.com.br");
//    gerenciador.incommingMessage(8, "GP:LAUNCHER:FAIL_START_PROCESS:3:firefox:www.uol.com.br");

/**********************  teste4 *********************************/
    gerenciador.processoStart(5, "gwenview", "");
    return a.exec();
}
