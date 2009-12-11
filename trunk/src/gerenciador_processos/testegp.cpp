#include "testegp.h"

#include <QDebug>

TesteGP::TesteGP()
{
    QObject::connect( &this->gerenciador, SIGNAL( stdOut(qint64, int, QString)),
                      this, SLOT(stdOut(qint64,int,QString)));

    QObject::connect( &this->gerenciador, SIGNAL(resultadoProcessoStart(int,
                                                                        QString,
                                                                        qint64)),
                      this, SLOT(resultadoProcessoStart(int, QString, qint64)));

    QObject::connect( &this->gerenciador, SIGNAL(sendMessage(int, QString)),
                      this, SLOT(saidaDeMensagensGP(int, QString)));

    QObject::connect( &this->gerenciador, SIGNAL(terminoDeProcesso(qint64,
                                                                   int,
                                                                   int)),
                      this, SLOT(terminoDeProcesso(qint64,
                                                   int,
                                                   int)));
}

TesteGP::~TesteGP()
{
}

void
TesteGP::stdOut(qint64 _pid, int _num_requisicao, QString _saida){
    Q_UNUSED(_pid)
    Q_UNUSED(_num_requisicao)
    qDebug() << Q_FUNC_INFO << _saida.toStdString().c_str();
}

void
TesteGP::resultadoProcessoStart(int _num_requisicao,
                                QString _processo,
                                qint64 _pid)
{
    Q_UNUSED(_processo)
    qDebug() << Q_FUNC_INFO << _pid;
    qDebug() << Q_FUNC_INFO << _num_requisicao;

//    this->gerenciador.stdIn(_pid, _num_requisicao, "p");
//    this->gerenciador.stdIn(_pid, _num_requisicao, "v");
//    this->gerenciador.stdIn(_pid, _num_requisicao, "b");

//    this->gerenciador.incommingMessage(6, "GP:CONTROL:PROCESS_KILLED:" + QString::number(_pid) + ":" + QString::number(_num_requisicao) + ":");
    this->gerenciador.incommingMessage(6, "GP:PROCESSO:STANDARD_OUTPUT:" + QString::number(_pid) + ":" + QString::number(_num_requisicao) + ":" + "merda1!" );
    this->gerenciador.incommingMessage(6, "GP:PROCESSO:STANDARD_OUTPUT:" + QString::number(_pid) + ":" + QString::number(_num_requisicao) + ":" + "merda2!" );
    this->gerenciador.incommingMessage(6, "GP:PROCESSO:STANDARD_OUTPUT:" + QString::number(_pid) + ":" + QString::number(_num_requisicao) + ":" + "merda3!" );

//    this->gerenciador.mataProcesso( _pid, 5, _num_requisicao);
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
        bool sucesso_ao_converter;

        this->num_requisicao = campos[3].toInt( &sucesso_ao_converter, 10 );
        if( sucesso_ao_converter == false )
        {
            qDebug() << Q_FUNC_INFO << "Ocorreu um erro ao converter.";
            exit(1);
        }

        this->pid = campos[4].toLongLong( &sucesso_ao_converter, 10 ) ;
        if( sucesso_ao_converter == false )
        {
            qDebug() << Q_FUNC_INFO << "Ocorreu um erro ao converter.";
            exit(1);
        }

        qDebug() << Q_FUNC_INFO << this->pid;

//        this->gerenciador.incommingMessage(6, "GP:PROCESSO:STANDARD_INPUT:" + QString::number(this->pid) + ":" + QString::number(this->num_requisicao) + ":" + "p:");
//        this->gerenciador.incommingMessage(6, "GP:PROCESSO:STANDARD_INPUT:" + QString::number(this->pid) + ":" + QString::number(this->num_requisicao) + ":" + "v:");
//        this->gerenciador.incommingMessage(6, "GP:PROCESSO:STANDARD_INPUT:" + QString::number(this->pid) + ":" + QString::number(this->num_requisicao) + ":" + "b:");

//        qint64
//        pid = static_cast<qint64>(this->pid);
//        this->gerenciador.mataProcesso( pid, 6, this->num_requisicao);

//        this->gerenciador.incommingMessage(6, "GP:CONTROL:KILL_PROCESS:" + QString::number(this->pid) + ":" + QString::number(this->num_requisicao) + ":");
    }
    else if( campos[2] == "PROCESS_KILLED" )
    {
        qDebug() << Q_FUNC_INFO << _mensagem;
    }
    else if( campos[2] == "STANDARD_OUTPUT" )
    {
//        qDebug() << Q_FUNC_INFO << _mensagem;
    }
    else if( campos[2] == "START_PROCESS" )
    {
//        this->gerenciador.incommingMessage(6, "GP:LAUNCHER:SUCCESS_START_PROCESS:14:123:pikaloka:");
    }
}

void
TesteGP::terminoDeProcesso( qint64 _pid, int num_requisicao, int _motivo )
{
    qDebug() << Q_FUNC_INFO << "Processo terminou: " << _pid
                                                     << num_requisicao
                                                     << _motivo;
}
