#include "gerenciadorprocessos.h"

#include <QDebug>
#include <QList>

#include "gpparserdepacotes.h"
#include "gpconfig.h"
#include "gpconstrutordepacotes.h"

GerenciadorProcessos::GerenciadorProcessos(QObject * _parent )
    : QObject(_parent)
{
    QObject::connect(&this->balancer, SIGNAL(sendMessage(int, QString)),
                     this, SLOT(enviaMensagem(int, QString)));

    QObject::connect(&this->launcher, SIGNAL(sendMessage(int, QString)),
                     this, SLOT(enviaMensagem(int,QString)));

    QObject::connect(&this->launcher, SIGNAL(novoProcesso(int, GP::Processo*)),
                     this, SLOT(novoProcesso(int,GP::Processo*)));

    QObject::connect(&this->launcher, SIGNAL(falhouStartProcesso(int,
                                                                 int,
                                                                 QString,
                                                                 QStringList)),
                     this, SLOT(falhouStartProcesso(int,int,QString,
                                                            QStringList)));
}

GerenciadorProcessos::~GerenciadorProcessos()
{

}

void
GerenciadorProcessos::peerNovo( const int& _id )
{
    this->balancer.peerNovo(_id);
}

void
GerenciadorProcessos::peerCaiu( const int& _id )
{

}

void
GerenciadorProcessos::incommingMessage(int _id, QString _mensagem)
{

    qDebug() << Q_FUNC_INFO << "chegou mensagem";

    qDebug() << Q_FUNC_INFO << _mensagem.toStdString().c_str();

    GP::PacoteBase*
    _pacote = GP::ParserDePacotes::getInstance().parseiaPacote(_mensagem);

    switch( _pacote->dono )
    {
        case GP::GP:
            qDebug() << Q_FUNC_INFO << "eh minha" << GP::GP;
        break;

        case GP::BALANCER:
            this->trataMensagemBalancer(_id, _pacote);
        break;

        case GP::LAUNCHER:
            this->trataMensagemLauncher( _id, _pacote );
        break;

        case GP::PROCESSO:
            qDebug() << Q_FUNC_INFO << "eh do processo";
            this->trataMensagemProcesso( _id, _pacote );
        break;
    }

}

void
GerenciadorProcessos::processoStart( int _num_requisicao,
                                                       QString _processo,
                                                       QString _parametros )
{
    QStringList
    parametros = _parametros.split(" ");

    int
    id_peer_host = this->balancer.getPeerHost();

    qDebug() << Q_FUNC_INFO << "solicitando que o launcher inicie o processo no host" << QString::number(id_peer_host);

    this->launcher.processoStart( _num_requisicao, id_peer_host,
                                  GP::GPConfig::getInstance().getMeuId(),
                                  _processo,
                                  parametros );
}

void
GerenciadorProcessos::meuId( int _meu_id )
{
    GP::GPConfig::getInstance().setMeuId(_meu_id);

    this->balancer.peerNovo(_meu_id);
}


void
GerenciadorProcessos::killProcess( const int _id_dono, const Q_PID _processo)
{

}

void
GerenciadorProcessos::stdIn( Q_PID _pid, int _num_requisicao, QString _entrada )
{
    QList<GP::Processo*>
    _processos = this->processos.values(_pid);

    for( int processo = 0; processo < _processos.size(); processo++ )
    {
        if( _processos[processo]->getNumRequisicao() == _num_requisicao )
        {
            qDebug() << Q_FUNC_INFO << "processo encontrado. enviando entrada";
            if( _processos[processo]->getIdHost()
                                     == GP::GPConfig::getInstance().getMeuId() )
            {
                _processos[processo]->stdIn(_entrada);
            }
            else
            {
                QString
                pacote = GP::ConstrutorDePacotes::getInstance().montaStdIn(
                                       _processos[processo]->getPid(),
                                       _processos[processo]->getNumRequisicao(),
                                       _entrada);

                emit this->sendMessage(_processos[processo]->getIdDono(),
                                       pacote);
            }
            return;
        }
    }

    qDebug() << Q_FUNC_INFO << "nao foi encontrado processo com esse pid e num_requisicao.";
}

