#include "gpadaptor.h"

#include <QDebug>

#include "dbusconfig.h"
#include "gerenciadordbus.h"

GPAdaptor::GPAdaptor( GerenciadorDBus* _parent )
    : QDBusAbstractAdaptor(_parent)
{
}

quint64
GPAdaptor::startProcesso( QString _nome_processo, QString _parametros )
{

    quint64
    id_solic = DBusConfig::getInstance().getNovoProcId();

    emit static_cast<GerenciadorDBus*>(this->parent())
            ->novaSolicitacaoDeProcesso(id_solic,
                                        _nome_processo,
                                        _parametros);
    return id_solic;
}
