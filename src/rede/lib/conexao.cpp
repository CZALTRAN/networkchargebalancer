#include "conexao.h"

#include <QDebug>

Rede::Conexao::Conexao(QObject* _parent ) : QTcpSocket(_parent)
{
    QObject::connect(this, SIGNAL(readyRead()),
                     this, SLOT(recebeDado()));
}

void
Rede::Conexao::enviaDado(QString _dado)
{
    if(this->isWritable())
    {
        QByteArray bloco;
        QDataStream saida(&bloco, QIODevice::ReadWrite);

        saida << (quint16)0;
        saida << _dado;
        saida.device()->seek(0);
        saida << (quint16)(bloco.size() - sizeof(quint16));

        this->flush();
        this->write(bloco);
        qDebug() << Q_FUNC_INFO << _dado;
    }
}

void
Rede::Conexao::recebeDado()
{
    quint16 bloco = 0;
    QDataStream entrada(this);

    while(this->bytesAvailable() > sizeof(quint16))
    {
        entrada >> bloco;

        if(this->bytesAvailable() < bloco)
            return;

        QString mensagem;
        entrada >> mensagem;

        qDebug() << Q_FUNC_INFO << mensagem;
        emit this->incommingMessage(mensagem);
    }
}
