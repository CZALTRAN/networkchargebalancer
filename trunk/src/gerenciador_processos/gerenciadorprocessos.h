#ifndef GERENCIADORPROCESSOS_H
#define GERENCIADORPROCESSOS_H

#include <QObject>

class GerenciadorProcessos : public QObject
{
Q_OBJECT
public:
    GerenciadorProcessos(QObject * _parent = NULL);

    ~GerenciadorProcessos();

public slots:

    void
    peerNovo( const int& _id );

    void
    peerCaiu( const int& _id );
};

#endif // GERENCIADORPROCESSOS_H
