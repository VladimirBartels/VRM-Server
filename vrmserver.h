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
    void sendDataToClient(uint clientId, QString data);

    void moveClientForward(uint clientId);
    void moveClientBackward(uint clientId);
    void moveClientLeft(uint clientId);
    void moveClientRight(uint clientId);
    void turnClientLeft(uint clientId);
    void turnClientRight(uint clientId);
    void stopClient(uint clientId);
    void changeClientSpeed(uint clientId, uint speed);

signals:

private:
    Ui::MainWindow *_ui;
    TcpServer *_server;
};

#endif // VRMSERVER_H
