#include "gerenciadordbus.h"

#include <QDebug>
#include <QDBusConnection>

#include "dbusconfig.h"

GerenciadorDBus::GerenciadorDBus(QObject *parent) :
    QObject(parent)
{
    this->interfaceGP = new GPAdaptor(this);

    if (! QDBusConnection::sessionBus().isConnected() )
    {
        qDebug() << Q_FUNC_INFO
                 << "Nao foi possivel se conectar ao servidor de dbus.";
        exit(1);
    }

    if (! QDBusConnection::sessionBus().registerService(
            DBus::DBusConfig::getInstance().name_service
            ))
    {
        qDebug() << Q_FUNC_INFO
                 << "Nao foi possivel registrar o servico xboga no dbus.";
        exit(1);
    }

    QDBusConnection::sessionBus().registerObject("/gp",
                                                 this->interfaceGP,
                                                 QDBusConnection::ExportAllContents);

}

GerenciadorDBus::~GerenciadorDBus()
{
}
