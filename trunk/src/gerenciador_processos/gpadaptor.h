#ifndef GPADAPTOR_H
#define GPADAPTOR_H

#include <QDBusAbstractAdaptor>

typedef qint64 Q_PID;

class GPAdaptor : public QDBusAbstractAdaptor
{
Q_OBJECT
Q_CLASSINFO("D-Bus Interface", "uel.computacao.xboga.gp")
public:

    GPAdaptor( QObject* _parent );

public slots:

    quint64
    startProcesso( QString _nome_processo, QString _parametros );

    Q_NOREPLY void
    standardInput( int _registro, QString _mensagem);

signals:

    Q_SCRIPTABLE void
    signalStartProcesso( int _registro, QString _processo, QString _parametros );

    Q_SCRIPTABLE void
    signalStandardInput( int _registro, QString _mensagem );

//sinais exportados
    void
    resultStartProcesso( int _id_requisicao, QString _processo, Q_PID _pid);

    void
    standardOutput( int _registro, QString _mensagem );
};

#endif // GPADAPTOR_H
