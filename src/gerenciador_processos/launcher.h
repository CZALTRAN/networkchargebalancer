#ifndef LAUNCHER_H
#define LAUNCHER_H

#include <QObject>

namespace GP
{
    class Launcher : public QObject
    {
    Q_OBJECT
    public:
        Launcher(QObject *parent = 0);

        ~Launcher();

    signals:

    public slots:

        void
        processoStart( const QString& );
    };
}

#endif // LAUNCHER_H
