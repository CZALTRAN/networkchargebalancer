#ifndef PING_H
#define PING_H

#include <QProcess>
#include <QStringList>
#include <QString>

namespace Rede{

    class Ping : public QObject
    {
    Q_OBJECT

        QStringList
        retorno;

        QProcess*
        ping;

    public:

        Ping( QString _host, QString _interface );

        ~Ping();

        QStringList
        getRetorno();

    private slots:

        void
        slotPingStdOutAndErr();
    };

}
#endif // PING_H
