#include "myclient.h"

MyClient::MyClient(QTcpSocket* socket_, QObject *parent) :
    socket(socket_),
    QObject(parent)
{
    connect(socket, SIGNAL(readyRead()), this, SLOT(getSignal()));
}

void MyClient::getSignal()
{
    emit sendSignal(this->socket);
}

QTcpSocket* MyClient::getSocket()
{
    return this->socket;
}
