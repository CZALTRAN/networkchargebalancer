#include "gerenciadorprocessos.h"

#include <QDebug>

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
GerenciadorProcessos::incommingMessage(const int& _id, const QString& _mensagem)
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
GerenciadorProcessos::processoStart( int _num_requisicao,
                                                       QString _processo,
                                                       QString _parametros )
{
    qDebug() << Q_FUNC_INFO << "parseando os parametros.";

    QStringList
    parametros = _parametros.split(" ");

    qDebug() << Q_FUNC_INFO << "pegando id do peer q vai processar.";

    int
    id_peer_host = this->balancer.getPeerHost();

    qDebug() << Q_FUNC_INFO << "solicitando que o launcher inicie o processo.";

    this->launcher.processoStart( _num_requisicao, id_peer_host,
                                  GP::GPConfig::getInstance().getMeuId(),
                                  _processo,
                                  parametros );
}

void
GerenciadorProcessos::meuId( int _meu_id )
{
    GP::GPConfig::getInstance().setMeuId(_meu_id);

    this->balancer.peerNovo(_meu_id);
}


void
GerenciadorProcessos::killProcess( const int _id_dono, const Q_PID _processo)
{

}

void
GerenciadorProcessos::novoProcesso(int _id_host, GP::Processo* _processo)
{
    if( GP::GPConfig::getInstance().getMeuId() == _id_host )
    {
        this->processos.insert(_processo->getPid(), _processo);
    }
}

void
GerenciadorProcessos::falhouStartProcesso( int _num_requisicao,
                                           int _id_dono,
                                           QString _processo )
{

}

