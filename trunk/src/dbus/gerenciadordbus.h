#ifndef GERENCIADORDBUS_H
#define GERENCIADORDBUS_H

#include <QObject>

#include "gpadaptor.h"

class GerenciadorDBus : public QObject
{
Q_OBJECT
public:
    GerenciadorDBus(QObject *parent = 0);

    ~GerenciadorDBus();

signals:

    void
    novaSolicitacaoDeProcesso( QString _processo, QString _parametros );

public slots:

    //testes:
    void
    testeNovoProcesso( QString _processo, QString _parametros);

private:

    GPAdaptor*
    interfaceGP;

    friend class GPAdaptor;
};

#endif // GERENCIADORDBUS_H
