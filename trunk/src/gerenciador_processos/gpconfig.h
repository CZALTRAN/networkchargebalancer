#ifndef PROCESSOSCONFIG_H
#define PROCESSOSCONFIG_H

#include <QHash>
#include <QPair>
#include <QProcess>
#include <QStringList>

#include "processo.h"

namespace GP
{
    class GPConfig
    {
        int
        meu_id;


    public:
        int
        getMeuId();

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
