#ifndef CLIENTRESEARCH_H
#define CLIENTRESEARCH_H

#include <QObject>
#include <QString>
#include <QTcpSocket>
#include <QDataStream>
#include <QTimer>

class ClientResearch : public QObject
{
    Q_OBJECT



public:
     ClientResearch(const QString host,int port);
     
     int getPropCode(){return code;}

    QTcpSocket *tcpSocket;
    bool getStatus();
    


public slots:
    void closeConnection();
    void connect2host();

signals:
    void statusChanged(bool);
    void hasReadSome(QString msg);
    void sendRiparazione(int code,double p_pCost,double p_pPublic);

private slots:
    void readyRead();
    void connected();
    void connectionTimeout();

    private:
    QString host;
    int port;
    bool status;
    quint16 m_nNextBlockSize = 0;
    QTimer *timeoutTimer;

    int code;
    double pCost ;
    double pPublic ;

};

#endif // CLIENTRESEARCH_H
