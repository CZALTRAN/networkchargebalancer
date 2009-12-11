#include "balanceadorcarga.h"

#include <QDebug>

#include "gpconfig.h"
#include "gpconstrutordepacotes.h"

GP::BalanceadorCarga::BalanceadorCarga(QObject *parent) :
    QObject(parent)
{
    this->peer_round_robin = this->peers.begin();

    GP::GPConfig::getInstance().setQtdeProcessos(0);
    GP::GPConfig::getInstance().setQtdeProcessosPermitidos(NUM_MAX_PROCESSOS);

}

GP::BalanceadorCarga::~BalanceadorCarga()
{


}

void
GP::BalanceadorCarga::peerCaiu( const int& _id )
{
    QHash<int, GP::Peer*>::iterator
    iterador = this->peers.find(_id);

    this->peers.erase(iterador);
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
        novo_peer->setQtdeProcessos(
                                GP::GPConfig::getInstance().getQtdeProcessos());
        novo_peer->setQtdeProcessosPermitidos(
                      GP::GPConfig::getInstance().getQtdeProcessosPermitidos());

        this->peers.insert(_id, novo_peer);
    }
    else
    {
        novo_peer->setPossuiRelacao(false);
        novo_peer->setQtdeProcessos(0);

        qDebug() << Q_FUNC_INFO << "Enviando status peer ao novo peer!";

        this->peers.insert(_id, novo_peer);

        QString
        pacote_status_peer =
        GP::ConstrutorDePacotes::getInstance().montaStatusPeer(
                      GP::GPConfig::getInstance().getQtdeProcessos(),
                      GP::GPConfig::getInstance().getQtdeProcessosPermitidos());

        emit this->sendMessage(_id, pacote_status_peer);
    }
}

void
GP::BalanceadorCarga::incommingMessage( const int& _id,
                                        const GP::PacoteBase* _pacote )
{
    Q_UNUSED(_id)
    Q_UNUSED(_pacote)
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

        this->peers.value(_id)->setQtdeProcessos(carga_peer + 1);

        this->peers.value(_id)->setPossuiRelacao(true);

        if( _id == GP::GPConfig::getInstance().getMeuId() )
        {
            GP::GPConfig::getInstance().setQtdeProcessos(carga_peer  + 1);

            QString
            pacote_status = GP::ConstrutorDePacotes::getInstance().montaStatusPeer(
                            GP::GPConfig::getInstance().getQtdeProcessos(),
                            GP::GPConfig::getInstance().getQtdeProcessosPermitidos());

            emit this->sendMessage(0, pacote_status);
        }

    }
    else
    {
        qDebug() << Q_FUNC_INFO << "Peer nao foi encontrado.";
    }
}

void
GP::BalanceadorCarga::removeCarga( const int& _id )
{
    if( this->peers.contains(_id) )
    {
        GP::Peer*
        peer = this->peers.value(_id);

        int
        carga_peer = peer->getQtdeProcessos();

        this->peers.value(_id)->setQtdeProcessos(carga_peer - 1);

        this->peers.value(_id)->setPossuiRelacao(true);

        if( _id == GP::GPConfig::getInstance().getMeuId() )
        {
            GP::GPConfig::getInstance().setQtdeProcessos(carga_peer - 1);

            QString
            pacote_status = GP::ConstrutorDePacotes::getInstance().montaStatusPeer(
                            GP::GPConfig::getInstance().getQtdeProcessos(),
                            GP::GPConfig::getInstance().getQtdeProcessosPermitidos());

            emit this->sendMessage(0, pacote_status);
        }

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

    GP::Peer*
    peer_atual;

    qDebug() << Q_FUNC_INFO << "Tamanho da hash: " << this->peers.size();

    if( this->peer_round_robin != this->peers.end() )
    {
        ponto_partida = this->peer_round_robin.value();

        peer_atual = this->peer_round_robin.value();
    }
    else
    {
        this->peer_round_robin = this->peers.begin();

        ponto_partida = this->peer_round_robin.value();

        peer_atual = this->peer_round_robin.value();
    }

    do
    {
        if( this->peers.contains( this->peers.key(peer_atual) ) )
        {

            if( ( peer_atual->getQtdeProcessosPermitidos()
                                        - peer_atual->getQtdeProcessos() ) > 0 )
            {
                this->avancaPeerRR();
                return peer_atual->getId();
            }

        }
        else
        {
            qDebug() << Q_FUNC_INFO << "UM PEER QUE A HASH NÃO POSSUI!";
        }

        this->avancaPeerAtual();

        peer_atual = this->peer_round_robin.value();

    }while( ponto_partida->getId() != peer_atual->getId() );

    return GP::GPConfig::getInstance().getMeuId();
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

void
GP::BalanceadorCarga::avancaPeerRR()
{
    if( this->peer_round_robin != this->peers.end() )
    {
        this->peer_round_robin++;
    }
    else
    {
        this->peer_round_robin = this->peers.begin();
    }
}

void
GP::BalanceadorCarga::avancaPeerAtual()
{
    this->peer_round_robin++;

    if( this->peer_round_robin == this->peers.end() )
    {
        this->peer_round_robin = this->peers.begin();
    }
}

