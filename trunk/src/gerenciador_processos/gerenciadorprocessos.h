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

    QHash<const Q_PID&, const GP::Processo*>
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
    void
    startProcess( const QString& _processo, const QStringList& _parametros );

    void
    killProcess( const int& _id_dono, const Q_PID& _processo );

signals:

    void
    sendMessage( const int& _id_destino, const QString& _mensagem);

    void
    messageBalancer( const int& _id, const GP::PacoteBase& _mensagem );

    void
    messageLauncher( const int& _id, const GP::PacoteBase& _mensagem );

    void
    terminoDeProcesso( const motivoFimProcesso& _motivo );
};

#endif // GERENCIADORPROCESSOS_H
