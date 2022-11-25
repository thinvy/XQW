#ifndef TFTILEWOREKER_HPP_
#define TFTILEWOREKER_HPP_

#include <tensorflow/lite/kernels/register.h>

#include "tensorflow/lite/examples/label_image/bitmap_helpers.h"
#include "tensorflow/lite/examples/label_image/get_top_n.h"
#include "tensorflow/lite/kernels/register.h"
#include "tensorflow/lite/optional_debug_tools.h"
#include "tensorflow/lite/profiling/profiler.h"
#include "tensorflow/lite/string_util.h"
#include "tensorflow/lite/tools/command_line_flags.h"
#include "tensorflow/lite/tools/delegates/delegate_provider.h"

#include <opencv2/videoio.hpp>
#include <opencv2/opencv.hpp>

#include "utils.hpp"
#include <iostream>
#include <armnn/ArmNN.hpp>
#include <armnn/Utils.hpp>
#include <delegate/armnn_delegate.hpp>
#include <delegate/DelegateOptions.hpp>

#define WARNING_IMAGE_RETREIVAL "Received invalid image path, could not run inference"
#define WARNING_INVOKE "Failed to run invoke"
#define WARNING_UNSUPPORTED_DATA_TYPE "Model data type currently not supported"
#define SCALE_FACTOR_UCHAR_TO_FLOAT (1 / 255.0F)
#include "../../Setting.hpp"

enum Delegate
{
    armNN,
    none
};

struct DetectBox
{
    float conf;
    float class_id;
    cv::Rect2d bbox;
};

using DetectbBoxList = std::vector<DetectBox>;

class TfliteWorker
{

public:
    // choose  delegate_type to selct model acceleration framework
    TfliteWorker(const std::string &modle_path, Delegate delegate_type = armNN, const int defaultThreads = 2);
    ~TfliteWorker();

private:
    // tflite interpreter for model inference
    std::unique_ptr<tflite::Interpreter> tflite_interpreter;
    std::unique_ptr<tflite::FlatBufferModel> tflite_model;

public:
    float *output_float;

    float zero_point;
    float scale;
    DetectbBoxList box_list;
    // error messafe
    std::string error_message_;

    // std::vector<float> output_tensor;
    int requried_width, requried_height, requried_channels;
    size_t requried_size_t;

public:
    // start inference ,return flase and error_message if faied
    bool inference(uchar *input_tensort, uchar *output_tensort);

    std::string error_message()
    {
        return this->error_message_;
    }
    // errorCalback : To do (may become a log record )
    void errorCallback()
    {
    }

    cv::Point3f getSize()
    {
        return cv::Point3f(requried_channels, requried_height, requried_width);
    }
};



class YoloWorker
{
public:
    std::shared_ptr<TfliteWorker> tflite_worker;

    YoloWorker(const std::string &modle_path)
    {
        this->tflite_worker = std::make_shared<TfliteWorker>(modle_path);
    }

public:
    bool preProcess(cv::Mat &frame, uchar *input_tensort)
    {
        cv::Point3f requires_size = this->tflite_worker->getSize();
        if (frame.empty())
        {
            return false;
        }
        cv::Mat m_frame=frame.clone();
        cv::Mat post_frame;
        cv::resize(m_frame, post_frame, cv::Size(requires_size.y, requires_size.z));
        memcpy(input_tensort, post_frame.data, post_frame.total() * post_frame.elemSize());
        return true;
    }

    bool postProcess(uchar *output_tensort, DetectbBoxList &result_list)
    {
        int anchor_size = ANCHOR_SIZE;
        int output_size = OUTPUT_SIZE;
        float conf_min = 0.;

        result_list.clear();
        bool if_nms = nms(tflite_worker->box_list, result_list);

        // for(auto temp:result_list){
        //     std::cout<<"nms box "<<temp.bbox<<"  "<<temp.conf<<std::endl;
        // }
        //  std::cout << "1 "<<std::endl;

        return true;
    }

    bool plotBox(cv::Mat &draw_frame, DetectbBoxList &result_list)
    {
        return true;
    }

    float iou(cv::Rect2d &a, cv::Rect2d &b)
    {
        cv::Rect2d same_rect = a & b;
        return same_rect.area() / (a.area() + b.area() - same_rect.area());
    }

    bool nms(DetectbBoxList &pre_list, DetectbBoxList &post_list)
    {
        std::sort(pre_list.begin(), pre_list.end(), [](DetectBox &a, DetectBox &b)
                  { return a.conf > b.conf; });
        while (pre_list.size() > 0)
        {
            post_list.push_back(pre_list.at(0));
            int index = 1;
            while (index < pre_list.size())
            {
                if (pre_list[0].class_id != pre_list.at(index).class_id)
                {
                    index++;
                    continue;
                }
                float iou_value = iou(pre_list.at(0).bbox, pre_list.at(index).bbox);
                if (iou_value > THRESHOLD)
                    pre_list.erase(pre_list.begin() + index);
                else
                    index++;
            }
            pre_list.erase(pre_list.begin());
        }
        return true;
    }
};

#endif