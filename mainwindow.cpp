#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    _vrmServer = new Vrmserver(ui);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_send_clicked()
{
    _vrmServer->sendDataToClient(ui->lineEdit_send->text());
}

void MainWindow::on_pushButton_connect_clicked()
{
    _vrmServer->startTcpServer();
}

void MainWindow::on_pushButton_disconnect_clicked()
{
    _vrmServer->stopTcpServer();
}

void MainWindow::on_pushButton_islistening_clicked()
{
    _vrmServer->pingServer();
}

void MainWindow::on_pushButton_moveForward_clicked()
{
    _vrmServer->moveClientForward();
}

void MainWindow::on_pushButton_moveBackward_clicked()
{
    _vrmServer->moveClientBackward();
}

void MainWindow::on_pushButton_moveLeft_clicked()
{
    _vrmServer->moveClientLeft();
}

void MainWindow::on_pushButton_moveRight_clicked()
{
    _vrmServer->moveClientRight();
}

void MainWindow::on_pushButton_turnLeft_clicked()
{
    _vrmServer->turnClientLeft();
}

void MainWindow::on_pushButton_turnRight_clicked()
{
    _vrmServer->turnClientRight();
}

void MainWindow::on_pushButton_Stop_clicked()
{
    _vrmServer->stopClient();
}

void MainWindow::on_pushButton_changeSpeed_clicked()
{
    _vrmServer->changeClientSpeed(ui->horizontalSlider_speed->value());
}
