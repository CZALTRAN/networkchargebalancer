#ifndef PROCESSO_H
#define PROCESSO_H

#include <QProcess>

namespace GP{

    class Processo
    {
    private:

        Q_PID
        pid;

        int
        id_dono;

    public:

        Processo();

        Processo( const GP::Processo& _processo );

        ~Processo();

        Q_PID
        getPid();

        int
        getIdDono();
    };

}
#endif // PROCESSO_H
