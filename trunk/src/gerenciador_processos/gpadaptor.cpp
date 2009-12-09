#include "gpadaptor.h"

#include <QDebug>
#include <QDBusConnection>
#include <QDBusMessage>

#include "../dbus/dbusconfig.h"

GPAdaptor::GPAdaptor( QObject* _parent )
    : QDBusAbstractAdaptor(_parent)
{
}

quint64
GPAdaptor::startProcesso( QString _nome_processo, QString _parametros )
{

    quint64
    id_solic = DBusConfig::getInstance().getNovoProcId();

    emit this->signalStartProcesso(id_solic, _nome_processo, _parametros );

    return id_solic;
}

void
GPAdaptor::standardInput( Q_PID _processo, int _identificador, QString _input )
{
    emit this->signalStandardInput( _processo, _identificador, _input );
}

void
GPAdaptor::slotStandardOutput( Q_PID _processo, int _registro, QString _mensagem )
{
    QDBusMessage
    sinal_standard_output;

    sinal_standard_output = QDBusMessage::createSignal(
            "/gp",
            "uel.computacao.xboga.gp",
            "standardOutput");

    QList<QVariant>
    argumentos;

    argumentos.push_back(_processo);
    argumentos.push_back(_registro);
    argumentos.push_back(_mensagem);

    sinal_standard_output.setArguments(argumentos);

    QDBusConnection::sessionBus().send( sinal_standard_output );
}

void
GPAdaptor::slotResultStartProcesso( int _id_requisicao,
                                QString _processo,
                                Q_PID _pid )
{
    QDBusMessage
    sinal_standard_output;

    sinal_standard_output = QDBusMessage::createSignal(
            "/gp",
            "uel.computacao.xboga.gp",
            "resultStartProcesso");

    QList<QVariant>
    argumentos;

    argumentos.push_back(_id_requisicao);
    argumentos.push_back(_processo);
    argumentos.push_back(_pid);

    sinal_standard_output.setArguments(argumentos);

    QDBusConnection::sessionBus().send( sinal_standard_output );
}
