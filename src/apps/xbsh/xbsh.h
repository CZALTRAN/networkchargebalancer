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

    void
    erroAoStart( const QString& _mensagem );

protected slots:

    void
    terminated( int _return_code );

    void
    displayPS1();
    
private:

    StandardInput*
    stdin;

    GerenciadorLancamento*
    gerenciador_lancamento;

    void
    displayBoasVindas();

};

#endif // XBSH_H
