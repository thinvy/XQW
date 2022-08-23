/*****************************************************************************************
 * Copyright (C) 2022 Renesas Electronics Corp.
 * This file is part of the RZ Edge AI Demo.
 *
 * The RZ Edge AI Demo is free software using the Qt Open Source Model: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * The RZ Edge AI Demo is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with the RZ Edge AI Demo.  If not, see <https://www.gnu.org/licenses/>.
 *****************************************************************************************/

#ifndef TFTILEWOREKER_HPP_
#define TFTILEWOREKER_CPP_

#include <tensorflow/lite/kernels/register.h>
#include <opencv2/videoio.hpp>

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

enum Delegate
{
    armNN,
    none
};

class TfliteWorker
{

public:
    // choose  delegate_type to selct model acceleration framework
    TfliteWorker(const std::string &modle_path, Delegate delegate_type = armNN, const int defaultThreads = 1);
    ~TfliteWorker();

private:
    // tflite interpreter for model inference
    std::unique_ptr<tflite::Interpreter> tflite_interpreter;
    std::unique_ptr<tflite::FlatBufferModel> tflite_model;

    // error messafe
    std::string error_message_;

    // std::vector<float> output_tensor;
    int requried_width, requried_height, requried_channels;
    size_t requried_size_t;

public:
    // start inference ,return flase and error_message if faied
    bool inference(float *input_tensort, float *output_tensort);

    std::string error_message()
    {
        return this->error_message_;
    }
    // errorCalback : To do (may become a log record )
    void errorCalback()
    {
    }

    cv::Point3f getSize()
    {
        return cv::Point3f(requried_channels, requried_height, requried_width);
    }
};

struct DetectBox
{
    float conf;
    float class_id;
    cv::Rect2d bbox;
};

using DetectbBoxList = std::vector<DetectBox>;

class YoloWorker
{
public:
    std::shared_ptr<TfliteWorker> tflite_worker;

    YoloWorker(const std::string &modle_path)
    {
        this->tflite_worker = std::make_shared<TfliteWorker>(modle_path);
    }

public:
    bool preProcess(cv::Mat &frame, float *input_tensort)
    {
        cv::Point3f requires_size = this->tflite_worker->getSize();
        if (frame.empty(()))
        {
            return false;
        }
        cv::Mat post_frame;
        cv::resize(frame, post_frame, cv::Size(requrirequires_size.y, requires_size.z), CV_8UC3);
        cv::divide(255.0, post_frame, post_frame, CV_16FC3);
        memcpy((void *)input_tensort, (void *)post_frame.data(), requires_size.x * requires_size.y * requires_size.z * sizeof(float));
    }

    bool postProcess(float *output_tensort, DetectbBoxList &result_list)
    {
        int anchor_size = 6300;
        int output_size = 6;
        int conf_min = 0.5;
        // 1*6*6300
        /*
        x
        y
        w
        h
        conf
        id_conf
        */
        result_list.clear();
        DetectbBoxList pre_list;
        for (int i = 0; i < anchor_size; i += output_size)
        {
            if (output_tensort[i + 4 * anchor_size] <= conf_min)
            {
                continue;
            }
            DetectBox temp;
            temp.bbox = cv::Rect2d(output_tensort[i + 0 * anchor_size], output_tensort[i + 1 * anchor_size], output_tensort[i + 2 * anchor_size], output_tensort[i + 3 * anchor_size]);
            temp.conf = output_tensort[i + 4 * anchor_size] * output_tensort[i + 5 * anchor_size];
            pre_list.push_back(temp);
        }
        bool if_nms = nms(pre_list, result_list);
        return true;
    }

    bool plotBox(cv::Mat &draw_frame DetectbBoxList &result_list)
    {
    }

    bool iou(cv::Rect2d &a, cv::Rect2d &b)
    {
        cv::Rect2d same_rect = a & b;
        return same_rect.area()/(a.area(+b.area()-same_rect.area());
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
                // cout << "iou:" << iou_value << endl;
                if (iou_value > THRESHOLD)
                    pre_list.erase(pre_list.begin() + index);
                else
                    index++;
            }
            pre_list.erase(pre_list.begin());
        }
        return true;
    }
}

#endif