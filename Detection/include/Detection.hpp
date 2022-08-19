#ifndef DETECTION_HPP_
#define DETECTION_HPP_
#include <iostream>
#include "./TfliteWorker.hpp"
#include "opencv2/opencv.hpp"
#include <iostream>
#include <fstream>
/* 检测模块定位
功能
1. 含tflite worker 可以进行推理，并得出结果，结果应该为class_idex + confidence + rect.x +rect.y

2. 接受图像Frame ,使用tflite得到识别结果

3. 接受警告的特别区域的设置（AROI)，并可判断识别结果(AFE)是否在其中

4. 对外可以传输 识别结果，是否在AROI内，在AROI内的(AFE)的图像

5. 可以接受其他设备传来的AFE图像，并与本设备识别得到的图像作比对，输出是否相同
*/

struct Target
{

    int idex;
    // 时间戳
    int timestamp;
    // 相对图像位置
    cv::Rect2d location;
    // 类别
    int class_idex;
    // 置信度
    float confidence;
    // 是否需要注意
    bool if_attention;
};

class Detection
{

    // std::string labels_path;
    std::vector<std::string> labels_list;

    std::string error_meassages_;
    // std::string model_path;
    TfliteWorker tflite_worker;

    // 收集需要找到的目标
    bool getTarget(cv::Mat &frame, std::vector<Target> &target_lists);

    // 判断目标是否在AROI中
    bool ifInAROI(Target &target);

    // 判断危险区域
    std::vector<cv::Rect2d> attention_roi;

    // 从其他设备传来
    bool ifSameTarget(Target &target, cv::Mat &targe_frame, Target &attention_target, cv::Mat &attention_frame);

public:
    Detection(const &std::string model_path, const std::string &labels_path) ;

    void errorCalback();

    std::string error_meassages();

    bool setAROI(cv::Rect &roi);

    bool deleteAROI(cv::Rect &roi);

    // read from .txt
    bool loadLabelList(const std::srting &labels_path);
};

#endif