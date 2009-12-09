#include <QApplication>

#include "monitorrede.h"

int main( int argc, char* argv[])
{
    QApplication
    app(argc,argv);

    MonitorRede*
    form = new MonitorRede();

    form->show();

    return app.exec();
}