void
GerenciadorProcessos::novoProcesso(int _id_host, GP::Processo* _processo)
{
    this->balancer.insereCarga(_id_host);

    if( GP::GPConfig::getInstance().getMeuId() == _id_host )
    {
        QObject::connect(_processo,
                         SIGNAL(stdOutAndErr(Q_PID,int,QString)),
                         this,
                         SLOT(pegaSaidaProcesso(Q_PID,int,QString)));

        this->processos.insertMulti(_processo->getPid(), _processo);

        if( _processo->getIdDono() == GP::GPConfig::getInstance().getMeuId() )
        {
            emit this->resultadoProcessoStart(_processo->getNumRequisicao(),
                                                           _processo->getNome(),
                                                           _processo->getPid());
        }
        else
        {
            QString
            pacote = GP::ConstrutorDePacotes::getInstance().montaSuccessStartProcess(
                                                      _processo->getNumRequisicao(),
                                                      _processo->getNome(),
                                                      _processo->getPid() );

            emit this->sendMessage(_processo->getIdDono(), pacote);
        }
    }
    else
    {
        qDebug() << Q_FUNC_INFO << "adcionando processo na hash 2#######";
        this->processos.insertMulti(_processo->getPid(), _processo);

        QString
        pacote = GP::ConstrutorDePacotes::getInstance().montaSuccessStartProcess(
                                                  _processo->getNumRequisicao(),
                                                  _processo->getNome(),
                                                  _processo->getPid() );

        emit this->sendMessage(_processo->getIdDono(), pacote);
        
        QString
        pacote_status= GP::ConstrutorDePacotes::getInstance().montaStatusPeer(
                      GP::GPConfig::getInstance().getQtdeProcessos(), 
                      GP::GPConfig::getInstance().getQtdeProcessosPermitidos());

        emit this->sendMessage(0, pacote_status);
    }

}

void
GerenciadorProcessos::falhouStartProcesso( int _num_requisicao,
                                           int _id_dono,
                                           QString _processo,
                                           QStringList _parametros )
{
    if( GP::GPConfig::getInstance().getMeuId() == _id_dono )
    {
        qDebug() << Q_FUNC_INFO << "Falhou startar processo!";

        emit this->resultadoProcessoStart(_num_requisicao, _processo, 0);
    }
    else
    {
        QString
        pacote = GP::ConstrutorDePacotes::getInstance().montaFailStartProcess(
                                                                _num_requisicao,
                                                                _processo,
                                                                _parametros);

        emit this->sendMessage(_id_dono, pacote);
    }

}

void
GerenciadorProcessos::enviaMensagem( int _id_destino, QString _mensagem )
{
    emit this->sendMessage(_id_destino, _mensagem);
}

void
GerenciadorProcessos::pegaSaidaProcesso( Q_PID _pid, int _num_requisicao, QString _saida )
{
    GP::Processo*
    processo = static_cast<GP::Processo*>(this->sender());

    if( processo != 0 )
    {
        if( processo->getIdDono() == GP::GPConfig::getInstance().getMeuId() )
        {
            emit this->stdOut(_pid, _num_requisicao, _saida);
        }
        else
        {
            QString
            stdOut = GP::ConstrutorDePacotes::getInstance().montaStdOut(
                                                                _pid,
                                                                _num_requisicao,
                                                                _saida);
            emit this->sendMessage(processo->getIdDono(), stdOut);
        }
    }
}

void
GerenciadorProcessos::trataMensagemBalancer( const int& _id,
                                             GP::PacoteBase* _pacote )
{
    switch( _pacote->nome )
    {
        case GP::STATUS_PEER :
             GP::PacoteStatusPeer*
             pacote = static_cast<GP::PacoteStatusPeer*>(_pacote);

             this->balancer.setStatusPeer(_id, pacote);
        break;
    }
}

