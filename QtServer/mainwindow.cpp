#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    server = new QTcpServer();
    server->listen(QHostAddress::Any, 6666);
    connect(server, SIGNAL(newConnection()), this, SLOT(acceptConnection()));
    connect(ui->send, SIGNAL(clicked()), this, SLOT(sendMsg()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::acceptConnection()
{
    QTcpSocket* client = server->nextPendingConnection();
    MyClient* myclient = new MyClient(client);
    clients.append(myclient);
    connect(myclient, SIGNAL(sendSignal(QTcpSocket*)), this, SLOT(readMsg(QTcpSocket*)));
    ui->output->append("new client connected");
    client->write("connect success");
    client->flush();
}

void MainWindow::readMsg(QTcpSocket* client)
{
    QString msg = client->readAll();
    if(msg.length() != 0)
    {
        ui->output->append(client->peerAddress().toString().toAscii() + " : " + msg);
    }

    QListIterator<MyClient*> it(clients);
    while (it.hasNext())
    {
        MyClient* temp = it.next();
        if(temp->getSocket() != client)
        {
            temp->getSocket()->write(msg.toAscii());
            temp->getSocket()->flush();
        }
    }
}
void MainWindow::sendMsg()
{
    QByteArray msg = ui->input->toPlainText().toAscii();
    QListIterator<MyClient*> it(clients);
    while (it.hasNext())
    {
        MyClient* temp = it.next();
        temp->getSocket()->write(msg);
        temp->getSocket()->flush();
    }
    ui->input->setText("");
}
