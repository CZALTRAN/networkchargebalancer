#ifndef APLICACAO_H
#define APLICACAO_H

#include <QString>

namespace GP
{
    class Aplicacao
    {
    private:
        QString
        nome;

        QString
        diretorio;

        bool
        x11;

    public:
        Aplicacao();

        Aplicacao( const QString& _nome, const QString& _diretorio, const bool& _x11 );

        QString
        getNome();

        QString
        getDiretorio();

        bool
        usaX11();

        void
        setNome( const QString& _nome );

        void
        setDiretorio( const QString& _diretorio );

        void
        setUsaX11( bool _usa_x11 );
    };
}

#endif // APLICACAO_H
