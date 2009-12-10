#include "gpinterface.h"

#include <QDebug>
GPInterface::GPInterface( QObject* _parent)
    : QObject(_parent)
{
    this->gp_interface = new QDBusInterface(
            "uel.computacao.xboga",
            "/gp",
            "uel.computacao.gp",
            QDBusConnection::sessionBus(),
            this);

    if ( ! this->redeOk() )
    {
        qDebug() << Q_FUNC_INFO << "nao foi prossivel detectar o servico dbus";
    }
}

GPInterface::~GPInterface()
{

}

bool
GPInterface::redeOk() const
{
    return (QDBusConnection::sessionBus().lastError().type() == QDBusError::NoError);
}

int
GPInterface::startProcesso( QString _nome_processo, QString _parametros )
{
    QList<QVariant>
    retorno = this->getArgumentsFromCall("startProcesso");

    int
    requisicao_id = retorno[0].toInt();

    this->minhas_requisicoes.push_back( requisicao_id);

    return requisicao_id;
}

void
GPInterface::slotResultStartProcesso( int _id_requisicao,
                                  QString _processo,
                                  qint64 _pid)
{
    if ( this->minhas_requisicoes.indexOf( _id_requisicao ) != -1 )
    {
        emit this->resultStartProcesso(_id_requisicao,
                                       _processo,
                                       _pid);
    }
}

void
GPInterface::slotStandardOutput( qint64 _processo,
                             int _registro,
                             QString _mensagem )
{
    if ( this->minhas_requisicoes.indexOf(_registro) != -1 )
    {
        emit this->standardOutput( _processo,
                                   _registro,
                                   _mensagem);
    }
}

void
GPInterface::slotStandardInput(qint64 _processo,
                               int _registro,
                               QString _mensagem)
{
    emit this->standardInput( _processo,
                              _registro,
                              _mensagem);
}

void
GPInterface::slotStartProcesso( QString _nome_processo, QString _parametros)
{
    emit this->startProcesso( _nome_processo,
                              _parametros );
}

QList<QVariant>
GPInterface::getArgumentsFromCall( QString _metodo )
{
    return this->gp_interface->call( _metodo ).arguments();
}
