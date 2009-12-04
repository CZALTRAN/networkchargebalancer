#include "balanceadorcarga.h"

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
GP::BalanceadorCarga::getPeerHost()
{
    //retorna o peer selecionado para processar
}



