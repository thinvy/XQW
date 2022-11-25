#include "./MainTask.hpp"

CameraTask::CameraTask(QObject *parent) : QObject(parent)
{
    camera = std::make_shared<CameraCV>();
    setCamera();
}

void CameraTask::directDislay()
{
    // if (if_direct_show == false)
    // {
    //     if_direct_show = true;
    // }
    // else
    // {
    //     if_direct_show = false;
    // }
}
void CameraTask::working()
{
    static int idex = 0;
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
            //std::cout<<"show? "<<if_direct_show<<std::endl;
            camera->getCvFrame(this->frame);
            if (this->frame.empty())
            {
                std::string error_msg;
                error_msg="1";
                emit videoLost(error_msg);
                return;
            }
            if (if_direct_show == 0)
            {
                cv::Mat m_frame;
                cv::resize(frame, m_frame, cv::Size(DISPLAY_WIGTH, DISPLAY_HEIGHT));
                std::vector<TrackingBox> temp_vector;
                emit toDisplay(m_frame, temp_vector);
            }
            idex++;
            if (idex == 8)
            {
                cv::Mat m_frame;
                cv::resize(frame, m_frame, cv::Size(DISPLAY_WIGTH, DISPLAY_WIGTH));

                emit toDetect(m_frame, this->if_direct_show);
                idex = 0;
            }
            emit toTransport(frame);
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
        // qDebug() << "open";

        // cv::resize(frame, frame, cv::Size(CAMERA_WIDTH, CAMERA_HEIGHT));
        // std::cout << "frame size " << frame.cols << "  " << frame.rows << std::endl;
        cv::Mat img = frame;
        timestamp += 0.0002;
        transporter->Write(img, timestamp);
    }
    else
    {
        setTransport();
    }
}

void TransVideoTask::setTransport()
{
    transporter = new VideoTransporter();
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
    detector = std::make_shared<YoloWorker>("/opt/gx-edge-ai-demo/models/person224-v5n-int8.tflite");
    redetect = std::make_shared<ReDetect>("/opt/gx-edge-ai-demo/models/reid16.tflite");

    tracking = std::make_shared<Tracking>();
    // setDetector();
}

void DetectTask::working(cv::Mat &frame, int if_direct_show)
{

    // if(frame.empty()){
    //     return;
    // }
    std::chrono::high_resolution_clock::time_point prcoss_start_time = std::chrono::system_clock::now();

    uchar input_tensor[INPUT_TESONR_SIZE];
    bool prep = detector->preProcess(frame, input_tensor);
    if (prep == false)
    {
        std::string error_msg = "prep failed";
        emit setFailed(error_msg);
        return;
    }
    uchar output_tensor[OUTPUT_TESONR_SIZE];
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
    if (detect_list.size() > 6)
    {
        return;
    }
    if (if_direct_show)
    {
        std::vector<cv::Rect2d> box_lists;
        for (auto a : detect_list)
        {
            a.bbox &= cv::Rect2d(0, 0, DISPLAY_WIGTH, DISPLAY_WIGTH);
            box_lists.push_back(a.bbox);
        }
        std::vector<TrackingBox> box;
        for (auto a : box_lists)
        {
            TrackingBox x;
            x.id = -1;
            x.box = a;
            box.push_back(x);
        }
        if (if_direct_show == 1)
        {
            emit toDisplay(frame, box);
        }
        else
        {

            // std::chrono::high_resolution_clock::time_point s1 = std::chrono::system_clock::now();
            this->tracking->track(frame, box_lists);

            // std::vector<cv::Rect2d> show_box;
            // for(auto a:this->tracking->frameTrackingResult){
            //     show_box.push_back(a.box);
            //     std::cout<<"i found the id is"<<a.id<<std::endl;
            // }
            // std::chrono::high_resolution_clock::time_point e1 = std::chrono::system_clock::now();
            // std::cout << "   here is tracking" << std::chrono::duration_cast<std::chrono::milliseconds>(e1 - s1).count() << std::endl;
            emit toDisplay(frame, this->tracking->frameTrackingResult);
        }
    }

    if (!detect_list.empty())
    {
        for (auto a : detect_list)
        {
            auto box = a.bbox;
            box &= cv::Rect2d(0, 0, DISPLAY_WIGTH, DISPLAY_WIGTH);
            cv::Mat tracking_frame = frame(box).clone();
            float vid[256] = {0};
            // this->redetect->inference(tracking_frame);
            emit toSent(vid, box, 0, 0);
        }
    }

    // std::chrono::high_resolution_clock::time_point prcoss_end_time = std::chrono::system_clock::now();

    // std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(prcoss_end_time - prcoss_start_time).count() << std::endl;

    // std::cout << "====================================================" << std::endl;
}

TransDataTask::TransDataTask(int port, QObject *parent) : QObject(parent)
{
    transporter = std::make_shared<ResultTransporter>(port);
    if_open = transporter->init();
    if (if_open == false) {
        // std::cout << transporter;
    }
}

void TransDataTask::transmit(float *id_vector, cv::Rect2d &rect, uint8_t camera_id, uint8_t person_id)
{
    if (if_open)
    {
        int box_int[4] = {rect.x, rect.y, rect.width, rect.height};
        int tx = transporter->Transmit(id_vector, box_int, camera_id, person_id);
        std::cout << "send" << std::endl;
        if (tx <= 0)
        {
            std::string error_msg = "trans faied";
            // std::cout << error_msg << std::endl;
            emit sentFailed(error_msg);
        }
        else
        {
            std::cout << "send : " << tx << std::endl;
        }
        receive();
    }
    else
    {
    //     std::cout << "no init " << std::endl;
    }
}

void TransDataTask::receive()
{
    if (if_open)
    {
        // cv::Mat frame_rx;
        float vector[256];
        int box_rx[4];
        uint8_t cam_id;
        uint8_t person_id;
        int rx = transporter->Receive(vector, box_rx, cam_id, person_id);

        if (rx > 0)
        {
            std::cout << "rerceive =>> box : " << box_rx[0] << " " << box_rx[1] << " " << box_rx[2] << " " << box_rx[3] << " "
                      << " cam_id : " << (int)cam_id << " person_id : " << (int)person_id << std::endl;
            cv::Rect2d box = cv::Rect2d(box_rx[0], box_rx[1], box_rx[2], box_rx[3]);
            emit toReDetect(vector, box, cam_id, person_id);
        }
    }
}
