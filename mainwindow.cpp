#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include "display.hpp"
#include <QTime>
#include <QObject>
//#include <opencv4/opencv2/opencv.hpp>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    timer=new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::display);
    connect(ui->reopen_cam_button,&QPushButton::pressed,this,&MainWindow::reOpenCam);
    connect(this,&MainWindow::videoLost,this,&MainWindow::videoErrorShow);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void  MainWindow::loginInShow(){

    //QT
    //QTime timer;
    cap.open(0);
    timer->start(1);
    this->show();
}

void MainWindow::display(){
     cv::Mat frame;
     cap>>frame;
     if(frame.empty()||!cap.isOpened()){
        emit videoLost();
         return ;
     }

     cv::cvtColor(frame, frame, cv::COLOR_BGR2RGB);//图像格式转换
     QImage disImage = QImage((const unsigned char*)(frame.data),frame.cols,frame.rows,QImage::Format_RGB888);
     //ui->viedo_area->viedo_play->setImage(disImage);
     this->ui->video_play->setImage(disImage);
}

void MainWindow::reOpenCam(){
    timer->stop();
    if(cap.isOpened()){
       cap.release();
    }
    cap.open(0);
    timer->start(1);
    qDebug("reopen sucessfully \n");
}

void MainWindow::videoErrorShow(){
     cv::Mat frame;
     frame=cv::imread("/home/verse/workspace/RZ/FoolishCaptureNet0/XQW-RZ-G2L/QtUi/MainCom/img/1.png");
     this->ui->if_right->setText("False");
     cv::cvtColor(frame, frame, cv::COLOR_BGR2RGB);//图像格式转换
     QImage disImage = QImage((const unsigned char*)(frame.data),frame.cols,frame.rows,QImage::Format_RGB888);
     this->ui->video_play->setImage(disImage);
}
