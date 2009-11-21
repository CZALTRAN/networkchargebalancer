#include "gerenciadorconexao.h"

Rede::GerenciadorConexao::GerenciadorConexao()
{

}


Rede::GerenciadorConexao::~GerenciadorConexao()
{


}

void
Rede::GerenciadorConexao::novaConexao( int _socket_descriptor)
{
    qDebug() << "teste";
    Q_UNUSED(_socket_descriptor);
}
