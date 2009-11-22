#include "gerenciadorrede.h"

#include "construtordepacotes.h"
#include "lib/getifaddrfromadapter.h"
#include "parserdepacotes.h"
#include "redeconfig.h"
#include "structpacotes.h"


GerenciadorRede::GerenciadorRede( QString _interface,
                                  Rede::Peer* _primeiro_peer )
{
    this->interface = _interface;

    this->gerenciador_conexoes = new Rede::GerenciadorConexao::GerenciadorConexao();
    this->ouvinte = new Rede::Ouvinte(this);
    this->ouvinte_procura = new Rede::Ouvinte(this);

    QObject::connect(this->ouvinte, SIGNAL(novaConn(int)),
                     this, SLOT(slotNovaConexao(int)));

    QObject::connect(this->ouvinte_procura, SIGNAL(novaConn(int)),
                     this,SLOT(informaServerInfo(int)));

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
    Rede::RedeConfig::getInstance().host = getIfaddrFromAdapter(this->interface);
    Rede::RedeConfig::getInstance().estado_atual = Rede::SERVER;

    Rede::Peer*
    eu_mesmo = new Rede::Peer();

    eu_mesmo->setId( Rede::RedeConfig::getInstance().meu_id );
    eu_mesmo->setHost( Rede::RedeConfig::getInstance().host );

    this->gerenciador_conexoes->addConexao( eu_mesmo );

    Rede::RedeConfig::getInstance().server_host = eu_mesmo;

    if (! this->ouvinte->startListen() )
    {
        exit(1);
    }

    if (! this->ouvinte_procura->startListen(2469))
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
                     this,SLOT(serverEncontrado(int,QString)));
}

void
GerenciadorRede::slotNovaConexao( const int& _socket_descriptor )
{
    switch( Rede::RedeConfig::getInstance().estado_atual )
    {
    case Rede::CONECTANDO:

        break;
    case Rede::CONECTADO:
        this->informaServerInfo(_socket_descriptor);
        break;
    case Rede::SERVER:
        //sou o servidor e preciso indicar ao novo socket sobre todas as conexões.
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

        break;
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

void
GerenciadorRede::informaServerInfo( const int& _socket_descriptor)
{
    Rede::Conexao*
    tmp_conexao = new Rede::Conexao();
    tmp_conexao->setSocketDescriptor( _socket_descriptor );

    QString
    mensagem = Rede::ConstrutorDePacotes::getInstance().montaServer();

    tmp_conexao->enviaDado(mensagem);
RedeConfig
    tmp_conexao->flush();
    tmp_conexao->close();
}

void
GerenciadorRede::serverEncontrado( const int& _id, const QString& _message )
{
    Q_UNUSED(_id)

    Rede::PacoteInformaServer*
    parseado = Rede::ParserDePacotes::parseiaPacote( _message );

    Rede::Peer*
    server = new Rede::Peer();

    server->setHost( parseado->host );
    server->setId( parseado->id );

    this->gerenciador_conexoes->addConexao( server );
    Rede::RedeConfig::server_host = server;

    server->conectar();

    QObject::connect( server, SIGNAL(incommingMessage(int,QString)),
                      this, SLOT(slotNovaMensagemFromPeer(int,QString)));
}

