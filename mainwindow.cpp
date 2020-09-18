#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    _supervisor = new Supervisor(ui);
    _vrmServer = new Vrmserver(ui);

    // set vrm control enabled per default
    on_radioButton_vrmControl_clicked();

    ui->view1->setScene(_supervisor);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_radioButton_vrmControl_clicked()
{
    // vrm control set enabled
    ui->view1->setEnabled(true);
    ui->pushButton_startStop->setEnabled(true);

    // manual control set disabled
    ui->groupBox_manualControl->setEnabled(false);

    // stop server for Manual Control
    _vrmServer->stopTcpServer();

    // create vrm case for vrm control
    _supervisor->createCase4();
}

void MainWindow::on_radioButton_manualControl_clicked()
{
    // manual control set enabled
    ui->groupBox_manualControl->setEnabled(true);

    // vrm control set disabled
    ui->view1->setEnabled(false);
    ui->pushButton_startStop->setEnabled(false);

    // destroy vrm case: set everyting to inital state
    _supervisor->init();
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

void MainWindow::on_horizontalSlider_speed_valueChanged(int value)
{
    // manual control is activated
    if (ui->radioButton_manualControl->isChecked())
    {
        _vrmServer->changeClientSpeed(value);
    }

    // vrm control is activated
    if (ui->radioButton_vrmControl->isChecked())
    {
        _supervisor->changeSpeed(value);
    }
}

void MainWindow::on_pushButton_startStop_clicked()
{
    _supervisor->startStopCase();
}
