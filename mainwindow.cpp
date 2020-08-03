#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    _server = new TcpServer(ui);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_send_clicked()
{
    _server->doSend(ui->lineEdit_send->text());
}

void MainWindow::on_pushButton_connect_clicked()
{
    _server->doConnect();
}

void MainWindow::on_pushButton_disconnect_clicked()
{
    _server->doDisconnect();
}

void MainWindow::on_pushButton_islistening_clicked()
{
    _server->isListening();
}
