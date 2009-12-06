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

    void
    incommingMessage( const int& _id, const QString& _mensagem );

public slots:

    //slots para comunicação externa
    void
    processoStart( int _num_requisicao, QString _processo,
                                        QString _parametros );

    void
    meuId( int _meu_id );

    void
    killProcess( int _id_dono, Q_PID _processo );

    //slots para comunicação interna
    void
    novoProcesso( int _id_host, const GP::Processo* _processo );

    void
    falhouStartProcesso( int _num_requisicao, int _id_dono,
                                              QString _processo );

signals:

    void
    sendMessage( const int& _id_destino, const QString& _mensagem);

    void
    terminoDeProcesso( const motivoFimProcesso& _motivo );
};

#endif // GERENCIADORPROCESSOS_H
