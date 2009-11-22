#ifndef REDECONFIG_H
#define REDECONFIG_H

#include <QList>
#include <QString>

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

        unsigned int
        meu_id;

        Rede::PEER_ESTADO
        estado_atual;

        QString
        host;

        static Rede::RedeConfig&
        getInstance()
        {
            static Rede::RedeConfig
            instancia;

            return instancia;
        }

    private:

        static Rede::RedeConfig
        instance;

        RedeConfig();

    };
}
#endif // REDECONFIG_H
