#ifndef TESTEGP_H
#define TESTEGP_H

#include <QObject>
#include <QProcess>
#include <QString>

#include "gerenciadorprocessos.h"

class TesteGP : public QObject
{
    Q_OBJECT
    public:
        TesteGP();

        virtual
        ~TesteGP();

        GerenciadorProcessos
        gerenciador;

    public slots:
        void
        stdOut(Q_PID _pid, int _num_requisicao, QString _saida);
};

#endif // TESTEGP_H
