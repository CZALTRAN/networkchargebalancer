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
        QString
        montaStartProcess( const QString& _processo, const QStringList _parametros );

        QString
        montaSuccessStartProcess( const QString& _processo, const Q_PID& _pid );

        QString
        montaFailStartProcess( const QString& _processo );

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
