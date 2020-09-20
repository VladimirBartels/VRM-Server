#include "tcpserver.h"
#include <QNetworkProxy>

#define SERVERADDRESS   "192.168.0.100"

TcpServer::TcpServer(Ui::MainWindow *ui) : _ui(ui)
{
    _tcpServer = new QTcpServer(this);

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

void TcpServer::doSend(uint clientId, QString data)
{
    _ui->textBrowser_log->append("Server sent " + data);
    if (_socketMap.contains(clientId))
    {
        _socketMap[clientId]->doSend(data.toUtf8());
    }
    else
    {
        _ui->textBrowser_log->append("TcpServer: No such value in socketMap");
    }
}

void TcpServer::sendMoveForward(uint clientId)
{
    QString command = createCommand(clientId, eMoveForward);
    _ui->textBrowser_log->append("Server sent 'move forward' command " + command);
    if (_socketMap.contains(clientId))
    {
        _socketMap[clientId]->doSend(command);
    }
    else
    {
        _ui->textBrowser_log->append("TcpServer: No such value in socketMap");
    }
}

void TcpServer::sendMoveBackward(uint clientId)
{
    QString command = createCommand(clientId, eMoveBackward);
    _ui->textBrowser_log->append("Server sent 'move backward' command " + command);
    if (_socketMap.contains(clientId))
    {
        _socketMap[clientId]->doSend(command);
    }
    else
    {
        _ui->textBrowser_log->append("TcpServer: No such value in socketMap");
    }
}

void TcpServer::sendMoveLeft(uint clientId)
{
    QString command = createCommand(clientId, eMoveLeft);
    _ui->textBrowser_log->append("Server sent 'move left' command " + command);
    if (_socketMap.contains(clientId))
    {
        _socketMap[clientId]->doSend(command);
    }
    else
    {
        _ui->textBrowser_log->append("TcpServer: No such value in socketMap");
    }
}

void TcpServer::sendMoveRight(uint clientId)
{   
    QString command = createCommand(clientId, eMoveRight);
    _ui->textBrowser_log->append("Server sent 'move right' command " + command);
    if (_socketMap.contains(clientId))
    {
        _socketMap[clientId]->doSend(command);
    }
    else
    {
        _ui->textBrowser_log->append("TcpServer: No such value in socketMap");
    }
}

void TcpServer::sendTurnLeft(uint clientId)
{
    QString command = createCommand(clientId, eTurnLeft);
    _ui->textBrowser_log->append("Server sent 'turn left' command " + command);
    if (_socketMap.contains(clientId))
    {
        _socketMap[clientId]->doSend(command);
    }
    else
    {
        _ui->textBrowser_log->append("TcpServer: No such value in socketMap");
    }
}

void TcpServer::sendTurnRight(uint clientId)
{
    QString command = createCommand(clientId, eTurnRight);
    _ui->textBrowser_log->append("Server sent 'turn left' command " + command);
    if (_socketMap.contains(clientId))
    {
        _socketMap[clientId]->doSend(command);
    }
    else
    {
        _ui->textBrowser_log->append("TcpServer: No such value in socketMap");
    }
}

void TcpServer::sendStop(uint clientId)
{
    QString command = createCommand(clientId, eStop);
    _ui->textBrowser_log->append("Server sent 'stop' command " + command);
    if (_socketMap.contains(clientId))
    {
        _socketMap[clientId]->doSend(command);
    }
    else
    {
        _ui->textBrowser_log->append("TcpServer: No such value in socketMap");
    }
}

void TcpServer::sendChangeSpeed(uint clientId, uint speed)
{
    QString command = createCommand(clientId, eChangeSpeed + speed);
    _ui->textBrowser_log->append("Server sent 'change speed' command " + command);
    if (_socketMap.contains(clientId))
    {
        _socketMap[clientId]->doSend(command);
    }
    else
    {
        _ui->textBrowser_log->append("TcpServer: No such value in socketMap");
    }
}

void TcpServer::newConnection()
{
    qDebug() << "Client is connected";
    _ui->textBrowser_log->append("Client is connected");

    TcpSocket *socket = new TcpSocket(_ui);

    // nextPendingConnection is a connected client's socket
    socket->setSocket(_tcpServer->nextPendingConnection());

    _ui->textBrowser_log->append("Client Address is: " + socket->getAddress());

    _ui->textBrowser_log->append("Sending Hello from Server to Client");
    socket->doSend("Hello from Server to Client");

    // TODO: maybe change map key from int to address string and put in a function
    // TODO: change address to 101
    if (socket->getAddress() == CLIENTADDR_1)
    {
        // if a client is already in the map and the same client is trying to connect again,
        // remove old cllient from the map and add a new one
        if (_socketMap.contains(1))
        {
                TcpSocket *oldSocket = _socketMap.take(1);
                delete oldSocket;
        }

        // insert a new client to the map and to the combobox
        _socketMap.insert(1, socket);
        _ui->comboBox_clientId->addItem(QString::number(1));        
    }

    if (socket->getAddress() == CLIENTADDR_2)
    {
        // if a client is already in the map and the same client is trying to connect again,
        // remove old cllient from the map and add a new one
        if (_socketMap.contains(2))
        {
                TcpSocket *oldSocket = _socketMap.take(2);
                delete oldSocket;
        }

        _socketMap.insert(2, socket);
        _ui->comboBox_clientId->addItem(QString::number(2));
    }
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
