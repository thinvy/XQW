#ifndef TRACKING_HPP_
#define TRACKING_HPP_

#include <opencv4/opencv2/tracking.hpp>
#include <opencv4/opencv2/opencv.hpp>

struct TrackPerson{
    cv::Point2d mat_point;
    double timestamp;
    int id;
};

using TrackList=std::vector<TrackPerson>;


class Tracking
{

    cv::Rect2d tracking_area;
    cv::Mat tracking_mat;
    // pt for tracker
    cv::Ptr<cv::Tracker> tracker;
    // 记录上次的tracking_box
    cv::Rect2d last_tracking_box;
    cv::Size trakcing_size;

public:
    bool track(cv::Mat &frame, cv::Rect2d &tracking_box);

    bool reInitTracker(cv::Rect2d &detect_box, cv::Mat &frame);

    Tracking();
};


class SortTracker{

};

#endif