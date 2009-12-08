#ifndef GPSTRUCTPACOTES_H
#define GPSTRUCTPACOTES_H

#include <QString>
#include <QStringList>
#include <QProcess>

namespace GP
{
    enum DonoPacote
    {
        GP,
        BALANCER,
        LAUNCHER
    };

    enum TipoPacote
    {
        START_PROCESS,
        FAIL_START_PROCESS,
        SUCCESS_START_PROCESS,
        STATUS_PEER
    };

    typedef struct PacoteBase
    {
        GP::TipoPacote
        nome;

        GP::DonoPacote
        dono;

    } PacoteBase;

    typedef struct PacoteStartProcess : public PacoteBase
    {
        int
        num_requisicao;

        QString
        processo;

        QStringList
        parametros;

    } PacoteStartProcess;

    typedef struct PacoteSuccessStartProcess : public PacoteBase
    {
        int
        num_requisicao;

        QString
        processo;

        Q_PID
        pid;

    } PacoteSuccessStartProcess;

    typedef struct PacoteFailStartProcess : public PacoteBase
    {
        int
        num_requisicao;

        QString
        processo;

        QStringList
        parametros;

    } PacoteFailStartProcess;

    typedef struct PacoteStatusPeer : public PacoteBase
    {
        int
        qtde_processos;

        int
        qtde_processos_permitidos;

    } PacoteStatusPeer;
}

#endif // STRUCTPACOTES_H