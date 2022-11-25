#ifndef MAINTASK_HPP_
#define MAINTASK_HPP_
// Camera Task
#include "Camera/include/Camera.hpp"
// Writer and reader Task
#include "Codec/include/VideoReader.hpp"
#include "Codec/include/VideoWriter.hpp"
// Detection Task
#include "Detection/include/Detection.hpp"
#include "Detection/include/ReDetect.hpp"
#include "Detection/include/Tracking.hpp"
//#include "Detection/include/TraEstim.hpp"
#include "Detection/include/TfliteWorker.hpp"
#include "./Transporter/include/ResultTransporter.hpp"
// Transporter Task
#include "Transporter/include/VideoTransporter.hpp"
#include <iostream>
#include <QObject>
#include <unistd.h>
#include <QDebug>
#include "./Setting.hpp"


class TransVideoTask : public QObject
{
    Q_OBJECT
    //std::shared_ptr<VideoTransporter> transporter;
    VideoTransporter *transporter;

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
    void toTransport(cv::Mat &frame);

    void videoLost(std::string &error_msg);

    void toDisplay(cv::Mat &frame, std::vector<TrackingBox> &boxes);

    void toDetect(cv::Mat &frame, int if_direct_show);

public:
    cv::Mat frame;

    int if_direct_show = 0;

    CameraTask(QObject *parent = nullptr);

    void working();

    void setCamera();

    void reboot();
public slots:
    void directDislay();

    //DetectTask detect_task;
};

class DetectTask : public QObject
{
    Q_OBJECT
    std::shared_ptr<YoloWorker> detector;

    std::shared_ptr<ReDetect> redetect;

    std::shared_ptr<Tracking> tracking;

    bool if_open{false};

    int i = 0;

public:
    DetectTask(QObject *parent = nullptr);

    void working(cv::Mat &frame, int if_direct_show);

signals:
    void setFailed(std::string &error_msg);

    void toDisplay(cv::Mat &frame, std::vector<TrackingBox> &rects);

    void toSent(float *id_vector, cv::Rect2d &rect, uint8_t camera_id, uint8_t person_id);
};


class TransDataTask : public QObject
{
    Q_OBJECT
    std::shared_ptr<ResultTransporter> transporter;
    bool if_open{false};

public:
    TransDataTask(int port = 5005, QObject *parent = nullptr);

    void transmit(float *id_vector, cv::Rect2d &rect, uint8_t camera_id, uint8_t person_id);

    void receive();

signals:
    void sentFailed(std::string &error_msg);

    void toReDetect(float *id_vector, cv::Rect2d &rect, uint8_t camera_id, uint8_t person_id);
};
#endif
