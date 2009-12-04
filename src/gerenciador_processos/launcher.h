#ifndef LAUNCHER_H
#define LAUNCHER_H

#include <QObject>
#include <QString>
#include <QStringList>

#include "structpacotes.h"
#include "processo.h"

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
        processoStart( const int& _id_host, const int& _id_dono, const QString& _processo, const QStringList& _parametros );

    public slots:

    signals:
        //sinais de comunicação externa
        void
        sendMessage( const int& _id_destino, QString _message );

        //sinais de comunicação interna
        void
        novoProcesso( const int& _id_host, const Processo& _processo );
    };
}

#endif // LAUNCHER_H
