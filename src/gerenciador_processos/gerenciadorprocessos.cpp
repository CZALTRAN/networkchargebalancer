#include "gerenciadorprocessos.h"

#include "parserdepacotes.h"

GerenciadorProcessos::GerenciadorProcessos(QObject * _parent )
    : QObject(_parent)
{
    QObject::connect(this, SIGNAL(messageBalancer(const int&, const GP::PacoteBase&)),
                     &this->balancer, SLOT(incommingMessage(const int&, const GP::PacoteBase&)));

    QObject::connect(this, SIGNAL(messageLauncher(const int&, const GP::PacoteBase&)),
                     &this->launcher, SLOT(incommingMessage(const int&, const GP::PacoteBase&)));

    QObject::connect(this, SIGNAL(processoLaunch(QString,QStringList)),
                     &this->launcher, SLOT(processoStart(QString,QStringList)));
    
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
GerenciadorProcessos::incommingMessage( const int& _id, const QString& _mensagem )
{

    GP::PacoteBase*
    _pacote = GP::ParserDePacotes::getInstance().parseiaPacote(_mensagem);

    switch( _pacote->nome )
    {
        case GP::BALANCER:
            emit this->messageBalancer( _id, *_pacote );
        break;

        case GP::LAUNCHER:
            emit this->messageLauncher( _id, *_pacote );
        break;

        case GP::GP:
        break;
    }

}

void
GerenciadorProcessos::killProcess( const int& _id_dono, const Q_PID& _processo)
{

}

void
GerenciadorProcessos::processoStart( const QString& _processo, const QStringList& _parametros )
{
    emit this->processoLaunch( _processo, _parametros );
}

