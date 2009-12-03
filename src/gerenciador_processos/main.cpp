#include <QtCore/QCoreApplication>

#include "gerenciadorprocessos.h"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    GerenciadorProcessos
    gerenciador;

    gerenciador.peerNovo(1);
    gerenciador.peerNovo(2);
    gerenciador.peerNovo(3);

    return a.exec();
}
