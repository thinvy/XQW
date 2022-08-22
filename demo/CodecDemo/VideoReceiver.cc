#include "VideoReceiver.h"
#include <ostream>

void pad_added_handler(GstElement *src, GstPad *pad, GstElement *queue){
    gst_element_link_pads(src, GST_PAD_NAME(pad), queue, nullptr);
}


VideoReceiver::~VideoReceiver() {
    if (pipeline_) {
        gst_element_set_state(pipeline_, GST_STATE_NULL);
        gst_object_unref(pipeline_);
        pipeline_ = nullptr;
    }
}

int VideoReceiver::Open(const std::string port) {
    src_            = gst_element_factory_make("udpsrc", "src");
    // buffer_         = gst_element_factory_make("rtpjitterbuffer", "jitterbuffer");
    queue0_         = gst_element_factory_make("queue", "QueueFlow");
    dpay_           = gst_element_factory_make("rtph264depay", "rtpdepay");
    parse_          = gst_element_factory_make("h264parse", "H264Parse");
    queue1_         = gst_element_factory_make("queue", "QueueFrame");
    decoder_        = gst_element_factory_make("avdec_h264", "decoder");
    sink_           = gst_element_factory_make("appsink", "CustomSink");


    pipeline_ = gst_pipeline_new("decode-pipeline");
    if (!pipeline_ || !src_ || !queue0_ || !dpay_ || !parse_ || !queue1_ || !decoder_ || !sink_) {
        std::cerr<< "Not all elements could be created" << std::endl;
        std::cout << "   pipline : " << pipeline_;
        std::cout << "   source : " << src_;
        std::cout << "   queue : " << queue0_;
        std::cout << "   dpay : " << dpay_;
        std::cout << "   parse : " << parse_;
        std::cout << "   queue1 : " << queue1_;
        std::cout << "   decoder : " << decoder_;
        std::cout << "   sink : " << sink_;
        std::cout << std::endl;
        return -1;
    }



    GstCaps *video_caps;
    gchar *video_caps_text;
    video_caps_text = g_strdup_printf("application/x-rtp, media=video, clock-rate=90000, encoding-name=H264, payload=96");
    video_caps = gst_caps_from_string(video_caps_text);
    if(!video_caps) {
        std::cerr << "gst_caps_from_string fail" << std::endl;
        return -1;
    }
	g_object_set(G_OBJECT(src_), "port", std::stoi(port), NULL);
    g_object_set(G_OBJECT(src_), "caps", video_caps, NULL);
    
	// g_object_set(G_OBJECT(src_), "sync", false, NULL);
	// g_object_set(G_OBJECT(src_), "async", false, NULL);

    g_object_set(G_OBJECT(sink_), "emit-signals", TRUE, "max-buffers", 1, nullptr);

    // 设置视频码率
    // g_object_set(G_OBJECT(decoder_), "bitrate", 1000 + bitrate_ / 1000, nullptr);

    gst_bin_add_many(GST_BIN(pipeline_), src_, queue0_, dpay_, parse_, queue1_, decoder_, sink_, nullptr);    

    if (gst_element_link_many(src_, queue0_, dpay_, parse_, queue1_, decoder_, sink_, nullptr) != TRUE ) {
        std::cerr << "Could not be linked 0" << std::endl;
        return -1;
    }

    // g_signal_connect(src_, "pad-added", (GCallback)pad_added_handler, queue0_);

    // Start playing
    auto ret = gst_element_set_state (pipeline_, GST_STATE_PLAYING);
    if (ret == GST_STATE_CHANGE_FAILURE) {
        std::cerr << "Unable to set the pipeline to the playing state" << std::endl;
        return -1;
    }
    std::cout << "wait for stream ..." << std::endl;
    GstSample *sample;
    // g_signal_emit_by_name(sink_, "pull-preroll", &sample);
    g_signal_emit_by_name(sink_, "pull-sample", &sample);
    std::cout << "receive frame success" << std::endl;
    if (sample) {
        std::cout << "recv frame" << std::endl;
        auto buffer = gst_sample_get_buffer(sample);
        // fetch video infomation
        if (paddedHeight_ == 0 && paddedWidth_ == 0) {
            GstCaps *caps = gst_sample_get_caps(sample);
            GstStructure* info = gst_caps_get_structure(caps, 0);
            gst_structure_get_int(info, "width", &paddedWidth_);
            gst_structure_get_int(info, "height", &paddedHeight_);
            const char* format = gst_structure_get_string(info, "format");
            gst_structure_get_fraction(info, "framerate", &framerate_.first, &framerate_.second);
            srcFmt_ = format;

            std::cout << "padded width:" << paddedWidth_ << "padded height:" << paddedHeight_ << std::endl;
            std::cout << "format:" << srcFmt_ << std::endl;
            std::cout << "framerate num:" << framerate_.first << "framerate den:" << framerate_.second << std::endl;
        }
        // release sample reference
        gst_sample_unref(sample);
    }

    // set pipeline to playing
    ret = gst_element_set_state(pipeline_, GST_STATE_PLAYING);
    if (ret == GST_STATE_CHANGE_FAILURE) {
        std::cerr<< "Unable to set the pipeline to the playing state" << std::endl;
        return -1;
    }

    // handle error or EOS. Atention: error handle will block, so don't use it.
    // ErrHandle(pipeline_);
    return 0;

}


