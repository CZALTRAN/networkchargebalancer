#ifndef STRUCTPACOTES_H
#define STRUCTPACOTES_H

#include <QString>

namespace Rede{

    typedef struct PacoteBase
    {
        QString
        nome;
    } PacoteBase;

    typedef struct PacoteInit : public PacoteBase
    {
        int
        id;
    } PacoteInit;

}

#endif // STRUCTPACOTES_H
