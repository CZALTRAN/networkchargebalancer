#ifndef LISTAPEERWIDGET_H
#define LISTAPEERWIDGET_H

#include <QTableWidget>

#include <redeinterface.h>

class ListaPeerWidget : public QTableWidget
{
public:
    ListaPeerWidget( QWidget* _parent = 0);

    ~ListaPeerWidget();

public slots:

    void
    novoPeer(int _id, QString _host );

private:

    RedeInterface*
    interface_rede;

};

#endif // LISTAPEERWIDGET_H
