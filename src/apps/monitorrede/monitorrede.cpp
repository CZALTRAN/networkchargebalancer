#include "monitorrede.h"

#include "QColor"
#include "QDebug"

MonitorRede::MonitorRede(QWidget* _parent )
    : QWidget(_parent)
{
    this->form = new Ui::Form();
    this->form->setupUi(this);
    this->rede_interface = new RedeInterface(this);
    this->watch_dog = new QTimer(this);

    this->watch_dog->setInterval(500);

    QObject::connect( this->watch_dog, SIGNAL(timeout()),
                      this,SLOT(setRedeStatus()));

    QObject::connect( this->rede_interface, SIGNAL(peerCaiu(int)),
                      this,SLOT(atualizaServer()));

    this->watch_dog->start();
    this->atualizaServer();
}

void
MonitorRede::setRedeStatus()
{
    if ( this->rede_interface->redeOk() )
    {
        this->form->status_rede->setPalette( QPalette("green") );
    }
    else
    {
        this->form->status_rede->setPalette( QPalette("red") );
    }
}

void
MonitorRede::atualizaServer()
{
    if ( this->rede_interface->redeOk() )
    {
        this->form->server_id->display( this->rede_interface->getServerId() );
    }
}
