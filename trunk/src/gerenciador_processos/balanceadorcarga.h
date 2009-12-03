#ifndef BALANCEADORCARGA_H
#define BALANCEADORCARGA_H

#include <QObject>
#include <QQueue>

#include "structpacotes.h"

namespace GP
{
    class BalanceadorCarga : public QObject
    {
    Q_OBJECT
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

    signals:
        void
        sendMessage( const int& _id_destino, const QString& _message );

    private:

    };
}

#endif // BALANCEADORCARGA_H
