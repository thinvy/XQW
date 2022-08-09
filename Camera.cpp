#include "./Camera.hpp"

//
// V4L2
//
#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <linux/videodev2.h>
#include <sys/ioctl.h>
#include <sys/mman.h>

namespace Foolish
{
    
    bool CameraV4L2::openCamera(std::string &camera_path)
    {
        if (camera_path.empty())
        {
            error_message_ = "error : camera path empty";
            return false;
        }

        // open camera

        fd_ = open(camera_path.c_str(), O_RDWR, 0777);
        if (fd_ < 0)
        {
            error_message_ = "error : camera open failed";
            return false;
        }

        // cheak camera

        struct v4l2_capability cap;
        memset(&cap, 0, sizeof(cap));
        if (ioctl(fd_, VIDIOC_QUERYCAP, &cap) == -1)
        {
            error_message_ = "error : camera type error";
            return false;
        }

        if ((cap.capabilities & V4L2_CAP_VIDEO_CAPTURE) != V4L2_CAP_VIDEO_CAPTURE)
        {
            error_message_ = "error : camera supports error";
            return false;
        }

        if ((cap.capabilities & V4L2_CAP_STREAMING) != V4L2_CAP_STREAMING)
        {
            error_message_ = "error : camera streaming error";
            return false;
        }

        // set camera parameters
        // 1. set video system
        // 2. set video image acquisition window size
        // 3. set video format

        struct v4l2_format fmt;
        memset(&fmt, 0, sizeof(fmt));
        fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        fmt.fmt.pix.width = param_.width;
        fmt.fmt.pix.height = param_.height;
        // fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_YUYV;
        fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_MJPEG;
        fmt.fmt.pix.field = V4L2_FIELD_INTERLACED;
        if (ioctl(fd_, VIDIOC_S_FMT, &fmt) == -1)
        {
            error_message_ = "error : camera set formate error";
            return false;
        }
        // 4. set camera frame rate
        struct v4l2_streamparm parm;
        memset(&parm, 0, sizeof(parm));
        parm.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        parm.parm.capture.timeperframe.numerator = 513;
        parm.parm.capture.timeperframe.denominator = 61612;
        parm.parm.capture.capturemode = 0;
        if (ioctl(fd_, VIDIOC_S_PARM, &parm) == -1)
        {
            error_message_ = "error : camera set streamparm error";
            return false;
        }

        std::cout<<"set camera param : " << std::endl;
        std::cout<< parm.parm.capture.timeperframe.numerator  << std::endl;
        std::cout<< parm.parm.capture.timeperframe.denominator << std::endl;

        // 5. set camera buffer
        struct v4l2_requestbuffers req;
        memset(&req, 0, sizeof(req));
        req.count = FREAM_BUFFER_NUM;
        req.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        req.memory = V4L2_MEMORY_MMAP;
        if ((ioctl(fd_, VIDIOC_REQBUFS, &req) == -1))
        {
            error_message_ = "error : camera malloc requestbuffers error";
            return false;
        }

        for (unsigned int i = 0; i < req.count; ++i)
        {
            struct v4l2_buffer buf;
            memset(&buf, 0, sizeof(buf));
            buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
            buf.memory = V4L2_MEMORY_MMAP;
            buf.index = i;
            if ((ioctl(fd_, VIDIOC_QUERYBUF, &buf) == -1))
            {
                error_message_ = "error : camera buffer error";
                return false;
            }
            frame_buffers_[i].length = buf.length;
            frame_buffers_[i].start = mmap(NULL, buf.length, PROT_READ | PROT_WRITE, MAP_SHARED, fd_, buf.m.offset);
            if (frame_buffers_[i].start == MAP_FAILED)
            {
                error_message_ = "error : camera mmap error";
                return -1;
            }
        }

        for (unsigned int i = 0; i < FREAM_BUFFER_NUM; i++)
        {
            struct v4l2_buffer buf;
            memset(&buf, 0, sizeof(buf));
            buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
            buf.memory = V4L2_MEMORY_MMAP;
            buf.index = i;
            if (ioctl(fd_, VIDIOC_QBUF, &buf) == -1)
            {
                error_message_ = "error : camera qbuf error";
            }
        }

        for (unsigned int i = 0; i < FREAM_BUFFER_NUM; i++)
        {
            struct v4l2_buffer buf;
            memset(&buf, 0, sizeof(buf));
            buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
            buf.memory = V4L2_MEMORY_MMAP;
            buf.index = i;
            if (ioctl(fd_, VIDIOC_QBUF, &buf) == -1)
            {
                error_message_ = "error : camera qbuf error";
            }
        }

        // camera open

        enum v4l2_buf_type type;
        type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        if (ioctl(fd_, VIDIOC_STREAMON, &type) == -1)
        {
            error_message_ = "error : camera stream on error";
        }

        error_message_ = "NONE";
        return true;
    }

