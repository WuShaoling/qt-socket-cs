#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QDebug>
#include <QString>
#include <QHostAddress>
#include <QByteArray>
#include <QLineEdit>
#include <QMessageBox>
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
    void on_connect_clicked();

    void on_send_clicked();

    void Read();

    void on_ok_clicked();

private:
    Ui::MainWindow *ui;
    QTcpSocket *socket;
    QString IP;
    int PORT;
};

#endif // MAINWINDOW_H
