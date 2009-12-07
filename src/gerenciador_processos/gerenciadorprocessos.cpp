#include "gerenciadorprocessos.h"

#include <QDebug>

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

    GP::PacoteBase*
    _pacote = GP::ParserDePacotes::getInstance().parseiaPacote(_mensagem);

    qDebug() << Q_FUNC_INFO << "ta parseada";

    switch( _pacote->dono )
    {
        case GP::BALANCER:
            qDebug() << Q_FUNC_INFO << "eh do balancer" << _id;
            this->trataMensagemBalancer(_id, _pacote);
        break;

        case GP::LAUNCHER:
            qDebug() << Q_FUNC_INFO << "eh do launcher";
            this->trataMensagemLauncher( _id, _pacote );
        break;

        case GP::GP:
            qDebug() << Q_FUNC_INFO << "eh minha" << GP::GP;
            qDebug() << Q_FUNC_INFO << _mensagem.toStdString().c_str();
        break;
    }

}

void
GerenciadorProcessos::processoStart( int _num_requisicao,
                                                       QString _processo,
                                                       QString _parametros )
{
    qDebug() << Q_FUNC_INFO << "parseando os parametros.";

    QStringList
    parametros = _parametros.split(" ");

    qDebug() << Q_FUNC_INFO << "pegando id do peer q vai processar.";

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

    qDebug() << Q_FUNC_INFO << "avisando o balancer sobre o novo peer";

    this->balancer.peerNovo(_meu_id);
}


void
GerenciadorProcessos::killProcess( const int _id_dono, const Q_PID _processo)
{

}

void
GerenciadorProcessos::novoProcesso(int _id_host, GP::Processo* _processo)
{
    if( GP::GPConfig::getInstance().getMeuId() == _id_host )
    {
        qDebug() << Q_FUNC_INFO << "adcionando processo na hash";
        this->processos.insert(_processo->getPid(), _processo);

        emit this->sucessoProcessoStart(_processo->getNumRequisicao(),
                                        _processo->getNome(),
                                        _processo->getPid());
    }
    else
    {
        qDebug() << Q_FUNC_INFO << "adcionando processo na hash";
        this->processos.insert(_processo->getPid(), _processo);

        QString
        pacote = GP::ConstrutorDePacotes::getInstance().montaSuccessStartProcess(
                                                  _processo->getNumRequisicao(),
                                                  _processo->getNome(),
                                                  _processo->getPid() );

        emit this->sendMessage(_processo->getIdDono(), pacote);
    }

    this->balancer.insereCarga(_id_host);
}

void
GerenciadorProcessos::falhouStartProcesso( int _num_requisicao,
                                           int _id_dono,
                                           QString _processo,
                                           QStringList _parametros )
{
    if( GP::GPConfig::getInstance().getMeuId() == _id_dono )
    {
        //emit this->processoStartFalhou(int _num_requisicao, QString _processo);
        qDebug() << Q_FUNC_INFO << "Falhou startar processo!";

        emit this->falhouProcessoStart(_num_requisicao, _processo);
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
    qDebug() << Q_FUNC_INFO << "enviando mensagem para a rede" << _mensagem.toStdString().c_str();
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

             qDebug() << Q_FUNC_INFO << "setando status do peer" << _id;

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
GerenciadorProcessos::trataStartProcess(const int& _id, GP::PacoteBase* _pacote)
{
    GP::PacoteStartProcess*
    pacote_start_process = static_cast<GP::PacoteStartProcess*>(_pacote);

    this->launcher.processoStart( pacote_start_process->num_requisicao,
                                         GP::GPConfig::getInstance().getMeuId(),
                                         _id,
                                         pacote_start_process->processo,
                                         pacote_start_process->parametros);
}

void
GerenciadorProcessos::trataSucessStartProcess( const int& _id,
                                               GP::PacoteBase* _pacote )
{
    GP::PacoteSuccessStartProcess*
    pacote_success_start_process =
                    static_cast<GP::PacoteSuccessStartProcess*>(_pacote);

    emit this->sucessoProcessoStart(
                            pacote_success_start_process->num_requisicao,
                            pacote_success_start_process->processo,
                            pacote_success_start_process->pid);
}

void
GerenciadorProcessos::trataFailStartProcess( const int& _id,
                                             GP::PacoteBase* _pacote )
{
    GP::PacoteFailStartProcess*
    pacote_fail_start_process =
                       static_cast<GP::PacoteFailStartProcess*>(_pacote);

    this->processoStart(pacote_fail_start_process->num_requisicao,
                        pacote_fail_start_process->processo,
                        pacote_fail_start_process->parametros.join("") );

}
