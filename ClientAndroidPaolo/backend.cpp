#include "backend.h"

Backend::Backend(QObject *parent) : QObject(parent)
{
    client = new ClientResearch("192.168.1.8",6547);

    connect(client, &ClientResearch::hasReadSome, this, &Backend::receivedSomething);
    connect(client, &ClientResearch::statusChanged, this, &Backend::setStatus);
    // FIXME change this connection to the new syntax
    connect(client->tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(gotError(QAbstractSocket::SocketError)));

    //connect data to source database
    connect(client, &ClientResearch::sendRiparazione, this ,&Backend::recivedRiparazione);


}


bool Backend::getStatus()
{
    return client->getStatus();
}

void Backend::setStatus(bool newStatus)
{
    //qDebug() << "new status is:" << newStatus;
    if (newStatus)
        { emit statusChanged("CONNECTED"); }
    else
    { emit statusChanged("DISCONNECTED"); }
}

void Backend::recivedRiparazione(int code, double p_pCosto, double p_pPubblico)
{
    emit sendCode(code);
    emit sendPCosto(p_pCosto);
    emit sendPPubblico(p_pPubblico);

}

void Backend::receivedSomething(QString msg)
{
    emit someMessage(msg);
}



void Backend::gotError(QAbstractSocket::SocketError err)
{
    //qDebug() << "got error";
    QString strError = "unknown";
    switch (err)
    {
        case 0:
            strError = "Connection was refused";
            break;
        case 1:
            strError = "Remote host closed the connection";
            break;
        case 2:
            strError = "Host address was not found";
            break;
        case 5:
            strError = "Connection timed out";
            break;
        default:
            strError = "Unknown error";
    }

    emit someError(strError);
}

void Backend::sendSearch(QString msg, quint16 type)
{
    QByteArray arrBlock;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
    //out.setVersion(QDataStream::Qt_5_10);
    out << qint16(0)  << type << msg ;

   // out << msg ;

    out.device()->seek(0);
    out << quint16(arrBlock.size() - sizeof(quint16));

    client->tcpSocket->write(arrBlock);
}

void Backend::connectClicked()
{
    client->connect2host();
}

/*
void Backend::sendUpdateRiparazione(QString codice,qint16 type)
{


    QByteArray arrBlock;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
    //out.setVersion(QDataStream::Qt_5_10);
    out << qint16(0)  << codice << type ;

    out.device()->seek(0);
    out << quint16(arrBlock.size() - sizeof(quint16));

    client->tcpSocket->write(arrBlock);



}
*/
void Backend::sendUpdateRiparazione(qint64 type,qint64 codice, double pCosto, double pPubblico)
{
    QDataStream out(client->tcpSocket);
    out  << type << codice << pCosto << pPubblico;
}

void Backend::disconnectClicked()
{
    client->closeConnection();
}