void
GerenciadorProcessos::trataMensagemLauncher( const int& _id,
                                             GP::PacoteBase* _pacote )
{
    switch( _pacote->nome )
    {
        case GP::START_PROCESS :
            this->trataStartProcess(_id, _pacote);
        break;

        case GP::SUCCESS_START_PROCESS :
            this->trataSucessStartProcess(_id, _pacote);
        break;

        case GP::FAIL_START_PROCESS :
            this->trataFailStartProcess(_id, _pacote);
        break;
    }
}

void
GerenciadorProcessos::trataMensagemProcesso( const int& _id,
                                             GP::PacoteBase* _pacote )
{
    qDebug() << Q_FUNC_INFO << "tratando msg de processo";

    switch( _pacote->nome )
    {
    case GP::STANDARD_INPUT:
        this->trataStdIn(_id, _pacote);
    break;

    case GP::STANDARD_OUTPUT:
        this->trataStdOut(_id, _pacote);
    }
}

void
GerenciadorProcessos::trataStartProcess(const int& _id, GP::PacoteBase* _pacote)
{
    GP::PacoteStartProcess*
    pacote_start_process = static_cast<GP::PacoteStartProcess*>(_pacote);

    if( this->balancer.getPermissaoProcessar() )
    {
        this->launcher.processoStart( pacote_start_process->num_requisicao,
                                         GP::GPConfig::getInstance().getMeuId(),
                                         _id,
                                         pacote_start_process->processo,
                                         pacote_start_process->parametros);
    }
    else
    {
        emit this->sendMessage(_id, GP::ConstrutorDePacotes::
                                    getInstance().montaFailStartProcess(
                                           pacote_start_process->num_requisicao,
                                           pacote_start_process->processo,
                                           pacote_start_process->parametros));

        qDebug() << Q_FUNC_INFO << "Nao vou fornecer processamento, minha carga esta cheia!";
    }
}

void
GerenciadorProcessos::trataSucessStartProcess( const int& _id,
                                               GP::PacoteBase* _pacote )
{
    GP::PacoteSuccessStartProcess*
    pacote_success_start_process =
                           static_cast<GP::PacoteSuccessStartProcess*>(_pacote);

    this->balancer.insereCarga(_id);

    GP::ProcessoExportado*
    processo_exportado = new GP::ProcessoExportado();

    processo_exportado->setPid(pacote_success_start_process->pid);
    processo_exportado->setIdDono(GP::GPConfig::getInstance().getMeuId());
    processo_exportado->setIdHost(_id);
    processo_exportado->setNome(pacote_success_start_process->processo);
    processo_exportado->setNumRequisicao(
                                  pacote_success_start_process->num_requisicao);

    this->processos.insertMulti(pacote_success_start_process->pid,
                           processo_exportado);

    emit this->resultadoProcessoStart(
                            pacote_success_start_process->num_requisicao,
                            pacote_success_start_process->processo,
                            pacote_success_start_process->pid);
}

void
GerenciadorProcessos::trataFailStartProcess( const int& _id,
                                             GP::PacoteBase* _pacote )
{
    Q_UNUSED(_id)

    GP::PacoteFailStartProcess*
    pacote_fail_start_process =
                       static_cast<GP::PacoteFailStartProcess*>(_pacote);

    this->processoStart(pacote_fail_start_process->num_requisicao,
                        pacote_fail_start_process->processo,
                        pacote_fail_start_process->parametros.join("") );

}

void
GerenciadorProcessos::trataStdIn( const int& _id, GP::PacoteBase* _pacote )
{
    qDebug() << Q_FUNC_INFO << "tratando StdIn";

    GP::PacoteStdIn*
    pacote_std_in = static_cast<GP::PacoteStdIn*>(_pacote);

    this->stdIn( pacote_std_in->pid,
                 pacote_std_in->num_requisicao,
                 pacote_std_in->entrada );
}

void
GerenciadorProcessos::trataStdOut( const int& _id, GP::PacoteBase* _pacote )
{
    GP::PacoteStdOut*
    pacote_std_out = static_cast<GP::PacoteStdOut*>(_pacote);

    this->stdOut( pacote_std_out->pid,
                 pacote_std_out->num_requisicao,
                 pacote_std_out->saida );
}
