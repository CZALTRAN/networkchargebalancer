#include "gpinterface.h"

#include <QDebug>

GPInterface::GPInterface( QObject* _parent)
    : QObject(_parent)
{
    this->gp_interface = new QDBusInterface(
            "uel.computacao.xboga",
            "/gp",
            "uel.computacao.xboga.gp",
            QDBusConnection::sessionBus(),
            this);

    if ( this->gp_interface->lastError().type() != QDBusError::NoError )
    {
        qDebug() << Q_FUNC_INFO <<"erro ao acessar a interface de gp do xboga";
    }
    else
    {

        this->connect( this->gp_interface,
                       SIGNAL(standardOutput( int , int , QString )),
                       SLOT(slotStandardOutput(int, int, QString ))
                       );

        this->connect( this->gp_interface,
                       SIGNAL(resultStartProcesso( int, QString, int )),
                       SLOT(slotResultStartProcesso( int, QString, int ))
                       );

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
    parametros;

    parametros.push_back(_nome_processo);
    parametros.push_back(_parametros);

    QList<QVariant>
    retorno = this->gp_interface->callWithArgumentList(
            QDBus::Block,
            "startProcesso",
            parametros ).arguments();

    int
    requisicao_id = retorno[0].toInt();

    this->minhas_requisicoes.push_back( requisicao_id);

    return requisicao_id;
}

void
GPInterface::slotResultStartProcesso( int _id_requisicao,
                                  QString _processo,
                                  int _pid)
{
    if ( this->minhas_requisicoes.indexOf( _id_requisicao ) != -1 )
    {
        emit this->resultStartProcesso(_id_requisicao,
                                       _processo,
                                       _pid);
    }
}

void
GPInterface::slotStandardOutput( int _processo,
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
