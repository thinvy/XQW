#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include "display.hpp"
#include <QTime>
#include <QObject>
#include <thread>
#include <QThread>
//#include <opencv4/opencv2/opencv.hpp>
#include <QMetaType>

#include "MainTask.hpp"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    timer = new QTimer(this);
    timer2 = new QTimer(this);
    cameraInit();
    TransVideoInit();
    detectionInit();
    connect(timer2, &QTimer::timeout, [=]()
            {
                if (ui->camera_model->text() == "Camera Model")
                {
                    camera_task->if_direct_show = 0;
                }
                else if (ui->camera_model->text() == "Detect Model")
                {
                    camera_task->if_direct_show = 1;
                }
                else
                {
                    camera_task->if_direct_show = 2;
                }
                // if(camera_task->if_open==fasle){
                //     std::string eroor="error";
                //     emit CameraTask::videoLost(eroor);
                // }
            });
    connect(ui->camera_model, &QPushButton::pressed, [=]
            {
                if (ui->camera_model->text() == "Camera Model")
                {
                    ui->camera_model->setText("Detect Model");
                }
                else if (ui->camera_model->text() == "Detect Model")
                {
                    ui->camera_model->setText("Tracking Model");
                }
                else
                {
                    ui->camera_model->setText("Camera Model");
                }
            });
}

void MainWindow::detectionInit()
{
    detect_thread = new QThread(this);
    detect_task = new DetectTask();
    detect_task->moveToThread(detect_thread);
    qRegisterMetaType<cv::Mat>("cv::Mat&");
    qRegisterMetaType<std::vector<cv::Rect2d>>("std::vector<cv::Rect2d>&");
    qRegisterMetaType<cv::Rect2d>("cv::Rect2d&");
    qRegisterMetaType<uint8_t>("uint8_t");
    qRegisterMetaType<uint8_t>("uint8_t&");
    qRegisterMetaType<std::vector<TrackingBox>>("std::vector<TrackingBox>&");
    // connect(camera_task,&CameraTask::getFrame,detect_task,&DetectTask::working);
    connect(camera_task, &CameraTask::toDetect, detect_task, &DetectTask::working, Qt::QueuedConnection);
    connect(detect_task, &DetectTask::toDisplay, this, &MainWindow::display, Qt::QueuedConnection);
    connect(detect_task, &DetectTask::toSent, transdata_task, &TransDataTask::transmit, Qt::QueuedConnection);
    detect_thread->start();
}

void MainWindow::cameraInit()
{
    camera_thread = new QThread(this);
    camera_task = new CameraTask();
    camera_task->moveToThread(camera_thread);
    qRegisterMetaType<cv::Mat>("cv::Mat&");

    // timely get frame
    connect(timer, &QTimer::timeout, camera_task, &CameraTask::working);
    // frame display
    qRegisterMetaType<std::vector<TrackingBox>>("std::vector<TrackingBox>&");
    connect(camera_task, &CameraTask::toDisplay, this, &MainWindow::display, Qt::QueuedConnection);

    qRegisterMetaType<std::string>("std::string&");
    qRegisterMetaType<std::vector<cv::Rect2d>>("std::vector<cv::Rect2d>&");
    qRegisterMetaType<bool>("bool&");
    qRegisterMetaType<uint8_t>("uint8_t&");
    // error display
    connect(camera_task, &CameraTask::videoLost, this, [=]()
            {
                cv::Mat img;
                img = cv::imread("/opt/gx-edge-ai-demo/img/1.png");
                if (!img.empty())
                {
                    cv::resize(img, img, cv::Size(512, 512));
                    this->ui->if_right->setText("False");
                    cv::cvtColor(img, img, cv::COLOR_BGR2RGB); //图像格式转换
                    QImage disImage = QImage((const unsigned char *)(img.data), img.cols, img.rows, QImage::Format_RGB888);
                    //this->ui->video_play->setImage(disImage);
                    QPixmap pix_img = QPixmap::fromImage(disImage);
                    this->ui->video_plays->setPixmap(pix_img);
                }
            });
    // reboot camera
    connect(ui->reopen_cam_button, &QPushButton::pressed, [=]()
            {
                timer->stop();
                camera_task->reboot();
                this->ui->if_right->setText("True");
                timer->start(10);
            });
    camera_thread->start();
}

void MainWindow::TransVideoInit()
{
    // init trans video Thread
    transvideo_thread = new QThread(this);
    transvideo_task = new TransVideoTask();
    transvideo_task->moveToThread(transvideo_thread);
    qRegisterMetaType<cv::Mat>("cv::Mat&");
    qRegisterMetaType<std::string>("std::string&");
    connect(camera_task, &CameraTask::toTransport, transvideo_task, &TransVideoTask::working, Qt::QueuedConnection);
    connect(transvideo_task, &TransVideoTask::setFailed, [=]()
            { ui->if_right_3->setText("Failed"); });
    //connect(detect_task, &DetectTask::toDisplay, transvideo_task, &TransVideoTask::working, Qt::QueuedConnection);
    transdata_task = new TransDataTask(5005);
    transdata_task->moveToThread(transvideo_thread);
    //connect()

    transvideo_thread->start();
}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loginInShow()
{

    timer->start(10);
    this->show();
    timer2->start(10000);
    emit startThread();
}

void MainWindow::display(cv::Mat &frame, std::vector<TrackingBox> &boxes)
{

    cv::Mat img = frame.clone();
    for (auto a : boxes)
    {
        std::string id;
        if(a.id==-1){
            id="";
        }else{
            id=std::to_string(a.id);
        }
        a.box&=cv::Rect2d(0,0,512,512);
        cv::Point2d pt=a.box.tl();
        if(pt.x<10){
            pt.x=10;
        }else if(pt.x>500){
            pt.x=500;
        }
        if(pt.y<10){
            pt.y=10;
        }else if(pt.y>500){
            pt.y=500;
        }
        cv::putText(img, id, a.box.tl(), 2, 2, cv::Scalar(0, 255, 0), 2);
        cv::rectangle(img, a.box, cv::Scalar(0, 255, 0), 2);
    }
    cv::cvtColor(img, img, cv::COLOR_BGR2RGB); //图像格式转换
    QImage disImage = QImage((const unsigned char *)(img.data), img.cols, img.rows, QImage::Format_RGB888);
    //this->ui->video_play->setImage(disImage);
    QPixmap pix_img = QPixmap::fromImage(disImage);
    this->ui->video_plays->setPixmap(pix_img);
}
