#ifndef GPADAPTOR_H
#define GPADAPTOR_H

#include <QDBusAbstractAdaptor>

class GerenciadorDBus;

class GPAdaptor : public QDBusAbstractAdaptor
{
Q_OBJECT
Q_CLASSINFO("D-Bus Interface", "uel.computacao.xboga.gp")
public:

    GPAdaptor( GerenciadorDBus* _parent );

public slots:

    quint64
    startProcesso( QString _nome_processo, QString _parametros );

    Q_NOREPLY void
    standardInput( quint64, QString );

signals:

    void
    resultStartProcesso( bool ok ,
                         qulonglong _pid,
                         QString _processo);


    friend class GerenciadorDBus;

};

#endif // GPADAPTOR_H
