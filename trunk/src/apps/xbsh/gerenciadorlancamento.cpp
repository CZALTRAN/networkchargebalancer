#include "gerenciadorlancamento.h"

#include <iostream>

GerenciadorLancamento::GerenciadorLancamento(QObject *parent) :
    QObject(parent)
{
    this->processo_rodando = false;
    this->gp_interface = new GPInterface(this);

    QObject::connect( this->gp_interface, SIGNAL(resultStartProcesso(int,QString,qint64)),
                      this,SLOT(resultProcessoStart(int,QString,qint64)));
}

void
GerenciadorLancamento::processaEntrada( const QString& _entrada )
{
    if ( this->processo_rodando )
    {
        this->gp_interface->slotStandardInput(this->pid_processo_rodando,
                                              this->registro_processo_rodando,
                                              _entrada);
    }
    else
    {
        this->processo_rodando = true;
        QStringList
        tokens = _entrada.split(' ');

        QString
        nome_processo = tokens[0];

        tokens.pop_front();

        if ( this->isProcessoNativo( nome_processo ) )
        {
            //todo
        }
        else
        {
            this->registro_processo_rodando =
                this->gp_interface->startProcesso(nome_processo,tokens.join(" ") );
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
        this->processo_rodando = true;
        this->pid_processo_rodando = _pid;
    }
    else if ( _pid > 0 && _id_requisicao == this->registro_processo_rodando )
    {
        this->processo_rodando = false;
        emit this->falhaAoStartProcesso("Erro ao iniciar o processo " + _processo );
    }
}

void
GerenciadorLancamento::startStdOut(  qint64 _processo,
                                     int _registro,
                                     QString _mensagem )
{
    if ( this->registerUserData() == _registro &&
         this->pid_processo_rodando == _processo)
    {
        emit this->endStdOut(_mensagem);
    }
}

bool
GerenciadorLancamento::isProcessoNativo( const QString& _processo_nome )
{
    //todo
    return false;
}
