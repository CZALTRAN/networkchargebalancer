#include "balanceadorcarga.h"
#include "gpconfig.h"

GP::BalanceadorCarga::BalanceadorCarga(QObject *parent) :
    QObject(parent)
{
}

GP::BalanceadorCarga::~BalanceadorCarga()
{


}

void
GP::BalanceadorCarga::peerCaiu( const int& )
{

}

void
GP::BalanceadorCarga::peerNovo( const int& )
{

}

void
GP::BalanceadorCarga::incommingMessage( const int& _id, const GP::PacoteBase& _pacote )
{

}

//void
//GP::BalanceadorCarga::novoProcesso( const int& _id_peer, const Processo& _processo )
//{
//    //se o processo for inicializado com sucesso
//    //o balancer o insere na hash de processos do peer _id_peer
//    //que está na hash de peers desta classe!! :D:D:D
//}

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
        this->peer_round_robin->next();
    }

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
            this->peer_round_robin->next();
        }
    }

    return GP::GPConfig::getInstance().getMeuId();
}



