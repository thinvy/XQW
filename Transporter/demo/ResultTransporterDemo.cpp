#pragma once

#include "udpbd_transporter.hpp"
#include <opencv4/opencv2/opencv.hpp>

#define TRANSMIT_MAT_WIDTH 60
#define TRANSMIT_MAT_HEIGTH 80

#pragma pack(1) 
typedef struct ResultFrameBD
{
    uint8_t _SOF_;
    struct Data
    {
        uint8_t mat_data[TRANSMIT_MAT_WIDTH*TRANSMIT_MAT_HEIGTH*3];
        int box[4];
        uint8_t camera_id;
        bool enable_reid;
        uint8_t person_id;
    } data;
    uint8_t _EOF_;
} ResultFrameBD;
#pragma pack() 


class ResultTransporter
{
public:
    ResultTransporter(int port) {
        port_ = port;
    }
    ~ResultTransporter() {
        transmiter_->close();
        receiver_->close();
    }
    bool init() {
        transmiter_ = std::make_shared<transporter::UdpBroadcaster>("Transmit", port_);
        receiver_ = std::make_shared<transporter::UdpBroadcaster>("Receive", port_);
        if (transmiter_->open() != true) {
            error_message_ = "open transmiter error : " + transmiter_->error_message();
            return false;
        }
        if (receiver_->open() != true) {
            error_message_ = "open receiver error : " + receiver_->error_message();
            return false;
        }
        return true;
    }
    int Transmit(cv::Mat &frame, int box[4], uint8_t camera_id, uint8_t person_id) {
        if(frame.empty()){
            return -1;
        }
        cv::Mat frame_resized;
        cv::resize(frame, frame_resized, cv::Size(TRANSMIT_MAT_WIDTH, TRANSMIT_MAT_HEIGTH));
        
        ResultFrameBD result_frame;
        result_frame._SOF_ = 0x66;
        result_frame._EOF_ = 0x88;
        memcpy(result_frame.data.mat_data, frame_resized.data, sizeof(result_frame.data.mat_data));
        // memcpy(result_frame.data.box, box, sizeof(box));
        result_frame.data.box[0] = box[0];
        result_frame.data.box[1] = box[1];
        result_frame.data.box[2] = box[2];
        result_frame.data.box[3] = box[3];
        result_frame.data.camera_id = camera_id;
        result_frame.data.enable_reid = true;
        result_frame.data.person_id = person_id;
        
        int tx_result = transmiter_->write(&result_frame, sizeof(result_frame));
        return tx_result;
    }
    
    int Receive(cv::Mat &frame, int box[4], uint8_t & camera_id, uint8_t & person_id) {

        ResultFrameBD result_frame;
        int rx_result = receiver_->read(&result_frame, sizeof(result_frame));

        if ((result_frame._SOF_ != 0x66) || (result_frame._EOF_ != 0x88)) {
            return -1;
        }

        frame = cv::Mat(cv::Size(TRANSMIT_MAT_WIDTH, TRANSMIT_MAT_HEIGTH), CV_8UC3);
        memcpy(frame.data, result_frame.data.mat_data, sizeof(result_frame.data.mat_data));
        // memcpy(box, result_frame.data.box, sizeof(box));
        box[0] = result_frame.data.box[0];
        box[1] = result_frame.data.box[1];
        box[2] = result_frame.data.box[2];
        box[3] = result_frame.data.box[3];
        camera_id = result_frame.data.camera_id;
        person_id = result_frame.data.person_id;

        return rx_result;
    }

    std::string error_message() {
        return error_message_;
    }

    
private:
    int port_;
    std::string error_message_;
    std::shared_ptr<transporter::Base> transmiter_;
    std::shared_ptr<transporter::Base> receiver_;
};

