#include "redeadaptor.h"

#include "gerenciadordbus.h"

RedeAdaptor::RedeAdaptor( GerenciadorDBus* _parent )
    : QDBusAbstractAdaptor(_parent)
{
}
