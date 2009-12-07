#include "gpparserdepacotes.h"

#include <QDebug>

#include "gpconstrutordepacotes.h"

GP::ParserDePacotes::ParserDePacotes()
{

}

GP::ParserDePacotes::~ParserDePacotes()
{

}

GP::ParserDePacotes&
GP::ParserDePacotes::getInstance()
{
    static GP::ParserDePacotes
    instance;

    return instance;
}


GP::PacoteBase*
GP::ParserDePacotes::parseiaPacote(const QString& _pacote) const
{
    QStringList
    campos = _pacote.split(SEPARADOR_DE_CAMPO);

    if( campos[2] == "START_PROCESS" )
    {
        return this->parseiaStartProcess(campos);
    }
    else if( campos[2] == "SUCCESS_START_PROCESS" )
    {
        return this->parseiaSuccessStartProcess(campos);
    }
    else if( campos[2] == "FAIL_START_PROCESS" )
    {
        return this->parseiaFailStartProcess(campos);
    }
    else if( campos[2] == "STATUS_PEER" )
    {
        return this->parseiaPacoteStatusPeer(campos);
    }
    else
    {
        qDebug() << Q_FUNC_INFO << "Nao foi possivel parsear o pacote";
        exit(1);
    }
}

GP::PacoteStartProcess*
GP::ParserDePacotes::parseiaStartProcess(
                                    const QStringList& _lista_parametros ) const
{
    GP::PacoteStartProcess*
    pacote = new GP::PacoteStartProcess;

    pacote->nome = GP::START_PROCESS;
    pacote->dono = GP::LAUNCHER;

    this->setaInteiroDePacote(_lista_parametros, 3, pacote->num_requisicao);

    pacote->processo = _lista_parametros[4];

    for( int parametro = 5; parametro < _lista_parametros.size(); parametro++ )
    {
        pacote->parametros.append(_lista_parametros[parametro]);
    }

    return pacote;
}

GP::PacoteSuccessStartProcess*
GP::ParserDePacotes::parseiaSuccessStartProcess(
                                    const QStringList& _lista_parametros ) const
{

}

GP::PacoteFailStartProcess*
GP::ParserDePacotes::parseiaFailStartProcess(
                                    const QStringList& _lista_parametros ) const
{

}

GP::PacoteStatusPeer*
GP::ParserDePacotes::parseiaPacoteStatusPeer(
                                    const QStringList& _lista_parametros ) const
{
    GP::PacoteStatusPeer*
    pacote = new GP::PacoteStatusPeer;

    pacote->nome = GP::STATUS_PEER;

    pacote->dono = GP::BALANCER;

    this->setaInteiroDePacote(_lista_parametros, 3, pacote->qtde_processos);

    this->setaInteiroDePacote(_lista_parametros,
                              4,
                              pacote->qtde_processos_permitidos);

    return pacote;
}

void
GP::ParserDePacotes::setaInteiroDePacote( const QStringList& _pacote,
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
