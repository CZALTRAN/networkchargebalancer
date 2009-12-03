#ifndef BALANCEADORCARGA_H
#define BALANCEADORCARGA_H

#include <QObject>
#include <QQueue>

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

    private:

    };
}

#endif // BALANCEADORCARGA_H
