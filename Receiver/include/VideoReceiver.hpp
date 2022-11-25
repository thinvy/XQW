#ifndef __VIDEO_RECEIVER_HPP__
#define __VIDEO_RECEIVER_HPP__


#include <string>
#include "opencv2/opencv.hpp"
#include <gst/gst.h>

class VideoReceiver {
public:
    ~VideoReceiver();
    /**
     * @brief 打开视频, url为视频的文件路径或者网络地址
     */
    int Open(const std::string port);

    /**
     * @brief 设置视频帧率
     * @param fps = framerate.first/framerate.second
     */
    void SetFramerate(std::pair<int, int> framerate) {
        framerate_ = framerate;
    }

    /**
     * @brief 设置视频分辨率
     */
    void SetSize(int width, int height) {
        width_ = width;
        height_ = height;
    }
    
    /**
     * @brief 设置视频码率
     * @param bitrate 单位bit/sec
     */
    void SetBitrate(int bitrate) {
        bitrate_ = bitrate;
    }

    /**
     * @brief 写入视频帧
     * @param timestamp 单位秒
     */
    int Read(const cv::Mat& frame);

private:
    int ReceiveDataFromePipeline(const cv::Mat& frame);
    GstElement *pipeline_; 
    GstElement *src_; 
    GstElement *buffer_; 
    GstElement *queue0_; 
    GstElement *dpay_; 
    GstElement *parse_; 
    GstElement *queue1_; 
    GstElement *decoder_; 
    GstElement *sink_;
    int paddedWidth_ = 0;
    int paddedHeight_ = 0;
    int width_= 0;
    int height_ = 0;
    int bitrate_ = 0;
    std::string srcFmt_;
    std::pair<int, int> framerate_{30, 1};
};

#endif