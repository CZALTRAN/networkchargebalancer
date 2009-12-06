#ifndef REDEADAPTOR_H
#define REDEADAPTOR_H

#include <QDBusAbstractAdaptor>

class GerenciadorDBus;

class RedeAdaptor : public QDBusAbstractAdaptor
{
Q_OBJECT
Q_CLASSINFO("D-Bus Interface", "uel.computacao.xboga.rede")
public:

    RedeAdaptor( GerenciadorDBus* _parent );

public slots:

};

#endif // REDEADAPTOR_H
