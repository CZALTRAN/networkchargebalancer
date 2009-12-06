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
        getPeerHost() const;

    public slots:

    signals:
        //sinais para comunicação interna
        void
        sendMessage( int _id_destino, QString _message );

    };
}

#endif // BALANCEADORCARGA_H
