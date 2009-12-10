#ifndef GERENCIADORPROCESSOS_H
#define GERENCIADORPROCESSOS_H

#include <QObject>
#include <QHash>
#include <QProcess>
#include <QList>

#include "balanceadorcarga.h"
#include "launcher.h"
#include "processo.h"

enum motivoFimProcesso
{
    PEER_CAIU,
    PEER_MATOU,
    SOLICITADO
};

class GerenciadorProcessos : public QObject
{
Q_OBJECT

    GP::BalanceadorCarga
    balancer;

    GP::Launcher
    launcher;

    QHash<Q_PID, GP::Processo*>
    processos;

public:
    GerenciadorProcessos(QObject * _parent = NULL);

    virtual
    ~GerenciadorProcessos();

public slots:
    //slots para comunicação externa
    void
    processoStart( int _num_requisicao, QString _processo,
                                        QString _parametros );

    void
    peerNovo( const int& _id );

    void
    peerCaiu( const int& _id );

    void
    meuId( int _meu_id );

    void
    incommingMessage( int _id, QString _mensagem );

    void
    mataProcesso( qint64 _pid, int _id_dono, int _num_requisicao );

    void
    stdIn( qint64 _pid, int _num_requisicao, QString _entrada );

    //slots para comunicação interna
    void
    novoProcesso( int _id_host, GP::Processo* _processo );

    void
    falhouStartProcesso( int _num_requisicao, int _id_dono,
                                              QString _processo,
                                              QStringList _parametros );

    void
    enviaMensagem( int _id_destino, QString _mensagem );

    void
    pegaSaidaProcesso( Q_PID _pid, int _num_requisicao, QString _saida );

signals:
    void
    stdOut( qint64 _pid, int _num_requisicao, QString _saida );

    void
    sendMessage( int _id_destino, QString _mensagem);

    void
    terminoDeProcesso( qint64 _pid, int num_requisicao,
                                   motivoFimProcesso _motivo );

    void
    resultadoProcessoStart( int _num_requisicao, QString _processo, qint64 _pid );

private:
    void
    trataMensagemBalancer( const int& _id, GP::PacoteBase* _pacote );

    void
    trataMensagemLauncher( const int& _id, GP::PacoteBase* _pacote );

    void
    trataMensagemProcesso( const int& _id, GP::PacoteBase* _pacote );

    void
    trataStartProcess( const int& _id, GP::PacoteBase* _pacote );

    void
    trataSucessStartProcess( const int& _id, GP::PacoteBase* _pacote );

    void
    trataFailStartProcess( const int& _id, GP::PacoteBase* _pacote );

    void
    trataStdIn( const int& _id, GP::PacoteBase* _pacote );

    void
    trataStdOut( const int& _id, GP::PacoteBase* _pacote );

    QList<GP::Processo*>
    buscaProcessosPorIdHost( const int& _id );

    QList<GP::Processo*>
    buscaProcessosPorIdDono( const int& _id );
};

#endif // GERENCIADORPROCESSOS_H
