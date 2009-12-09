#include <QtCore/QCoreApplication>

#include <QDebug>
#include <QProcess>
#include <QObject>

#include "gerenciadorprocessos.h"
#include "testegp.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    TesteGP
    testeGp;

    qDebug() << Q_FUNC_INFO << "setando meuId";

    testeGp.gerenciador.meuId(5);

    qDebug() << Q_FUNC_INFO << "startando processo";

    testeGp.gerenciador.peerNovo(6);
    testeGp.gerenciador.peerNovo(7);
    testeGp.gerenciador.peerNovo(8);

    testeGp.gerenciador.incommingMessage(6, "GP:BALANCER:STATUS_PEER:0:1:");
    testeGp.gerenciador.incommingMessage(7, "GP:BALANCER:STATUS_PEER:0:1:");
    testeGp.gerenciador.incommingMessage(8, "GP:BALANCER:STATUS_PEER:0:1:");

///*********************** teste1 **********************************/
//    testeGp.gerenciador.processoStart(1, "firefox", "www.google.com");
//    testeGp.gerenciador.processoStart(4, "firefox", "www.google.com");
//    testeGp.gerenciador.incommingMessage(6, "GP:LAUNCHER:SUCCESS_START_PROCESS:4:123:firefox:");
//    testeGp.gerenciador.incommingMessage(6, "GP:BALANCER:STATUS_PEER:1:1:");
//    testeGp.gerenciador.processoStart(5, "firefox", "www.google.com");
//    testeGp.gerenciador.incommingMessage(7, "GP:LAUNCHER:SUCCESS_START_PROCESS:5:123:firefox:");
//    testeGp.gerenciador.incommingMessage(7, "GP:BALANCER:STATUS_PEER:1:1:");
//    testeGp.gerenciador.processoStart(2, "firefox", "www.youtube.com");
//    testeGp.gerenciador.incommingMessage(8, "GP:LAUNCHER:SUCCESS_START_PROCESS:2:123:firefox:");
//    testeGp.gerenciador.incommingMessage(8, "GP:BALANCER:STATUS_PEER:1:1:");
//    testeGp.gerenciador.processoStart(3, "firefox", "www.uol.com.br");
//    testeGp.gerenciador.processoStart(3, "firefox", "www.redtube.com");
//    testeGp.gerenciador.incommingMessage(6, "GP:BALANCER:STATUS_PEER:0:1:");
//    testeGp.gerenciador.processoStart(3, "firefox", "www.tube8.com");
//    testeGp.gerenciador.incommingMessage(6, "GP:LAUNCHER:SUCCESS_START_PROCESS:3:123:firefox:");
//
///*********************** teste2 **********************************/
//    testeGp.gerenciador.incommingMessage(6, "GP:LAUNCHER:START_PROCESS:3:firefox:www.google.com");
//    testeGp.gerenciador.incommingMessage(7, "GP:LAUNCHER:START_PROCESS:3:firefox:www.uel.br");
//    testeGp.gerenciador.incommingMessage(8, "GP:LAUNCHER:START_PROCESS:3:firefox:docs.google.com");
//    testeGp.gerenciador.incommingMessage(7, "GP:LAUNCHER:START_PROCESS:3:firefox:www.mundocanibal.com.br");
//
///*********************** teste3 *********************************/
//    testeGp.gerenciador.processoStart(1, "firefox", "www.google.com");
//    testeGp.gerenciador.processoStart(4, "firefox", "www.uol.com.br");
//    testeGp.gerenciador.incommingMessage(6, "GP:LAUNCHER:FAIL_START_PROCESS:3:firefox:www.uol.com.br");
//    testeGp.gerenciador.incommingMessage(7, "GP:LAUNCHER:FAIL_START_PROCESS:3:firefox:www.uol.com.br");
//    testeGp.gerenciador.incommingMessage(8, "GP:LAUNCHER:FAIL_START_PROCESS:3:firefox:www.uol.com.br");
//
///**********************  teste4 *********************************/
//    testeGp.gerenciador.processoStart(5, "gwenview", "");
//    testeGp.gerenciador.processoStart(5, "kcalc", "");

/********************** teste5 *********************************/
//    testeGp.gerenciador.processoStart(5, "ping", "192.168.1.101");

/********************** teste6 *********************************/
    testeGp.gerenciador.incommingMessage(6, "GP:LAUNCHER:START_PROCESS:5:ping:192.168.1.101");
    return a.exec();
}

