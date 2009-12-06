#include "gpadaptor.h"

#include <QDebug>

#include "gerenciadordbus.h"

GPAdaptor::GPAdaptor( GerenciadorDBus* _parent )
    : QDBusAbstractAdaptor(_parent)
{
}

void
GPAdaptor::startProcesso( QString _nome_processo, QString _parametros )
{
    emit static_cast<GerenciadorDBus*>(this->parent())
            ->novaSolicitacaoDeProcesso(_nome_processo,_parametros);
}
