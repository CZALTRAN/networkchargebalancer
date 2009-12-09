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
    standardInput( Q_PID _processo, int _registro, QString _mensagem);

    void
    slotStandardOutput( Q_PID _processo, int _registro, QString _mensagem );

    void
    slotResultStartProcesso( int _id_requisicao, QString _processo, Q_PID _pid );

signals:

    Q_SCRIPTABLE void
    signalStartProcesso( int _registro, QString _processo, QString _parametros );

    Q_SCRIPTABLE void
    signalStandardInput( Q_PID _processo, int _registro, QString _mensagem );

//sinais exportados
    void
    resultStartProcesso( int _id_requisicao, QString _processo, Q_PID _pid);

    void
    standardOutput( Q_PID _processo, int _registro, QString _mensagem );
};

#endif // GPADAPTOR_H
