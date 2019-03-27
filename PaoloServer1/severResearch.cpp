#include "serverResearch.h"

ClientResearch::ClientResearch(QObject *parent) : QObject(parent)
{

    tcpServer = new QTcpServer();
    sermath = new ServicesMatematichs();

}

QList<QTcpSocket*> ClientResearch::getClients()
{
    return clients;
}

void ClientResearch::newConnection()
{
    QTcpSocket *clientSocket = tcpServer->nextPendingConnection();
    //connette il segnale disconnessione e cancella il socket esistente
    connect(clientSocket,&QTcpSocket::disconnected,clientSocket,&QTcpSocket::deleteLater);
    connect(clientSocket, &QTcpSocket::readyRead, this, &ClientResearch::readClient);


    clients << clientSocket;

    sendToClient(clientSocket, "Reply: connection established");

}
/*
void ClientResearch::readClient()
{
    QTcpSocket *clientSocket = static_cast<QTcpSocket*>(sender());
    QDataStream in(clientSocket);


    for (;;)
        {
            if (!m_nNextBlockSize)
            {
                if (clientSocket->bytesAvailable() < sizeof(quint16)) { break; }
                in >> m_nNextBlockSize;
            }
            if (clientSocket->bytesAvailable() < m_nNextBlockSize) { break; }
            QString str;
            qint16 type;

            emit gotNewMesssage(str);

            m_nNextBlockSize = 0;


        in >> type ;


        switch (type) {

        case 1:if(type == 1){
                in >> str;
                sendToClient(clientSocket, str);
                qDebug()<< "chiamata uno ";
                break;

            }

        case 2:if(type == 2){
                in >> str;
                sendMag(clientSocket, str);
                break;

            }
        case 3:if(type == 3){
                qDebug()<< "chiamata tre ";
                QString c_codice;
                //  double p_prezzoCosto;
                //  double p_prezzoPubblico;
                in  >> c_codice;
                if (!in.commitTransaction())
                                return;
                break;
            }


        }


}

}
*/

void ClientResearch::readClient()
{
    Q_ASSERT(dynamic_cast<QTcpSocket*>(sender()));
    QTcpSocket *clientSocket = static_cast<QTcpSocket*>(sender());
    QDataStream in(clientSocket);
    for (;;) {
        in.startTransaction();
        qint64 type;
        in >> type;
        switch (type) {
        case 1:{
            QString str;
            in >> str;
            if (!in.commitTransaction())
                return;
            sendToClient(clientSocket, str);
            break;
        }
        case 2:{
            QString str;
            in >> str;
            if (!in.commitTransaction())
                return;
            sendMag(clientSocket, str);
            break;
        }
        case 3:{
            qint64 c_codice;
            double p_prezzoCosto;
            double p_prezzoPubblico;
            in >> c_codice >> p_prezzoCosto >> p_prezzoPubblico;
            if (!in.commitTransaction())
                return;
           // doSomethingWithData(c_codice ,p_prezzoCosto ,p_prezzoPubblico);
            break;
        }
        }
    }
}
qint64 ClientResearch::sendToClient(QTcpSocket *socket, const QString &str)
{
    this->connectDb();
    QByteArray byteArray;
    // QBuffer buffer(&byteArray);

    //buffer.open(QIODevice::WriteOnly);
    QDataStream stream(&byteArray,QIODevice::WriteOnly);
    QSqlQuery query;
    query.prepare("SELECT Nbusta,costo,vendita FROM tabripa where  Nbusta =(?)");
    query.bindValue(0, str);
    query.exec();
    while (query.next()){
        if(query.isValid()){
            code = query.record().value("Nbusta").toInt();
            pCost = sermath->lireToEuro( query.record().value("costo").toDouble());
            pPublic = sermath->lireToEuro( query.record().value("vendita").toDouble());

            stream << code <<pCost << pPublic ;
            db.close();



            //buffer.close();
        }

    }

    return socket->write(byteArray);
    this->disconnect();


}

qint64 ClientResearch::sendMag(QTcpSocket *socket, const QString &str)
{

    this->connectDb();
    QByteArray byteArray;
    // QBuffer buffer(&byteArray);

    //buffer.open(QIODevice::WriteOnly);
    QDataStream stream(&byteArray,QIODevice::WriteOnly);
    QSqlQuery query;
    query.prepare("SELECT codice,prezzopu,prezzoco FROM tabmag where  codice =(?)");
    query.bindValue(0, str);
    query.exec();
    while (query.next()){
        if(query.isValid()){
            code = query.record().value("codice").toInt();
            pCost = sermath->lireToEuro( query.record().value("prezzoco").toDouble());
            pPublic = sermath->lireToEuro( query.record().value("prezzopu").toDouble());

            stream << code <<pCost << pPublic ;

            //buffer.close();
        }

    }

    return socket->write(byteArray);
}

qint64 ClientResearch::updateRiparazione(qint64 codice, double prezzoCosto, double prezzoPubblico)
{
    //this->connectDb();
    this->newConnection();
    QSqlQuery query;
    query.prepare("UPDATE tabripa SET costo = :costo vendita=:vendita WHERE Nbusta =:Nbusta");
    query.bindValue(":Nbusta", codice);
    query.bindValue(":costo", prezzoCosto);
    query.bindValue(":vendita", prezzoPubblico);

    return query.exec();
    db.close();

}








void ClientResearch::connectDb()
{

    db = QSqlDatabase::addDatabase("QODBC3");

    db.setDatabaseName("DRIVER={Microsoft Access Driver (*.mdb)};FIL={MS Access};DBQ=D:\\GoogleDrive\\dati.mdb;Uid=;Pwd=gmpa;");

    db.open();

    if(!db.isOpen()){
        qDebug() <<db.lastError();
    }
    else
        {
            qDebug() << "Database: connection ok";
            // createDatabase("Sensor_Objects");
           // db.close();
    }
}

void ClientResearch::disconnectDb()
{
    db.close();
}

