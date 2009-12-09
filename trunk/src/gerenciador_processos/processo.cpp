#include "processo.h"

GP::Processo::Processo( QObject* _parent )
    : QObject(_parent)
{
}

GP::Processo::~Processo()
{

}

Q_PID
GP::Processo::getPid()
{
    return this->pid;
}

QString
GP::Processo::getNome()
{
    return this->nome;
}

int
GP::Processo::getIdDono()
{
    return this->id_dono;
}

int
GP::Processo::getIdHost()
{
    return this->id_host;
}

int
GP::Processo::getNumRequisicao()
{
    return this->num_requisicao;
}

void
GP::Processo::setPid( const Q_PID& _pid )
{
    this->pid = _pid;
}

void
GP::Processo::setNome(const QString& _nome)
{
    this->nome = _nome;
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

void
GP::Processo::setIdHost( const int& _id_host )
{
    this->id_host = _id_host;
}

