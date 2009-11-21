#ifndef REDECONFIG_H
#define REDECONFIG_H

#include <QList>

namespace Rede
{
    class RedeConfig
    {
    public:

        bool
        server;

        unsigned int
        meu_id;

        static Rede::RedeConfig
        getInstance();

    private:

        RedeConfig();


    };
}
#endif // REDECONFIG_H
