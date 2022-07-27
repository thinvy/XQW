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
#ifdef DUNFELL
#include "tensorflow/lite/delegates/xnnpack/xnnpack_delegate.h"
#endif


#define WARNING_IMAGE_RETREIVAL "Received invalid image path, could not run inference"
#define WARNING_INVOKE "Failed to run invoke"
#define WARNING_UNSUPPORTED_DATA_TYPE "Model data type currently not supported"
#define SCALE_FACTOR_UCHAR_TO_FLOAT (1/255.0F)



enum Delegate { armNN, xnnpack, none };

class TfliteWorker 
{

public:
    TfliteWorker(const std::string &modle_path, Delegate delegate_type,const  int defaultThreads);
    ~TfliteWorker();

private:
    std::unique_ptr<tflite::Interpreter> tflite_interpreter;
    std::unique_ptr<tflite::FlatBufferModel> tflite_model;
    std::string error_message_;


    Mode mode_selected=PE;

    // std::vector<float> output_tensor;
    int requried_width, requried_height, requried_channels;
    size_t requried_size_t;



public:
    bool inference(const cv::Mat &frame,std::vector<float> &output_tensort,int &item_stride,int &time_cost);
    std::string error_message(){
        return this->error_message_;
    }

    void errorCalback(){

    }

};



#endif