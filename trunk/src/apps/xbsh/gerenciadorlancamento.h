#ifndef GERENCIADORLANCAMENTO_H
#define GERENCIADORLANCAMENTO_H

#include "../gpinterface.h"

#include <QObject>
#include <QStringList>

class GerenciadorLancamento : public QObject
{
Q_OBJECT
public:

    bool
    is_processo_rodando;

    GerenciadorLancamento(QObject *parent = 0);

    void
    processaEntrada( const QString& _entrada );

signals:

    void
    recebiEntrada( QString _entrada );

    void
    endStdOut( QString _saida );

    void
    falhaAoStartProcesso( QString _erro );

    void
    processoTerminado( int _return_code );

protected slots:

    void
    resultProcessoStart( int _id_requisicao, QString _processo, qint64 _pid );

    void
    startStdOut(  int _processo, int _registro, QString _mensagem );

    void
    processoNativoTerminado();

private:

    GPInterface*
    gp_interface;

    qint64
    pid_processo_rodando;

    int
    registro_processo_rodando;

    bool
    isProcessoNativo( const QString& _processo_nome );

    void
    startProcessoNativo( const QString& _processo_nome,
                         const QStringList& _argumentos );
};

#endif // GERENCIADORLANCAMENTO_H
