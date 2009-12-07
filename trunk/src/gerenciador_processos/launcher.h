#ifndef LAUNCHER_H
#define LAUNCHER_H

#include <QObject>
#include <QString>
#include <QStringList>

#include "structpacotes.h"
#include "processo.h"
#include "processoexportado.h"
#include "processolocalouimportado.h"

namespace GP
{
    enum ProcessosPermitidos
    {
        FIREFOX
    };

    class Launcher : public QObject
    {
    Q_OBJECT
    public:
        Launcher(QObject *parent = 0);

        ~Launcher();

        void
        incommingMessage( const int& _id, const GP::PacoteBase& _pacote );

        void
        processoStart( const int& _num_requisicao, const int& _id_host,
                                               const int& _id_dono,
                                               const QString& _nome,
                                               const QStringList& _parametros );

    public slots:

    signals:
        //sinais de comunicação externa
        void
        sendMessage( int _id_destino, QString _message );

        //sinais de comunicação interna
        void
        novoProcesso( int _id_host, GP::Processo* _processo );

        void
        falhouStartProcesso(int _num_requisicao, int _id_dono,
                                                 QString _nome,
                                                 QStringList _parametros);

    private:
        ProcessoLocalOuImportado*
        startaProcessoLocal( const int& _num_requisicao, const int& _id_dono,
                                               const QString& _nome,
                                               const QStringList& _parametros );

        void
        startaProcessoRemoto( const int& _num_requisicao,
                                               const int& _id_host,
                                               const int& _id_dono,
                                               const QString& _nome,
                                               const QStringList& _parametros );
    };
}

#endif // LAUNCHER_H
