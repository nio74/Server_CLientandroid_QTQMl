#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>
#include "clientResearch.h"

class Backend : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool currentStatus READ getStatus NOTIFY statusChanged)
public:
    explicit Backend(QObject *parent = nullptr);
     bool getStatus();

signals:
     void statusChanged(QString newStatus);
     void someError(QString err);
     void someMessage(QString msg);
     void sendCode(int code);
     void sendPCosto(double p_pCosto);
     void sendPPubblico(double p_pPubblico);

public slots:

     void setStatus(bool newStatus);

     void recivedRiparazione(int code,double p_pCosto,double p_Pubblico);
     void receivedSomething(QString msg);
     void gotError(QAbstractSocket::SocketError err);
     void sendSearch(QString msg, quint16 type);
     void sendUpdateRiparazione(qint64 type,qint64 codice, double pCosto, double pPubblico);
     void connectClicked();
     void disconnectClicked();
private:
     ClientResearch *client;
     int codiceBusta;
     double prezzoCosto,prezzoPubblico;

};

#endif // BACKEND_H
