#ifndef PARSERDEPACOTES_H
#define PARSERDEPACOTES_H

#include <QStringList>

#include "structpacotes.h"

namespace GP
{
    class ParserDePacotes
    {
    public:
        static ParserDePacotes&
        getInstance();

        PacoteBase*
        parseiaPacote( const QString& _pacote ) const;

    private:
        ParserDePacotes();

        ~ParserDePacotes();

        PacoteStartProcess*
        parseiaStartProcess( const QStringList& _lista_parametros ) const;

        PacoteSuccessStartProcess*
        parseiaSuccessStartProcess( const QStringList& _lista_parametros ) const;

        PacoteFailStartProcess*
        parseiaFailStartProcess( const QStringList& _lista_parametros ) const;

        PacoteStatusPeer*
        parseiaPacoteStatusPeer( const QStringList& _lista_parametros ) const;
    };
}

#endif // PARSERDEPACOTES_H
