#include "standardinput.h"

#include <iostream>
#include <QDebug>

#include "gerenciadorlancamento.h"

StandardInput::StandardInput( GerenciadorLancamento* _parent )
    : QThread(_parent)
{
}

void
StandardInput::run()
{

//    qDebug() << Q_FUNC_INFO << this->thread();

    char
    input_str[20000];

    QString
    input;

    forever
    {
        GerenciadorLancamento*
        pai = dynamic_cast<GerenciadorLancamento*>(this->parent());

//        if (! pai->is_processo_rodando )
//        {
//            std::cout << "[ XBoga SHell ] -> ";
//        }
        std::cin.getline(input_str, 20000);
        input = input_str;


        emit this->entrada(input);
    }
}
