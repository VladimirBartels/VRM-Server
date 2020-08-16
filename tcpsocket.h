#ifndef TCPSOCKET_H
#define TCPSOCKET_H

#include <QObject>
#include <QTcpSocket>
#include <QAbstractSocket>

#include "ui_mainwindow.h"

class TcpSocket : public QObject
{
    Q_OBJECT
public:
    TcpSocket(Ui::MainWindow *ui);

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
