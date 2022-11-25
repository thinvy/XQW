#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include <opencv2/opencv.hpp>
#include <QTimer>
#include <unistd.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    timer=new QTimer(this);
    timer1 =new QTimer(this);
    timer2 =new QTimer(this);
    timer3 =new QTimer(this);
    //receiverThreadInit();

//    cap0.open("/home/qylann/Videos/rz_video/1.mp4");
    cap1.open("/home/qylann/Videos/rz_video/2.mp4");
//    cap2.open("/home/qylann/Videos/rz_video/2.mp4");
    cap3.open("/home/qylann/Videos/rz_video/3.avi");
    cap4.open("/home/qylann/Videos/rz_video/1.mp4");
    map.initMapCam();
//    connect(timer,&QTimer::timeout,[=](){
//        cv::Mat img;
//        cap0>>img;
//        while(ix<120){
//            ix++;
//            cap0>>img;
//        }
//        if(!img.empty()){
//            cv::cvtColor(img, img, cv::COLOR_BGR2RGB);
//            QImage disImage = QImage((const unsigned char*)(img.data),img.cols,img.rows,QImage::Format_RGB888);
//            this->ui->main_video->setImage(disImage);
//        }

//    });

    test_pos = cv::Point2f(112, 112);
    test_size = cv::Size(25, 100);
    test_state_0 = 0;
    test_state_1 = 0;

    connect(timer,&QTimer::timeout,[=](){
        cv::Mat img;
        cap1>>img;
        while(ix1<90){
            ix1++;
            cap1>>img;
            usleep(1);
        }
        if(!img.empty()){
            cv::cvtColor(img, img, cv::COLOR_BGR2RGB);
            QImage disImage = QImage((const unsigned char*)(img.data),img.cols,img.rows,QImage::Format_RGB888);
            this->ui->video1->setImage(disImage);
        }

    });
    connect(timer,&QTimer::timeout,[=](){
        cv::Mat img;
        while(ix2<105){
            ix2++;
            cap2>>img;
            //usleep(1120);
        }
        cap2>>img;
        if(!img.empty()){
            cv::cvtColor(img, img, cv::COLOR_BGR2RGB);
            QImage disImage = QImage((const unsigned char*)(img.data),img.cols,img.rows,QImage::Format_RGB888);
            this->ui->video2->setImage(disImage);
        }

    });
    connect(timer,&QTimer::timeout,[=](){
        cv::Mat img;
        while(ix2<105){
            ix2++;
            cap2>>img;
            //usleep(1120);
        }
        cap2>>img;
        if(!img.empty()){
            cv::cvtColor(img, img, cv::COLOR_BGR2RGB);
            QImage disImage = QImage((const unsigned char*)(img.data),img.cols,img.rows,QImage::Format_RGB888);
            this->ui->openGLWidget_5->setImage(disImage);
        }
    });
    connect(timer1,&QTimer::timeout,[=](){
        cv::Mat img;
        while(ix3<65){
            ix3++;
            cap2>>img;
            //usleep(1120);
        }
        cap3>>img;
        if(!img.empty()){
            cv::cvtColor(img, img, cv::COLOR_BGR2RGB);
            QImage disImage = QImage((const unsigned char*)(img.data),img.cols,img.rows,QImage::Format_RGB888);
            this->ui->video3->setImage(disImage);
            //cv::waitKey(2);
        }

    });
    connect(timer1,&QTimer::timeout,[=](){
        cv::Mat img;
        cap4>>img;
        while(ix4<0){
            ix4++;
            //cap3>>img;
//            usleep(2140);
        }
        if(!img.empty()){
            cv::cvtColor(img, img, cv::COLOR_BGR2RGB);
            QImage disImage = QImage((const unsigned char*)(img.data),img.cols,img.rows,QImage::Format_RGB888);
            this->ui->video4->setImage(disImage);
//            cv::waitKey(2);
          //  sleep(1);
        }

    });

    connect(timer2,&QTimer::timeout,[=](){
        cv::Mat img=map.getMap();
//        std::cout << "test pos : " << test_pos << std::endl;
//        std::cout << "test size : " << test_size << std::endl;
        map.drawPoint(img, 0, test_pos, test_size);
        map.drawMapCam(img, 0);


//        if (test_size.width >= 60) {
//            test_state_0 = 0;
//        }
//        else if (test_size.width <= 5) {
//            test_state_0 = 1;
//        }

//        if (test_state_0 == 0) {
//            test_size.width -= 5;
//        }
//        else if (test_state_0 == 1) {
//            test_size.width += 5;
//        }
        if (test_pos.x >= 224) {
            test_state_0 = 0;
        }
        else if (test_pos.x <= 0) {
            test_state_0 = 1;
        }

        if (test_state_0 == 0) {
            test_pos.x -= 15;
        }
        else if (test_state_0 == 1) {
            test_pos.x += 15;
        }

        cv::resize(img,img,cv::Size(300,200));
        //cap1>>img;
        if(!img.empty()){
            cv::cvtColor(img, img, cv::COLOR_BGR2RGB);
            QImage disImage = QImage((const unsigned char*)(img.data),img.cols,img.rows,QImage::Format_RGB888);
            this->ui->map_show->setImage(disImage);
        }
        timer2->stop();
        timer2->start(100);

    });



}

