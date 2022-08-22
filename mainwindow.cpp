#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include "display.hpp"
#include <QTime>
#include <QObject>
#include <thread>
#include <QThread>
//#include <opencv4/opencv2/opencv.hpp>
#include <QMetaType>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    timer=new QTimer(this);
    cameraInit();
    TransVideoInit();
}


void MainWindow::cameraInit(){
    camera_thread=new QThread(this);
    camera_task=new CameraTask();
    camera_task->moveToThread(camera_thread);
    qRegisterMetaType<cv::Mat>("cv::Mat&");
    // timely get frame
    connect(timer, &QTimer::timeout,camera_task,&CameraTask::working);
    // frame display
    connect(camera_task,&CameraTask::getFrame,this,&MainWindow::display,Qt::QueuedConnection);
    qRegisterMetaType<std::string>("std::string&");
    // error display
    connect(camera_task,&CameraTask::videoLost,this,[=](){
        cv::Mat img;
        img=cv::imread("/home/verse/workspace/RZ/FoolishCaptureNet0/XQW-RZ-G2L/img/1.png");
        this->ui->if_right->setText("False");
        if(!img.empty()){
            cv::cvtColor(img, img, cv::COLOR_BGR2RGB);//图像格式转换
            QImage disImage = QImage((const unsigned char*)(img.data),img.cols,img.rows,QImage::Format_RGB888);
            //this->ui->video_play->setImage(disImage);
            QPixmap pix_img=QPixmap::fromImage(disImage);
            this->ui->video_plays->setPixmap(pix_img);
        }
    });
    // reboot camera
    connect(ui->reopen_cam_button,&QPushButton::pressed,[=](){
        timer->stop();
        camera_task->reboot();
        timer->start(10);
    });
    camera_thread->start();
}

void MainWindow::TransVideoInit(){
    // init trans video Thread
    transvideo_thread= new QThread(this);
    transvideo_task=new TransVideoTask();
    transvideo_task->moveToThread(transvideo_thread);
    qRegisterMetaType<cv::Mat>("cv::Mat&");
    qRegisterMetaType<std::string>("std::string&");
    connect(camera_task,&CameraTask::getFrame,transvideo_task,&TransVideoTask::working,Qt::QueuedConnection);
    connect(transvideo_task,&TransVideoTask::setFailed,[=](){
       ui->if_right_3->setText("Failed");
    });
    transvideo_thread->start();
}
MainWindow::~MainWindow()
{
    delete ui;
}

void  MainWindow::loginInShow(){

    timer->start(10);
    this->show();
    emit startThread();
}

void MainWindow::display(cv::Mat &frame){

      cv::Mat img=frame.clone();
      cv::cvtColor(img, img, cv::COLOR_BGR2RGB);//图像格式转换
      QImage disImage = QImage((const unsigned char*)(img.data),img.cols,img.rows,QImage::Format_RGB888);
      //this->ui->video_play->setImage(disImage);
      QPixmap pix_img=QPixmap::fromImage(disImage);
      this->ui->video_plays->setPixmap(pix_img);
}

