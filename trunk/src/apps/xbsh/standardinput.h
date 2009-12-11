#ifndef STANDARDINPUT_H
#define STANDARDINPUT_H

#include <QThread>

class GerenciadorLancamento;

class StandardInput : public QThread
{
Q_OBJECT
public:
    StandardInput( GerenciadorLancamento* _parent = 0 );

    void
    run();

signals:

    void
    entrada(QString _input);
};

#endif // STANDARDINPUT_H
