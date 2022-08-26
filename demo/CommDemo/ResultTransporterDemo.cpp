#include "ResultTransporter.hpp"
#include <iostream>
#include <opencv4/opencv2/opencv.hpp>

int main()
{
    ResultTransporter tp(5004);
    if (tp.init() != true) {
        std::cout << "init error : " << tp.error_message() << std::endl;
    }
    
    cv::VideoCapture cap;
    cap.open(0);

    while(true) {
        cv::Mat frame;
        cap.read(frame);
        int box[4] = {0, 1, 2, 3};
        int tx = tp.Transmit(frame, box, 0, 0);

        cv::Mat frame_rx;
        int box_rx[4];
        uint8_t cam_id;
        uint8_t person_id;
        int rx = tp.Receive(frame_rx, box, cam_id, person_id);

        if (rx > 0) {
            cv::imshow("frame", frame_rx);
            std::cout << "box : " << box[0] << " " << box[1] << " " << box[2] << " " << box[3] << " " 
                    << " cam_id : " << (int)cam_id << " person_id : " << (int)person_id << std::endl;
        }
        cv::waitKey(30);
    }

    return 0;
}