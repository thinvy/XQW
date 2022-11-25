#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTime>
#include "MainTask.hpp"
#include <QThread>
#include <opencv2/opencv.hpp>
#include "DrawMap/include/Map.hpp"



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    int main_idex=1;
//    std::vector<QThread*> receiver_threads_pool;
//    std::vector<VideoReceiverTask*> receiver_tasks_pool;
    void receiverThreadInit();
    void messageReceiverThreadInit();
    //void setDisplay(int i);
    QThread* thread;
    QThread* msg_thread;
    VideoReceiverTask *task;
    MessageReceiverTask *msg_task;
    cv::VideoCapture cap0;
    cv::VideoCapture cap1;
    cv::VideoCapture cap2;
    cv::VideoCapture cap3;
    cv::VideoCapture cap4;
    int ix=0;
        int ix1=0;
            int ix2=0;
                int ix3=0;
                int ix4=0;
    cv::Mat stream_frame;
    cv::Mat person1_frame;
    cv::Mat person2_frame;
    Map map;
    void video1Display(cv::Mat &frame);
    void mapUpdate(int *boxes, float *person_vector);
public slots:
    void loginInShow();

private:
    Ui::MainWindow *ui;


    QTimer *timer;
    QTimer *timer1;
    QTimer *timer2;
    QTimer *timer3;

    cv::Point2f test_pos;
    cv::Size test_size;
    int test_state_0;
    int test_state_1;
};
#endif // MAINWINDOW_H
