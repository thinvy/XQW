#ifndef MAINTASK_HPP_
#define MAINTASK_HPP_

#include "./Receiver/include/VideoReceiver.hpp"
#include <QObject>
#include <iostream>
#include "./DrawMap/include/Map.hpp"
#include "Receiver/include/ResultTransporter.hpp"

#define WIDTH 640
#define HEIGHT 480
const std::string PORT = "5004";

class VideoReceiverTask : public QObject
{
    Q_OBJECT
    //std::shared_ptr<VideoTransporter> transporter;

    bool if_open{false};

    VideoReceiver *receiver;

    std::string port_id;

public:
    VideoReceiverTask(const std::string &port_id ="5004", QObject *parent = nullptr):QObject(parent){
        this->port_id="5004";
        setReceiver();
    }
    ~VideoReceiverTask(){
        if(if_open){
            delete  receiver;
        }
    }

    void working()
    {
        if (if_open)
        {
            cv::Mat frame;
            frame.create(cv::Size(WIDTH, HEIGHT), CV_8UC3);
            receiver->Read(frame);
            emit getFrame(frame);
        }else{
            setReceiver();
        }
    }

    void setReceiver()
    {
        receiver = new VideoReceiver();
        std::pair<int, int> frame_rate{30, 1};
        receiver->SetSize(WIDTH, HEIGHT);
        receiver->SetFramerate(frame_rate);
        auto ret = receiver->Open(this->port_id);
        if (ret < 0)
        {
            if_open = false;
            delete receiver;
            std::string error_msg = "video receiver set failed";
            std::cout<<error_msg<<std::endl;
            emit setFailed(error_msg);
        }
        else
        {
            if_open = true;
        }
    }
signals:
    void setFailed(std::string &error_msg);

    void getFrame(cv::Mat &frame);
};



class MessageReceiverTask : public QObject
{
    Q_OBJECT
    //std::shared_ptr<VideoTransporter> transporter;

    bool if_open{false};

    ResultTransporter *receiver;

    std::string port_id;

public:
    MessageReceiverTask(QObject *parent = nullptr):QObject(parent){
        setReceiver();
    }
    ~MessageReceiverTask(){
        if(if_open){
            delete  receiver;
        }
    }

    void working()
    {
        if (if_open)
        {
            float vid[256];
            int box_rx[4];
            uint8_t cam_id;
            uint8_t person_id;
            std::cout << "1" << std::endl;
            int rx = receiver->Receive(vid, box_rx, cam_id, person_id);
            std::cout << "2" << std::endl;
            if (rx > 0) {
                emit getMessage(box_rx, vid);
            }

        }else{
            setReceiver();
        }
    }

    void setReceiver()
    {
        receiver = new ResultTransporter(5005);
        if_open = true;
        auto ret = receiver->init();
        if (ret  == false) {
            std::string error_msg = "message receiver set failed";
            std::cout<<error_msg<<std::endl;
            error_msg = receiver->error_message();
            std::cout<<error_msg<<std::endl;
            if_open = false;
            delete receiver;
            emit setFailed(error_msg);
        }
        else
        {
            if_open = true;
        }
    }
signals:
    void setFailed(std::string &error_msg);
    void getMessage(int *boxes, float *person_vector);
};

#endif
