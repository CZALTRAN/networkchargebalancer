#ifndef GPADAPTOR_H
#define GPADAPTOR_H

#include <QDBusAbstractAdaptor>

class GerenciadorDBus;

class GPAdaptor : public QDBusAbstractAdaptor
{
Q_OBJECT
Q_CLASSINFO("D-Bus Interface", "uel.computacao.xboga.GP")
public:

    GPAdaptor( GerenciadorDBus* _parent );

public slots:

    Q_NOREPLY void
    startProcesso( QString _nome_processo, QString _parametros );

signals:

    void
    resultStartProcesso( qulonglong _pid, QString _processo );

};

#endif // GPADAPTOR_H
