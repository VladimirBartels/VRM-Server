#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "vrmserver.h"
#include "supervisor.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_radioButton_vrmControl_clicked();
    void on_radioButton_manualControl_clicked();

    void on_pushButton_send_clicked();
    void on_pushButton_connect_clicked();
    void on_pushButton_disconnect_clicked();
    void on_pushButton_islistening_clicked();

    void on_pushButton_moveForward_clicked();
    void on_pushButton_moveBackward_clicked();
    void on_pushButton_moveLeft_clicked();
    void on_pushButton_moveRight_clicked();
    void on_pushButton_turnLeft_clicked();
    void on_pushButton_turnRight_clicked();
    void on_pushButton_Stop_clicked();

    void on_horizontalSlider_speed_valueChanged(int value);

    void on_pushButton_startStop_clicked();


private:

    Ui::MainWindow *ui;
    Vrmserver *_vrmServer;
    Supervisor *_supervisor;
};
#endif // MAINWINDOW_H
