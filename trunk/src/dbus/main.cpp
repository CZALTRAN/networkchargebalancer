#include <QCoreApplication>

#include "gerenciadordbus.h"

int main(int argc, char* argv[] )
{
    QCoreApplication
    app (argc,argv);

    GerenciadorDBus*
    gerente_dbus = new GerenciadorDBus();

    return app.exec();
}
