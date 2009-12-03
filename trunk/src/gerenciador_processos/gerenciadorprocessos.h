#ifndef GERENCIADORPROCESSOS_H
#define GERENCIADORPROCESSOS_H

#include <QObject>

#include "balanceadorcarga.h"
#include "launcher.h"

class GerenciadorProcessos : public QObject
{
Q_OBJECT

    GP::BalanceadorCarga
    balancer;

    GP::Launcher
    launcher;

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

signals:

    void
    sendMessage( const int& _id_destino, const QString& _mensagem);

    void
    messageBalancer( const int& _id, const GP::PacoteBase& _mensagem );

    void
    messageLauncher( const int& _id, const GP::PacoteBase& _mensagem );

};

#endif // GERENCIADORPROCESSOS_H
