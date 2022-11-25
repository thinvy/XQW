#ifndef REDETECT_HPP_
#define REDETECT_HPP_

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
#include "./TfliteWorker.hpp"

#define WARNING_IMAGE_RETREIVAL "Received invalid image path, could not run inference"
#define WARNING_INVOKE "Failed to run invoke"
#define WARNING_UNSUPPORTED_DATA_TYPE "Model data type currently not supported"
#define SCALE_FACTOR_UCHAR_TO_FLOAT (1 / 255.0F)
#include "../../Setting.hpp"

class ReDetect
{

public:
    // choose  delegate_type to selct model acceleration framework
    ReDetect(const std::string &modle_path, Delegate delegate_type = none, const int defaultThreads = 2);
    ~ReDetect();

private:
    // tflite interpreter for model inference
    std::unique_ptr<tflite::Interpreter> tflite_interpreter;
    std::unique_ptr<tflite::FlatBufferModel> tflite_model;

public:
    float *output_float;
    float *input_float;

public:
    // start inference ,return flase and error_message if faied
    bool inference(cv::Mat &frame);

    float getdistance(float *x_map, float *y_map){
        // 256
        float a=0.0;
        float b=0.0;
        float c=0.0;
        for(int i=0;i<256;i++){
            a+=x_map[i]*y_map[i];
            b+=x_map[i]*x_map[i];
            c+=y_map[i]*y_map[i];
        }
        return a/(sqrt(b*c));
    }
};

#endif