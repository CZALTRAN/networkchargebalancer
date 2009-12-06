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
    novaSolicitacaoDeProcesso( quint64 _id, QString _processo, QString _parametros );

public slots:

    void
    resultStartProcesso( bool _sucesso, QString _processo, quint64 _id );

private:

    GPAdaptor*
    interfaceGP;

    friend class GPAdaptor;
    friend class RedeAdaptor;
};

#endif // GERENCIADORDBUS_H
