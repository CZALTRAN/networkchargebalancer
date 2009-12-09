#include "testegp.h"

#include <QDebug>

TesteGP::TesteGP()
{
    QObject::connect( &this->gerenciador, SIGNAL( stdOut(Q_PID, int, QString)),
                      this, SLOT(stdOut(Q_PID,int,QString)));

    QObject::connect( &this->gerenciador, SIGNAL(resultadoProcessoStart(int, QString, Q_PID)),
                      this, SLOT(resultadoProcessoStart(int, QString, Q_PID)));

    QObject::connect( &this->gerenciador, SIGNAL(sendMessage(int, QString)),
                      this, SLOT(saidaDeMensagensGP(int, QString)));
}

TesteGP::~TesteGP()
{
}

void
TesteGP::stdOut(Q_PID _pid, int _num_requisicao, QString _saida){
    qDebug() << Q_FUNC_INFO << _saida.toStdString().c_str();
}

void
TesteGP::resultadoProcessoStart(int _num_requisicao, QString _processo, Q_PID _pid)
{
    qDebug() << Q_FUNC_INFO << _pid;

    this->gerenciador.stdIn(_pid, _num_requisicao, "p");
    this->gerenciador.stdIn(_pid, _num_requisicao, "v");
    this->gerenciador.stdIn(_pid, _num_requisicao, "b");
}


void
TesteGP::saidaDeMensagensGP(int _id, QString _mensagem)
{
    Q_UNUSED(_id)
    qDebug() << Q_FUNC_INFO << _mensagem;

    QStringList
    campos = _mensagem.split(";");

    _mensagem = campos.join("");

    campos = _mensagem.split(":");

    if( campos[2] == "SUCCESS_START_PROCESS" )
    {
        this->pid= campos[4];
        this->num_requisicao = campos[3];

        qDebug() << Q_FUNC_INFO << this->pid;

        this->gerenciador.incommingMessage(6, "GP:PROCESSO:STANDARD_INPUT:" + this->pid + ":" + this->num_requisicao + ":" + "p:");
        this->gerenciador.incommingMessage(6, "GP:PROCESSO:STANDARD_INPUT:" + this->pid + ":" + this->num_requisicao + ":" + "v:");
        this->gerenciador.incommingMessage(6, "GP:PROCESSO:STANDARD_INPUT:" + this->pid + ":" + this->num_requisicao + ":" + "b:");

    }
}
