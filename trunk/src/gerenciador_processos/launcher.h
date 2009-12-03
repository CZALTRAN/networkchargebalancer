#ifndef LAUNCHER_H
#define LAUNCHER_H

#include <QObject>
#include <QString>
#include <QStringList>

#include "structpacotes.h"

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

    signals:
        void
        sendMessage( int _id_destino, QString _message );

    public slots:

        void
        processoStart( const QString& _processo, const QStringList& _parametros );

        void
        incommingMessage( const int& _id, const GP::PacoteBase& _pacote );

    };
}

#endif // LAUNCHER_H
