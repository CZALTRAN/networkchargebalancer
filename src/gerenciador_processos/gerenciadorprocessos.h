#ifndef GERENCIADORPROCESSOS_H
#define GERENCIADORPROCESSOS_H

#include <QObject>
#include <QHash>
#include <QProcess>

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

    QHash<const Q_PID, const GP::Processo*>
    processos;

public:
    GerenciadorProcessos(QObject * _parent = NULL);

    virtual
    ~GerenciadorProcessos();

    public slots:

    void
    peerNovo( const int& _id );

    void
    peerCaiu( const int& _id );

public slots:

    //slots para comunicação externa
    void
    processoStart( int _num_requisicao, QString _processo,
                                        QString _parametros );

    void
    meuId( int _meu_id );

    void
    incommingMessage( int _id, QString _mensagem );

    void
    killProcess( int _id_dono, Q_PID _processo );

    //slots para comunicação interna
    void
    novoProcesso( int _id_host, GP::Processo* _processo );

    void
    falhouStartProcesso( int _num_requisicao, int _id_dono,
                                              QString _processo,
                                              QStringList _parametros );

    void
    enviaMensagem( int _id_destino, QString _mensagem );

signals:

    void
    sendMessage( int _id_destino, QString _mensagem);

    void
    terminoDeProcesso( motivoFimProcesso _motivo );

    void
    resultadoProcessoStart( int _num_requisicao, QString _processo, Q_PID _pid );

private:
    void
    trataMensagemBalancer( const int& _id, GP::PacoteBase* _pacote );

    void
    trataMensagemLauncher( const int& _id, GP::PacoteBase* _pacote );

    void
    trataStartProcess( const int& _id, GP::PacoteBase* _pacote );

    void
    trataSucessStartProcess( const int& _id, GP::PacoteBase* _pacote );

    void
    trataFailStartProcess( const int& _id, GP::PacoteBase* _pacote );
};

#endif // GERENCIADORPROCESSOS_H
