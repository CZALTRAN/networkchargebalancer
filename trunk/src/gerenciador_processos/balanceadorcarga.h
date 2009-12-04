#ifndef BALANCEADORCARGA_H
#define BALANCEADORCARGA_H

#include <QObject>
#include <QQueue>
#include <QHash>
#include <QHashIterator>

#include "structpacotes.h"
#include "gppeer.h"
#include "processo.h"

namespace GP
{
    class BalanceadorCarga : public QObject
    {
    Q_OBJECT

    private:
        QHash<const int, const Peer*>
        peers;

        int
        qtde_peers;

        QHashIterator<const int, const Peer*>*
        peer_round_robin;

    public:
        BalanceadorCarga(QObject *parent = 0);

        ~BalanceadorCarga();

        void
        peerCaiu( const int& _id );

        void
        peerNovo( const int& _id );

        void
        incommingMessage( const int& _id, const PacoteBase& _pacote );

        int
        getPeerHost();

    public slots:
//        void
//        novoProcesso( const int& _id_peer, const Processo& _processo );

    signals:
        //sinais para comunicação externa
        void
        sendMessage( const int& _id_destino, const QString& _message );

        //sinais para comunicação interna
    };
}

#endif // BALANCEADORCARGA_H
