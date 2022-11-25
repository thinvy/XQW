#include "../include/TfliteWorker.hpp"

TfliteWorker::TfliteWorker(const std::string &modle_path, Delegate delegate_type, const int defaultThreads)
{

    //load model from file
    // std::cout << "1" << std::endl;
    output_float = new float[ANCHOR_SIZE * OUTPUT_SIZE];
    this->tflite_model = tflite::FlatBufferModel::BuildFromFile(modle_path.c_str());
    // set tflite resolver to build interpreter
    tflite::ops::builtin::BuiltinOpResolver tflite_resolver;
    tflite::InterpreterBuilder(*this->tflite_model, tflite_resolver)(&this->tflite_interpreter);

    // std::cout << "2" << std::endl;

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
    TfLiteTensor *requried_d;
    requried_d=this->tflite_interpreter->tensor(this->tflite_interpreter->inputs()[0]);
    requried_height = requried_dimensions->data[1];
    requried_width = requried_dimensions->data[2];
    requried_channels = requried_dimensions->data[3];

    std::cout << "requried_height" << requried_height << std::endl;
    std::cout << "requried_width" << requried_width << std::endl;
    std::cout << "requried_channels" << requried_channels << std::endl;
    std::cout <<" requried  zero point"<<requried_d->params.zero_point<<std::endl;
    std::cout <<" requried  scale" <<requried_d->params.scale<<std::endl;
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
    }

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

TfliteWorker::~TfliteWorker()
{
    this->tflite_interpreter.reset();
}

bool TfliteWorker::inference(uchar *input_tensort, uchar *output_tensort)
{
    if (input_tensort == nullptr)
    {
        this->error_message_ = WARNING_IMAGE_RETREIVAL;
        this->errorCallback();
    }

    // process frame
    std::chrono::high_resolution_clock::time_point prcoss_start_time = std::chrono::high_resolution_clock::now();
    // set input data
    if (this->requried_size_t == sizeof(float))
    {
        // std::cout << "0" << std::endl;
        memcpy(tflite_interpreter->typed_tensor<float>(tflite_interpreter->inputs()[0]), input_tensort, requried_height * requried_width * requried_channels);
    }
    else if (this->requried_size_t == sizeof(uint8_t))
    {
        uchar *input = tflite_interpreter->typed_input_tensor<uint8_t>(0);
        memcpy(input, input_tensort, requried_height * requried_width * requried_channels);
    }

    std::chrono::high_resolution_clock::time_point prcoss_stop_time = std::chrono::high_resolution_clock::now();

    //tflite_interpreter->SetAllowFp16PrecisionForFp32(true);
    tflite_interpreter->SetNumThreads(2); //quad core

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
    int time_cost = int(std::chrono::duration_cast<std::chrono::milliseconds>(inference_stop_time - inference_start_time).count());

    TfLiteTensor *pOutputTensor = tflite_interpreter->tensor(tflite_interpreter->outputs()[0]);
    zero_point = pOutputTensor->params.zero_point;
    scale = pOutputTensor->params.scale;
    // std::cout << "zero_point  " << zero_point << std::endl;
    // std::cout << "scale       " << scale << std::endl;
    box_list.clear();
    for (size_t i = 0; i < OUTPUT_SIZE * ANCHOR_SIZE; i+=1)
    {
        // std::cout << (int)pOutputTensor->data.uint8[i] << " ";
        output_tensort[i] = pOutputTensor->data.uint8[i];
        output_float[i] = ((int)(pOutputTensor->data.uint8[i]));
        if((int)(pOutputTensor->data.uint8[i])>255||((int)(pOutputTensor->data.uint8[i])<0)){
            std::cout<<"error"<<std::endl;
            sleep(1);
        }
        // std::cout<<std::setprecision(2) << 100*output_float[i]/ 255.0 << " ";
        if (i % 6 == 0){
            // std::cout << std::setprecision(2) << 100*output_float[i]/ 255.0 <<std::endl;
            if(100*output_float[i+4]/ 255.0 >56){

                DetectBox temp;
                temp.bbox=cv::Rect2d(DISPLAY_WIGTH*1.0*(output_float[i]/ 255.0-output_float[i+2]/ 255.0/2.0),
                            DISPLAY_WIGTH*1.0*(output_float[i+1]/ 255.0-output_float[i+3]/ 255.0/2.0),
                            DISPLAY_WIGTH*1.0*output_float[i+2]/ 255.0,
                            DISPLAY_WIGTH*1.0*output_float[i+3]/ 255.0);
                temp.class_id=0;
                temp.conf=output_float[i+4]/ 255.0*output_float[i+5]/ 255.0;
                box_list.push_back(temp);
            }
        }
    }

    return true;
}
