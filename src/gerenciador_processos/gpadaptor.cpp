#include "gpadaptor.h"

#include <QDebug>
#include <QDBusConnection>
#include <QDBusMessage>

#include "gerenciadorprocessos.h"
#include "../dbus/dbusconfig.h"

GPAdaptor::GPAdaptor( GerenciadorProcessos* _parent )
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
    QList<QVariant>
    argumentos;

    argumentos.push_back(_processo);
    argumentos.push_back(_registro);
    argumentos.push_back(_mensagem);

    this->sendSignal( "standardOutput", argumentos );
}

void
GPAdaptor::slotResultStartProcesso( int _id_requisicao,
                                QString _processo,
                                Q_PID _pid )
{
    QList<QVariant>
    argumentos;

    argumentos.push_back(_id_requisicao);
    argumentos.push_back(_processo);
    argumentos.push_back(_pid);

    this->sendSignal( "resultStartProcesso", argumentos );
}

void
GPAdaptor::slotProcessoTerminou( qint64 _processo, int _registro, int _retorno)
{
    QList<QVariant>
    argumentos;

    argumentos.push_back(_processo);
    argumentos.push_back(_registro);
    argumentos.push_back(_retorno);

    this->sendSignal( "processoTerminou", argumentos );
}

void
GPAdaptor::sendSignal( QString _metodo, QList<QVariant> _argumentos)
{
    QDBusMessage
    sinal;

    sinal = QDBusMessage::createSignal(
            "/gp",
            "uel.computacao.xboga.gp",
            _metodo);

    sinal.setArguments( _argumentos );

    QDBusConnection::sessionBus().send( sinal );
}