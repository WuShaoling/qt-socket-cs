#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    IP = "127.0.0.1";
    PORT = 6666;
    ui->ip->setText(IP);
    ui->port->setText(QString::number(PORT));
    socket = new QTcpSocket(this);
    connect(socket, SIGNAL(readyRead()), this, SLOT(Read()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_connect_clicked()
{
    if(IP == NULL || PORT == 0)
    {
        QMessageBox::information(this,"warnning","please set ip and port value");
        return;
    }
    socket->connectToHost(QHostAddress(IP), PORT);
}


void MainWindow::on_send_clicked()
{
    QString msg = ui->input->toPlainText();
    socket->write(msg.toAscii());
    socket->flush();
    ui->input->setText("");
}

void MainWindow::Read()
{
    QString msg = socket->readAll();
    ui->output->append(msg);
}

void MainWindow::on_ok_clicked()
{
    if(ui->ip->text() != NULL && ui->port->text() != NULL)
    {
        IP = ui->ip->text();
        //检查IP
        QString pattern("((0?[0-9]?[0-9])|(1[0-9][0-9])|(2[01234][0-9])|(25[012345]))\.((0?[0-9]?[0-9])|(1[0-9][0-9])|(2[01234][0-9])|(25[012345]))\.((0?[0-9]?[0-9])|(1[0-9][0-9])|(2[01234][0-9])|(25[012345]))\.((0?[0-9]?[0-9])|(1[0-9][0-9])|(2[01234][0-9])|(25[012345]))");
        QRegExp rx(pattern);
        if(!rx.exactMatch(IP))
        {
            QMessageBox::information(this,"failed","ip error");
            return;
        }

        //端口
        PORT = ui->port->text().toInt();
        if(PORT < 1024 || PORT > 65536)
        {
            QMessageBox::information(this,"failed","port error");
            return;
        }
        QMessageBox::information(this,"success","ok");
    }
}
