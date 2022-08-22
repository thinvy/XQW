#include "VideoTransporter.h"
#include <ostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>

void TestCameraReadVidioTransporter(std::string url, std::string outUrl, std::string outPort, int count) {
    std::cout << "video:" << url << std::endl;

    int width = 1280, height = 720;
    std::pair<int, int> frame_rate{30, 1};

    cv::VideoCapture camera;
    camera.open(url);
    if (!camera.isOpened()) {
		std::cout << "camera open failed " << std::endl;
		return;
    }
    camera.set(cv::CAP_PROP_FOURCC, cv::VideoWriter::fourcc('M', 'J', 'P', 'G'));
    camera.set(cv::CAP_PROP_FRAME_WIDTH, width);
    camera.set(cv::CAP_PROP_FRAME_HEIGHT, height);
    camera.set(cv::CAP_PROP_FPS, frame_rate.first);

    std::cout << "width : " << width << "  heigth : " << height << std::endl;

    
    std::cout << "camera open finish " << std::endl;

    VideoTransporter transporter;
    transporter.SetSize(width, height);
    transporter.SetFramerate(frame_rate);
    auto ret = transporter.Open(outUrl, outPort);
    if (ret < 0) return;
    std::cout << "transporter open finish " << std::endl;

    
    while (true) {
        cv::Mat frame;
        camera.read(frame);
        if (frame.empty() == true) {
            break;
        }
        transporter.Write(frame);
        cv::imshow("frame", frame);
        cv::waitKey(1);
    }
    camera.release();
    std::cout << "video read write test exit" << std::endl;
}

int main(int argc, char* argv[]) {
    gst_init(&argc, &argv);

    std::string cameraURL(argv[1]);
    std::string outputUrl(argv[2]);
    std::string outputPort(argv[3]);

    TestCameraReadVidioTransporter(cameraURL, outputUrl, outputPort, 10000);

    return 0;
}