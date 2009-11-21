#ifndef REDECONFIG_H
#define REDECONFIG_H

#include <QList>

namespace Rede
{

    enum PEER_ESTADO
    {
        PROCURANDO_SERVER,
        CONECTANDO,
        CONECTADO,
        SERVER
    };

    class RedeConfig
    {
    public:

        bool
        server;

        unsigned int
        meu_id;

        Rede::PEER_ESTADO
        estado_atual;

        QString
        host;

        static Rede::RedeConfig
        getInstance();

    private:

        RedeConfig();


    };
}
#endif // REDECONFIG_H
