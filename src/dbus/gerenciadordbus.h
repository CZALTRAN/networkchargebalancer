#ifndef GERENCIADORDBUS_H
#define GERENCIADORDBUS_H

#include <QObject>

#include "gpadaptor.h"
#include "redeadaptor.h"

class GerenciadorDBus : public QObject
{
Q_OBJECT
public:
    GerenciadorDBus(QObject *parent = 0);

    ~GerenciadorDBus();

signals:

    void
    novaSolicitacaoDeProcesso( int _id, QString _processo, QString _parametros );

public slots:

    void
    resultStartProcesso( bool _sucesso, QString _processo, int _id );

private:

    GPAdaptor*
    interfaceGP;

    RedeAdaptor*
    interfaceRede;

    friend class GPAdaptor;
    friend class RedeAdaptor;
};

#endif // GERENCIADORDBUS_H