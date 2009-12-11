#include "xbsh.h"

#include <QDebug>


XBSh::XBSh(QObject *_parent)
    : QObject(_parent)
{
    this->stdin = new StandardInput(this);
    this->gerenciador_lancamento = new GerenciadorLancamento(this);

    QObject::connect( this->stdin, SIGNAL(entrada(QString)),
                      this, SLOT(recebeEntrada(QString)),
                      Qt::DirectConnection);

    QObject::connect( this->gerenciador_lancamento, SIGNAL(recebiEntrada(QString)),
                      this, SLOT(recebeEntrada(QString)));

    QObject::connect( this->gerenciador_lancamento, SIGNAL(endStdOut(QString)),
                      this,SLOT(displayStdOut(QString)));

    this->displayBoasVindas();
    this->stdin->start();
}

XBSh::~XBSh()
{

}

void
XBSh::recebeEntrada( QString _input )
{
    this->gerenciador_lancamento->processaEntrada( _input );

    if (! this->gerenciador_lancamento->is_processo_rodando )
    {
        this->displayPS1();
    }
}

void
XBSh::displayStdOut( QString _mensagem )
{
    qDebug(_mensagem.toAscii());
}

void
XBSh::terminated( int _return_code )
{
    //todo
    this->displayPS1();
}

void
XBSh::displayBoasVindas()
{
    std::cout << "********** Bem vindo ao XBoga SHell **********" << std::endl
              << "UNIVERSIDADE ESTADUAL DE LONDRINA" << std::endl
              << "DEPARTAMENTO DE COMPUTACAO" << std::endl
              << "SISTEMAS OPERACIONAIS" << std::endl;
    this->displayPS1();
}

void
XBSh::displayPS1()
{
    std::cout << "[ XBoga SHell ] -> ";
}
