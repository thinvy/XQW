#include <iostream>
#include <memory>
#include "../../Camera.hpp"


int main()
{
    std::shared_ptr<Foolish::Camera> camera;
    camera = std::make_shared<Foolish::CameraV4L2>();

    Foolish::CameraParam camera_param;
    camera_param.width = 640;
    camera_param.height = 480;
    camera_param.exporsure = 100;

    camera->setCamera(camera_param);

    std::string camera_path("/dev/video0");
    if (camera->openCamera(camera_path) == false)
    {
        std::string error_msg;
        camera->getErrorMessage(error_msg);
        std::cout << error_msg << std::endl;
        return 1;
    }

    while (true)
    {

        //  start inference and get time
        std::chrono::high_resolution_clock::time_point start_time = std::chrono::high_resolution_clock::now();
        if (camera->process() == false)
        {
            std::string error_msg;
            camera->getErrorMessage(error_msg);
            std::cout << error_msg << std::endl;
            // return 1;
            continue;
        }

        cv::Mat frame;

        // get interpreter time;
        camera->getCvFrame(frame);
        std::chrono::high_resolution_clock::time_point stop_time = std::chrono::high_resolution_clock::now();

        int time_cost = int(std::chrono::duration_cast<std::chrono::milliseconds>(stop_time - start_time).count());
        std::cout<<"the time cost is : "<<time_cost<<std::endl;
        // std::cout << "rows: " << frame.rows << " cols: " << frame.cols << std::endl;

        cv::imshow("camera test", frame);

        if (cv::waitKey(1) == 27) {
            break;
        }
        std::cout << std::endl;
    }

    return 0;
}