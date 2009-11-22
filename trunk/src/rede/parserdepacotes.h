#ifndef PARSERDEPACOTES_H
#define PARSERDEPACOTES_H

#include <QString>

#include "structpacotes.h"

namespace Rede
{
    class ParserDePacotes
    {
    public:
        static ParserDePacotes&
        getInstance();

        PacoteBase*
        parseiaPacote( const QString _pacote ) const;

    private:
        ParserDePacotes();

        ~ParserDePacotes();

        PacoteInit*
        parseiaInit( const QString _pacote ) const;
    };
}

#endif // PARSERDEPACOTES_H
