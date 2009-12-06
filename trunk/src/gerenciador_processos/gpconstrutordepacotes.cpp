#include "gpconstrutordepacotes.h"

GP::ConstrutorDePacotes::ConstrutorDePacotes()
{
}

GP::ConstrutorDePacotes&
GP::ConstrutorDePacotes::getInstance()
{
    static GP::ConstrutorDePacotes
    instance;

    return instance;
}

QString
GP::ConstrutorDePacotes::montaStartProcess( const int& _num_requisicao,
                                            const int& _id_dono,
                                            const QString& _processo,
                                            const QStringList _parametros )
{

}

QString
GP::ConstrutorDePacotes::montaSuccessStartProcess( const int& _num_requisicao,
                                                   const QString& _processo,
                                                   const Q_PID& _pid )
{

}

QString
GP::ConstrutorDePacotes::montaFailStartProcess( const int& _num_requisicao,
                                                const QString& _processo )
{

}

QString
GP::ConstrutorDePacotes::montaStatusPeer( const int& _qtde_processos )
{

}
