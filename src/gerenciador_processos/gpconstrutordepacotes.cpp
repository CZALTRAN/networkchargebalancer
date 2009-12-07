#include "gpconstrutordepacotes.h"

#include "structpacotes.h"

GP::ConstrutorDePacotes::ConstrutorDePacotes()
{
}

GP::ConstrutorDePacotes&
GP::ConstrutorDePacotes::getInstance()
{
    static GP::ConstrutorDePacotes
    instance;

    return instance;
}

QString
GP::ConstrutorDePacotes::montaStartProcess( const int& _num_requisicao,
                                            const QString& _processo,
                                            const QStringList _parametros )
{
    QString
    pacote = "GP" + SEPARADOR_DE_CAMPO;
    pacote += "LAUNCHER" + SEPARADOR_DE_CAMPO;
    pacote += "START_PROCESS" + SEPARADOR_DE_CAMPO;
    pacote += QString::number(_num_requisicao) + SEPARADOR_DE_CAMPO;
    pacote += _processo + SEPARADOR_DE_CAMPO;
    pacote += _parametros.join(SEPARADOR_DE_CAMPO);

    return pacote;
}

QString
GP::ConstrutorDePacotes::montaSuccessStartProcess( const int& _num_requisicao,
                                                   const QString& _processo,
                                                   const Q_PID& _pid )
{

}

QString
GP::ConstrutorDePacotes::montaFailStartProcess( const int& _num_requisicao,
                                                const QString& _processo,
                                                const QStringList& _parametros )
{

}

QString
GP::ConstrutorDePacotes::montaStatusPeer( const int& _qtde_processos,
                                          const int& _qtde_processos_permitidos)
{
    QString
    pacote = "GP" + SEPARADOR_DE_CAMPO;
    pacote += "BALANCER" + SEPARADOR_DE_CAMPO;
    pacote += "STATUS_PEER" + SEPARADOR_DE_CAMPO;
    pacote += QString::number(_qtde_processos ) + SEPARADOR_DE_CAMPO;
    pacote += QString::number(_qtde_processos_permitidos) + SEPARADOR_DE_CAMPO;

    return pacote;
}
