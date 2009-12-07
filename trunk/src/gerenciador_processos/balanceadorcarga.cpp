#include "balanceadorcarga.h"

#include <QDebug>

#include "gpconfig.h"
#include "gpconstrutordepacotes.h"

GP::BalanceadorCarga::BalanceadorCarga(QObject *parent) :
    QObject(parent)
{
    this->peer_round_robin = this->peers.begin();

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

        this->peers.insert(_id, novo_peer);
    }
    else
    {
        novo_peer->setPossuiRelacao(false);
        novo_peer->setQtdeProcessos(0);
        //novo_peer->setQtdeProcessosPermitidos(NUM_MAX_PROCESSOS);
        this->peers.insert(_id, novo_peer);
    }
    QString
    pacote_status_peer =
    GP::ConstrutorDePacotes::getInstance().montaStatusPeer(0, NUM_MAX_PROCESSOS);

    emit this->sendMessage(0, pacote_status_peer);
}

void
GP::BalanceadorCarga::incommingMessage( const int& _id, const GP::PacoteBase* _pacote )
{

}

void
GP::BalanceadorCarga::insereCarga( const int& _id )
{
    if( this->peers.contains(_id) )
    {
        GP::Peer*
        peer = this->peers.value(_id);

        int
        carga_peer = peer->getQtdeProcessos();

        peer->setQtdeProcessos(carga_peer + 1);

        peer->setPossuiRelacao(true);

    }
    else
    {
        qDebug() << Q_FUNC_INFO << "Peer nao foi encontrado.";
    }
}

int
GP::BalanceadorCarga::getPeerHost()
{
    GP::Peer*
    ponto_partida;

    if( this->peer_round_robin != this->peers.end() )
    {
        ponto_partida = this->peer_round_robin.value();
    }
    else
    {
        QHash<int, Peer*>::iterator
        iterador_temp = this->peers.begin();

        ponto_partida = iterador_temp.value();
    }

    while( true )
    {
        if( this->peer_round_robin != this->peers.end() )
        {
            this->peer_round_robin++;
        }
        else
        {
            this->peer_round_robin = this->peers.begin();
        }

        GP::Peer*
        peer_atual = this->peer_round_robin.value();

        if( this->peers.contains( this->peers.key(peer_atual) ) )
        {

            if( ( peer_atual->getQtdeProcessosPermitidos() - peer_atual->getQtdeProcessos() ) > 0 )
            {
                return peer_atual->getId();
            }

            if( peer_atual->getId() == ponto_partida->getId() )
            {
                return GP::GPConfig::getInstance().getMeuId();
            }
        }
    }
}

void
GP::BalanceadorCarga::setStatusPeer( const int _id,
                                     const GP::PacoteStatusPeer* _pacote )
{
    GP::Peer*
    peer;

    if( this->peers.contains(_id) )
    {
        peer = this->peers.value(_id);

        peer->setQtdeProcessos(_pacote->qtde_processos);
        peer->setQtdeProcessosPermitidos(_pacote->qtde_processos_permitidos);

        qDebug() << Q_FUNC_INFO << "atualizando carga no peer" << peer->getId();

        if( _id == GP::GPConfig::getInstance().getMeuId() )
        {
            QString
            pacote_status_peer =
                        GP::ConstrutorDePacotes::getInstance().montaStatusPeer(
                                            _pacote->qtde_processos,
                                            _pacote->qtde_processos_permitidos);

            emit this->sendMessage(0, pacote_status_peer);
        }
    }
    else
    {
        qDebug() << Q_FUNC_INFO << "Peer nao foi encontrado";
    }
}

bool
GP::BalanceadorCarga::getPermissaoProcessar()
{
    if( (GP::GPConfig::getInstance().getQtdeProcessosPermitidos()
                         - GP::GPConfig::getInstance().getQtdeProcessos()) > 0 )
    {
        return true;
    }

    return false;
}



