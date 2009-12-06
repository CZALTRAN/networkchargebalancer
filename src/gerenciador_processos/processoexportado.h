#ifndef PROCESSOEXPORTADO_H
#define PROCESSOEXPORTADO_H

#include "processo.h"

#include <QProcess>

namespace GP
{
    class ProcessoExportado : public Processo
    {
    Q_OBJECT

        Q_PID
        pid;

        int
        id_host;

    public:
        ProcessoExportado();

        Q_PID
        getPid();

        int
        getIdHost();

        void
        setPid( const Q_PID& _pid );

        void
        setIdHost( const int& _id_host );

        void
        stdIn(const QString& _entrada);

    };
}

#endif // PROCESSOEXPORTADO_H
