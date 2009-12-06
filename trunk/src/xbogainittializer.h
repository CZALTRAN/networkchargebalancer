#ifndef XBOGAINITTIALIZER_H
#define XBOGAINITTIALIZER_H

#include <QObject>

#include "rede/gerenciadorrede.h"
#include "gerenciador_processos/gerenciadorprocessos.h"
#include "dbus/gerenciadordbus.h"

class XBogaInittializer : public QObject
{
Q_OBJECT
public:
    XBogaInittializer(int argc, char* argv[], QObject *parent = 0);

signals:

public slots:

private:

    GerenciadorProcessos*
    gprocessos;

    GerenciadorRede*
    grede;

    GerenciadorDBus*
    dbus;

};

#endif // XBOGAINITTIALIZER_H
