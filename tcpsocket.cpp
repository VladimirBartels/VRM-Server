#include "tcpsocket.h"
#include <QHostAddress>
#include <QDebug>

TcpSocket::TcpSocket(Ui::MainWindow *ui) : _ui(ui)
{
    qDebug() << "tcpsocket::tcpsocket()";

    _tcpSocket = new QTcpSocket();
}

TcpSocket::~TcpSocket()
{
    if (_tcpSocket)
    {
        delete _tcpSocket;
        _tcpSocket = nullptr;
    }
}

void TcpSocket::setSocket(QTcpSocket *socket)
{
    _tcpSocket = socket;

    // connect QTcpSocket signals to our slots
    connectSignals();
}

void TcpSocket::doDisconnect()
{
    qDebug() << "Disconnecting...";
    _ui->textBrowser_log->append("Disconnecting...\n");

    _tcpSocket->disconnectFromHost();
}

void TcpSocket::doSend(QString data)
{
    // write data to socket (send to client)
    _tcpSocket->write(data.toUtf8());
}

void TcpSocket::connectSignals()
{
    // connect default QTcpSocket signals to our (tcpsocket) slots
    connect(_tcpSocket, SIGNAL(connected()),          this, SLOT(slotConnected()),          Qt::UniqueConnection);
    connect(_tcpSocket, SIGNAL(disconnected()),       this, SLOT(slotDisconnected()),       Qt::UniqueConnection);
    connect(_tcpSocket, SIGNAL(bytesWritten(qint64)), this, SLOT(slotBytesWritten(qint64)), Qt::UniqueConnection);
    connect(_tcpSocket, SIGNAL(readyRead()),          this, SLOT(slotReadyRead()),          Qt::UniqueConnection);
}

QString TcpSocket::getAddress()
{
    return _tcpSocket->peerAddress().toString();
}

void TcpSocket::slotConnected()
{
    qDebug() << "Connected...";
    _ui->textBrowser_log->append("Connected...\n");
}

void TcpSocket::slotDisconnected()
{
    qDebug() << "Client has disconnected...";

    _ui->textBrowser_log->append("Client has disconnected...\n");

    // TODO: maybe put it in separated function
    // remove client 1 from combo box
    if (_tcpSocket->peerAddress().toString() == CLIENTADDR_1)
    {
        for (int i = 0; i < _ui->comboBox_clientId->count(); i++)
        {
            if (_ui->comboBox_clientId->itemText(i) == "1")
            {
                _ui->comboBox_clientId->removeItem(i);
                break;
            }
        }

        // removing from socketMap is done by client reconnecting in tcpserver
    }

    // remove client 2 from combo box
    if (_tcpSocket->peerAddress().toString() == CLIENTADDR_2)
    {
        for (int i = 0; i < _ui->comboBox_clientId->count(); i++)
        {
            if (_ui->comboBox_clientId->itemText(i) == "2")
            {
                _ui->comboBox_clientId->removeItem(i);
                break;
            }
        }

        // removing from socketMap is done by client reconnecting in tcpserver
    }
}

void TcpSocket::slotBytesWritten(qint64 bytes)
{
    qDebug() << bytes << " bytes written...";
}

void TcpSocket::slotReadyRead()
{
    qDebug() << "reading...";

    // read the data from the socket
    _ui->textBrowser_log->append("client: " + QString(_tcpSocket->readAll()));
}
