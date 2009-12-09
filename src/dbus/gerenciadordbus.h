#ifndef GERENCIADORDBUS_H
#define GERENCIADORDBUS_H

#include <QObject>
#include <QDBusAbstractAdaptor>

class GerenciadorDBus : public QObject
{
Q_OBJECT
public:
    GerenciadorDBus(QObject *parent = 0);

    ~GerenciadorDBus();

    bool
    registrarNovoAdaptador( QDBusAbstractAdaptor* adaptador, QString _path);

};

#endif // GERENCIADORDBUS_H
