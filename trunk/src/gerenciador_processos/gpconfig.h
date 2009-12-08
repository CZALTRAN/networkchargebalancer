#ifndef PROCESSOSCONFIG_H
#define PROCESSOSCONFIG_H

#include <QHash>

#include "aplicacao.h"

namespace GP
{
    class GPConfig
    {
        int
        meu_id;

        int
        qtde_processos;

        int
        qtde_processos_permitidos;

        QHash<QString,const Aplicacao*>
        aplicacoes;

    public:
        int
        getMeuId();

        int
        getQtdeProcessos();

        int
        getQtdeProcessosPermitidos();

        Aplicacao*
        getAplicacao(const QString& _nome);

        bool
        getPossuiAplicacao(const QString& _nome);

        void
        setMeuId(const int& _meu_id);

        void
        setQtdeProcessos( const int& _qtde );

        void
        setQtdeProcessosPermitidos( const int& _qtde );

        static GPConfig&
        getInstance();

    private:

        static GP::GPConfig
        instance;

        GPConfig();

        GPConfig( GPConfig const& );

        GP::GPConfig&
        operator= ( GP::GPConfig const& );

    };
}
#endif // PROCESSOSCONFIG_H
