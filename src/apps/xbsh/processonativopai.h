#ifndef PROCESSONATIVOPAI_H
#define PROCESSONATIVOPAI_H

#include <QStringList>
#include <QThread>

#include "../gpinterface.h"

class ProcessoNativoPai : public QThread
{
public:

    int
    return_code;

    ProcessoNativoPai( const QStringList& _args, QObject* _parent = 0 );

    virtual void
    run() = 0;

protected:

    GPInterface*
    gp_interface;

    QStringList
    args;

    virtual void
    printHelp() = 0;

    QString
    getStringArgument( const QString& _parametro );

    int
    getIntArgument( const QString& _parametro );

    void
    throwError( const QString& _erro );

};

#endif // PROCESSONATIVOPAI_H
