#ifndef GPPARSERDEPACOTES_H
#define GPPARSERDEPACOTES_H

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

        //PACOTES DO LAUNCHER
        PacoteStartProcess*
        parseiaStartProcess( const QStringList& _lista_parametros ) const;

        PacoteSuccessStartProcess*
        parseiaSuccessStartProcess( const QStringList& _lista_parametros ) const;

        PacoteFailStartProcess*
        parseiaFailStartProcess( const QStringList& _lista_parametros ) const;

        //PACOTES DO BALANCER
        PacoteStatusPeer*
        parseiaPacoteStatusPeer( const QStringList& _lista_parametros ) const;

        //PACOTES DE PROCESSO
        PacoteStdIn*
        parseiaStdIn( const QStringList& _lista_parametros ) const;

        PacoteStdOut*
        parseiaStdOut( const QStringList& _lista_parametros ) const;

        //LOGICA INTERNA
        void
        setaInteiroDePacote( const QStringList& _pacote, int _posicao,
                                                         int& campo) const;

        void
        setaInt64DePacote( const QStringList& _pacote, int _posicao,
                                                         qint64& campo) const;
    };
}

#endif // PARSERDEPACOTES_H
