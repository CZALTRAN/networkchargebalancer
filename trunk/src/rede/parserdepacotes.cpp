#include "parserdepacotes.h"

#include <QDebug>
#include <QStringList>

#include "construtordepacotes.h"

Rede::ParserDePacotes::ParserDePacotes()
{
}

Rede::ParserDePacotes::~ParserDePacotes()
{

}

Rede::ParserDePacotes&
Rede::ParserDePacotes::getInstance()
{
    static Rede::ParserDePacotes
    instance;

    return instance;
}

Rede::PacoteBase*
Rede::ParserDePacotes::parseiaPacote( const QString _pacote ) const
{
    QStringList
    lista_de_campos = _pacote.split( SEPARADOR_DE_CAMPO );

    if( lista_de_campos[0] == "INIT" )
    {
        return this->parseiaInit( lista_de_campos );
    }
    else if ( lista_de_campos[0] == "NOVOPEER" )
    {
        return this->parseiaNovoPeer( lista_de_campos );
    }
    else if ( lista_de_campos[0] == "SERVER" )
    {
        return this->parseiaInformaServer( lista_de_campos );
    }
    else if ( lista_de_campos[0] == "MEUID" )
    {
        return this->parseiaMeuId( lista_de_campos );
    }


    return 0;
}

Rede::PacoteInit*
Rede::ParserDePacotes::parseiaInit( const QStringList& _lista_parametros ) const
{
    Rede::PacoteInit*
    pacote = new Rede::PacoteInit;

    pacote->nome = Rede::INIT;

    this->setaInteiroDePacote( _lista_parametros, 1, pacote->id );
    this->setaInteiroDePacote( _lista_parametros, 2, pacote->total_peers );

    return pacote;
}

Rede::PacoteNovoPeer*
Rede::ParserDePacotes::parseiaNovoPeer( const QStringList& _lista_parametros ) const
{
    Rede::PacoteNovoPeer*
    pacote = new Rede::PacoteNovoPeer;

    pacote->nome = Rede::NOVO_PEER;
    pacote->host = _lista_parametros.value(1);
    this->setaInteiroDePacote( _lista_parametros,2,pacote->id);

    return pacote;
}

Rede::PacoteInformaServer*
Rede::ParserDePacotes::parseiaInformaServer( const QStringList& _lista_parametros ) const
{
    Rede::PacoteInformaServer*
    pacote = new Rede::PacoteInformaServer;

    pacote->nome = Rede::INFORMA_SERVER;
    pacote->host = _lista_parametros.value(1);
    this->setaInteiroDePacote(_lista_parametros,2,pacote->id);

    return pacote;
}

Rede::PacoteMeuId*
Rede::ParserDePacotes::parseiaMeuId( const QStringList& _lista_parametros ) const
{
    Rede::PacoteMeuId*
    pacote = new Rede::PacoteMeuId;

    pacote->nome = Rede::MEU_ID;
    this->setaInteiroDePacote(_lista_parametros,1,pacote->id);

    return pacote;
}

void
Rede::ParserDePacotes::setaInteiroDePacote( const QStringList& _pacote,
                                            int _posicao,
                                            int& campo) const
{
    bool sucesso_ao_converter;

    campo = _pacote.value(_posicao).toInt( &sucesso_ao_converter, 10 ) ;
    if( sucesso_ao_converter == false )
    {
        qDebug() << Q_FUNC_INFO << "Ocorreu um erro ao parsear pacote.";
        exit(1);
    }
}

