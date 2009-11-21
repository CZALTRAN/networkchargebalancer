#ifndef CONEXAO_H
#define CONEXAO_H

#include <QTcpSocket>

#define PORTA_PRIMEIRA_CONEXAO

namespace Rede
{
    class Conexao : public QTcpSocket
    {
        Q_OBJECT

    public:

        Conexao(QObject* _parent = NULL);

    public slots:

        void
        enviaDado(QString _dado);

        void
        recebeDado();

    signals:

        void
        incommingMessage(QString _dado);
    };
}
#endif // CONEXAO_H
