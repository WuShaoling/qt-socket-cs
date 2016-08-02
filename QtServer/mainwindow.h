#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>
#include <QHostAddress>
#include <QString>
#include <QByteArray>
#include <QList>

#include "myclient.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:
    void acceptConnection();
    void readMsg(QTcpSocket*);
    void sendMsg();
private:
    Ui::MainWindow *ui;
    QTcpServer *server;
    QList<MyClient*> clients;
};

#endif // MAINWINDOW_H
