#include "../include/Tracking.hpp"
#include "../include/Common.hpp"
#include <opencv4/opencv2/opencv.hpp>
#include <chrono>

int main(int argc, char *argv[])
{

    if (argc != 2)
    {
        std::cout << "[ERROT], input argv num error" << std::endl;
        exit(1);
    }
    cv::VideoCapture cap(argv[1]);
    if (!cap.isOpened())
    {
        std::cout << "[ERROT], VIDEO STREAM IS EMPTY " << std::endl;
        exit(1);
    }
    cv::Mat frame;
    for (int i = 0; i < 60; i++)
        cap >> frame;
    // cv::Rect2d traking_rect = cv::Rect2d(550, 20, 50, 150);
    // cv::Rect2d traking_rect=cv::Rect2d(502,15,90,300); //for B
    cv::Rect2d traking_rect = cv::Rect2d(180, 5, 40, 90);
    Tracking trakcing; 
    trakcing.reInitTracker(traking_rect, frame);
    // draw to ensure the first tracking rect is right
    cv::rectangle(frame, traking_rect, cv::Scalar(0, 0, 255), 2);
    cv::imshow("1", frame);
    cv::waitKey(0);
    trakcing.track(frame, traking_rect);

    KalmanTracker tracker = KalmanTracker(cv::Rect2f(traking_rect));
    int i = 0;
    while (1)
    {
        cap >> frame;
        cv::Rect2f predict_box = tracker.predict();
        cv::rectangle(frame, predict_box, cv::Scalar(0, 255, 0), 2);
        if((i++)<=10||i%3==0)
        {

            // get cost time
            auto start = std::chrono::system_clock::now();
            std::cout << "if trakcing right " << bool(trakcing.track(frame, traking_rect)) << std::endl;
            auto end = std::chrono::system_clock::now();
            double duration = std::chrono::duration<double, std::milli>(end - start).count();

            // std::cout<<"cost time "<<duration<<" ms"<<std::endl;
            // show
            tracker.update(cv::Rect2f(traking_rect.x, traking_rect.y, traking_rect.width, traking_rect.height));
            auto temp = tracker.get_state();
            // traking_rect=cv::Rect2d(temp.x,temp.y,temp.width,temp.height);
            // cv::rectangle(frame,traking_rect,cv::Scalar(0,0,255),2);
            cv::rectangle(frame,temp,cv::Scalar(255,0,0),2);
            std::cout << "traking area " << traking_rect << std::endl
                      << std::endl;
        }
        cv::imshow("1", frame);
        // if(i==352){
        //     traking_rect=cv::Rect2d(230,10,50,120);
        //     trakcing.reInitTracker(traking_rect, frame);
        // }
        std::cout<<"i= "<<i<<std::endl;
        if (cv::waitKey(50) == 27)
        {
            cap.release();
            exit(0);
        }
        /* code */
    }
    return 0;
}