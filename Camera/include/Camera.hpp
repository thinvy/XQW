#ifndef CAMERA_HPP_
#define CAMERA_HPP_

#include "opencv2/opencv.hpp"
#include <iostream>

namespace Foolish
{
    struct CameraParam
    {
        int width = 640;
        int height = 480;
        int exporsure = 100;
    };

    class Camera
    {
    public:
        virtual void setCamera(CameraParam &param) = 0;
        virtual bool openCamera(std::string &camera_path) = 0;
        virtual bool closeCamera() = 0;
        virtual bool process() = 0;
        virtual bool getCvFrame(cv::Mat &frame) = 0;
        virtual const unsigned char *getRGBFrame() = 0;
        virtual const unsigned char *getYUVFrame() = 0;
        virtual void getErrorMessage(std::string &error_msg) = 0;
    };

    class CameraCV : public Camera
    {
    public:
        const unsigned char *getRGBFrame() { return NULL; }
        const unsigned char *getYUVFrame() { return NULL; }
        bool process() { return true; }
        void getErrorMessage(std::string &error_msg) {}
        bool openCamera(std::string &camera_path) override
        {
            cap.open(camera_path);
            cap.set(cv::CAP_PROP_FOURCC, cv::VideoWriter::fourcc('M', 'J', 'P', 'G'));
            cap.set(cv::CAP_PROP_FRAME_WIDTH, param_.width);
            cap.set(cv::CAP_PROP_FRAME_HEIGHT, param_.height);
            cap.set(cv::CAP_PROP_FPS, 120);
            // cap.set(cv::CAP_PROP_FOURCC, cv::VideoWriter::fourcc('M', 'J', 'P', 'G'));
            // cap.open(camera_path);
            return cap.isOpened();
        }
        bool closeCamera() override
        {
            cap.release();
            return (!cap.isOpened());
        }
        bool getCvFrame(cv::Mat &frame) override
        {
            cap.read(frame);
            return (!frame.empty());
        }
        void setCamera(CameraParam &param) override
        {
            param_.width = param.width;
            param_.height = param.height;
            param_.exporsure = param.exporsure;
            // cap.set(cv::CAP_PROP_FRAME_WIDTH, param.width);
            // cap.set(cv::CAP_PROP_FRAME_HEIGHT, param.height);
            // cap.set(cv::CAP_PROP_FPS, 60);
            // cap.set(cv::CAP_PROP_FOURCC, cv::VideoWriter::fourcc('M', 'J', 'P', 'G'));
            // cap.set(cv::CAP_PROP_AUTO_EXPOSURE, param.exporsure);
        }
        CameraCV() {}

    private:
        cv::VideoCapture cap;
        CameraParam param_;
    };

    class CameraGS : public Camera
    {
    public:
        bool openCamera(std::string &camera_path) override;
        bool closeCamera() override;
        bool getCvFrame(cv::Mat &frame) override;
        void setCamera(CameraParam &param) override;
        CameraGS();
    };

    //
    // V4L2
    //

#define FREAM_BUFFER_NUM 10

    class CameraV4L2 : public Camera
    {
    public:
        void setCamera(CameraParam &param) override
        {
            param_.width = param.width;
            param_.height = param.height;
            param_.exporsure = param.exporsure;
        }
        bool openCamera(std::string &camera_path) override;
        bool closeCamera() override;
        bool process() override;
        bool getCvFrame(cv::Mat &frame) override
        {
            frame = cv::Mat(param_.height, param_.width, CV_8UC3, frame_rgb_);
            return (!frame.empty());
        }
        const unsigned char *getRGBFrame() override
        {
            return frame_rgb_;
        }
        const unsigned char *getYUVFrame() override
        {
            return frame_yuv_;
        }
        void getErrorMessage(std::string &error_msg) override
        {
            error_msg = error_message_;
        }

        CameraV4L2() { fd_ = -1; }

    private:
        std::string error_message_;

    private:
        cv::Mat frame_cv_mat_;
        unsigned char frame_rgb_[640 * 480 * 3];
        unsigned char frame_yuv_[640 * 480 * 2];

    private:
        struct CameraParam param_;

    private:
        void yuv_to_rgb(unsigned char *yuv, unsigned char *rgb);

    private:
        int fd_;
        struct FrameBuffer
        {
            void *start;
            size_t length;
        } frame_buffers_[FREAM_BUFFER_NUM];
    };

}

#endif