#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <fire.h>
#include <QTimer>
#include <QTcpServer>
#include <QTcpSocket>
#include "opencv.hpp"
using namespace std;
using namespace cv;

const QString ip="127.0.0.1";
const int port = 8888;

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
    void hasNewClient();
    void readyRead();
    void disconsucces();
    void on_fenshanbtn_clicked();

private:
    Ui::MainWindow *ui;
    Fire m_fire; //定义一个用于检测图像火焰的对象
    QTimer m_timer;//定义一个定时器用于定时检测图像中的火焰
    VideoCapture m_frame;//定义一个用于获取图像视频帧的获取器

    QTcpServer *m_server; //用于开启一个TCP监听服务
    QTcpSocket *m_socket;//用于和硬件进行通信的套接字
};

#endif // MAINWINDOW_H
