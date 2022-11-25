#include "../include/ReDetect.hpp"

ReDetect::ReDetect(const std::string &modle_path, Delegate delegate_type, const int defaultThreads)
{

    output_float = new float[256];
    input_float = new float[256 * 128 * 3];
    this->tflite_model = tflite::FlatBufferModel::BuildFromFile(modle_path.c_str());
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
        }
    }

    if (this->tflite_interpreter->AllocateTensors() != kTfLiteOk)
    {
    }

    this->tflite_interpreter->SetProfiler(nullptr);
    this->tflite_interpreter->SetNumThreads(defaultThreads);



    int output_height, output_width, output_channels;
    TfLiteIntArray *output_dimensions;
    output_dimensions = this->tflite_interpreter->tensor(this->tflite_interpreter->outputs()[0])->dims;
    output_height = output_dimensions->data[1];
    output_width = output_dimensions->data[2];
    output_channels = output_dimensions->data[3];

    std::cout << "output_height" << output_height << std::endl;
    std::cout << "output_width" << output_width << std::endl;
    std::cout << "output_channels" << output_channels << std::endl;

    // tflite::PrintInterpreterState(tflite_interpreter.get());
}

ReDetect::~ReDetect()
{
    this->tflite_interpreter.reset();
}

bool ReDetect::inference(cv::Mat &frame)
{
    if (frame.empty())
    {
        return false;
    }
    cv::Mat img;
    cv::resize(frame, img, cv::Size(256, 128));
    std::chrono::high_resolution_clock::time_point prcoss_start_time = std::chrono::high_resolution_clock::now();
    int n = 0;
    for (int y = 0; y < img.rows; y++)
    {
        for (int x = 0; x < img.cols; x++)
        {
            for (int c = 0; c < img.channels(); c++)
            {
                tflite_interpreter->typed_tensor<float>(tflite_interpreter->inputs()[0])[n++] = (float)img.data[y * img.step + x * img.elemSize() + c];

            }
        }
    }

    std::chrono::high_resolution_clock::time_point prcoss_stop_time = std::chrono::high_resolution_clock::now();

    //  start inference and get time
    std::chrono::high_resolution_clock::time_point inference_start_time = std::chrono::high_resolution_clock::now();
    // get interpreter time;
    if (tflite_interpreter->Invoke() != kTfLiteOk)
    {
        return false;
    }

    std::chrono::high_resolution_clock::time_point inference_stop_time = std::chrono::high_resolution_clock::now();
    // get time_cost
    int time_cost = int(std::chrono::duration_cast<std::chrono::milliseconds>(inference_stop_time - inference_start_time).count());
    // std::cout<<"REID "<<time_cost<<std::endl;
    TfLiteTensor *pOutputTensor = tflite_interpreter->tensor(tflite_interpreter->outputs()[0]);

    // std::cout<<"the tensort"<<std::endl;
    for (size_t i = 0; i < 256; i += 1)
    {
        output_float[i] = tflite_interpreter->typed_output_tensor<float>(0)[i];
        // std::cout<<output_float[i]<<" ,";
    }
    std::cout<<std::endl<<std::endl;
    // float bb[]={
    //     0.173637 ,-1.05177 ,-0.719128 ,0.753727 ,-0.739868 ,-0.0623487 ,-0.208757 ,0.0114336 ,0.358174 ,0.404875 ,0.924393 ,0.215949 ,0.927208 ,0.611483 ,-0.185713 ,-0.168182 ,0.0760386 ,0.637111 ,0.416128 ,0.692897 ,0.170613 ,-1.18434 ,-1.10185 ,-0.161114 ,0.0813787 ,-0.502078 ,-0.370589 ,-0.102727 ,-0.0891437 ,-0.209162 ,-0.619288 ,0.465356 ,-0.223512 ,0.283707 ,-0.48526 ,0.300689 ,-0.398718 ,0.0181134 ,0.355737 ,-0.260115 ,0.643229 ,0.29128 ,-0.392496 ,0.366139 ,-0.0974087 ,-0.239453 ,0.237623 ,0.692041 ,0.192847 ,-0.0191557 ,-0.726364 ,-0.886335 ,-1.12277 ,-0.0610729 ,0.0951118 ,0.596307 ,-0.190321 ,-1.26142 ,0.957625 ,0.102412 ,0.709797 ,0.462534 ,-0.3156 ,0.0443892 ,0.203924 ,-0.384161 ,-0.336726 ,1.09775 ,0.24057 ,0.317167 ,1.29347 ,-0.0640779 ,0.987137 ,-0.516043 ,0.208973 ,-0.0842408 ,-0.72285 ,-0.297798 ,0.994052 ,0.596333 ,0.0249453 ,0.314169 ,-0.150268 ,-0.54639 ,-0.306738 ,1.19677 ,-0.568945 ,-0.706745 ,0.538283 ,0.0686863 ,-0.699749 ,-0.459021 ,0.0816772 ,-0.287503 ,0.137161 ,0.437624 ,0.0905037 ,-0.074968 ,-0.0678889 ,0.450368 ,0.001544 ,0.160789 ,0.577297 ,0.00211906 ,0.119815 ,0.408371 ,-0.704422 ,1.13715 ,0.60661 ,-0.72389 ,0.657653 ,0.160981 ,-0.974812 ,-0.45925 ,-0.0194732 ,0.539425 ,-0.527745 ,0.514708 ,-0.217092 ,0.687044 ,0.567967 ,-0.192023 ,0.157574 ,-0.242474 ,-0.651163 ,0.161984 ,-0.337482 ,-0.134075 ,0.386291 ,0.207346 ,0.269531 ,-0.244059 ,-0.751986 ,0.0450653 ,-1.28863 ,-0.697274 ,0.427618 ,-0.213375 ,-0.282183 ,0.0994631 ,-0.55274 ,-0.34375 ,0.586486 ,0.101224 ,-0.16616 ,-0.249514 ,-0.463998 ,1.00066 ,0.34824 ,-0.220656 ,-0.539268 ,0.518719 ,-0.641782 ,0.30475 ,-0.787534 ,0.83274 ,-0.330816 ,-0.0543735 ,-0.669907 ,-0.0996615 ,-0.144347 ,0.522696 ,0.14182 ,0.00619411 ,-0.00320246 ,0.639592 ,-0.0797211 ,0.220852 ,0.372508 ,-0.0067241 ,-0.12009 ,-0.783866 ,0.112612 ,-0.675719 ,0.316255 ,0.715364 ,-0.819605 ,-0.142628 ,-0.110473 ,0.57251 ,0.0761198 ,-0.0551736 ,0.704779 ,-0.0989567 ,0.308486 ,0.755084 ,-0.0262197 ,0.104514 ,0.147416 ,-0.571778 ,0.499916 ,0.525795 ,-0.0173651 ,0.959435 ,0.0414007 ,-0.760641 ,0.472872 ,0.0319204 ,-0.868682 ,-0.268848 ,0.958677 ,-0.412161 ,-0.273842 ,0.480611 ,-0.84067 ,-0.305705 ,0.352515 ,-0.274346 ,0.103686 ,0.222971 ,-0.302303 ,-0.592837 ,-0.303721 ,-0.42062 ,-0.690244 ,-1.1615 ,-0.290018 ,0.10739 ,0.814468 ,-0.444732 ,-0.691712 ,-1.28254 ,0.618517 ,-0.091434 ,-0.0265124 ,0.197633 ,-0.919034 ,-0.341565 ,0.354372 ,0.362827 ,-0.197152 ,0.109436 ,-0.348581 ,0.131639 ,-0.219902 ,0.1721 ,0.0677459 ,-0.709185 ,0.384084 ,-0.206954 ,-0.0840468 ,-0.373388 ,0.00153255 ,-0.259167 ,0.119821 ,0.579067 ,0.0834389 ,0.232353 ,0.805297 ,0.557148 ,0.102547 ,-0.169378 ,-0.108223 ,-1.27419 ,-0.366688 ,-0.418578 
    // };

    // float distance = this->getdistance(output_float,bb);
    // std::cout<<"distance  "<<distance<<std::endl;

    return true;
}
