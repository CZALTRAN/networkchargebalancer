#ifndef GPCONSTRUTORDEPACOTES_H
#define GPCONSTRUTORDEPACOTES_H

#include <QString>
#include <QStringList>
#include <QProcess>

namespace GP
{
    class ConstrutorDePacotes
    {
    public:
        static ConstrutorDePacotes&
        getInstance();

        QString
        montaStartProcess( const int& _num_requisicao, const int& _id_dono,
                                                const QString& _processo,
                                                const QStringList _parametros );

        QString
        montaSuccessStartProcess( const int& _num_requisicao,
                                  const QString& _processo,
                                  const Q_PID& _pid );

        QString
        montaFailStartProcess( const int& _num_requisicao,
                               const QString& _processo );

        QString
        montaStatusPeer( const int& _qtde_processos );

    private:
        ConstrutorDePacotes();

        ConstrutorDePacotes( ConstrutorDePacotes const&);

        ConstrutorDePacotes&
        operator= ( ConstrutorDePacotes const& );
    };
}

#endif // CONSTRUTORDEPACOTES_H
