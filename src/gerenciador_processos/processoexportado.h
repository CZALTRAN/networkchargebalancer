#ifndef PROCESSOEXPORTADO_H
#define PROCESSOEXPORTADO_H

#include "processo.h"

#include <QProcess>

namespace GP
{
    class ProcessoExportado : public Processo
    {
    Q_OBJECT

        int
        id_host;

    public:
        ProcessoExportado();

        ProcessoExportado( Q_PID _pid, int _id_host );

        int
        getIdHost();

        void
        setIdHost( const int& _id_host );

        void
        stdIn(const QString& _entrada);

    };
}

#endif // PROCESSOEXPORTADO_H
