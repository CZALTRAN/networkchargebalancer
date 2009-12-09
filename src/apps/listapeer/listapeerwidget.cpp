#include "listapeerwidget.h"

#include <QDebug>
#include <QStringList>

ListaPeerWidget::ListaPeerWidget( QWidget* _parent )
    : QTableWidget(_parent)
{
    this->interface_rede = new RedeInterface(this);

    QString
    linha;

    QTableWidgetItem*
    tmp_item;

    this->setColumnCount(2);

    QString
    id;

    QString
    host;

    this->setEnabled(false);

    foreach( linha, this->interface_rede->getListPeers() )
    {
        id = linha.split(';').at(0);

        host = linha.split(';').at(1);

        this->setRowCount( this->rowCount() + 1 );

        tmp_item = new QTableWidgetItem(id, 0);

        this->setItem(this->rowCount() -1 , 0 ,tmp_item);


        tmp_item = new QTableWidgetItem(host, 0);

        this->setItem(this->rowCount() -1 , 1 ,tmp_item);

    }
    QObject::connect( this->interface_rede, SIGNAL(novoPeer(int,QString)),
                      this,SLOT(novoPeer(int,QString)));
}

ListaPeerWidget::~ListaPeerWidget()
{


}

void
ListaPeerWidget::novoPeer(int _id, QString _host )
{
    QTableWidgetItem*
    nova_celula;

    this->setRowCount( this->rowCount() + 1);

    nova_celula = new QTableWidgetItem( QString::number(_id), 0);
    this->setItem( this->rowCount() - 1, 0, nova_celula);

    nova_celula = new QTableWidgetItem( _host, 0);
    this->setItem( this->rowCount() - 1, 1, nova_celula);
}
