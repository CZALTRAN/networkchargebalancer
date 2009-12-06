#ifndef PROCESSO_H
#define PROCESSO_H

#include <QObject>
#include <QString>

namespace GP{

    class Processo : public QObject
    {
    Q_OBJECT

    private:
        int
        id_dono;

        int
        num_requisicao;

    public:
        Processo( QObject* _parent=0 );

        virtual
        ~Processo();

        int
        getIdDono();

        int
        getNumRequisicao();

        void
        setIdDono( const int& _id_dono );

        void
        setNumRequisicao( const int& _num_requisicao );

        virtual void
        stdIn(const QString& _entrada)=0;

    signals:
        QString
        stdOutAndErr();

    };

}
#endif // PROCESSO_H
