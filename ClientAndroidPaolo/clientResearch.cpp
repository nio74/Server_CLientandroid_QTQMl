#include "clientResearch.h"
#include <QBuffer>


ClientResearch::ClientResearch(const QString hostAddress, int portNumber) : QObject (),m_nNextBlockSize(0)
{
    status = false;
    tcpSocket = new QTcpSocket();

    host = hostAddress;
    port = portNumber;

    timeoutTimer = new QTimer();
    timeoutTimer->setSingleShot(true);
    connect(timeoutTimer, &QTimer::timeout, this, &ClientResearch::connectionTimeout);

    connect(tcpSocket, &QTcpSocket::disconnected, this, &ClientResearch::closeConnection);

}

bool ClientResearch::getStatus(){return status;}

void ClientResearch::closeConnection()
{
    timeoutTimer->stop();

    //qDebug() << tcpSocket->state();
    disconnect(tcpSocket, &QTcpSocket::connected, 0, 0);
    disconnect(tcpSocket, &QTcpSocket::readyRead, 0, 0);

    bool shouldEmit = false;
    switch (tcpSocket->state())
    {
        case 0:
            tcpSocket->disconnectFromHost();
            shouldEmit = true;
            break;
        case 2:
            tcpSocket->abort();
            shouldEmit = true;
            break;
        default:
            tcpSocket->abort();
    }

    if (shouldEmit)
    {
        status = false;
        emit statusChanged(status);
    }

}

void ClientResearch::connect2host()
{

    timeoutTimer->start(3000);

    tcpSocket->connectToHost(host, port);
    connect(tcpSocket, &QTcpSocket::connected, this, &ClientResearch::connected);
    connect(tcpSocket, &QTcpSocket::readyRead, this, &ClientResearch::readyRead);
}

void ClientResearch::readyRead()
{
   QDataStream in(tcpSocket);

    in >> code >> pCost >> pPublic;

    qDebug() << code << pCost << pPublic;

    emit sendRiparazione(code,pCost,pPublic);
    //afhter send data close the connction
    this->closeConnection();

}

void ClientResearch::connected()
{
    status = true;
    emit statusChanged(status);

}

void ClientResearch::connectionTimeout()
{
    //qDebug() << tcpSocket->state();
    if(tcpSocket->state() == QAbstractSocket::ConnectingState)
    {
        tcpSocket->abort();
        emit tcpSocket->error(QAbstractSocket::SocketTimeoutError);
    }
}
