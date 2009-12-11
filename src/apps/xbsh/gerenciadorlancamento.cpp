#include "gerenciadorlancamento.h"

#include <iostream>

#include <QDebug>

#include "ps/ps.h"
#include "kill/kill.h"

GerenciadorLancamento::GerenciadorLancamento(QObject *parent) :
    QObject(parent)
{

    qDebug() << Q_FUNC_INFO << this->thread();

    this->is_processo_rodando = false;
    this->gp_interface = new GPInterface(this);

    QObject::connect( this->gp_interface, SIGNAL(resultStartProcesso(int,QString,qint64)),
                      this,SLOT(resultProcessoStart(int,QString,qint64)));

    QObject::connect( this->gp_interface, SIGNAL(standardOutput(int,int,QString)),
                      this,SLOT(startStdOut(int,int,QString)));
    
    QObject::connect( this->gp_interface, SIGNAL(processoTerminado(int,int,int)),
                      this,SLOT(processoNaoNativoTerminado(int,int,int)));
}

void
GerenciadorLancamento::processaEntrada( const QString& _entrada )
{
    if ( this->is_processo_rodando )
    {
        this->gp_interface->slotStandardInput(this->pid_processo_rodando,
                                              this->registro_processo_rodando,
                                              _entrada);
    }
    else
    {
        this->is_processo_rodando = true;
        QStringList
        argumentos = _entrada.split(' ');

        QString
        nome_processo = argumentos[0];

        argumentos.pop_front();

        if ( this->isProcessoNativo( nome_processo ) )
        {
            this->startProcessoNativo( nome_processo, argumentos );
        }
        else
        {
            this->registro_processo_rodando =
                this->gp_interface->startProcesso(nome_processo,argumentos.join(" ") );
        }
    }
}

void
GerenciadorLancamento::resultProcessoStart( int _id_requisicao,
                                            QString _processo,
                                            qint64 _pid )
{
    if ( _pid > 0 && _id_requisicao == this->registro_processo_rodando )
    {
        this->is_processo_rodando = true;
        this->pid_processo_rodando = _pid;

    }
    else if ( _pid == 0 && _id_requisicao == this->registro_processo_rodando )
    {
        this->is_processo_rodando = false;
        emit this->falhaAoStartProcesso("Erro ao iniciar o processo " + _processo );
    }
}

void
GerenciadorLancamento::startStdOut(  int _processo,
                                     int _registro,
                                     QString _mensagem )
{
    if ( this->registro_processo_rodando == _registro &&
         this->pid_processo_rodando == _processo)
    {
        emit this->endStdOut(_mensagem);
    }
}

void
GerenciadorLancamento::processoNativoTerminado()
{
    ProcessoNativoPai*
    processo_terminado = dynamic_cast<ProcessoNativoPai*>(this->sender());

    if ( processo_terminado != 0 )
    {
        int
        return_code = processo_terminado->return_code;

        emit this->processoTerminado(return_code);
    }
    else
    {
        //nao deveria estar aqui
    }
    this->is_processo_rodando = false;
}

void
GerenciadorLancamento::processoNaoNativoTerminado(int _processo,
                                                  int _registro,
                                                  int _retorno)
{
    if ( this->pid_processo_rodando == _processo &&
         this->registro_processo_rodando == _registro )
    {
        this->is_processo_rodando = false;
        emit this->processoTerminado( _retorno );
    }
}

bool
GerenciadorLancamento::isProcessoNativo( const QString& _processo_nome )
{
    if ( _processo_nome == "ps" ||
         _processo_nome == "kill" ||
         _processo_nome == "exit" )
        return true;
    return false;
}

void
GerenciadorLancamento::startProcessoNativo( const QString& _processo_nome,
                                            const QStringList& _argumentos )
{
    ProcessoNativoPai*
    processo_nativo;

    if ( _processo_nome == "ps")
    {
        processo_nativo = new Ps(_argumentos, 0);
    }
    else if ( _processo_nome == "kill")
    {
        processo_nativo = new Kill(_argumentos, 0);
    }
    else if ( _processo_nome == "exit" )
    {
        exit(0);
    }

    QObject::connect( processo_nativo, SIGNAL(finished()),
                      this,SLOT(processoNativoTerminado()));

    QObject::connect( processo_nativo, SIGNAL(terminated()),
                      this,SLOT(processoNativoTerminado()));

    processo_nativo->start();
}
