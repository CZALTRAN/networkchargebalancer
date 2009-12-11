#include "processonativopai.h"

ProcessoNativoPai::ProcessoNativoPai( const QStringList& _args,
                                      QObject* _parent )
    : QThread(_parent)
{
    this->args = _args;
    this->gp_interface = new GPInterface(this);
    this->return_code = 0;
}

QString
ProcessoNativoPai::getStringArgument( const QString& _parametro )
{
    int
    index_parametro = this->args.indexOf( _parametro ) + 1;

    return this->args[ index_parametro ];
}

int
ProcessoNativoPai::getIntArgument( const QString& _parametro )
{
    int
    index_parametro = this->args.indexOf( _parametro ) + 1;

    bool
    ok;

    int
    parametro = this->args[ index_parametro ].toInt( &ok );

    if ( ! ok )
    {
        this->throwError( "parametro nao reconhecido!" );
    }
    else
    {
        return parametro;
    }
}

void
ProcessoNativoPai::throwError( const QString& _erro )
{
    this->return_code = 1;
    this->terminate();
}
