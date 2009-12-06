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

        QHash<QString,const Aplicacao*>
        aplicacoes;

    public:
        int
        getMeuId();

        Aplicacao*
        getAplicacao(const QString& _nome);

        bool
        getPossuiAplicacao(const QString& _nome);

        void
        setMeuId(const int& _meu_id);

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
