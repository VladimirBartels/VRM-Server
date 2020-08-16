#include "tcpserver.h"
#include <QNetworkProxy>

#define SERVERADDRESS   "192.168.0.100"
#define CLIENTADDRESS_1 "192.168.0.101"
#define CLIENTADDRESS_2 "192.168.0.102"

TcpServer::TcpServer(Ui::MainWindow *ui) : _ui(ui)
{
    _tcpServer = new QTcpServer(this);
    _socket = new TcpSocket(ui);

    // whenever a client connects, it will emit signal
    connect(_tcpServer, SIGNAL(newConnection()), this, SLOT(newConnection()));
}

void TcpServer::doConnect()
{
    if (!_tcpServer->listen(QHostAddress(SERVERADDRESS), 80))
    {
        qDebug() << "Server could not start";
        qDebug() << _tcpServer->errorString();
        _ui->textBrowser_log->append("Server could not start");
        _ui->textBrowser_log->append(_tcpServer->errorString());
    }
    else
    {
        qDebug() << "Server started!";
        _ui->textBrowser_log->append("Server started!");
    }

    qDebug() << "Server Address is:" + _tcpServer->serverAddress().toString();
    qDebug() << "Server Port is:" + QString::number(_tcpServer->serverPort());

    _ui->textBrowser_log->append("Server Address is: " + _tcpServer->serverAddress().toString());
    _ui->textBrowser_log->append("Server Port is: " + QString::number(_tcpServer->serverPort()));
}

void TcpServer::doDisconnect()
{
    // closes the server (will not listen to incoming connections)
    _tcpServer->close();

    _ui->textBrowser_log->append("Server is not listening anymore");
}

bool TcpServer::isListening()
{
    // check if server is listening
    return _tcpServer->isListening();
}

void TcpServer::doSend(QString data)
{
    _ui->textBrowser_log->append("Server sent " + data);
    _socket->doSend(data.toUtf8());
}

void TcpServer::sendMoveForward()
{
    _ui->textBrowser_log->append("Server sent 'move forward' command " + QString::number(eMoveForward));
    _socket->doSend(QString::number(eMoveForward));
}

void TcpServer::sendMoveBackward()
{
    _ui->textBrowser_log->append("Server sent 'move backward' command " + QString::number(eMoveBackward));
    _socket->doSend(QString::number(eMoveBackward));
}

void TcpServer::sendMoveLeft()
{
    _ui->textBrowser_log->append("Server sent 'move left' command " + QString::number(eMoveLeft));
    _socket->doSend(QString::number(eMoveLeft));
}

void TcpServer::sendMoveRight()
{   
    _ui->textBrowser_log->append("Server sent 'move right' command " + QString::number(eMoveRight));
    _socket->doSend(QString::number(eMoveRight));
}

void TcpServer::sendTurnLeft()
{
    _ui->textBrowser_log->append("Server sent 'turn left' command " + QString::number(eTurnLeft));
    _socket->doSend(QString::number(eTurnLeft));
}

void TcpServer::sendTurnRight()
{
    _ui->textBrowser_log->append("Server sent 'turn left' command " + QString::number(eTurnRight));
    _socket->doSend(QString::number(eTurnRight));
}

void TcpServer::sendStop()
{
    _ui->textBrowser_log->append("Server sent 'stop' command " + QString::number(eStop));
    _socket->doSend(QString::number(eStop));
}

void TcpServer::sendChangeSpeed(uint speed)
{
    _ui->textBrowser_log->append("Server sent 'change speed' command " + QString::number(eChangeSpeed + speed));
    _socket->doSend(QString::number(eChangeSpeed + speed));
}

void TcpServer::newConnection()
{
    qDebug() << "Client is connected";
    _ui->textBrowser_log->append("Client is connected");

    // nextPendingConnection is a connected client's socket
    _socket->setSocket(_tcpServer->nextPendingConnection());

    _ui->textBrowser_log->append("Client Address is: " + _socket->getAddress());

    _ui->textBrowser_log->append("Sending Hello from Server to Client");
    _socket->doSend("Hello from Server to Client");
}
