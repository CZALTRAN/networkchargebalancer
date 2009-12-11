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

        Q_PID
        pid;

        int
        num_requisicao;

    public slots:
        void
        stdOut(qint64 _pid, int _num_requisicao, QString _saida);

        void
        resultadoProcessoStart(int _num_requisicao, QString _processo, qint64 _pid);

        void
        saidaDeMensagensGP(int _id, QString _mensagem);

        void
        terminoDeProcesso( qint64 _pid, int num_requisicao,
                                       int _motivo );
};

#endif // TESTEGP_H
