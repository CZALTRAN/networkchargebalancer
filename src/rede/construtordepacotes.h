#ifndef CONSTRUTORDEPACOTES_H
#define CONSTRUTORDEPACOTES_H

#define SEPARADOR_DE_CAMPO QString(":")

#include <QString>

namespace Rede
{
    class ConstrutorDePacotes
    {
    public:
        static ConstrutorDePacotes
        getInstance();

        QString
        montaInit( const int _id, const int _total_peers );

    private:
        ConstrutorDePacotes();
    };
}
#endif // CONSTRUTORDEPACOTES_H
