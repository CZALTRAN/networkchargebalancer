#ifndef REDECONFIG_H
#define REDECONFIG_H

#include <QList>
#include <QString>

namespace Rede
{
    class Peer;

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

        int
        meu_id;

        Rede::PEER_ESTADO
        estado_atual;

        QString
        host;

        Rede::Peer*
        server_host;

        int
        qtdePeers;

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

        RedeConfig( RedeConfig const& );

        Rede::RedeConfig&
        operator= ( Rede::RedeConfig const& );

    };
}
#endif // REDECONFIG_H
