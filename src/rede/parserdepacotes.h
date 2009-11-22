#ifndef PARSERDEPACOTES_H
#define PARSERDEPACOTES_H

#include <QString>

#include "structpacotes.h"

namespace Rede
{
    class ParserDePacotes
    {
    public:
        ParserDePacotes();

        ~ParserDePacotes();

        PacoteBase*
        parseiaPacote( const QString _pacote ) const;

        PacoteInit*
        parseiaInit( const QString _pacote ) const;
    };
}

#endif // PARSERDEPACOTES_H
