#include "gppeer.h"

GP::Peer::Peer()
{
    this->possui_relacao = false;
    this->qtde_processos = 0;
    this->qtde_processos_permitidos = 0;
}

GP::Peer::Peer( const int& _id, const bool& _possui_relacao,
                                const int& _qtde_processos,
                                const int& _qtde_processos_permitidos )
{
    this->id = _id;
    this->possui_relacao = _possui_relacao;
    this->qtde_processos = _qtde_processos;
    this->qtde_processos_permitidos = _qtde_processos_permitidos;
}

GP::Peer::~Peer()
{

}

void
GP::Peer::setId( const int& _id )
{
    this->id = _id;
}

void
GP::Peer::setPossuiRelacao( const bool& _possui_relacao)
{
    this->possui_relacao = _possui_relacao;
}

void
GP::Peer::setQtdeProcessos( const int& _qtde_processos)
{
    this->qtde_processos = _qtde_processos;
}

void
GP::Peer::setQtdeProcessosPermitidos(const int& _qtde_processos)
{
    this->qtde_processos_permitidos = _qtde_processos;
}

int
GP::Peer::getId()
{
    return this->id;
}

bool
GP::Peer::getPossuiRelacao()
{
    return this->possui_relacao;
}

int
GP::Peer::getQtdeProcessos()
{
    return this->qtde_processos;
}

int
GP::Peer::getQtdeProcessosPermitidos()
{
    return this->qtde_processos_permitidos;
}
