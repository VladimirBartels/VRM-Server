#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QObject>
#include <QTcpServer>

#include "tcpsocket.h"
#include "ui_mainwindow.h"

class TcpServer : public QObject
{
    Q_OBJECT
public:
    TcpServer(Ui::MainWindow *ui);

    void doConnect();
    void doDisconnect();
    void isListening();
    void doSend(QString data);;

signals:

public slots:
    void newConnection();

private:
    QTcpServer *_tcpServer;
    //QTcpSocket *_socket;
    TcpSocket *_socket;
    Ui::MainWindow *_ui;
};

#endif // TCPSERVER_H
