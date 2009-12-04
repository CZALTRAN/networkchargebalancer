#include "processo.h"

GP::Processo::Processo(QObject* _parent)
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

int
GP::Processo::getIdDono()
{
    return this->id_dono;
}

QString
GP::Processo::stdOutAndErr()
{

}
