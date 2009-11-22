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
        return this->parseiaInit( _pacote );
    }

    return 0;
}

Rede::PacoteInit*
Rede::ParserDePacotes::parseiaInit( const QString _pacote ) const
{
    qDebug() << Q_FUNC_INFO << "Parseando pacote init";

    QStringList
    lista_de_campos = _pacote.split( SEPARADOR_DE_CAMPO );

    Rede::PacoteInit
    pacote;

    pacote.nome = lista_de_campos.value(0);

    bool sucesso_ao_converter;
    pacote.id = lista_de_campos.value(1).toInt( &sucesso_ao_converter, 10 ) ;

    if( sucesso_ao_converter == true )
    {
        qDebug() << Q_FUNC_INFO << "Ocorreu um erro ao parsear pacote.";
        exit(1);
    }

    return &pacote;
}

