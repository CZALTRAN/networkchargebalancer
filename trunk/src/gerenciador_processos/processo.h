#ifndef PROCESSO_H
#define PROCESSO_H

#include <QObject>
#include <QProcess>
#include <QString>

namespace GP{

    class Processo : public QObject
    {
    Q_OBJECT

    protected:
        Q_PID
        pid;

        QString
        nome;
        
        int
        id_dono;

        int
        id_host;

        int
        num_requisicao;

    public:
        Processo( QObject* _parent=0 );

        virtual
        ~Processo();

        Q_PID
        getPid();

        QString
        getNome();

        int
        getIdDono();

        int
        getNumRequisicao();

        void
        setPid( const Q_PID& _pid );

        void
        setNome( const QString& _nome );

        void
        setIdDono( const int& _id_dono );

        void
        setNumRequisicao( const int& _num_requisicao );

        int
        getIdHost();

        void
        setIdHost( const int& _id_host );

        virtual void
        stdIn(const QString& _entrada)=0;

    signals:
        QString
        stdOutAndErr(Q_PID _pid, int, QString _saida);

    };

}
#endif // PROCESSO_H
