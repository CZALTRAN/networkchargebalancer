#include "processo.h"

GP::Processo::Processo( QObject* _parent )
    : QObject(_parent)
{
}

GP::Processo::~Processo()
{

}

int
GP::Processo::getIdDono()
{
    return this->id_dono;
}

int
GP::Processo::getNumRequisicao()
{
    return this->num_requisicao;
}

void
GP::Processo::setIdDono( const int& _id_dono )
{
    this->id_dono = _id_dono;
}

void
GP::Processo::setNumRequisicao( const int& _num_requisicao )
{
    this->num_requisicao = _num_requisicao;
}
