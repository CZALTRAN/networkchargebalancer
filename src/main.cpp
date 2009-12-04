#include <QCoreApplication>

#include "xbogainittializer.h"

int main( int argc, char* argv[])
{
    QCoreApplication
    xboga(argc,argv);

    XBogaInittializer(argc,argv);

    return xboga.exec();
}
