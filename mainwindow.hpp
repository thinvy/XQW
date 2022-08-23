#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP
#include <opencv2/opencv.hpp>
#include <QMainWindow>
#include <QTimer>
#include "MainTask.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    cv::VideoCapture cap;
    QTimer * timer;
    CameraTask *camera_task;
    QThread *camera_thread;
    void cameraInit();


    TransVideoTask *transvideo_task;
    QThread *transvideo_thread;
    void TransVideoInit();
    void display(cv::Mat &frame);

    DetectTask *detect_task;
    void detectionInit();

public slots:
    void  loginInShow();

signals:
    void  startThread();
private:
    Ui::MainWindow *ui;
    // MainTask main_task;
};
#endif // MAINWINDOW_HPP
