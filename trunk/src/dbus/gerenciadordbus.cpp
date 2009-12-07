#include "gerenciadordbus.h"

#include <QDebug>
#include <QtDBus>

#include "dbusconfig.h"

GerenciadorDBus::GerenciadorDBus(QObject *parent) :
    QObject(parent)
{
    this->interfaceGP = new GPAdaptor(this);
    this->interfaceRede = new RedeAdaptor(this);

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

    bool ok = false;

    ok = QDBusConnection::sessionBus().registerObject("/rede",
                                                      this->interfaceRede,
                                                      QDBusConnection::ExportAllContents);

    if ( ! ok )
    {
        qDebug() << "nao foi possivel registrar os servicos necessarios para a aplicacao";
        exit(1);
    }

    ok = QDBusConnection::sessionBus().registerObject("/gp",
                                                      this->interfaceGP,
                                                      QDBusConnection::ExportAllContents);

    if ( ! ok )
    {
        qDebug() << "nao foi possivel registrar os servicos necessarios para a aplicacao";
        exit(1);
    }

}

GerenciadorDBus::~GerenciadorDBus()
{
}

void
GerenciadorDBus::resultStartProcesso( bool _sucesso,
                                      QString _processo,
                                      int _id )
{
    emit this->interfaceGP->resultStartProcesso(_sucesso,
                                                _id,
                                                _processo);
}
