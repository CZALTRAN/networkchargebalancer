#include <QtCore/QCoreApplication>

#include "gerenciadorprocessos.h"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    GerenciadorProcessos
    gerenciador;

    gerenciador.meuId(3);

    gerenciador.processoStart(123, "firefox", "www.xvideos.com");

    return a.exec();
}