    bool CameraV4L2::process()
    {
        

        std::chrono::high_resolution_clock::time_point start_time = std::chrono::high_resolution_clock::now();

        struct v4l2_buffer buf;
        memset(&buf, 0, sizeof(buf));
        buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        buf.memory = V4L2_MEMORY_MMAP;

        
        

        std::chrono::high_resolution_clock::time_point stop_time = std::chrono::high_resolution_clock::now();

        if (ioctl(fd_, VIDIOC_DQBUF, &buf) < 0)
        {
            error_message_ = "error : camera dqbuf error";
            return false;
        }

        std::chrono::high_resolution_clock::time_point stop_time1 = std::chrono::high_resolution_clock::now();
        
        // usleep(40000);

        memset(frame_yuv_, 0, sizeof(frame_yuv_));
        std::cout << "bytes : " << buf.bytesused << std::endl;
        // memcpy(frame_yuv_, frame_buffers_[buf.index].start, buf.bytesused);
        // memcpy(frame_yuv_, frame_buffers_[buf.index].start, sizeof(frame_yuv_));
        // yuv_to_rgb(frame_yuv_, frame_rgb_);
        // yuv_to_rgb((unsigned char *)frame_buffers_[buf.index].start, frame_rgb_);
        
        // switch (buf.index) {
        //     case 0:
        //     case 1:
        //     case 2:
        //     case 3:
        //     case 4:
        // }
        if (ioctl(fd_, VIDIOC_QBUF, &buf) == -1)
        {
            error_message_ = "error : camera qbuf error";
        }
        
        std::chrono::high_resolution_clock::time_point stop_time2 = std::chrono::high_resolution_clock::now();

        

        int time_cost0 = int(std::chrono::duration_cast<std::chrono::milliseconds>(stop_time - start_time).count());
        int time_cost1 = int(std::chrono::duration_cast<std::chrono::milliseconds>(stop_time1 - stop_time).count());
        int time_cost2 = int(std::chrono::duration_cast<std::chrono::milliseconds>(stop_time2 - stop_time1).count());
        std::cout << "buffer index : " << buf.index << std::endl;
        std::cout << "the time cost is : " << time_cost0 << std::endl;
        std::cout << "the time cost1 is : " << time_cost1 << std::endl;
        std::cout << "the time cost2 is : " << time_cost2 << std::endl;

        error_message_ = "NONE";
        return true;
    }

    bool CameraV4L2::closeCamera()
    {
        // close camera
        enum v4l2_buf_type type;
        type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        if ((ioctl(fd_, VIDIOC_STREAMOFF, &type) == -1))
        {
            error_message_ = "error : camera stream off error";
            return false;
        }

        // relase memory
        for (unsigned int i = 0; i < FREAM_BUFFER_NUM; i++)
        {
            if (munmap(frame_buffers_[i].start, frame_buffers_[i].length) == -1)
            {
                error_message_ = "error : camera munmap error!!!";
                return false;
            }
        }

        close(fd_);

        error_message_ = "NONE";
        return true;
    }

    // void CameraV4L2::yuv_to_rgb(unsigned char *yuv, unsigned char *rgb)
    // {
    //     unsigned int i;
    //     unsigned char *y0 = yuv + 0;
    //     unsigned char *u0 = yuv + 1;
    //     unsigned char *y1 = yuv + 2;
    //     unsigned char *v0 = yuv + 3;

    //     unsigned char *r0 = rgb + 0;
    //     unsigned char *g0 = rgb + 1;
    //     unsigned char *b0 = rgb + 2;
    //     unsigned char *r1 = rgb + 3;
    //     unsigned char *g1 = rgb + 4;
    //     unsigned char *b1 = rgb + 5;

    //     float rt0 = 0, gt0 = 0, bt0 = 0, rt1 = 0, gt1 = 0, bt1 = 0;

    //     for (i = 0; i <= (param_.width * param_.height) / 2; i++)
    //     {
    //         bt0 = 1.164 * (*y0 - 16) + 2.018 * (*u0 - 128);
    //         gt0 = 1.164 * (*y0 - 16) - 0.813 * (*v0 - 128) - 0.394 * (*u0 - 128);
    //         rt0 = 1.164 * (*y0 - 16) + 1.596 * (*v0 - 128);

    //         bt1 = 1.164 * (*y1 - 16) + 2.018 * (*u0 - 128);
    //         gt1 = 1.164 * (*y1 - 16) - 0.813 * (*v0 - 128) - 0.394 * (*u0 - 128);
    //         rt1 = 1.164 * (*y1 - 16) + 1.596 * (*v0 - 128);

    //         if (rt0 > 250)
    //             rt0 = 255;
    //         if (rt0 < 0)
    //             rt0 = 0;

    //         if (gt0 > 250)
    //             gt0 = 255;
    //         if (gt0 < 0)
    //             gt0 = 0;

    //         if (bt0 > 250)
    //             bt0 = 255;
    //         if (bt0 < 0)
    //             bt0 = 0;

    //         if (rt1 > 250)
    //             rt1 = 255;
    //         if (rt1 < 0)
    //             rt1 = 0;

    //         if (gt1 > 250)
    //             gt1 = 255;
    //         if (gt1 < 0)
    //             gt1 = 0;

    //         if (bt1 > 250)
    //             bt1 = 255;
    //         if (bt1 < 0)
    //             bt1 = 0;

    //         *r0 = (unsigned char)rt0;
    //         *g0 = (unsigned char)gt0;
    //         *b0 = (unsigned char)bt0;

    //         *r1 = (unsigned char)rt1;
    //         *g1 = (unsigned char)gt1;
    //         *b1 = (unsigned char)bt1;

    //         yuv = yuv + 4;
    //         rgb = rgb + 6;
    //         if (yuv == NULL)
    //             break;

    //         y0 = yuv;
    //         u0 = yuv + 1;
    //         y1 = yuv + 2;
    //         v0 = yuv + 3;

    //         r0 = rgb + 0;
    //         g0 = rgb + 1;
    //         b0 = rgb + 2;
    //         r1 = rgb + 3;
    //         g1 = rgb + 4;
    //         b1 = rgb + 5;
    //     }
    // }

    void CameraV4L2::yuv_to_rgb(unsigned char *yuv, unsigned char *rgb)
    {
        cv::Mat yuvMat(param_.height, param_.width, CV_8UC2, yuv);;
        cv::Mat rgbMat(param_.height, param_.width, CV_8UC3);
        cv::cvtColor(yuvMat, rgbMat, cv::COLOR_YUV2RGB_YUYV);
        memcpy(rgb, rgbMat.data, param_.height*param_.width*3);
    }
}
