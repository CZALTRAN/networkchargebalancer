#include "redeadaptor.h"

#include <QDebug>

#include "gerenciadorrede.h"

RedeAdaptor::RedeAdaptor( GerenciadorRede* _parent )
    : QDBusAbstractAdaptor( _parent )
{

}

QString
RedeAdaptor::getAllPeers()
{
    return dynamic_cast<GerenciadorRede*>(this->parent())->getCSVPeers();
}

int
RedeAdaptor::getServer()
{
    return dynamic_cast<GerenciadorRede*>(this->parent())->getServer();
}
