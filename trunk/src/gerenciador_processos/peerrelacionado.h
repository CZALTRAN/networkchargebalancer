//////////////////////
/********************/
/* Esta classe não  */
/* será mais usada! */
/* (por enquanto)   */
/********************/
//////////////////////

#ifndef PEERRELACIONADO_H
#define PEERRELACIONADO_H

#include "peer.h"

#include <QHash>
#include <QProcess>
#include <QObject>

#include "processo.h"

namespace GP
{
    class PeerRelacionado : public Peer, public QObject
    {
    Q_OBJECT

    private:
        QHash<const Q_PID&,const Processo*>
        processos;

    public:
        PeerRelacionado(QObject* _parent);

        const Processo*
        getProcesso(const Q_PID& _pid);

        void
        insereProcesso(const Q_PID& _pid, const Processo* _processo);

    };
}

#endif // PEERRELACIONADO_H
