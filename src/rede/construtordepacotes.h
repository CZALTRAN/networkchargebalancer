#ifndef CONSTRUTORDEPACOTES_H
#define CONSTRUTORDEPACOTES_H

#define SEPARADOR_DE_CAMPO QString(";")

#include <QString>

namespace Rede
{
    class ConstrutorDePacotes
    {
    public:
        static ConstrutorDePacotes&
        getInstance()
        {
            static Rede::ConstrutorDePacotes
            instance;

            return instance;
        }

        QString
        montaInit( const int _id, const int _total_peers );

        QString
        montaNovoPeer( const QString& _host, const int& _id );

        QString
        montaServer();

        QString
        montaMeuId();

        QString
        montaGP( const int& _id, const QString& _mensagem );

    private:
        ConstrutorDePacotes();

        ConstrutorDePacotes( ConstrutorDePacotes const&);

        Rede::ConstrutorDePacotes&
        operator= ( Rede::ConstrutorDePacotes const& );

    };
}
#endif // CONSTRUTORDEPACOTES_H
