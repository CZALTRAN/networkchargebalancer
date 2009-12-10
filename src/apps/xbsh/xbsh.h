#ifndef XBSH_H
#define XBSH_H

#include <iostream>

#include <QObject>
#include <QStringList>

#include <QTimer>

#include "gerenciadorlancamento.h"
#include "standardinput.h"

class XBSh : public QObject
{
Q_OBJECT
public:

    XBSh(QObject *_parent = 0);

    ~XBSh();

signals:

public slots:

    void
    recebeEntrada( QString _input );

    void
    displayStdOut(  QString _mensagem );

private:

    StandardInput*
    stdin;

    GerenciadorLancamento*
    gerenciador_lancamento;

    void
    displayBoasVindas();

    void
    displayPS1();
};

#endif // XBSH_H
