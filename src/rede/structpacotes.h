#ifndef STRUCTPACOTES_H
#define STRUCTPACOTES_H

#include <QString>

namespace Rede{

    enum TipoPacote
    {
        INIT,
        NOVO_PEER,
        INFORMA_SERVER,
        MEU_ID,
        GP
    };

    typedef struct PacoteBase
    {
        Rede::TipoPacote
        nome;

        int
        id;

    } PacoteBase;

    typedef struct PacoteInit : public PacoteBase
    {

        int
        total_peers;

    } PacoteInit;

    typedef struct PacoteNovoPeer :public PacoteBase
    {
        QString
        host;

    } PacoteNovoPeer;

    typedef struct PacoteInformaServer : public PacoteBase
    {
        QString
        host;

    } PacoteInformaServer;

    typedef struct PacoteMeuId : public PacoteBase
    {
        QString
        host;

    } PacoteMeuId;

    typedef struct PacoteGP : public PacoteBase
    {
        QString
        mensagem;

    } PacoteGP;
}

#endif // STRUCTPACOTES_H
