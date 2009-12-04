#ifndef PROCESSOLOCALOUIMPORTADO_H
#define PROCESSOLOCALOUIMPORTADO_H

#include <QProcess>
#include <QObject>

#include "processo.h"

namespace GP
{
    class ProcessoLocalOuImportado : public QProcess, public Processo
    {
    public:
        ProcessoLocalOuImportado(const QObject& _parent);

        ProcessoLocalOuImportado( const QProcess& _processo );

        virtual
        ~ProcessoLocalOuImportado();
   };
}

#endif // PROCESSOLOCALOUIMPORTADO_H
