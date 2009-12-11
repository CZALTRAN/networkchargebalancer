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

    qDebug() << Q_FUNC_INFO << " recebi uma nova solicitacao de processo: "
            << _nome_processo;
    emit this->signalStartProcesso(id_solic, _nome_processo, _parametros );

    return id_solic;
}

void
GPAdaptor::matarProcesso( int _pid, int _id_dono, int _num_requisicao )
{
    emit this->signalMatarProcesso( _pid, _id_dono, _num_requisicao );
}

QString
GPAdaptor::getProcessos()
{
    QString
    ret = dynamic_cast<GerenciadorProcessos*>(this->parent())->getProcessos();

    return ret;
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

    //gambiarra azia pro dbus nao dar azia!!!
    int
    i = _processo;

    argumentos.push_back(i);
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

    //gambiarra azia pro dbus nao dar azia!!!
    int
    i = _pid;

    argumentos.push_back(_id_requisicao);
    argumentos.push_back(_processo);
    argumentos.push_back(i);

    this->sendSignal( "resultStartProcesso", argumentos );
}

void
GPAdaptor::slotProcessoTerminou( qint64 _processo, int _registro, int _retorno)
{
    QList<QVariant>
    argumentos;

    //gambiarra azia pro dbus nao dar azia!!!
    int
    i = _processo;

    argumentos.push_back(i);
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
