#include "xbogainittializer.h"

XBogaInittializer::XBogaInittializer( int argc, char* argv[], QObject *parent) :
    QObject(parent)
{

    if (argc == 3)
        this->grede = new GerenciadorRede( argv[1],argv[2],this);
    else
        this->grede = new GerenciadorRede( argv[1],0,this);

    this->gprocessos = new GerenciadorProcessos(this);
}
