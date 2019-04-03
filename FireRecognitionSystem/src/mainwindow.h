#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <fire.h>
#include <QTimer>
#include <QSerialPort>
#include "opencv.hpp"
using namespace std;
using namespace cv;


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_camerabtn_clicked();
    void timedone();
    void on_filebtn_clicked();
    void readyRead();
    void on_fenshanbtn_clicked();

    void on_portbtn_clicked();

    void on_closeBtn_clicked();

private:
    Ui::MainWindow *ui;
    Fire m_fire; //定义一个用于检测图像火焰的对象
    QTimer m_timer;//定义一个定时器用于定时检测图像中的火焰
    VideoCapture m_frame;//定义一个用于获取图像视频帧的获取器

    QSerialPort m_port; //用于和串口进行数据通信
};

#endif // MAINWINDOW_H
