#include "balanceadorcarga.h"

#include <QDebug>

#include "gpconfig.h"

GP::BalanceadorCarga::BalanceadorCarga(QObject *parent) :
    QObject(parent)
{
    this->peer_round_robin = new QHashIterator<const int, const GP::Peer*>(this->peers);
}

GP::BalanceadorCarga::~BalanceadorCarga()
{


}

void
GP::BalanceadorCarga::peerCaiu( const int& )
{

}

void
GP::BalanceadorCarga::peerNovo( const int& _id )
{
    GP::Peer*
    novo_peer = new GP::Peer();

    novo_peer->setId(_id);

    if( GP::GPConfig::getInstance().getMeuId() == _id )
    {
        novo_peer->setPossuiRelacao(true);
        novo_peer->setQtdeProcessos(0);
        novo_peer->setQtdeProcessosPermitidos(2);
    }
    else
    {
        novo_peer->setPossuiRelacao(false);
    }
}

void
GP::BalanceadorCarga::incommingMessage( const int& _id, const GP::PacoteBase& _pacote )
{

}

int
GP::BalanceadorCarga::getPeerHost() const
{
    QHashIterator<const int, const Peer*>*
    ponto_de_partida = this->peer_round_robin;

    if( this->peer_round_robin->hasNext() )
    {
        this->peer_round_robin->next();
    }
    else
    {
        this->peer_round_robin->toFront();

        //this->peer_round_robin->next();
    }

    qDebug() << Q_FUNC_INFO << "iterando ate encontrar um peer disponivel.";

    while( this->peer_round_robin != ponto_de_partida )
    {
        GP::Peer
        peer_atual = *this->peer_round_robin->value();

        if( peer_atual.getQtdeProcessosPermitidos() - peer_atual.getQtdeProcessos() )
        {
            return peer_atual.getId();
        }

        if( this->peer_round_robin->hasNext() )
        {
            this->peer_round_robin->next();
        }
        else
        {
            this->peer_round_robin->toFront();
            //this->peer_round_robin->next();
        }
    }

    return GP::GPConfig::getInstance().getMeuId();
}



