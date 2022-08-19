#include "../include/Tracking.hpp"

bool Tracking::track(cv::Mat &frame, cv::Rect2d &tracking_box)
{
    if (frame.empty() || last_tracking_box.empty())
    {
        return false;
    }
    cv::Rect2d max_size = cv::Rect2d(0, 0, frame.size().width, frame.size().height);
    int tracking_height = tracking_area.height;
    int tracking_width = tracking_area.width;
    int temp_x, temp_y;
    if (last_tracking_box.x - 0.5 * tracking_width <= 0)
    {
        temp_x = 0;
    }
    else
    {
        temp_x = last_tracking_box.x - 0.5 * tracking_width;
    }
    if (last_tracking_box.y - 0.5 * tracking_height <= 0)
    {
        temp_y = 0;
    }
    else
    {
        temp_y = last_tracking_box.y - 0.5 * tracking_height;
    }

    this->tracking_area = cv::Rect2d(temp_x, temp_y, tracking_width, tracking_height);
    this->tracking_mat = frame;

    bool if_tacking = tracker->update(tracking_mat, tracking_box);
    last_tracking_box = tracking_box;
    return if_tacking;
}

bool Tracking::reInitTracker(cv::Rect2d &detect_box, cv::Mat &frame)
{
    if (detect_box.empty() || frame.empty())
    {
        return false;
    }
    cv::Rect2d max_size = cv::Rect2d(0, 0, frame.size().width, frame.size().height);
    this->tracking_area = cv::Rect2d(detect_box.x - 0.5 * detect_box.width, detect_box.y - 0.5 * detect_box.height, 2 * detect_box.width, 2 * detect_box.height);

    this->tracking_area &= max_size;
    this->tracking_mat = frame;
    tracker->init(tracking_mat, detect_box);
    last_tracking_box = detect_box;
    bool if_tacking = tracker->update(tracking_mat, last_tracking_box);
}

Tracking::Tracking() : tracking_area(cv::Rect2d()), tracking_mat(cv::Mat()), last_tracking_box(cv::Rect2d())
{
    tracker = cv::TrackerKCF::create();
}
