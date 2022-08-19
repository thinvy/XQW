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

#include "../include/TfliteWorker.hpp"

TfliteWorker::TfliteWorker(const std::string &modle_path, Delegate delegate_type, const int defaultThreads)
{

    //load model from file
    this->tflite_model = tflite::FlatBufferModel::BuildFromFile(modle_path.c_str());
    // set tflite resolver to build interpreter
    tflite::ops::builtin::BuiltinOpResolver tflite_resolver;
    tflite::InterpreterBuilder(*this->tflite_model, tflite_resolver)(&this->tflite_interpreter);

    /* Setup the delegate */
    if (delegate_type == armNN)
    {
        // set armnn options
        std::vector<armnn::BackendId> backends = {armnn::Compute::CpuAcc};
        armnnDelegate::DelegateOptions delegateOptions(backends);
        // set Armmptr
        using ArmmPtr = std::unique_ptr<TfLiteDelegate, decltype(&armnnDelegate::TfLiteArmnnDelegateDelete)>;
        ArmmPtr armnnTfLiteDelegate(armnnDelegate::TfLiteArmnnDelegateCreate(delegateOptions), armnnDelegate::TfLiteArmnnDelegateDelete);

        /* Instruct the Interpreter to use the armnnDelegate */
        if (this->tflite_interpreter->ModifyGraphWithDelegate(std::move(armnnTfLiteDelegate)) != kTfLiteOk)
        {
            this->error_message_ = "ArmNN Delegate could not be used to modify the graph\n";
            this->errorCallback();
        }
    }
    else
    {
        //  select delegateType is none
    }

    if (this->tflite_interpreter->AllocateTensors() != kTfLiteOk)
    {
        this->error_message_ = "Failed to allocate tensors!";
        this->errorCallback();
    }

    this->tflite_interpreter->SetProfiler(nullptr);
    this->tflite_interpreter->SetNumThreads(defaultThreads);

    // set requried_dim
    TfLiteIntArray *requried_dimensions;
    requried_dimensions = this->tflite_interpreter->tensor(this->tflite_interpreter->inputs()[0])->dims;
    requried_height = requried_dimensions->data[1];
    requried_width = requried_dimensions->data[2];
    requried_channels = requried_dimensions->data[3];
    if (tflite_interpreter->tensor(tflite_interpreter->inputs()[0])->type == kTfLiteFloat32)
    {
        requried_size_t = sizeof(float);
    }
    else if (tflite_interpreter->tensor(tflite_interpreter->inputs()[0])->type == kTfLiteUInt8)
    {
        requried_size_t = sizeof(uint8_t);
    }
    else
    {
        this->error_message_ = "Model data type currently not supported!";
        this->errorCallback();
        return false;
    }
}

TfliteWorker::~TfliteWorker()
{
    this->tflite_interpreter.reset();
}

bool TfliteWorker::inference(const cv::Mat &frame, std::vector<float> &output_tensor, int &item_stride, int &time_cost)
{
    output_tensor.clear();
    if (frame.empty())
    {
        this->error_message_ = WARNING_IMAGE_RETREIVAL;
        this->errorCallback();
    }

    // process frame
    std::chrono::high_resolution_clock::time_point prcoss_start_time = std::chrono::high_resolution_clock::now();
    cv::Mat resize_frame;
    cv::resize(frame, resize_frame, cv::Size(requried_height, requried_width));
    // set input data
    if (this->requried_size_t == sizeof(float))
    {
        /*
         * Convert cv::Mat data type from 8-bit unsigned char to 32-bit float.
         * The data of the image needs to be divided by 255.0f as CV_8UC3 ranges
         * from 0 to 255, whereas CV_32FC3 ranges from 0 to 1
         */
        resize_frame.convertTo(resize_frame, CV_32FC3, SCALE_FACTOR_UCHAR_TO_FLOAT);
        memcpy(tflite_interpreter->typed_tensor<float>(tflite_interpreter->inputs()[0]), resize_frame.data, resize_frame.total() * resize_frame.elemSize());
    }
    else if (this->requried_size_t == sizeof(uint8_t))
    {
        //copy data from mat to tensor
        memcpy(tflite_interpreter->typed_tensor<uint8_t>(tflite_interpreter->inputs()[0]), resize_frame.data, resize_frame.total() * resize_frame.elemSize());
    }

    std::chrono::high_resolution_clock::time_point prcoss_stop_time = std::chrono::high_resolution_clock::now();

    //  start inference and get time
    std::chrono::high_resolution_clock::time_point inference_start_time = std::chrono::high_resolution_clock::now();
    // get interpreter time;
    if (tflite_interpreter->Invoke() != kTfLiteOk)
    {
        this->error_message_ = WARNING_INVOKE;
        this->errorCallback();
        return false;
    }
    std::chrono::high_resolution_clock::time_point inference_stop_time = std::chrono::high_resolution_clock::now();
// get time_cost
    time_cost = int(std::chrono::duration_cast<std::chrono::milliseconds>(inference_stop_time - inference_start_time).count());
// get output_tensort
    std::vector<int> output_tensor_count;
    /* Cycle through each output tensor and store all data */
    for (size_t i = 0; i < tflite_interpreter->outputs().size(); i++)
    {
        /* Total number of data elements */
        int output_count = tflite_interpreter->output_tensor(i)->bytes / this->requried_size_t;

        output_tensor_count.push_back(output_count);

        for (int k = 0; k < output_count; k++)
        {
            float output = tflite_interpreter->typed_output_tensor<float>(i)[k];
            output_tensor.push_back(output);
        }
    }
// get item_stride

    output_tensor_count.pop_back();
    item_stride = output_tensor_count.pop_back();
 
    return true;
}
