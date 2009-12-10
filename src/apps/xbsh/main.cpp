#include <QtCore/QCoreApplication>

#include "xbsh.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    XBSh*
    b = new XBSh();

    return a.exec();
}
