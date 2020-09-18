#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QObject>
#include <QTcpServer>

#include "tcpsocket.h"
#include "ui_mainwindow.h"

enum eCarSpeed
{
    eNoSpeed    = 0,
    eSlow       = 1,
    eNormal     = 2,
    eFast       = 3
};

enum eCommands
{
    eMoveForward    = 100,
    eMoveBackward   = 101,
    eMoveLeft       = 102,
    eMoveRight      = 103,
    eTurnLeft       = 104,
    eTurnRight      = 105,
    eStop           = 106,
    eChangeSpeed    = 1050
};

class TcpServer : public QObject
{
    Q_OBJECT
public:
    TcpServer(Ui::MainWindow *ui);

    void doConnect();
    void doDisconnect();
    bool isListening();
    void doSend(QString data);

    void sendMoveForward(uint clientId);
    void sendMoveBackward(uint clientId);
    void sendMoveLeft(uint clientId);
    void sendMoveRight(uint clientId);
    void sendTurnLeft(uint clientId);
    void sendTurnRight(uint clientId);
    void sendStop(uint clientId);
    void sendChangeSpeed(uint clientId, uint speed);

signals:

public slots:
    void newConnection();

private:
    QString createCommand(uint clientId, uint commandId);

    QTcpServer *_tcpServer;
    //QTcpSocket *_socket;
    TcpSocket *_socket;
    Ui::MainWindow *_ui;
};

#endif // TCPSERVER_H
