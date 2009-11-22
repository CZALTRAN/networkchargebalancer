#include "gerenciadorrede.h"

#include "construtordepacotes.h"
#include "parserdepacotes.h"
#include "redeconfig.h"
#include "structpacotes.h"

GerenciadorRede::GerenciadorRede( Rede::Peer* _primeiro_peer )
{
    this->gerenciador_conexoes = new Rede::GerenciadorConexao::GerenciadorConexao();
    this->ouvinte = new Rede::Ouvinte(this);

    QObject::connect(this->ouvinte, SIGNAL(novaConn(int)),
                     this, SLOT(slotNovaConexao(int)));

    if ( _primeiro_peer == NULL )
    {
        this->startComoServer();
    }
    else
    {
        this->buscaPorServer(_primeiro_peer);
    }

}

GerenciadorRede::~GerenciadorRede()
{

}

void
GerenciadorRede::startComoServer()
{
    Rede::RedeConfig::getInstance().meu_id = 1;
    Rede::RedeConfig::getInstance().estado_atual = Rede::SERVER;

    if (! this->ouvinte->startListen() )
    {
        exit(1);
    }
}

void
GerenciadorRede::buscaPorServer( Rede::Peer* _primeiro_peer )
{
    Rede::RedeConfig::getInstance().estado_atual = Rede::PROCURANDO_SERVER;

    _primeiro_peer->conectar();

    this->gerenciador_conexoes->tmp_peer = _primeiro_peer;

    QObject::connect(_primeiro_peer,SIGNAL(incommingMessage(int,QString)),
                     this,SLOT(slotNovaMensagemFromPeer(int,QString)));
}

void
GerenciadorRede::informaServerInfo( const int& _socket_descriptor)
{
    Rede::Conexao*
    tmp_conexao = new Rede::Conexao();
    tmp_conexao->setSocketDescriptor( _socket_descriptor );

    QString
    mensagem = Rede::ConstrutorDePacotes::getInstance().montaServer();

    tmp_conexao->enviaDado(mensagem);

    tmp_conexao->flush();
    tmp_conexao->close();
}

void
GerenciadorRede::slotNovaConexao(int _socket_descriptor )
{
    qDebug() << Rede::RedeConfig::getInstance().meu_id;

    if ( Rede::RedeConfig::getInstance().estado_atual == Rede::SERVER )
    { //sou o servidor e preciso indicar ao novo socket sobre todas as conexões.

        qDebug() << Q_FUNC_INFO << "tenho que indicar o server para o socket "
                 << _socket_descriptor;

        Rede::Peer*
        novo_peer = this->gerenciador_conexoes->novaConexao( _socket_descriptor );

        novo_peer->sendInit( this->gerenciador_conexoes->getTotalConn() );

        emit this->novoPeer( novo_peer->getHost(), novo_peer->getId() );

        QObject::connect(this,SIGNAL(novoPeer(const QString&, const int&)),
                         novo_peer,SLOT(enviaNovoPeer(const QString&, const int&)));

        QObject::connect(novo_peer,SIGNAL(incommingMessage(int,QString)),
                         this,SLOT(slotNovaMensagemFromPeer(int,QString)));
    }
    else
    { //não sou o servidor e preciso indicar quem é e fechar a conexão.
        this->informaServerInfo(_socket_descriptor);
    }

}

void
GerenciadorRede::slotNovaMensagemFromPeer( const int& _id, const QString& _message )
{
    Rede::PacoteBase*
    pacote = Rede::ParserDePacotes::getInstance().parseiaPacote(_message);

    switch ( Rede::RedeConfig::getInstance().estado_atual )
    {
     case Rede::PROCURANDO_SERVER:

        switch( pacote->nome )
        {
        case Rede::INFORMA_SERVER: // Recebe informa_server de um peer qualquer
            //this->conectaNoServer(pacote);
            break;
        case Rede::INIT: // Recebe informa_server do proprio server
            //this->configuraConexao(pacote);
            Rede::RedeConfig::getInstance().estado_atual = Rede::CONECTANDO;
            break;
        }

         break;
    case Rede::SERVER:
        // Recebe quem é o server ( novo peer )

        // Recebe reclamação ( novo peer, numero de peers )

        // Recebe pacotes que não são relativos a gerencia de rede

        // Recebe pacote informando que não é mais o server

        break;
    case Rede::CONECTADO:
        // Recebe quem é o server ( novo peer )

        // Recebe pacote novo_peer

        // Recebe pacotes que não são relativos a gerencia de rede

        // Recebe pacote ( conectar novamente novo peer )

        // Recebe pacote informando quem é novo server ( remetente é o novo )

        break;
    case Rede::CONECTANDO:
        // Recebe pacote de requisição de conexão ( veteranos )

        // Recebe pacote novo_peer

        break;
    }
}
