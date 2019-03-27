#include "serverthings.h"

ServerThings::ServerThings(QObject *parent) : QObject(parent)
{

    tcpServer = new QTcpServer();
}

QList<QTcpSocket*> ServerThings::getClients()
{
    return clients;
}

void ServerThings::newConnection()
{
    QTcpSocket *clientSocket = tcpServer->nextPendingConnection();
    //connette il segnale disconnessione e cancella il socket esistente
    connect(clientSocket,&QTcpSocket::disconnected,clientSocket,&QTcpSocket::deleteLater);


}

void ServerThings::readClient()
{
    QTcpSocket *clientSocket = static_cast<QTcpSocket*>(sender());
    QDataStream in (clientSocket);

    for (;;) {
        if(!m_nNextBlockSize){
            if(clientSocket->bytesAvailable()< m_nNextBlockSize){

                QString str;
                in >> str;

                emit recivedMessage(str);
                m_nNextBlockSize = 0;
                if(sendToClient)

            }
        }


    }

}

qint64 ServerThings::sendToClient(QTcpSocket *socket, const QString &str)
{
    /*
    QByteArray arrBlock;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
    //out.setVersion(QDataStream::Qt_5_10);
    //out << quint16(0) << QTime::currentTime() << str;
    out << quint16(0) << str;

    out.device()->seek(0);
    out << quint16(arrBlock.size() - sizeof(quint16));

    return socket->write(arrBlock);
    */


    QByteArray arrBlock;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);

    QSqlQuery query ("SELECT * FROM riparazioni");
    while (query.next()) {
        QSqlRecord record = query.record();

    }

}QSqlQuery

/*
QSqlQuery query("SELECT * FROM newTab");
QVector<QStringList> lst;
while (query.next())
{
    QSqlRecord record = query.record();
    QStringList tmp;
    for(int i=0; i < record.count(); i++)
    {
        tmp << record.value(i).toString();
    }
    lst.append(tmp);
}
foreach (const QStringList &var, lst) {
    qDebug() << var;
}
*/
