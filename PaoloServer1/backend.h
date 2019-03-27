#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>
#include "serverResearch.h"

class Backend : public QObject
{
    Q_OBJECT
public:
    explicit Backend(QObject *parent = nullptr);

signals:
    void smbConnected();

public slots:
    QString stopServer();
    QString startServer();
     void smbConnectedToServer();
private:
     ClientResearch *server;
};

#endif // BACKEND_H
