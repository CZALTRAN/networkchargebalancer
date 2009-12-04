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

    public:
        Peer();

        Peer( const int& _id, const bool& _possui_relacao, const int& _qtde_processos );

        virtual
        ~Peer();

        void
        setId(const int& _id);

        void
        setPossuiRelacao(const int& _possui_relacao);

        void
        setQtdeProcessos(const int& _qtde_processos);

        int
        getId();

        bool
        getPossuiRelacao();

        int
        getQtdeProcessos();
    };
}

#endif // PEER_H
