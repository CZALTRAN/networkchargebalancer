#include "construtordepacotes.h"

Rede::ConstrutorDePacotes::ConstrutorDePacotes()
{

}

QString
Rede::ConstrutorDePacotes::montaInit( const int _id, const int _total_peers )
{
    QString pacote;

    pacote = "INIT" + SEPARADOR_DE_CAMPO;
    pacote += QString::number(_id) + SEPARADOR_DE_CAMPO;
    pacote += QString::number(_total_peers) + SEPARADOR_DE_CAMPO;

    return pacote;
}

QString
Rede::ConstrutorDePacotes::montaNovoPeer( const QString& _host )
{
    QString
    pacote;

    pacote = "NOVOPEER" + SEPARADOR_DE_CAMPO;
    pacote += _host + SEPARADOR_DE_CAMPO;

    return pacote;
}
