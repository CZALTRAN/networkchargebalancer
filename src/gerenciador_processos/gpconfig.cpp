#include "gpconfig.h"

GP::GPConfig::GPConfig()
{
    GP::Aplicacao*
    aplicacao_temp = new Aplicacao();

    aplicacao_temp->setNome("firefox");
    aplicacao_temp->setUsaX11(true);

    this->aplicacoes.insert("firefox", aplicacao_temp);
}

GP::GPConfig::GPConfig( GPConfig const& )
{

}

int
GP::GPConfig::getMeuId()
{
    return this->meu_id;
}

int
GP::GPConfig::getQtdeProcessos()
{
    return this->qtde_processos;
}

int
GP::GPConfig::getQtdeProcessosPermitidos()
{
    return this->qtde_processos_permitidos;
}

GP::Aplicacao*
GP::GPConfig::getAplicacao(const QString& _nome)
{
    if( this->aplicacoes.contains(_nome) )
    {
        GP::Aplicacao*
        app_retorno = this->aplicacoes.value(_nome);

        return app_retorno;
    }

    return 0;
}

bool
GP::GPConfig::getPossuiAplicacao(const QString& _nome)
{
    if( this->aplicacoes.contains(_nome) )
    {
        return true;
    }

    return false;
}

void
GP::GPConfig::setMeuId(const int& _meu_id)
{
    this->meu_id = _meu_id;
}

void
GP::GPConfig::setQtdeProcessos( const int& _qtde )
{
    this->qtde_processos = _qtde;
}

void
GP::GPConfig::setQtdeProcessosPermitidos( const int& _qtde )
{
    this->qtde_processos_permitidos = _qtde;
}


GP::GPConfig&
GP::GPConfig::getInstance()
{
    static GP::GPConfig
    instancia;

    return instancia;
}


