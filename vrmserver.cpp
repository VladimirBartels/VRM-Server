#include "vrmserver.h"

#define CAR_ID 1

//Vrmserver::Vrmserver(QObject *parent) : QObject(parent)
//{

//}

Vrmserver::Vrmserver(Ui::MainWindow *ui) : _ui(ui)
{
    _server = new TcpServer(ui);
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

void Vrmserver::sendDataToClient(QString data)
{
    _server->doSend(data);
}

void Vrmserver::moveClientForward()
{
    _server->sendMoveForward(CAR_ID);
}

void Vrmserver::moveClientBackward()
{
    _server->sendMoveBackward(CAR_ID);
}

void Vrmserver::moveClientLeft()
{
    _server->sendMoveLeft(CAR_ID);
}

void Vrmserver::moveClientRight()
{
    _server->sendMoveRight(CAR_ID);
}

void Vrmserver::turnClientLeft()
{
    _server->sendTurnLeft(CAR_ID);
}

void Vrmserver::turnClientRight()
{
    _server->sendTurnRight(CAR_ID);
}

void Vrmserver::stopClient()
{
    _server->sendStop(CAR_ID);
}

void Vrmserver::changeClientSpeed(uint speed)
{
    _server->sendChangeSpeed(CAR_ID, speed);
}
