#include "../include/VideoReader.hpp"
#include "../include/VideoWriter.hpp"
#include <ostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>

void TestCameraReadVidioWrite(std::string url, std::string outUrl, int count) {
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

    VideoWriter writer;
    writer.SetSize(width, height);
    writer.SetFramerate(frame_rate);
    auto ret = writer.Open(outUrl);
    if (ret < 0) return;
    std::cout << "writer open finish " << std::endl;

    
    int seq = 0;
    double timestamp = 0.08;
    while (seq++ < count) {
        std::cout << seq << std::endl;

        cv::Mat frame;
        camera.read(frame);
        if (frame.empty() == true) {
            break;
        }
        std::cout << "width : " << frame.cols << "  heigth : " << frame.rows << std::endl;
        // std::string filename = "./bin/"  + std::to_string(seq) + ".jpg";
        // cv::imwrite(filename, frame);
        timestamp += 0.04;
        writer.Write(frame, timestamp);
        cv::imshow("frame", frame);
        cv::waitKey(1);
    }
    camera.release();
    std::cout << "video read write test exit" << std::endl;
}

int main(int argc, char* argv[]) {
    gst_init(&argc, &argv);

    std::string inputUrl(argv[1]);
    std::string outputUrl(argv[2]);

    TestCameraReadVidioWrite(inputUrl, outputUrl, 100);

    return 0;
}