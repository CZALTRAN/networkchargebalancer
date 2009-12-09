#include "gpadaptor.h"

#include <QDebug>

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
GPAdaptor::standardInput( int _identificador, QString _input )
{
    emit this->signalStandardInput( _identificador, _input );
}
