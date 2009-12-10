#ifndef GPCONSTRUTORDEPACOTES_H
#define GPCONSTRUTORDEPACOTES_H

#include <QString>
#include <QStringList>
#include <QProcess>

#ifndef SEPARADOR_DE_CAMPO
#define SEPARADOR_DE_CAMPO QString(":")
#endif //SEPARADOR_DE_CAMPO

namespace GP
{
    class ConstrutorDePacotes
    {
    public:
        static ConstrutorDePacotes&
        getInstance();

        //pacotes do Launcher
        QString
        montaStartProcess( const int& _num_requisicao,
                           const QString& _processo,
                           const QStringList _parametros );

        QString
        montaSuccessStartProcess( const int& _num_requisicao,
                                  const QString& _processo,
                                  const Q_PID& _pid );

        QString
        montaFailStartProcess( const int& _num_requisicao,
                               const QString& _processo,
                               const QStringList& _parametros );

        //pacotes do Balancer
        QString
        montaStatusPeer( const int& _qtde_processos,
                         const int& _qtde_processos_permitidos );

        //pacotes de Processos
        QString
        montaStdIn( const Q_PID& _pid, const int& _num_requisicao,
                                       const QString& _entrada );

        QString
        montaStdOut( const Q_PID& _pid, const int& _num_requisicao,
                                        const QString& _saida );

        //pacotes do GP
        QString
        montaKillProcess( const Q_PID& _pid, const int& _num_requisicao );

        QString
        montaProcessKilled( const Q_PID& _pid, const int& _num_requisicao );

    private:
        ConstrutorDePacotes();

        ConstrutorDePacotes( ConstrutorDePacotes const&);

        ConstrutorDePacotes&
        operator= ( ConstrutorDePacotes const& );
    };
}

#endif // CONSTRUTORDEPACOTES_H
