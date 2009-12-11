#ifndef PS_H
#define PS_H

#include "../processonativopai.h"

class Ps : public ProcessoNativoPai
{
public:
    Ps( const QStringList& _argumentos, QObject* _parent = 0 );

    void
    run();

    void
    printHelp();
};

#endif // PS_H
