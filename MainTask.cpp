#include "./MainTask.hpp"

CameraTask::CameraTask(QObject *parent) : QObject(parent)
{
    camera = std::make_shared<CameraCV>();
    setCamera();
}
void CameraTask::working()
{
    if (camera->isOpened())
    {

        if (camera->process() == false)
        {
            std::string error_msg;
            camera->getErrorMessage(error_msg);
            emit videoLost(error_msg);
        }
        else
        {
            camera->getCvFrame(this->frame);
            emit getFrame(this->frame);
        }
    }
    else
    {
        std::string error_msg = "video error";
        emit videoLost(error_msg);
    }
}

void CameraTask::setCamera()
{
    CameraParam camera_param;
    camera_param.width = CAMERA_WIDTH;
    camera_param.height = CAMERA_HEIGHT;
    camera_param.exporsure = CAMERA_EXPORSURE;
    camera_param.fps = CAMERA_FPS * 2;
    camera->setCamera(camera_param);
    std::string path = camera_path;
    if (!camera->openCamera(path))
    {
        std::string error_msg;
        camera->getErrorMessage(error_msg);
        emit videoLost(error_msg);
    }
}

void CameraTask::reboot()
{
    // this->camera->closeCamera();
    if (!camera->isOpened())
        setCamera();
}

TransVideoTask::TransVideoTask(QObject *parent) : QObject(parent)
{
    //transporter =  new VideoTransporter;
    //std::make_shared<VideoTransporter>();
    setTransport();
}

void TransVideoTask::working(cv::Mat &frame)
{
    static double timestamp = 0.002;
    if (if_open)
    {
        // qDebug()<<"open";
        cv::Mat img = frame;
        timestamp += 0.0002;
        transporter->Write(frame, timestamp);
    }
    else
    {
        setTransport();
    }
}

void TransVideoTask::setTransport()
{
    transporter =  new VideoTransporter();
    transporter->SetSize(CAMERA_WIDTH, CAMERA_HEIGHT);
    std::pair<int, int> frame_rate(CAMERA_FPS, 1);
    transporter->SetFramerate(frame_rate);
    auto ret = transporter->Open(OUTURL, OUTPORT);
    if (ret < 0)
    {
        if_open = false;
        std::string error_msg = "set failed";
        delete transporter;
        emit setFailed(error_msg);
    }
    else
    {
        if_open = true;
    }
    // qDebug()<<"set ";
}

DetectTask::DetectTask(QObject *parent) : QObject(parent)
{
    detector = std::make_shared<YoloWorker>("models/person-v5lite.tflite");
    // setDetector();
}

void DetectTask::working(cv::Mat &frame)
{
    float *input_tensor; // tensor (1, 320, 320, 3)
    bool prep = detector->preProcess(frame, input_tensor);
    if (prep == false) 
    {
        std::string error_msg = "prep failed";
        emit setFailed(error_msg);
    }
    float *output_tensor;
    bool proc = detector->tflite_worker->inference(input_tensor, output_tensor);
    if (proc == false) 
    {
        std::string error_msg = "proc failed";
        emit setFailed(error_msg);
    }
    DetectbBoxList detect_list;
    bool fproc = detector->postProcess(output_tensor, detect_list);
    if (fproc == false)
    {
        std::string error_msg = "fproc failed";
        emit setFailed(error_msg);
    }

    // qDebug() << "detect_list " << detect_list;
}



