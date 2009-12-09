#include "testegp.h"

#include <QDebug>

TesteGP::TesteGP()
{
    QObject::connect( &this->gerenciador, SIGNAL( stdOut(Q_PID, int, QString)),
                      this, SLOT(stdOut(Q_PID,int,QString)));
}

TesteGP::~TesteGP()
{
}

void
TesteGP::stdOut(Q_PID _pid, int _num_requisicao, QString _saida){
    qDebug() << Q_FUNC_INFO << _saida.toStdString().c_str();
}
