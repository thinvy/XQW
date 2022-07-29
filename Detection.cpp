#include "Detection.hpp"

// 收集需要找到的目标
bool Detection::getTarget(cv::Mat &frame, std::vector<Target> &target_lists)
{
}

// 判断目标是否在AROI中
bool Detection::ifInAROI(Target &target)
{
    if (attention_roi.empty())
    {
        return false;
    }
    else
    {
        for (auto a : attention_roi)
        {
            if (target.location == (a & target.location))
                return true;
        }
    }
    return false;
}

// 从其他设备传来
bool Detection::ifSameTarget(Target &target, cv::Mat &targe_frame, Target &attention_target, cv::Mat &attention_frame)
{
    if (target.class_idex != attention_target.class_idex)
    {
        return false;
    }
    // 判断图像形似度
    return true;
}


Detection::Detection(const &std::string model_path, const std::string &labels_path) : tflite_worker(model_path)
{
    this->loadLabelList(labels_path);
}


void Detection::errorCalback()
{
}


std::string Detection::error_meassages()
{
    return this->error_meassages_;
}

bool Detection::setAROI(cv::Rect &roi)
{
    for (auto a : attention_roi)
    {
        if (a == roi)
        {
            this->error_meassages_ = "The Attention ROI  has been added";
            errorCallback();
            return false;
        }
    }
    this->attention_roi.push_back(roi);
    return true;
}


bool Detection::deleteAROI(cv::Rect &roi)
{
    for (auto a : attention_roi)
    {
        if (a == roi)
        {
            attention_roi.erase(a);
            return true;
        }
    }
    this->error_meassages_ = "No found the target Roi";
    errorCallback();
    return false;
}

// read from .txt
bool Detection::loadLabelList(const std::srting &labels_path)
{
    // 设置labels list
    this->labels_list.clear();

    std::ifstream fd;
    fd.open(labels_path.c_str());
    if (!fd.is_open())
    {
        this->error_meassages_ = "The labels txt open faied .";
        errorCallback();
        return false;
    }
    std::string temp;
    while (getline(fd, temp))
    {
        labels_list.push_back(temp);
    }
    fd.close();
    return true;
}
