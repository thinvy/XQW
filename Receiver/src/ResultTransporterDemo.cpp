#include "ResultTransporter.hpp"
#include <iostream>
#include <opencv4/opencv2/opencv.hpp>

int main()
{
    ResultTransporter tp(5005);
    if (tp.init() != true) {
        std::cout << "init error : " << tp.error_message() << std::endl;
    }
    
    // cv::VideoCapture cap;
    // cap.open(0);

    while(true) {
        // cv::Mat frame;
        // cap.read(frame);
        // int box[4] = {0, 1, 2, 3};
        // int tx = tp.Transmit(frame, box, 0, 0);
        // if (tx < 0) {
        //     std::cout << "send error" << std::endl;
        // }

        // cv::Mat frame_rx;
        float vid[256];
        int box_rx[4];
        uint8_t cam_id;
        uint8_t person_id;
        int rx = tp.Receive(vid, box_rx, cam_id, person_id);

        if (rx > 0) {
            // cv::imshow("frame", frame_rx);
            std::cout << "box : " << box_rx[0] << " " << box_rx[1] << " " << box_rx[2] << " " << box_rx[3] << " " 
                    << " cam_id : " << (int)cam_id << " person_id : " << (int)person_id << std::endl;
        }
        cv::waitKey(30);
    }

    return 0;
}