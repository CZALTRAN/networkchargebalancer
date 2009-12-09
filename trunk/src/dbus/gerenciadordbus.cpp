#include "gerenciadordbus.h"

#include <QDebug>
#include <QtDBus>

#include "dbusconfig.h"

GerenciadorDBus::GerenciadorDBus(QObject *parent) :
    QObject(parent)
{
    if (! QDBusConnection::sessionBus().isConnected() )
    {
        qDebug() << Q_FUNC_INFO
                 << "Nao foi possivel se conectar ao servidor de dbus.";
        exit(1);
    }

    if (! QDBusConnection::sessionBus().registerService(
            DBusConfig::getInstance().name_service
            ))
    {
        qDebug() << Q_FUNC_INFO
                 << "Nao foi possivel registrar o servico xboga no dbus.";
        exit(1);
    }
}

GerenciadorDBus::~GerenciadorDBus()
{
}

bool
GerenciadorDBus::registrarNovoAdaptador( QDBusAbstractAdaptor* adaptador,
                                         QString _path)
{
    bool
    registrado;

    registrado = QDBusConnection::sessionBus().registerObject(
            _path,
            adaptador,
            QDBusConnection::ExportNonScriptableContents
            );

    return registrado;
}

