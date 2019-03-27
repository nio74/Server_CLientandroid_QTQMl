#include "backend.h"

Backend::Backend(QObject *parent) : QObject(parent)
{
    server = new ClientResearch();

    connect(server->tcpServer,&QTcpServer::newConnection,this,&Backend::smbConnectedToServer);

}

QString Backend::startServer()
{
    if (!server->tcpServer->listen(QHostAddress::Any, 6547))
    {
        return "Error! The port is taken by some other service";
    }
    else
    {
        connect(server->tcpServer, &QTcpServer::newConnection, server, &ClientResearch::newConnection);
        //server->connectDb();
        return "Server started, port is openned";
    }
}



void Backend::smbConnectedToServer()
{
    emit smbConnected();
}

QString Backend::stopServer()
{
    if(server->tcpServer->isListening())
    {
        disconnect(server->tcpServer, &QTcpServer::newConnection, server, &ClientResearch::newConnection);

        QList<QTcpSocket *> clients = server->getClients();
        for(int i = 0; i < clients.count(); i++)
        {
            //server->sendToClient(clients.at(i), "Connection closed");
            server->sendToClient(clients.at(i), "0");
        }

        server->tcpServer->close();
        return "Server stopped, post is closed";
    }
    else
    {
        return "Error! Server was not running";
    }
}
