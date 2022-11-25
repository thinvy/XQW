#ifndef TRACKING_HPP_
#define TRACKING_HPP_

#include <opencv4/opencv2/tracking.hpp>
#include <opencv4/opencv2/opencv.hpp>
#include "./Common.hpp"
// #define DBL_EPSILON 0.5
#define IOU_THRESHOLD 0.3
#define MAX_AGE 1
#define MIN_HITS 3

struct TrackingBox
{
    cv::Rect2d box;
    int id;
};

class BatchTracker
{
public:
    BatchTracker(cv::Mat &frame, cv::Rect2d &rect);

    BatchTracker();

    void kfInit(cv::Rect2d &rect);

    cv::Rect2d predict(cv::Mat &frame);

    cv::Rect2d getRect(float cx, float cy, float s, float r);

    cv::Rect2d update(cv::Mat &frame, cv::Rect2d &rect);

    cv::KalmanFilter kf;
    cv::Rect2d last_rect;
    cv::Ptr<cv::Tracker> kcf;
    int since_update_age = 0;
    static int tracker_count;
    int id;
    int m_hits;
    int m_hit_streak;
    int m_age;
};

class Tracking
{

    double GetIOU(cv::Rect2d &bb_test, cv::Rect2d &bb_gt);

    std::vector<BatchTracker> trackers;

    std::vector<cv::Rect2d> predict_boxs;

public:
    std::vector<TrackingBox> frameTrackingResult;

    Tracking();

    bool track(cv::Mat &frame, std::vector<cv::Rect2d> &detect_boxs);
};

#endif