int VideoReceiver::Read(const cv::Mat& frame) {
    return ReceiveDataFromePipeline(frame);
}


// 主要功能：将pipeline中的数据拷贝到cv:Mat
int VideoReceiver::ReceiveDataFromePipeline(const cv::Mat& frame) {
    GstSample *sample;
    // 使用pull-sample拉取视频帧，并映射到map变量，通过map拷贝出frame数据
    g_signal_emit_by_name(sink_, "pull-sample", &sample);

    if (sample) {
        auto buffer = gst_sample_get_buffer(sample);

        // fetch timestamp
        // timestamp = static_cast<double>(GST_BUFFER_PTS(buffer)) / static_cast<double>(GST_SECOND);
        // std::cout << "timestamp:" << timestamp << std::endl;
        // std::cout << std::endl;

        // copy buffer data into cv::Mat
        GstMapInfo map;
        if (gst_buffer_map(buffer, &map, GST_MAP_READ)) {
            if (srcFmt_ != "NV12" && srcFmt_ != "I420") {
                std::cout << "unsupported src pixel format" << std::endl;
                return -1;
            }

            static cv::Mat image;//(height_*3/2, width_, CV_8UC1, cv::Scalar(0,0,255));
            if (image.empty()) {
                image.create(cv::Size(width_, height_ * 3 / 2), CV_8UC1);
            }

            // 1. copy into cv::Mat
            if (paddedWidth_ == width_) {
                memcpy(image.data, map.data, width_ * sizeof(uint8_t) * height_);
                memcpy(image.data + height_ * width_, map.data + paddedHeight_ * width_, width_ * sizeof(uint8_t) * height_ / 2);
            } 
            else {
                // copy Y-channel, jump the padding width
                for (int i = 0; i < height_; ++i) {
                    memcpy(image.data + i * width_, map.data + i * paddedWidth_, width_ * sizeof(uint8_t));
                }
                // copy UV-channel, jump the padding width
                for (int i = 0; i < height_ / 2; ++i) {
                    memcpy(image.data + (height_ + i) * width_, map.data + (paddedHeight_ + i) * paddedWidth_, width_ * sizeof(uint8_t));
                }
            }
            
            // 2. convert format
            if (srcFmt_ == "NV12") {
                cv::cvtColor(image, frame, cv::COLOR_YUV2BGR_NV12);
            } 
            else {
                cv::cvtColor(image, frame, cv::COLOR_YUV2BGR_I420);
            }

            // release buffer mapping
            gst_buffer_unmap(buffer, &map);
        }
        // release sample reference
        gst_sample_unref(sample);
        return 0;
    } 
    else {
      std::cerr << "recv null frame"  << std::endl;
      return -1;
    }
}