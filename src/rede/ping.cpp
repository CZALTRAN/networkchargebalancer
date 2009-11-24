#include "ping.h"

#include <cstdlib>
#include <QTextStream>
#include <QDebug>

#include "redeconfig.h"

Rede::Ping::Ping( QString _host, QString _interface ) : QObject()
{
    QString
    programa;

    QStringList
    parametros;

    parametros << "-c" << "4" << "-I" << _interface << _host;

    programa = "ping";

    this->ping = new QProcess(this);

    this->ping->setProcessChannelMode(QProcess::MergedChannels);

    QObject::connect(this->ping, SIGNAL(readyReadStandardOutput()),
                     this, SLOT(slotPingStdOutAndErr()));

    this->ping->start(programa, parametros);

    this->ping->waitForFinished(40000);
}

Rede::Ping::~Ping()
{

}

QStringList
Rede::Ping::getRetorno()
{
    return this->retorno;
}

void
Rede::Ping::slotPingStdOutAndErr()
{
    QString
    linha_retorno;

    QTextStream
    stream_saida(this->ping);

    while(!stream_saida.atEnd())
    {
        stream_saida >> linha_retorno;
        qDebug() << Q_FUNC_INFO << linha_retorno;
    }

    this->retorno.append(linha_retorno);
}
