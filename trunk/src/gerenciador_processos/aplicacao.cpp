#include "aplicacao.h"

GP::Aplicacao::Aplicacao()
{
}

GP::Aplicacao::Aplicacao( const QString& _nome, const QString& _diretorio, const bool& _x11 )
{
    this->nome = _nome;
    this->diretorio = _diretorio;
    this->x11 = _x11;
}

QString
GP::Aplicacao::getNome()
{
    return this->nome;
}

QString
GP::Aplicacao::getDiretorio()
{
    return this->diretorio;
}

bool
GP::Aplicacao::usaX11()
{
    return this->x11;
}

void
GP::Aplicacao::setNome( const QString& _nome )
{
    this->nome = _nome;
}

void
GP::Aplicacao::setDiretorio( const QString& _diretorio )
{
    this->diretorio = _diretorio;
}

void
GP::Aplicacao::setUsaX11( bool _usa_x11 )
{
    this->x11 = _usa_x11;
}
