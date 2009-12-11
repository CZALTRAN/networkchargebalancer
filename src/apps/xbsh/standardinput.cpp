#include "standardinput.h"

#include <iostream>
#include <QDebug>

StandardInput::StandardInput( QObject* _parent )
    : QThread(_parent)
{
}

void
StandardInput::run()
{

    qDebug() << Q_FUNC_INFO << this->thread();

    char
    input_str[20000];

    QString
    input;

    forever
    {
        std::cin.getline(input_str, 20000);
        input = input_str;
        emit this->entrada(input);
    }
}
