#include "processo.h"

GP::Processo::Processo()
{
}

GP::Processo::Processo( const GP::Processo& _processo )
{
    this->id_dono = _processo.id_dono;
    this->pid = _processo.pid;
}

GP::Processo::~Processo()
{

}

Q_PID
GP::Processo::getPid()
{
    return this->pid;
}

int
GP::Processo::getIdDono()
{
    return this->id_dono;
}
