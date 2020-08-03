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

void TcpServer::isListening()
{
    // check if server is listening
    if (_tcpServer->isListening() == true)
    {
        _ui->textBrowser_log->append("Server is listening");
    }
    else
    {
        _ui->textBrowser_log->append("Server is NOT listening");
    }
}

void TcpServer::doSend(QString data)
{
    _ui->textBrowser_log->append("Server sent " + data);
    _socket->doSend(data.toUtf8());
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
