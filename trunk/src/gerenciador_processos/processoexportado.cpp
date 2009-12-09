#include "processoexportado.h"

#include "gpconstrutordepacotes.h"

GP::ProcessoExportado::ProcessoExportado()
{
}

void
GP::ProcessoExportado::stdIn(const QString& _entrada)
{
    QString
    pacote_std_in = GP::ConstrutorDePacotes::getInstance().montaStdIn(
                                                           this->pid,
                                                           this->num_requisicao,
                                                           _entrada);
    //parei aquii
}
