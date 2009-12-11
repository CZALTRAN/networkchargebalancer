#ifndef GPADAPTOR_H
#define GPADAPTOR_H

#include <QDBusAbstractAdaptor>

typedef qint64 Q_PID;

class GerenciadorProcessos;

class GPAdaptor : public QDBusAbstractAdaptor
{
Q_OBJECT
Q_CLASSINFO("D-Bus Interface", "uel.computacao.xboga.gp")
public:

    GPAdaptor( GerenciadorProcessos* _parent );

public slots:

    Q_NOREPLY void
    standardInput( qint64 _processo, int _registro, QString _mensagem);

    quint64
    startProcesso( QString _nome_processo, QString _parametros );

    Q_SCRIPTABLE void
    slotStandardOutput( qint64 _processo, int _registro, QString _mensagem );

    Q_SCRIPTABLE void
    slotResultStartProcesso( int _id_requisicao, QString _processo, qint64 _pid );

    Q_SCRIPTABLE void
    slotProcessoTerminou( qint64 _processo, int _registro, int retorno);

signals:

    //sinais exportados
    void
    resultStartProcesso( int _id_requisicao, QString _processo, int _pid);

    void
    standardOutput( int _processo, int _registro, QString _mensagem );

    void
    processoTerminou( int _processo, int _registro, int retorno);

    Q_SCRIPTABLE void
    signalStartProcesso( int _registro, QString _processo, QString _parametros );

    Q_SCRIPTABLE void
    signalStandardInput( qint64 _processo, int _registro, QString _mensagem );

private:

    void
    sendSignal( QString _metodo, QList<QVariant> _argumentos);
};

#endif // GPADAPTOR_H
