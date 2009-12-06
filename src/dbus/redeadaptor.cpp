#include "redeadaptor.h"

#include <QDebug>

#include "gerenciadordbus.h"

RedeAdaptor::RedeAdaptor( GerenciadorDBus* _parent )
    : QDBusAbstractAdaptor( _parent )
{
}

