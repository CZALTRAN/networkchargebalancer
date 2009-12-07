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
        qDebug() << Q_FUNC_INFO << "setando as configuracoes do peer";

        novo_peer->setPossuiRelacao(true);
        novo_peer->setQtdeProcessos(0);
        novo_peer->setQtdeProcessosPermitidos(2);

        qDebug() << Q_FUNC_INFO << "construindo pacote e enviando para a rede";

        QString
        pacote_status_peer =
        GP::ConstrutorDePacotes::getInstance().montaStatusPeer(0, NUM_MAX_PROCESSOS);

        emit this->sendMessage(0, pacote_status_peer);

        qDebug() << Q_FUNC_INFO << "inserindo peer na hash";

        this->peers.insert(_id, novo_peer);
    }
    else
    {
        novo_peer->setPossuiRelacao(false);
        novo_peer->setQtdeProcessos(0);
        //novo_peer->setQtdeProcessosPermitidos(NUM_MAX_PROCESSOS);
        this->peers.insert(_id, novo_peer);
    }
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

        qDebug() << Q_FUNC_INFO << "inserindo carga no peer" << peer->getId();

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
    qDebug() << Q_FUNC_INFO << "posicionando marcador para a iteracao";

    qDebug() << Q_FUNC_INFO << "criando peer marcador";

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

    qDebug() << Q_FUNC_INFO << "iterando ate encontrar um peer disponivel.";

    while( true )
    {
        qDebug() << Q_FUNC_INFO << "iteracao";

        if( this->peer_round_robin != this->peers.end() )
        {
            qDebug() << Q_FUNC_INFO << "incrementando iterador";
            this->peer_round_robin++;
        }
        else
        {
            qDebug() << Q_FUNC_INFO << "o iterador esta no final. voltando..";
            this->peer_round_robin = this->peers.begin();
        }

        qDebug() << Q_FUNC_INFO << "atribuindo valor ao peer de iteracao";

        GP::Peer*
        peer_atual = this->peer_round_robin.value();

        qDebug() << Q_FUNC_INFO << "testando peer de iteracao";

        if( this->peers.contains( this->peers.key(peer_atual) ) )
        {

            if( ( peer_atual->getQtdeProcessosPermitidos() - peer_atual->getQtdeProcessos() ) > 0 )
            {
                qDebug() << Q_FUNC_INFO << "id do peer_atual" << peer_atual->getId();

                return peer_atual->getId();
            }

            qDebug() << Q_FUNC_INFO << "testando se o round-robin acabou";

            if( peer_atual->getId() == ponto_partida->getId() )
            {
                return GP::GPConfig::getInstance().getMeuId();
            }
        }
    }
}

void
GP::BalanceadorCarga::setStatusPeer( const int& _id,
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



