#include "VideoReceiver.h"
#include <ostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>

void TestCameraReadVidioReceiver(std::string port) {

    int width = 1280, height = 720;
    std::pair<int, int> frame_rate{30, 1};

    VideoReceiver receiver;
    receiver.SetSize(width, height);
    receiver.SetFramerate(frame_rate);
    auto ret = receiver.Open(port);
    if (ret < 0) return;
    std::cout << "receiver open finish " << std::endl;

    while (true) {
        cv::Mat frame;
        frame.create(cv::Size(width, height), CV_8UC3);
        receiver.Read(frame);
        if (frame.empty() == true) {
            continue;
        }
        cv::imshow("frame", frame);
        cv::waitKey(1);
    }
}

int main(int argc, char* argv[]) {
    gst_init(&argc, &argv);

    std::string port(argv[1]);

    TestCameraReadVidioReceiver(port);

    return 0;
}