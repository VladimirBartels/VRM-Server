#include "vrmserver.h"

//Vrmserver::Vrmserver(QObject *parent) : QObject(parent)
//{

//}

Vrmserver::Vrmserver(Ui::MainWindow *ui) : _ui(ui)
{
    _server = new TcpServer(ui);
}

Vrmserver::~Vrmserver()
{
    if (_server)
    {
        delete _server;
        _server = nullptr;
    }
}

void Vrmserver::startTcpServer()
{
    _server->doConnect();
}

void Vrmserver::stopTcpServer()
{
    _server->doDisconnect();
}

void Vrmserver::pingServer()
{
    if (_server->isListening() == true)
    {
        _ui->textBrowser_log->append("Server is listening");
    }
    else
    {
        _ui->textBrowser_log->append("Server is NOT listening");
    }
}

void Vrmserver::sendDataToClient(uint clientId, QString data)
{
    _server->doSend(clientId, data);
}

void Vrmserver::moveClientForward(uint clientId)
{
    _server->sendMoveForward(clientId);
}

void Vrmserver::moveClientBackward(uint clientId)
{
    _server->sendMoveBackward(clientId);
}

void Vrmserver::moveClientLeft(uint clientId)
{
    _server->sendMoveLeft(clientId);
}

void Vrmserver::moveClientRight(uint clientId)
{
    _server->sendMoveRight(clientId);
}

void Vrmserver::turnClientLeft(uint clientId)
{
    _server->sendTurnLeft(clientId);
}

void Vrmserver::turnClientRight(uint clientId)
{
    _server->sendTurnRight(clientId);
}

void Vrmserver::stopClient(uint clientId)
{
    _server->sendStop(clientId);
}

void Vrmserver::changeClientSpeed(uint clientId, uint speed)
{
    _server->sendChangeSpeed(clientId, speed);
}
