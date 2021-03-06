#ifndef TCPSOCKET_H
#define TCPSOCKET_H

#include <QObject>
#include <QTcpSocket>
#include <QAbstractSocket>

#include "ui_mainwindow.h"

#define CLIENTADDR_1    "192.168.0.103"
#define CLIENTADDR_2    "192.168.0.102"

class TcpSocket : public QObject
{
    Q_OBJECT
public:
    TcpSocket(Ui::MainWindow *ui);
    ~TcpSocket();

    void setSocket(QTcpSocket *socket);
    void doDisconnect();
    void doSend(QString data);
    void connectSignals();

    QString getAddress();

signals:

public slots:
    void slotConnected();
    void slotDisconnected();
    void slotBytesWritten(qint64 bytes);
    void slotReadyRead();

private slots:

private:
    Ui::MainWindow *_ui;
    QTcpSocket *_tcpSocket;
};

#endif // TCPSOCKET_H
