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
        parseiaInit( const QStringList& _pacote ) const;

        PacoteNovoPeer*
        parseiaNovoPeer( const QStringList& _pacote ) const;

        PacoteInformaServer*
        parseiaInformaServer( const QStringList& _pacote ) const;

        Rede::PacoteMeuId*
        parseiaMeuId( const QStringList& _lista_parametros ) const;

        Rede::PacoteGP*
        parseiaGP( const QStringList& _lista_parametros ) const;

        void
        setaInteiroDePacote( const QStringList& _pacote,
                             int _posicao,
                             int& _campo) const;
    };
}

#endif // PARSERDEPACOTES_H
