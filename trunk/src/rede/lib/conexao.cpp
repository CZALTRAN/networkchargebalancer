/*
   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License version 2 as published by the Free Software Foundation.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public License
   along with this library; see the file COPYING.LIB.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/
#include "conexao.h"

using namespace Rede_Cliente;

Conexao::Conexao(QObject* _parent ) : QTcpSocket(_parent)
{
    QObject::connect(this, SIGNAL(readyRead()),
                     this, SLOT(recebeDado()));
}

void
Conexao::enviaDado(QString _dado)
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
    }
}

void
Conexao::recebeDado()
{
    quint16 bloco = 0;
    QDataStream entrada(this);
    entrada.setVersion(QDataStream::Qt_4_0);
    
    while(this->bytesAvailable() > sizeof(quint16))
    {
        entrada >> bloco;

        if(this->bytesAvailable() < bloco)
            return;

        QString mensagem;
        entrada >> mensagem;

        emit this->incommingMessage(mensagem);
    }

}
