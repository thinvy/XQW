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

    
    std::string camera_path("/dev/video2");
    if (camera->openCamera(camera_path) == false) {
        std::string error_msg;
        camera->getErrorMessage(error_msg);
        std::cout << error_msg << std::endl;
        return 1;
    }


    while (true) {



        if (camera->process() == false) {
            std::string error_msg;
            camera->getErrorMessage(error_msg);
            std::cout << error_msg << std::endl;
            // return 1;
            continue;
        }
        

        cv::Mat frame;

        camera->getCvFrame(frame);

        // std::cout << "rows: " << frame.rows << " cols: " << frame.cols <<std::endl;

        cv::imshow("camera test", frame);

        if (cv::waitKey(1) == 27) {
            break;
        }
    }

    return 0;
}