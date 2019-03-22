#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QFileInfo>
#include <QImage>
#include <QMovie>
#include <QHostAddress>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_server = new QTcpServer;
    m_socket = new QTcpSocket;

    m_server->listen(QHostAddress(ip),port);

    connect(m_server,SIGNAL(newConnection()),this,SLOT(hasNewClient()));


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_camerabtn_clicked()
{
    if(m_frame.isOpened()){
        m_frame.release();
    }
    m_frame.open(0);
    connect(&m_timer,SIGNAL(timeout()),this,SLOT(timedone()));
    m_timer.setInterval(300);
    m_timer.start();
}

void MainWindow::timedone()
{
    Mat img;//顶一个Mat数据结构用于存储当前的图像数据
    m_frame.operator >>(img);//读取一帧图像数据
    if(!img.empty()){//如果图像读取成功
        QImage image = m_fire.CheckColor(img);//检测火焰并绘画绿色矩形框
        ui->label->setPixmap(QPixmap::fromImage(image));//将画好的新图像显示到界面上
    }

}

void MainWindow::on_filebtn_clicked()
{
    // 1、关闭视频帧接口
    if(m_frame.isOpened()){
        m_frame.release();
    }

    // 2、获取视频文件路径
    QString name = QFileDialog::getOpenFileName();
    QFileInfo info(name);
    QString filePath =  info.absoluteFilePath();

    if(!m_frame.open(filePath.toStdString())){
        //打开视频文件失败
        QMessageBox::warning(this,"打开文件","打开视频文件失败");
        return;
    }else{
        //打开视频文件成功
        m_timer.setInterval(50);
        connect(&m_timer,SIGNAL(timeout()),this,SLOT(timedone()));
        m_timer.start();
    }
}

void MainWindow::hasNewClient()
{
    //当有新的客户端到来的时候
    m_socket = m_server->nextPendingConnection();
    connect(m_socket,SIGNAL(readyRead()),this,SLOT(readyRead()));
    connect(m_socket,SIGNAL(disconnected()),this,SLOT(disconsucces()));
    ui->wifi->setPixmap(QPixmap::fromImage(QImage(":/imgs/wifi_green.png")));

}

void MainWindow::readyRead()
{
    QByteArray arr = m_socket->readAll();
    QString data(arr);
    // data -->  [0]  no mq
    // data -->  [1]   yes mq
    if(data.startsWith('[')&&data.endsWith(']')){
        if(data.length()==3){
            if(data[1]=='0'){
                ui->mq->setPixmap(QPixmap::fromImage(QImage(":/imgs/fire_green.png")));
            }else if(data[1]=='1'){
                ui->mq->setPixmap(QPixmap::fromImage(QImage(":/imgs/fire_red.png")));
            }
        }
    }
}

void MainWindow::disconsucces()
{
    ui->wifi->setPixmap(QPixmap::fromImage(QImage(":/imgs/wifi_red.png")));
}

void MainWindow::on_fenshanbtn_clicked()
{
    //风扇开关处理
    if(ui->fenshanbtn->text()=="打开风扇"){
        QString packet ="{\"s\":0}";
        if(m_socket->write(packet.toStdString().data())){
            QMovie *moive =new QMovie(":/imgs/fenshan.gif");
            ui->fenshan->setMovie(moive);
            moive->start();
            ui->fenshanbtn->setText("关闭风扇");
        }
    }else{
        QString packet ="{\"s\":1}";
        if(m_socket->write(packet.toStdString().data())){
            ui->fenshan->setPixmap(QPixmap::fromImage(QImage(":/imgs/fenshan.png")));
            ui->fenshanbtn->setText("打开风扇");
        }
    }
}
