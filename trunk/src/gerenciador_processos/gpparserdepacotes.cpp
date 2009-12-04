#include "gpparserdepacotes.h"

GP::ParserDePacotes::ParserDePacotes()
{

}

GP::ParserDePacotes::~ParserDePacotes()
{

}

GP::ParserDePacotes&
GP::ParserDePacotes::getInstance()
{
    static GP::ParserDePacotes
    instance;

    return instance;
}


GP::PacoteBase*
GP::ParserDePacotes::parseiaPacote(const QString& _pacote) const
{

}

GP::PacoteStartProcess*
GP::ParserDePacotes::parseiaStartProcess( const QStringList& _lista_parametros ) const
{

}

GP::PacoteSuccessStartProcess*
GP::ParserDePacotes::parseiaSuccessStartProcess( const QStringList& _lista_parametros ) const
{

}

GP::PacoteFailStartProcess*
GP::ParserDePacotes::parseiaFailStartProcess( const QStringList& _lista_parametros ) const
{

}

GP::PacoteStatusPeer*
GP::ParserDePacotes::parseiaPacoteStatusPeer( const QStringList& _lista_parametros ) const
{

}
