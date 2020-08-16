#include "vrmserver.h"

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
    _server->sendMoveForward();
}

void Vrmserver::moveClientBackward()
{
    _server->sendMoveBackward();
}

void Vrmserver::moveClientLeft()
{
    _server->sendMoveLeft();
}

void Vrmserver::moveClientRight()
{
    _server->sendMoveRight();
}

void Vrmserver::turnClientLeft()
{
    _server->sendTurnLeft();
}

void Vrmserver::turnClientRight()
{
    _server->sendTurnRight();
}

void Vrmserver::stopClient()
{
    _server->sendStop();
}

void Vrmserver::changeClientSpeed(uint speed)
{
    _server->sendChangeSpeed(speed);
}
