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
const std::string OUTURL ="192.168.1.126";
const std::string OUTPORT ="5004";


class TransVideoTask : public QObject
{
    Q_OBJECT
    std::shared_ptr<VideoTransporter> transporter;
    bool if_open{false};

public:
    TransVideoTask(QObject *parent = nullptr) : QObject(parent)
    {
        transporter = std::make_shared<VideoTransporter>();
        setTransport();
    }
    void working(cv::Mat &frame)
    {
        static double timestamp=0.002;
        if (if_open)
        {
            //qDebug()<<"open";
            cv::Mat img = frame;
            timestamp +=0.0002;
            transporter->Write(frame, timestamp);
        }
        else
        {
            setTransport();
        }
    }
    void setTransport()
    {
        transporter->SetSize(CAMERA_WIDTH, CAMERA_HEIGHT);
        std::pair<int, int> frame_rate(CAMERA_FPS, 1);
        transporter->SetFramerate(frame_rate);
        auto ret = transporter->Open(OUTURL, OUTPORT);
        if (ret < 0)
        {
            if_open = false;
            std::string error_msg = "set failed";
            emit setFailed(error_msg);
        }else{
            if_open=true;
        }
        //qDebug()<<"set ";
    }
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
    CameraTask(QObject *parent = nullptr) : QObject(parent)
    {
        camera = std::make_shared<CameraCV>();
        setCamera();
    }
    void working()
    {
        if (camera->isOpened())
        {

            if (camera->process() == false)
            {
                std::string error_msg;
                camera->getErrorMessage(error_msg);
                emit videoLost(error_msg);
            }
            else
            {
                camera->getCvFrame(this->frame);
                emit getFrame(this->frame);
            }
        }
        else
        {
            std::string error_msg = "video error";
            emit videoLost(error_msg);
        }
    }

    void setCamera()
    {
        CameraParam camera_param;
        camera_param.width = CAMERA_WIDTH;
        camera_param.height = CAMERA_HEIGHT;
        camera_param.exporsure = CAMERA_EXPORSURE;
        camera_param.fps = CAMERA_FPS * 2;
        camera->setCamera(camera_param);
        std::string path = camera_path;
        if (!camera->openCamera(path))
        {
            std::string error_msg;
            camera->getErrorMessage(error_msg);
            emit videoLost(error_msg);
        }
    }

    void reboot()
    {
        //this->camera->closeCamera();
        if(!camera->isOpened())
            setCamera();
    }
};

#endif
