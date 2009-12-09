#include "processolocalouimportado.h"

#include <QTextStream>
#include <QDebug>

GP::ProcessoLocalOuImportado::ProcessoLocalOuImportado(QObject* _parent)
    : GP::Processo(_parent)
{
}

GP::ProcessoLocalOuImportado::~ProcessoLocalOuImportado()
{
    this->processo->kill();
}

void
GP::ProcessoLocalOuImportado::start(const QString& _processo,
                                    const QStringList& _parametros)
{
    qDebug() << Q_FUNC_INFO << "startando processo: " << _processo << _parametros.size();

    for( int i = 0; i<_parametros.size(); i++ )
    {
        qDebug() << Q_FUNC_INFO << "valor parametro: " << _parametros[i];
    }
    this->processo = new QProcess(this);

    this->processo->setProcessChannelMode(QProcess::MergedChannels);

    QObject::connect(this->processo, SIGNAL(readyReadStandardOutput()),
                     this, SLOT(pegaSaidaProcesso()));

    this->processo->start(_processo, _parametros);

    this->pid = this->processo->pid();
}

bool
GP::ProcessoLocalOuImportado::waitForStarted(int _tempo)
{
    return this->processo->waitForStarted(_tempo);
}

void
GP::ProcessoLocalOuImportado::stdIn(const QString& _entrada)
{
    this->processo->write(_entrada.toStdString().c_str());
}

void
GP::ProcessoLocalOuImportado::pegaSaidaProcesso()
{
    QString
    retorno;

    QStringList
    linha_retorno;

    QTextStream
    stream_saida(this->processo);

    while(!stream_saida.atEnd())
    {
        stream_saida >> retorno;

        linha_retorno.append(retorno);
    }

    retorno = linha_retorno.join(" ");

    emit this->stdOutAndErr(this->pid, this->num_requisicao, retorno);
}
