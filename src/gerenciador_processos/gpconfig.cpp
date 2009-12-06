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

GP::Aplicacao*
GP::GPConfig::getAplicacao(const QString& _nome)
{
    if( this->aplicacoes.contains(_nome) )
    {
        GP::Aplicacao
        app_retorno = *this->aplicacoes.value(_nome);

        return &app_retorno;
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

GP::GPConfig&
GP::GPConfig::getInstance()
{
    static GP::GPConfig
    instancia;

    return instancia;
}

GP::GPConfig&
GP::GPConfig::operator= ( GP::GPConfig const& )
{

}


