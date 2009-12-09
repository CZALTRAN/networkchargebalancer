#ifndef MONITORREDE_H
#define MONITORREDE_H

#include <QWidget>
#include <QTimer>

#include "ui_monitor_rede.h"
#include "../redeinterface.h"

class MonitorRede : public QWidget
{
Q_OBJECT
public:
    MonitorRede(QWidget* _parent = 0);

public slots:

    void
    setRedeStatus( );

    void
    atualizaServer();

private:

    Ui::Form* form;

    RedeInterface*
    rede_interface;

    QTimer*
    watch_dog;
};

#endif // MONITORREDE_H
