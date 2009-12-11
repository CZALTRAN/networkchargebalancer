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

QString
GerenciadorProcessos::getProcessos()
{
    QHash<Q_PID, GP::Processo*>::iterator
    iterador = this->processos.begin();

    QStringList
    processos;

    for( ; iterador != this->processos.end(); iterador++ )
    {
        QString
        processo = iterador.value()->getNome() + ":";
        processo += QString::number(iterador.value()->getPid()) + ":";
        processo += QString::number(iterador.value()->getIdDono()) + ":";
        processo += QString::number(iterador.value()->getIdHost()) + ":";
        processo += QString::number(iterador.value()->getNumRequisicao()) + ":";
        processos.append(processo);
    }

    return processos.join(";");
}

void
GerenciadorProcessos::peerNovo( const int& _id )
{
    this->balancer.peerNovo(_id);
}

//MÉTODO SUPER_GAMBIARRA MODE ON
//PRECISO ENCONTRAR UMA SOLUÇÃO MELHOR DEPOIS
void
GerenciadorProcessos::peerCaiu( const int& _id )
{
    qDebug() << Q_FUNC_INFO << "Removendo os meus processos que estao sendo processados pelo peer " << _id;

    QList<GP::Processo*>
    processos_exportados_para_o_peer = this->buscaProcessosPorIdDono(
            GP::GPConfig::getInstance().getMeuId());

    for( int processo = 0;
         processo < processos_exportados_para_o_peer.size();
         processo++ )
    {
        QHash<Q_PID, GP::Processo*>::iterator
        iterador = this->processos.find(
                          processos_exportados_para_o_peer[processo]->getPid());

        while( iterador != this->processos.end() )
        {
            if( iterador.value()->getPid()
                    == processos_exportados_para_o_peer[processo]->getPid())
            {
                if( iterador.value()->getIdHost()
                    == processos_exportados_para_o_peer[processo]->getIdHost() )
                {
                    qint64
                    pid = static_cast<qint64>(iterador.value()->getPid());

                    emit this->terminoDeProcesso(
                                           pid,
                                           iterador.value()->getNumRequisicao(),
                                           PEER_CAIU);

                    qDebug() << Q_FUNC_INFO << "Removido o processo: " << iterador.value()->getNome();
                    delete iterador.value();
                    this->processos.erase(iterador);

                    iterador = this->processos.end();
                }
            }
            if( iterador != this->processos.end() )
            {
                iterador++;
            }
        }
    }

    QList<GP::Processo*>
    processos_do_peer = this->buscaProcessosPorIdDono(_id);

    qDebug() << Q_FUNC_INFO << "Removendo os processos do peer " << _id;

    for( int processo = 0; processo < processos_do_peer.size(); processo++ )
    {
        QHash<Q_PID, GP::Processo*>::iterator
        iterador = this->processos.find(processos_do_peer[processo]->getPid());

        while( iterador != this->processos.end() )
        {
            if( iterador.value()->getPid()
                    == processos_do_peer[processo]->getPid() )
            {
                if( iterador.value()->getIdDono()
                                   == processos_do_peer[processo]->getIdDono() )
                {
                    qDebug() << Q_FUNC_INFO << "Removi o processo: " << iterador.value()->getNome();
                    delete iterador.value();
                    this->processos.erase(iterador);

                    this->balancer.removeCarga(
                                        GP::GPConfig::getInstance().getMeuId());

                    iterador = this->processos.end();
                }
            }
            if( iterador != this->processos.end() )
            {
                iterador++;
            }
        }
    }

    this->balancer.peerCaiu(_id);
}

