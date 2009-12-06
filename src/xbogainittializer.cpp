#include "xbogainittializer.h"

XBogaInittializer::XBogaInittializer( int argc, char* argv[], QObject *parent) :
    QObject(parent)
{

    if (argc == 3)
        this->grede = new GerenciadorRede( argv[1],argv[2],this);
    else
        this->grede = new GerenciadorRede( argv[1],0,this);

    this->gprocessos = new GerenciadorProcessos(this);

    QObject::connect( this->grede, SIGNAL(meuId(int)),
                      this->gprocessos, SLOT(meuId(int)));

    QObject::connect( this->grede, SIGNAL(novoPeer(int)),
                      this->gprocessos, SLOT(peerNovo(int)));

    QObject::connect( this->grede, SIGNAL(peerCaiu(int)),
                      this->gprocessos, SLOT(peerCaiu(int)));
}
