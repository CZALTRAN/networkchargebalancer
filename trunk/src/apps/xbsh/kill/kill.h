#ifndef KILL_H
#define KILL_H

#include "../processonativopai.h"

#include "../../gpinterface.h"

class Kill : public ProcessoNativoPai
{
public:
    Kill( const QStringList& _argumentos, QObject* _parent = 0 );

    void
    run();

    void
    printHelp();
};

#endif // KILL_H