void
GerenciadorProcessos::incommingMessage(int _id, QString _mensagem)
{

    GP::PacoteBase*
    _pacote = GP::ParserDePacotes::getInstance().parseiaPacote(_mensagem);

    switch( _pacote->dono )
    {
        case GP::GP:
            this->trataMensagemGP(_id, _pacote);
        break;

        case GP::BALANCER:
            this->trataMensagemBalancer(_id, _pacote);
        break;

        case GP::LAUNCHER:
            this->trataMensagemLauncher( _id, _pacote );
        break;

        case GP::PROCESSO:
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
GerenciadorProcessos::mataProcesso( qint64 _pid,
                                    int _id_dono,
                                    int _num_requisicao)
{
    Q_UNUSED(_pid)
//    Q_PID
//    pid = static_cast<Q_PID>(_pid);

    QList<GP::Processo*>
    processos_id = this->buscaProcessosPorIdDono(_id_dono);

    for( int processo = 0;
         processo < processos_id.size();
         processo++ )
    {
        QHash<Q_PID, GP::Processo*>::iterator
        iterador = this->processos.find(
                          processos_id[processo]->getPid());

        while( iterador != this->processos.end() )
        {
            if( iterador.value()->getPid()
                    == processos_id[processo]->getPid())
            {
                if( iterador.value()->getNumRequisicao()
                    == _num_requisicao )
                {
                    qDebug() << Q_FUNC_INFO << "mesmo num_req";
                    if( iterador.value()->getIdDono()
                                     == GP::GPConfig::getInstance().getMeuId() )
                    {
                        qint64
                        pid = static_cast<qint64>(iterador.value()->getPid());

                        emit this->terminoDeProcesso(
                                           pid,
                                           iterador.value()->getNumRequisicao(),
                                           SOLICITADO);

                        qDebug() << Q_FUNC_INFO << "Matei processo meu!";
                        qDebug() << Q_FUNC_INFO << "merda123";
                        if(iterador.value()->getIdHost() != GP::GPConfig::getInstance().getMeuId())
                        {
                            qDebug() << Q_FUNC_INFO << "enviando kill_process";
                            QString
                            pacote_kill_process =
                            GP::ConstrutorDePacotes::getInstance().montaKillProcess(
                                    iterador.value()->getPid(),
                                    iterador.value()->getNumRequisicao());

                            emit this->sendMessage(iterador.value()->getIdHost(), pacote_kill_process);
                        }

                        qDebug() << Q_FUNC_INFO << "merda";
                    }
                    else
                    {
                        //envia pacote atraves da rede!
                        qDebug() << Q_FUNC_INFO << "Matei processo de outro kra!";

                        QString
                        pacote_process_killed=
                        GP::ConstrutorDePacotes::getInstance().montaProcessKilled(
                                          iterador.value()->getPid(),
                                          iterador.value()->getNumRequisicao());

                        qDebug() << Q_FUNC_INFO << pacote_process_killed;

                        emit this->sendMessage(_id_dono, pacote_process_killed);
                    }

                    qDebug() << Q_FUNC_INFO << "Removido o processo: " << iterador.value()->getNome();
                    delete iterador.value();
                    this->processos.erase(iterador);

                    iterador = this->processos.end();
                }
            }
            if( iterador != this->processos.end() )
            {
                iterador++;
            }
        }
    }
}

void
GerenciadorProcessos::stdIn( qint64 _pid, int _num_requisicao, QString _entrada )
{
    Q_PID
    pid = static_cast<Q_PID>(_pid);

    qDebug() << Q_FUNC_INFO << pid;

    QList<GP::Processo*>
    _processos = this->processos.values(pid);

    for( int processo = 0; processo < _processos.size(); processo++ )
    {
        if( _processos[processo]->getNumRequisicao() == _num_requisicao )
        {
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
            qint64
            pid = static_cast<qint64>(_processo->getPid());

            emit this->resultadoProcessoStart(_processo->getNumRequisicao(),
                                                           _processo->getNome(),
                                                           pid);
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
GerenciadorProcessos::pegaSaidaProcesso( Q_PID _pid,
                                         int _num_requisicao,
                                         QString _saida )
{
    GP::Processo*
    processo = static_cast<GP::Processo*>(this->sender());

    if( processo != 0 )
    {
        if( processo->getIdDono() == GP::GPConfig::getInstance().getMeuId() )
        {
            qint64
            pid = static_cast<qint64>(_pid);
            emit this->stdOut(pid, _num_requisicao, _saida);
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
GerenciadorProcessos::mataProcessoExportado( const int& _id_host,
                       const Q_PID& _pid,
                       const int& _num_requisicao )
{
    Q_UNUSED(_pid)
    QList<GP::Processo*>
    processos_id = this->buscaProcessosPorIdHost(_id_host);

    for( int processo = 0;
         processo < processos_id.size();
         processo++ )
    {
        QHash<Q_PID, GP::Processo*>::iterator
        iterador = this->processos.find(
                          processos_id[processo]->getPid());

        while( iterador != this->processos.end() )
        {
            if( iterador.value()->getPid()
                    == processos_id[processo]->getPid())
            {
                if( iterador.value()->getNumRequisicao()
                    == _num_requisicao )
                {
                    if( iterador.value()->getIdHost()
                                     == _id_host )
                    {
                        qint64
                        pid = static_cast<qint64>(iterador.value()->getPid());

                        emit this->terminoDeProcesso(
                                           pid,
                                           iterador.value()->getNumRequisicao(),
                                           PEER_MATOU);

                        qDebug() << Q_FUNC_INFO << "Matei processo meu!";

                        qDebug() << Q_FUNC_INFO << "Removido o processo: " << iterador.value()->getNome();
                        delete iterador.value();
                        this->processos.erase(iterador);

                        iterador = this->processos.end();
                    }
                }
            }
            if( iterador != this->processos.end() )
            {
                iterador++;
            }
        }
    }

}

void
GerenciadorProcessos::mataProcessoImportado( const int& _id_dono,
                       const Q_PID& _pid,
                       const int& _num_requisicao )
{
    Q_UNUSED(_pid)
    QList<GP::Processo*>
    processos_id = this->buscaProcessosPorIdDono(_id_dono);

    for( int processo = 0;
         processo < processos_id.size();
         processo++ )
    {
        QHash<Q_PID, GP::Processo*>::iterator
        iterador = this->processos.find(
                          processos_id[processo]->getPid());

        while( iterador != this->processos.end() )
        {
            if( iterador.value()->getPid()
                    == processos_id[processo]->getPid())
            {
                if( iterador.value()->getNumRequisicao()
                    == _num_requisicao )
                {
                    if( iterador.value()->getIdDono()
                                     == _id_dono )
                    {
                        qDebug() << Q_FUNC_INFO << "Matei processo do kra!";

                        qDebug() << Q_FUNC_INFO << "Removido o processo: " << iterador.value()->getNome();
                        delete iterador.value();
                        this->processos.erase(iterador);

                        iterador = this->processos.end();
                    }
                }
            }
            else
            {
                qDebug() << Q_FUNC_INFO << "###Processo Invalido: " << processos_id[processo]->getPid();
            }
            if( iterador != this->processos.end() )
            {
                iterador++;
            }
        }
    }
}


void
GerenciadorProcessos::trataMensagemGP( const int& _id, GP::PacoteBase* _pacote )
{
    switch( _pacote->nome )
    {
        case GP::KILL_PROCESS:
            this->trataKillProcess(_id, _pacote);
        break;

        case GP::PROCESS_KILLED:
            this->trataProcessKilled(_id, _pacote);
        break;
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
GerenciadorProcessos::trataKillProcess( const int& _id, GP::PacoteBase* _pacote )
{
    GP::PacoteKillProcess*
    pacote = static_cast<GP::PacoteKillProcess*>(_pacote);

    this->mataProcessoImportado(_id, pacote->pid, pacote->num_requisicao);
}

void
GerenciadorProcessos::trataProcessKilled( const int& _id, GP::PacoteBase* _pacote )
{
    GP::PacoteProcessKilled*
    pacote = static_cast<GP::PacoteProcessKilled*>(_pacote);

    this->mataProcessoExportado(_id, pacote->pid, pacote->num_requisicao);
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

    qint64
    pid = static_cast<qint64>(pacote_success_start_process->pid);

    emit this->resultadoProcessoStart(
                            pacote_success_start_process->num_requisicao,
                            pacote_success_start_process->processo,
                            pid);
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
    Q_UNUSED(_id)
    qDebug() << Q_FUNC_INFO << "tratando StdIn";

    GP::PacoteStdIn*
    pacote_std_in = static_cast<GP::PacoteStdIn*>(_pacote);

    qint64
    pid = static_cast<qint64>(pacote_std_in->pid);

    this->stdIn( pid,
                 pacote_std_in->num_requisicao,
                 pacote_std_in->entrada );
}

void
GerenciadorProcessos::trataStdOut( const int& _id, GP::PacoteBase* _pacote )
{
    Q_UNUSED(_id)
    GP::PacoteStdOut*
    pacote_std_out = static_cast<GP::PacoteStdOut*>(_pacote);

    qint64
    pid = static_cast<qint64>(pacote_std_out->pid);

    emit this->stdOut( pid,
                 pacote_std_out->num_requisicao,
                 pacote_std_out->saida );
}

QList<GP::Processo*>
GerenciadorProcessos::buscaProcessosPorIdHost( const int& _id )
{
    QList<GP::Processo*>
    lista_de_processos;

    QHash<Q_PID, GP::Processo*>::iterator
    iterador = this->processos.begin();

    for( ; iterador != this->processos.end(); iterador++ )
    {
        if( iterador.value()->getIdHost() == _id )
        {
            qDebug() << Q_FUNC_INFO << "encontrei um processo: " << iterador.value()->getPid();
            lista_de_processos.append(iterador.value());
        }
    }

    return lista_de_processos;
}

QList<GP::Processo*>
GerenciadorProcessos::buscaProcessosPorIdDono( const int& _id )
{
    QList<GP::Processo*>
    lista_de_processos;

    QHash<Q_PID, GP::Processo*>::iterator
    iterador = this->processos.begin();

    for( ; iterador != this->processos.end(); iterador++ )
    {
        if( iterador.value()->getIdDono() == _id )
        {
            qDebug() << Q_FUNC_INFO << "encontrei um processo: " << iterador.value()->getPid();
            lista_de_processos.append(iterador.value());
        }
    }

    return lista_de_processos;
}
