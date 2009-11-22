#include "gerenciadorrede.h"

#include "construtordepacotes.h"
#include "lib/getifaddrfromadapter.h"
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
        qDebug() << Q_FUNC_INFO << "Nao foi possivel inicializar o ouvinte(6969)";
        exit(1);
    }

    if (! this->ouvinte_procura->startListen(2469))
    {
        qDebug() << Q_FUNC_INFO << "Nao foi possivel inicializar o ouvinte_procura(6969)";
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
        qDebug() << Q_FUNC_INFO << "Entrei no conectando";
        this->addConexaoNovoPeer( _socket_descriptor );
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
         case Rede::SERVER:
            // Recebe quem é o server ( novo peer )
          qDebug() << Q_FUNC_INFO << "Entrei no server.";

        // Recebe pacote informando que não é mais o server

        break;
    case Rede::CONECTADO:
        // Recebe quem é o server ( novo peer )

        // Recebe pacote novo_peer

            break;
         case Rede::CONECTADO:
            // Recebe quem é o server ( novo peer )
          qDebug() << Q_FUNC_INFO << "Entrei no conectado.";

            switch( pacote->nome )
            {
               case Rede::NOVO_PEER:
                 qDebug() << Q_FUNC_INFO << "Entrei no novo_peer.";
                 this->recebeNovoPeer(pacote);
               break;
            }
            // Recebe pacote novo_peer

        // Recebe pacote informando quem é novo server ( remetente é o novo )

        break;
    case Rede::CONECTANDO:
        // Recebe pacote de requisição de conexão ( veteranos )

        // Recebe pacote novo_peer

            break;
         case Rede::CONECTANDO:
             // Recebe pacote de requisição de conexão ( veteranos )

             qDebug() << Q_FUNC_INFO << "Entrei no conectando.";

             switch( pacote->nome )
             {
                 case Rede::INIT: // Recebe init do proprio server
                    qDebug() << Q_FUNC_INFO << "Entrei no init.";
                    this->recebeInit(pacote);
                 break;
                 case Rede::NOVO_PEER:
                    qDebug() << Q_FUNC_INFO << "Entrei no novo_peer.";
                    this->recebeNovoPeer(pacote);
                 break;
             }

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

    tmp_conexao->flush();
    tmp_conexao->close();
}

void
GerenciadorRede::serverEncontrado( const int& _id, const QString& _message )
{
    Q_UNUSED(_id)

    Rede::RedeConfig::getInstance().estado_atual = Rede::CONECTANDO;

    Rede::PacoteInformaServer*
    parseado = static_cast<Rede::PacoteInformaServer*>(
                Rede::ParserDePacotes::getInstance().parseiaPacote( _message ));

    Rede::Peer*
    server = new Rede::Peer();

    server->setHost( parseado->host );
    server->setId( parseado->id );

    server->conectar();
    this->ouvinte_procura->startListen(2469);

    this->gerenciador_conexoes->addConexao( server );
    Rede::RedeConfig::getInstance().server_host = server;

    QObject::connect( server, SIGNAL(incommingMessage(int,QString)),
                      this, SLOT(slotNovaMensagemFromPeer(int,QString)));
}

void
GerenciadorRede::recebeInit( Rede::PacoteBase* const _pacote )
{
    Rede::PacoteInit*
    pacote = static_cast<Rede::PacoteInit*>(_pacote);

    this->qtdePeers = pacote->total_peers;

    Rede::RedeConfig::getInstance().meu_id = pacote->id;
}

void
GerenciadorRede::recebeNovoPeer( Rede::PacoteBase* const _pacote )
{
    Rede::PacoteNovoPeer*
    pacote = static_cast<Rede::PacoteNovoPeer*>(_pacote);

    Rede::Peer*
    novo_peer = new Rede::Peer();

    novo_peer->setHost(pacote->host);
    novo_peer->setId(pacote->id);

    novo_peer->conectar();

    this->gerenciador_conexoes->addConexao(novo_peer);
}

void
GerenciadorRede::addConexaoNovoPeer( const int& _socket_descriptor )
{
    Rede::Peer*
    peer = new Rede::Peer(_socket_descriptor);

    this->gerenciador_conexoes->addConexao(peer);
}
