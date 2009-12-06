#include <QCoreApplication>
#include <QDebug>
#include <QtDBus>

int main ( int argc,char* argv[])
{
    QCoreApplication app( argc, argv );

    if (! QDBusConnection::sessionBus().isConnected() )
    {
        qDebug() << "nao conectei nessa pegada do capeta";
        exit(1);
    }

    QDBusInterface
    interface("uel.computacao.xboga","/");

    qDebug() << QDBusConnection::sessionBus().lastError().message();

    return app.exec();
}
