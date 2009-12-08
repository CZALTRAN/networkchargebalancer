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


    gerenciador.processoStart(1, "firefox", "www.google.com");
    gerenciador.processoStart(4, "firefox", "www.google.com");
    gerenciador.incommingMessage(6, "GP:BALANCER:STATUS_PEER:1:1:");
    gerenciador.processoStart(5, "firefox", "www.google.com");
    gerenciador.incommingMessage(7, "GP:BALANCER:STATUS_PEER:1:1:");
    gerenciador.processoStart(2, "firefox", "www.youtube.com");
    gerenciador.incommingMessage(8, "GP:BALANCER:STATUS_PEER:1:1:");
    gerenciador.processoStart(3, "firefox", "www.uol.com.br");
    gerenciador.processoStart(3, "firefox", "www.redtube.com");
    gerenciador.incommingMessage(7, "GP:BALANCER:STATUS_PEER:0:1:");
    gerenciador.processoStart(3, "firefox", "www.tube8.com");


    return a.exec();
}
