#ifndef LISTAPEERWIDGET_H
#define LISTAPEERWIDGET_H

#include <QTableWidget>

#include <redeinterface.h>

class ListaPeerWidget : public QTableWidget
{
Q_OBJECT
public:
    ListaPeerWidget( QWidget* _parent = 0);

    ~ListaPeerWidget();

    void
    updateTable();

public slots:

    void
    novoPeer(QString _host, int _id );

    void
    peerCaiu( int _id );

private:

    RedeInterface*
    interface_rede;

};

#endif // LISTAPEERWIDGET_H
