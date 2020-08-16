#ifndef VRMSERVER_H
#define VRMSERVER_H

#include <QObject>

#include "ui_mainwindow.h"
#include "tcpserver.h"

class Vrmserver : public QObject
{
    Q_OBJECT
public:
    //explicit Vrmserver(QObject *parent = nullptr);
    Vrmserver(Ui::MainWindow *ui);

    void startTcpServer();
    void stopTcpServer();
    void pingServer();
    void sendDataToClient(QString data);

    void moveClientForward();
    void moveClientBackward();
    void moveClientLeft();
    void moveClientRight();
    void turnClientLeft();
    void turnClientRight();
    void stopClient();
    void changeClientSpeed(uint speed);

signals:

private:
    Ui::MainWindow *_ui;
    TcpServer *_server;
};

#endif // VRMSERVER_H
