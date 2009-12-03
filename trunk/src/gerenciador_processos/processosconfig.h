#ifndef PROCESSOSCONFIG_H
#define PROCESSOSCONFIG_H

#include <QHash>
#include <QPair>
#include <QProcess>
#include "processo.h"

namespace GP
{
    class ProcessosConfig
    {
        QHash< const QPair< Q_PID, int >&, Processo >
        processos;

    public:

        void
        insereProcesso( Processo& _processo );

        Processo
        getProcesso( Q_PID _pid, int _id_dono );

        static ProcessosConfig&
        getInstance();

    private:

        static GP::ProcessosConfig
        instance;

        ProcessosConfig();

        ProcessosConfig( ProcessosConfig const& );

        GP::ProcessosConfig&
        operator= ( GP::ProcessosConfig const& );

    };
}
#endif // PROCESSOSCONFIG_H
