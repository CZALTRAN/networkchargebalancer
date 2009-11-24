#include "construtordepacotes.h"

#include "redeconfig.h"
#include "peer.h"

Rede::ConstrutorDePacotes::ConstrutorDePacotes()
{

}

QString
Rede::ConstrutorDePacotes::montaInit( const int _id, const int _qtde_peers )
{
    QString pacote;

    pacote = "INIT" + SEPARADOR_DE_CAMPO;
    pacote += QString::number(_id) + SEPARADOR_DE_CAMPO;
    pacote += QString::number(_qtde_peers) + SEPARADOR_DE_CAMPO;

    return pacote;
}

QString
Rede::ConstrutorDePacotes::montaNovoPeer( const QString& _host, const int& _id )
{
    QString
    pacote("NOVOPEER" + SEPARADOR_DE_CAMPO);

    pacote += _host + SEPARADOR_DE_CAMPO;
    pacote += QString::number(_id) + SEPARADOR_DE_CAMPO;
    return pacote;
}

QString
Rede::ConstrutorDePacotes::montaServer()
{
    QString
    pacote("SERVER" + SEPARADOR_DE_CAMPO);

    pacote += Rede::RedeConfig::getInstance().server_host->getHost();
    pacote += SEPARADOR_DE_CAMPO;

    pacote += QString::number(Rede::RedeConfig::getInstance().server_host->getId());
    pacote += SEPARADOR_DE_CAMPO;

    return pacote;
}

QString
Rede::ConstrutorDePacotes::montaMeuId()
{
    QString
    pacote("MEUID" + SEPARADOR_DE_CAMPO );

    pacote += QString::number( Rede::RedeConfig::getInstance().meu_id ) + SEPARADOR_DE_CAMPO;

    qDebug() << Q_FUNC_INFO << "montando com id: " << Rede::RedeConfig::getInstance().meu_id
            << " e host: " << Rede::RedeConfig::getInstance().host ;

    return pacote;
}
