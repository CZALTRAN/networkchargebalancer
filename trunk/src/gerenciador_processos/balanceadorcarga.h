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

    QHash<const int, const GP::Peer*>
    peers;

    int
    qtde_peers;

    QHashIterator<const int, const GP::Peer*>*
    peer_round_robin;

    public:
        BalanceadorCarga(QObject *parent = 0);

        ~BalanceadorCarga();

        void
        peerCaiu( const int& );

        void
        peerNovo( const int& );

    public slots:
        void
        incommingMessage( const int& _id, const GP::PacoteBase& _pacote );

        void
        enviaPeerHost(int* _id);

        void
        novoProcesso( const int& _id_peer, const Processo& _processo );

    signals:
        void
        sendMessage( const int& _id_destino, const QString& _message );

    private:
        int
        selecionaPeer();

    };
}

#endif // BALANCEADORCARGA_H
