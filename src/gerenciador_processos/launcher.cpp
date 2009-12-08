#include "launcher.h"

#include "gpconfig.h"
#include "gpconstrutordepacotes.h"

GP::Launcher::Launcher(QObject *parent) :
    QObject(parent)
{


}

GP::Launcher::~Launcher()
{


}

void
GP::Launcher::incommingMessage(const int& _id,
                               const GP::PacoteBase& _parametros)
{

}

void
GP::Launcher::processoStart( const int& _num_requisicao,
                             const int& _id_host,
                             const int& _id_dono,
                             const QString& _nome,
                             const QStringList& _parametros )
{
    if( GP::GPConfig::getInstance().getPossuiAplicacao(_nome) )
    {
        if( _id_host == GP::GPConfig::getInstance().getMeuId() )
        {
            GP::Processo*
            processo_criado;

            processo_criado = this->startaProcessoLocal( _num_requisicao,
                                                         _id_dono,
                                                         _nome,
                                                         _parametros );

            if( processo_criado != 0 )
            {
                emit this->novoProcesso(_id_host, processo_criado);
            }
            else
            {
                emit this->falhouStartProcesso(_num_requisicao, _id_dono,
                                                                _nome,
                                                                _parametros);
            }
        }
        else
        {
            this->startaProcessoRemoto( _num_requisicao, _id_host, _id_dono,
                                                                   _nome,
                                                                   _parametros);
        }
    }
    else
    {

        emit this->falhouStartProcesso(_num_requisicao, _id_dono, _nome,
                                                                  _parametros);
    }
}

GP::ProcessoLocalOuImportado*
GP::Launcher::startaProcessoLocal( const int& _num_requisicao,
                                   const int& _id_dono,
                                   const QString& _nome,
                                   const QStringList& _parametros )
{
    GP::ProcessoLocalOuImportado*
    processo = new GP::ProcessoLocalOuImportado();

    processo->setNumRequisicao(_num_requisicao);
    processo->setIdDono(_id_dono);

    if( GP::GPConfig::getInstance().getAplicacao(_nome)->usaX11() )
    {
        //essa porra vai mudar!
        processo->start(_nome, _parametros);
    }
    else
    {
        processo->start(_nome, _parametros);
    }

    if( processo->waitForStarted() )
    {
        QString
        pacote_status = GP::ConstrutorDePacotes::getInstance().montaStatusPeer(
                        GP::GPConfig::getInstance().getQtdeProcessos(),
                        GP::GPConfig::getInstance().getQtdeProcessosPermitidos());

        emit this->sendMessage(0, pacote_status);
        return processo;
    }
    else
    {
        emit this->falhouStartProcesso( _num_requisicao,
                                        _id_dono,
                                        _nome,
                                        _parametros );
        return 0;
    }
}

void
GP::Launcher::startaProcessoRemoto( const int& _num_requisicao,
                                    const int& _id_host,
                                    const int& _id_dono,
                                    const QString& _nome,
                                    const QStringList& _parametros )
{
    QString
    pacote = GP::ConstrutorDePacotes::getInstance().montaStartProcess(
                                                                _num_requisicao,
                                                                _nome,
                                                                _parametros);

    emit this->sendMessage(_id_host, pacote );
}
