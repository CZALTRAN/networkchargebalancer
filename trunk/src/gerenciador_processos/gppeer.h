#ifndef GPPEER_H
#define GPPEER_H

namespace GP
{
    class Peer
    {
    private:

        int
        id;

        bool
        possui_relacao;

        int
        qtde_processos;

        int
        qtde_processos_permitidos;

    public:
        Peer();

        Peer( const int& _id, const bool& _possui_relacao,
                              const int& _qtde_processos,
                              const int& _qtde_processos_permitidos );

        virtual
        ~Peer();

        void
        setId(const int& _id);

        void
        setPossuiRelacao(const bool& _possui_relacao);

        void
        setQtdeProcessos(const int& _qtde_processos);

        void
        setQtdeProcessosPermitidos(const int& _qtde_processos);

        int
        getId();

        bool
        getPossuiRelacao();

        int
        getQtdeProcessos();

        int
        getQtdeProcessosPermitidos();
    };
}

#endif // PEER_H
