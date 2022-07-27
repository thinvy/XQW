#ifndef CAMERA_HPP_
#define CAMERA_HPP_
#include "QObject"
#include "opencv2/opencv.hpp"
#include <iostream>

struct CameraParam
{
    int width = 640;
    int height = 480;
    int exporsure = 100;
};

class Camera
{

public:
    virtual bool openCamera(std::string &camera_path) = 0;
    virtual bool closeCamera() = 0;
    virtual bool getFrame(cv::Mat &frame) = 0;
    virtual void setCamera(CameraParam &param) = 0;
};

class CameraCV : public Camera
{
public:
    bool openCamera(std::string &camera_path) override
    {
        cap.open(camera_path);
        return cap.isOpened();
    }
    bool closeCamera() override
    {
        cap.release();
        return (!cap.isOpened());
    }
    bool getFrame(cv::Mat &frame) override
    {
        cap.read(frame);
        return (!frame.empty());
    }
    void setCamera(CameraParam &param) override
    {
        cap.set(cv::CAP_PROP_FOURCC, cv::VideoWriter::fourcc('U', 'Y', 'V', 'Y'));
        cap.set(cv::CAP_PROP_FRAME_WIDTH, param.width);
        cap.set(cv::CAP_PROP_FRAME_HEIGHT, param.height);
        cap.set(cv::CAP_PROP_AUTO_EXPOSURE, param.exporsure);
    }
    CameraCV(){}

private:
    cv::VideoCapture cap;
};

class CameraGS : public Camera
{

    bool openCamera(std::string &camera_path) override;
    bool closeCamera() override;
    bool getFrame(cv::Mat &frame) override;
    void setCamera(CameraParam &param) override;
    CameraGS();
};

#endif