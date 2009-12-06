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

public slots:

private:

    GPAdaptor*
    interfaceGP;
};

#endif // GERENCIADORDBUS_H
