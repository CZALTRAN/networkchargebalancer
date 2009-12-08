#ifndef BALANCEADORCARGA_H
#define BALANCEADORCARGA_H

#include <QObject>
#include <QQueue>
#include <QHash>
#include <QMutableHashIterator>

#include "structpacotes.h"
#include "gppeer.h"
#include "processo.h"

#define NUM_MAX_PROCESSOS 3

namespace GP
{
    class BalanceadorCarga : public QObject
    {
    Q_OBJECT

        QHash<int, Peer*>
        peers;

        int
        qtde_peers;

        QHash<int, Peer*>::iterator
        peer_round_robin;

    public:
        BalanceadorCarga(QObject *parent = 0);

        ~BalanceadorCarga();

        void
        peerCaiu( const int& _id );

        void
        peerNovo( const int& _id );

        void
        incommingMessage( const int& _id, const PacoteBase* _pacote );

        void
        insereCarga( const int& _id );

        int
        getPeerHost();

        void
        setStatusPeer( const int _id, const PacoteStatusPeer* _pacote );

        bool
        getPermissaoProcessar();

    public slots:

    signals:
        //sinais para comunicação interna
        void
        sendMessage( int _id_destino, QString _message );

    private:
        void
        avancaPeerRR();

        void
        avancaPeerAtual();
    };
}

#endif // BALANCEADORCARGA_H
