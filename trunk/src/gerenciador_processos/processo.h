#ifndef PROCESSO_H
#define PROCESSO_H

#include <QProcess>
#include <QString>

namespace GP{

    class Processo : public QProcess
    {
    Q_OBJECT
    
    private:
        Q_PID
        pid;

        int
        id_dono;

    public:
        Processo();

        Processo( const GP::Processo& _processo );

        virtual
        ~Processo();

        Q_PID
        getPid();

        int
        getIdDono();

    public slots:
        QString
        stdOutAndErr();

    signals:
        void
        stdIn(const QString& _entrada);

    };

}
#endif // PROCESSO_H
