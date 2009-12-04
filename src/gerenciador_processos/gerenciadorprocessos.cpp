#include "gerenciadorprocessos.h"

#include "gpparserdepacotes.h"
#include "gpconfig.h"

GerenciadorProcessos::GerenciadorProcessos(QObject * _parent )
    : QObject(_parent)
{

}

GerenciadorProcessos::~GerenciadorProcessos()
{

}

void
GerenciadorProcessos::peerNovo( const int& _id )
{

}

void
GerenciadorProcessos::peerCaiu( const int& _id )
{

}

void
GerenciadorProcessos::incommingMessage( const int& _id, const QString& _mensagem )
{

    GP::PacoteBase*
    _pacote = GP::ParserDePacotes::getInstance().parseiaPacote(_mensagem);

    switch( _pacote->dono )
    {
        case GP::BALANCER:
            this->balancer.incommingMessage( _id, *_pacote );
        break;

        case GP::LAUNCHER:
            this->launcher.incommingMessage( _id, *_pacote );
        break;

        case GP::GP:
        break;
    }

}

void
GerenciadorProcessos::processoStart( const QString _processo, const QStringList _parametros )
{
    int
    id_peer_host = this->balancer.getPeerHost();

    this->launcher.processoStart( id_peer_host, GP::GPConfig::getInstance().getMeuId(), _processo, _parametros );
}

void
GerenciadorProcessos::killProcess( const int& _id_dono, const Q_PID& _processo)
{

}

void
GerenciadorProcessos::novoProcesso( const int& _id_host, const GP::Processo& _processo )
{

}


