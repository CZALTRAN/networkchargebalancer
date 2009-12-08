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

        QString
        montaStatusPeer( const int& _qtde_processos,
                         const int& _qtde_processos_permitidos );

    private:
        ConstrutorDePacotes();

        ConstrutorDePacotes( ConstrutorDePacotes const&);

        ConstrutorDePacotes&
        operator= ( ConstrutorDePacotes const& );
    };
}

#endif // CONSTRUTORDEPACOTES_H