void MainWindow::receiverThreadInit(){
    qRegisterMetaType<cv::Mat>("cv::Mat&");
    qRegisterMetaType<std::string>("std::string&");
    task=new VideoReceiverTask("5004");
    thread =new QThread(this);
    task->moveToThread(thread);
    connect(timer,&QTimer::timeout,task,&VideoReceiverTask::working);
    qRegisterMetaType<cv::Mat>("cv::Mat&");
    connect(task,&VideoReceiverTask::getFrame,this,&MainWindow::video1Display);
    thread->start();
}

void MainWindow::video1Display(cv::Mat &frame){
    if(!frame.empty()){
        stream_frame = frame.clone();
        cv::cvtColor(frame, frame, cv::COLOR_BGR2RGB);
        QImage disImage = QImage((const unsigned char*)(frame.data),frame.cols,frame.rows,QImage::Format_RGB888);
        this->ui->main_video->setImage(disImage);
    }
}

void MainWindow::messageReceiverThreadInit(){
//    qRegisterMetaType<cv::Mat>("float[]&");
//    qRegisterMetaType<std::string>("int[]&");

    msg_task = new MessageReceiverTask();
    msg_thread = new QThread(this);
    msg_task->moveToThread(msg_thread);
    connect(timer, &QTimer::timeout, msg_task,& MessageReceiverTask::working);
    connect(msg_task,&MessageReceiverTask::getMessage,this,&MainWindow::mapUpdate);
    msg_thread->start();
}

void MainWindow::mapUpdate(int *boxes, float *person_vector) {
    std::cout << "receive one message" << std::endl;
    int x = boxes[0];
    int y = boxes[1];
    int w = boxes[2];
    int h = boxes[3];

    cv::Mat img=map.getMap();
    map.drawPoint(img, 0, cv::Point(x+w/2, y+h/2), cv::Size(w, h));
    map.drawMapCam(img, 0);
    cv::resize(img,img,cv::Size(300,200));
    if(!img.empty()){
        cv::cvtColor(img, img, cv::COLOR_BGR2RGB);
        QImage disImage = QImage((const unsigned char*)(img.data),img.cols,img.rows,QImage::Format_RGB888);
        this->ui->map_show->setImage(disImage);
    }

    if (!stream_frame.empty()) {
        cv::Mat frame_resize;
        cv::resize(stream_frame, frame_resize, cv::Size(550, 550));
        cv::Mat person_img(frame_resize, cv::Rect(x, y, x+w, y+h));
        cv::resize(person_img, person_img, cv::Size(101, 192));
//        cv::cvtColor(person_img, person_img,cv::COLOR_BGR2RGB);
        person1_frame = person_img.clone();
//        QImage disImage = QImage((const unsigned char*)(person_img.data),person_img.cols,person_img.rows,QImage::Format_RGB888);
//        this->ui->main_video->setImage(disImage);
    }


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loginInShow()
{
    this->show();
    timer->start(45);
    timer1->start(45);
    timer2->start(40);
    timer3->start(45);
    receiverThreadInit();
    messageReceiverThreadInit();
}
