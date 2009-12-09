#ifndef GP_INTERFACE_H
#define GP_INTERFACE_H

#include <QObject>
#include <QDBusAbstractInterface>
#include <QDBusConnection>

class GPInterface : public QObject
{
Q_OBJECT
public:

    GPInterface( QObject* _parent = 0;);

    ~GPInterface();

private:

    QDBusInterface*
    gp_interface;
};


#endif //GP_INTERFACE_H
