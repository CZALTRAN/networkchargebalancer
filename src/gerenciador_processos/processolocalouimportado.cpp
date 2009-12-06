#include "processolocalouimportado.h"

GP::ProcessoLocalOuImportado::ProcessoLocalOuImportado(QObject* _parent)
    : GP::Processo(_parent)
{

}

GP::ProcessoLocalOuImportado::~ProcessoLocalOuImportado()
{

}

void
GP::ProcessoLocalOuImportado::start(const QString& _processo, const QStringList& _parametros)
{
    this->processo = new QProcess(this);

    this->processo->start(_processo, _parametros);
}

bool
GP::ProcessoLocalOuImportado::waitForStarted(int _tempo)
{
    return this->processo->waitForStarted(_tempo);
}

void
GP::ProcessoLocalOuImportado::stdIn(const QString& _entrada)
{

}
