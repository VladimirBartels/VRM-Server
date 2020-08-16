#include "tcpsocket.h"
#include <QHostAddress>
#include <QDebug>

TcpSocket::TcpSocket(Ui::MainWindow *ui) : _ui(ui)
{
    qDebug() << "tcpsocket::tcpsocket()";

    _tcpSocket = new QTcpSocket();
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
    qDebug() << "Disconnected...";
    _ui->textBrowser_log->append("Disconnected...\n");
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
