#ifndef MYCLIENT_H
#define MYCLIENT_H

#include <QObject>
#include <QTcpSocket>

class MyClient : public QObject
{
    Q_OBJECT
public:
    explicit MyClient(QTcpSocket*, QObject *parent = 0);
    QTcpSocket* getSocket();
signals:
    void sendSignal(QTcpSocket*);
public slots:
    void getSignal();
private:
    QTcpSocket* socket;
};

#endif // MYCLIENT_H
