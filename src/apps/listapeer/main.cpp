#include <QApplication>

#include "listapeerwidget.h"

int main( int argc, char* argv[])
{
    QApplication app( argc, argv );

    ListaPeerWidget*
    boga = new ListaPeerWidget();

    boga->show();

    return app.exec();
}
