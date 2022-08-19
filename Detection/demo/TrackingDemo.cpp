#include "../../include/Tracking.hpp"
#include <opencv4/opencv2/opencv.hpp>
#include <chrono>  

int main(int argc, char* argv[]){

    if(argc!=2){
        std::cout<<"[ERROT], input argv num error"<<std::endl;
        exit(1);
    }
    cv::VideoCapture cap(argv[1]);
    if(!cap.isOpened()){
        std::cout<<"[ERROT], VIDEO STREAM IS EMPTY "<<std::endl;
        exit(1);
    }
    cv::Mat frame;
    // for(int i=0;i<250;i++)
    cap>>frame;
    cv::Rect2d traking_rect=cv::Rect2d(100,290,140,70);
    // cv::Rect2d traking_rect=cv::Rect2d(242,72,120,330);
    Tracking  trakcing;
    trakcing.reInitTracker(traking_rect,frame);
    // draw to ensure the first tracking rect is right 
    cv::rectangle(frame,traking_rect,cv::Scalar(0,0,255),2);
    cv::imshow("1",frame);
    cv::waitKey(1000);

    while (1)
    {
        cap>>frame;
        // get cost time
        auto start=std::chrono::system_clock::now();
        std::cout<<"if trakcing right " << bool(trakcing.track(frame,traking_rect)) <<std::endl;
        auto end=std::chrono::system_clock::now();
        double duration = std::chrono::duration<double,std::milli>(end - start).count();
        std::cout<<"cost time "<<duration<<" ms"<<std::endl;
        // show
        cv::rectangle(frame,traking_rect,cv::Scalar(0,0,255),2);
        std::cout<<"traking area "<<traking_rect<<std::endl<<std::endl;
        cv::imshow("1",frame);
        if(cv::waitKey(30)==27){
            cap.release();
            exit(0);
        }
        /* code */
    }
    return 0;

}