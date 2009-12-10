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

    if (! this->gerenciador_lancamento->processo_rodando )
    {
        this->displayPS1();
    }
}

void
XBSh::displayStdOut( QString _mensagem )
{
    std::cout << _mensagem.toStdString();
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
