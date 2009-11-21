#ifndef GERENCIADORCONEXAO_H
#define GERENCIADORCONEXAO_H

#include <QObject>

#include "lib/conexao.h"
#include "lib/ouvinte.h"

namespace Rede
{
    class GerenciadorConexao : public QObject
    {
        Rede::Ouvinte*
        Ouvinte;

    public:
        GerenciadorConexao();

        virtual
        ~GerenciadorConexao();


    };
}

#endif // GERENCIADORCONEXAO_H
