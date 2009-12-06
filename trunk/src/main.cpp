#include <QCoreApplication>

#include "xbogainittializer.h"

int main( int argc, char* argv[])
{
    QCoreApplication
    xboga(argc,argv);

    XBogaInittializer*
    xboga_manager = new XBogaInittializer(argc,argv);

    return xboga.exec();
}
