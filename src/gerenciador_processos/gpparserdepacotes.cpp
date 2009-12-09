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
    else if( campos[2] == "STANDARD_INPUT")
    {
        return this->parseiaStdIn(campos);
    }
    else if( campos[2] == "STANDARD_OUTPUT")
    {
        return this->parseiaStdOut(campos);
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
    GP::PacoteSuccessStartProcess*
    pacote = new GP::PacoteSuccessStartProcess;

    pacote->nome = GP::SUCCESS_START_PROCESS;
    pacote->dono = GP::LAUNCHER;

    this->setaInteiroDePacote(_lista_parametros, 3, pacote->num_requisicao);

    bool sucesso_ao_converter;

    this->setaInt64DePacote(_lista_parametros, 4, pacote->pid );

    pacote->processo = _lista_parametros[5];

    return pacote;
}

GP::PacoteFailStartProcess*
GP::ParserDePacotes::parseiaFailStartProcess(
                                    const QStringList& _lista_parametros ) const
{
    GP::PacoteFailStartProcess*
    pacote = new GP::PacoteFailStartProcess;

    pacote->nome = GP::FAIL_START_PROCESS;
    pacote->dono = GP::LAUNCHER;

    this->setaInteiroDePacote(_lista_parametros, 3, pacote->num_requisicao);

    pacote->processo = _lista_parametros[4];

    for( int parametro = 5; parametro < _lista_parametros.size(); parametro++ )
    {
        pacote->parametros.append(_lista_parametros[parametro]);
    }

    return pacote;
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

GP::PacoteStdIn*
GP::ParserDePacotes::parseiaStdIn( const QStringList& _lista_parametros ) const
{
    GP::PacoteStdIn*
    pacote = new GP::PacoteStdIn;

    pacote->nome = GP::STANDARD_INPUT;
    pacote->dono = GP::PROCESSO;

    this->setaInt64DePacote(_lista_parametros, 3, pacote->pid);
    this->setaInteiroDePacote(_lista_parametros, 4, pacote->num_requisicao);

    return pacote;
}

GP::PacoteStdOut*
GP::ParserDePacotes::parseiaStdOut( const QStringList& _lista_parametros ) const
{
    GP::PacoteStdOut*
    pacote = new GP::PacoteStdOut;

    pacote->nome = GP::STANDARD_INPUT;
    pacote->dono = GP::PROCESSO;

    this->setaInt64DePacote(_lista_parametros, 3, pacote->pid);
    this->setaInteiroDePacote(_lista_parametros, 4, pacote->num_requisicao);

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

void
GP::ParserDePacotes::setaInt64DePacote( const QStringList& _pacote,
                                            int _posicao,
                                            qint64& campo) const
{
    bool sucesso_ao_converter;

    campo = _pacote.value(_posicao).toLongLong( &sucesso_ao_converter, 10 ) ;
    if( sucesso_ao_converter == false )
    {
        qDebug() << Q_FUNC_INFO << "Ocorreu um erro ao parsear pacote.";
        exit(1);
    }
}
