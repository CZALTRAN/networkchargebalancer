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

        QString
        pid;

        QString
        num_requisicao;

    public slots:
        void
        stdOut(Q_PID _pid, int _num_requisicao, QString _saida);

        void
        resultadoProcessoStart(int _num_requisicao, QString _processo, Q_PID _pid);

        void
        saidaDeMensagensGP(int _id, QString _mensagem);
};

#endif // TESTEGP_H
