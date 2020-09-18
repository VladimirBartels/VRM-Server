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
        qDebug() << "Server could not start or is already started";
        qDebug() << _tcpServer->errorString();
        _ui->textBrowser_log->append("Server could not start or is already started");
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

void TcpServer::sendMoveForward(uint clientId)
{
    QString command = createCommand(clientId, eMoveForward);
    _ui->textBrowser_log->append("Server sent 'move forward' command " + command);
    _socket->doSend(command);
}

void TcpServer::sendMoveBackward(uint clientId)
{
    QString command = createCommand(clientId, eMoveBackward);
    _ui->textBrowser_log->append("Server sent 'move backward' command " + command);
    _socket->doSend(command);
}

void TcpServer::sendMoveLeft(uint clientId)
{
    QString command = createCommand(clientId, eMoveLeft);
    _ui->textBrowser_log->append("Server sent 'move left' command " + command);
    _socket->doSend(command);
}

void TcpServer::sendMoveRight(uint clientId)
{   
    QString command = createCommand(clientId, eMoveRight);
    _ui->textBrowser_log->append("Server sent 'move right' command " + command);
    _socket->doSend(command);
}

void TcpServer::sendTurnLeft(uint clientId)
{
    QString command = createCommand(clientId, eTurnLeft);
    _ui->textBrowser_log->append("Server sent 'turn left' command " + command);
    _socket->doSend(command);
}

void TcpServer::sendTurnRight(uint clientId)
{
    QString command = createCommand(clientId, eTurnRight);
    _ui->textBrowser_log->append("Server sent 'turn left' command " + command);
    _socket->doSend(command);
}

void TcpServer::sendStop(uint clientId)
{
    QString command = createCommand(clientId, eStop);
    _ui->textBrowser_log->append("Server sent 'stop' command " + command);
    _socket->doSend(command);
}

void TcpServer::sendChangeSpeed(uint clientId, uint speed)
{
    QString command = createCommand(clientId, eChangeSpeed + speed);
    _ui->textBrowser_log->append("Server sent 'change speed' command " + command);
    _socket->doSend(command);
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

// a command format 8 bytes:
// example: S1:0101E
// [0]   S   - start
// [1]   1   - id of a client
// [2]   :   - spacer between client id and a command id
// [3-6] 101 - a command id
// [7]   E   - end of the command
QString TcpServer::createCommand(uint clientId, uint commandId)
{
    QString command = "";

    if (clientId >= 10)
    {
        _ui->textBrowser_log->append("Client id is out of range [0..9]");
        return "";
    }

    if (commandId >= 10000)
    {
        _ui->textBrowser_log->append("Command id is out of range [0..9999]");
        return "";
    }

    // building a command
    command = "S" + QString::number(clientId) + ":" + QStringLiteral("%1").arg(commandId, 4) + "E";

    return command;
}
