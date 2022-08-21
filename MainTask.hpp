#ifndef MAINTASK_HPP_
#define MAINTASK_HPP_
// Camera Task
#include "Camera/include/Camera.hpp"
// Writer and reader Task
#include "Codec/include/VideoReader.hpp"
#include "Codec/include/VideoWriter.hpp"
// Detection Task
//#include "Detection/include/Detection.hpp"
//#include "Detection/include/ReDetect.hpp"
//#include "Detection/include/Tracking.hpp"
//#include "Detection/include/TraEstim.hpp"
// Transporter Task
#include "Transporter/include/VideoTransporter.hpp"
#include <iostream>
#include <QObject>
#include <unistd.h>
#include <QDebug>

// const param
const std::string camera_path = "/dev/video0";
const int CAMERA_WIDTH = 640;
const int CAMERA_HEIGHT = 480;
const int CAMERA_EXPORSURE = 100;
const int CAMERA_FPS = 30;
const std::string OUTURL = "192.168.1.126";
const std::string OUTPORT = "5004";

class TransVideoTask : public QObject
{
    Q_OBJECT
    std::shared_ptr<VideoTransporter> transporter;
    bool if_open{false};

public:
    TransVideoTask(QObject *parent = nullptr);

    void working(cv::Mat &frame);

    void setTransport();
signals:
    void setFailed(std::string &error_msg);
};

class CameraTask : public QObject
{
    Q_OBJECT
    std::shared_ptr<Camera> camera;
signals:
    void getFrame(cv::Mat &frame);
    void videoLost(std::string &error_msg);

public:
    cv::Mat frame;
    CameraTask(QObject *parent = nullptr);
    void working();

    void setCamera();

    void reboot();
};
#endif
