#ifndef PROCESSOLOCALOUIMPORTADO_H
#define PROCESSOLOCALOUIMPORTADO_H

#include <QProcess>
#include <QObject>

#include "processo.h"

namespace GP
{
    class ProcessoLocalOuImportado : public Processo
    {
    Q_OBJECT

    private:
        QProcess*
        processo;

    public:
        ProcessoLocalOuImportado(QObject* _parent = 0);

        virtual
        ~ProcessoLocalOuImportado();

        void
        start(const QString& _processo, const QStringList& _parametros);

        bool
        waitForStarted(int _tempo = 30000);

        void
        stdIn(const QString& _entrada);
   };
}

#endif // PROCESSOLOCALOUIMPORTADO_H
