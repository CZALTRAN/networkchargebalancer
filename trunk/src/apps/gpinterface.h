#ifndef GP_INTERFACE_H
#define GP_INTERFACE_H

#include <QObject>
#include <QDBusInterface>
#include <QDBusConnection>
#include <QList>

class GPInterface : public QObject
{
Q_OBJECT
public:

    GPInterface( QObject* _parent = 0);

    ~GPInterface();

    bool
    redeOk() const;

    int
    startProcesso( QString _nome_processo, QString _parametros );

    QStringList
    getAllProcesses();

public slots:

    void
    slotResultStartProcesso( int _id_requisicao, QString _processo, int _pid);

    void
    slotStandardOutput( int _processo, int _registro, QString _mensagem );

    void
    slotStandardInput(qint64 _processo, int _registro, QString _mensagem);

    void
    slotStartProcesso( QString _nome_processo, QString _parametros);

    void
    slotProcessoTerminado( int _processo, int _registro, int retorno );

    void
    matarProcesso( int _pid, int _id_peer_dono, int _requisicao );

signals:

    void
    standardInput( int _processo, int _registro, QString _mensagem);

    void
    resultStartProcesso( int _id_requisicao, QString _processo, qint64 _pid );

    void
    standardOutput(  int _processo, int _registro, QString _mensagem );

    void
    processoTerminado( int _processo, int _registro, int retorno );

private:

    QDBusInterface*
    gp_interface;

    QList<int>
    minhas_requisicoes;

    QList<QVariant>
    getArgumentsFromCall( QString _metodo );
};


#endif //GP_INTERFACE_H
