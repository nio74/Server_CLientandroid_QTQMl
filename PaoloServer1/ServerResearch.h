#ifndef SERVERTHINGS_H
#define SERVERTHINGS_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QDataStream>
#include <QList>
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QBuffer>
#include <servicesmatematichs.h>

class ClientResearch : public QObject
{
    Q_OBJECT
public:
    explicit ClientResearch(QObject *parent = nullptr);

    QTcpServer *tcpServer;
    QList<QTcpSocket*> getClients();
    

signals:
    void recivedMessage(QString msg);
    void gotNewMesssage(QString msg);

public slots:
    virtual void newConnection();
    void readClient();
    qint64 sendToClient(QTcpSocket *socket, const QString &str);
    qint64 sendMag(QTcpSocket *socket, const QString &str);
    qint64 updateRiparazione(qint64 codice,double prezzoCosto,double prezzoPubblico);
    void connectDb();
    void disconnectDb();

private:
    QSqlDatabase db;
    QList<QTcpSocket*> clients;
    quint16 m_nNextBlockSize = 0;
    QSqlQuery query;

    ServicesMatematichs *sermath;


    int code;
    double pCost, pPublic;
    
};

#endif // SERVERTHINGS_H
