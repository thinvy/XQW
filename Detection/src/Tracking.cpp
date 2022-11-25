#include "../include/Tracking.hpp"

int BatchTracker::tracker_count = 0;

BatchTracker::BatchTracker(cv::Mat &frame, cv::Rect2d &rect)
{
    kcf = cv::TrackerKCF::create();
    kcf->init(frame, rect);
    kfInit(rect);
    last_rect = rect;
    id = tracker_count;
    tracker_count += 1;
}

BatchTracker::BatchTracker()
{
    kcf = cv::TrackerKCF::create();
    kf = cv::KalmanFilter();
    last_rect = cv::Rect2d();
}

void BatchTracker::kfInit(cv::Rect2d &rect)
{
    int stateNum = 7;
    int measureNum = 4;
    kf = cv::KalmanFilter(stateNum, measureNum, 0);
    cv::Mat measurement = cv::Mat::zeros(measureNum, 1, CV_32F);

    kf.transitionMatrix = (cv::Mat_<float>(stateNum, stateNum)
                               << 1,
                           0, 0, 0, 1, 0, 0,
                           0, 1, 0, 0, 0, 1, 0,
                           0, 0, 1, 0, 0, 0, 1,
                           0, 0, 0, 1, 0, 0, 0,
                           0, 0, 0, 0, 1, 0, 0,
                           0, 0, 0, 0, 0, 1, 0,
                           0, 0, 0, 0, 0, 0, 1);
    cv::setIdentity(kf.measurementMatrix);
    cv::setIdentity(kf.processNoiseCov, cv::Scalar::all(1e-2));
    cv::setIdentity(kf.measurementNoiseCov, cv::Scalar::all(1));
    cv::setIdentity(kf.errorCovPost, cv::Scalar::all(1e-2));
    // initialize state vector with bounding box in [cx,cy,s,r] style
    kf.statePost.at<float>(0, 0) = rect.x + rect.width / 2;
    kf.statePost.at<float>(1, 0) = rect.y + rect.height / 2;
    kf.statePost.at<float>(2, 0) = rect.area();
    kf.statePost.at<float>(3, 0) = rect.width / rect.height;
}

cv::Rect2d BatchTracker::predict(cv::Mat &frame)
{
    since_update_age += 1;
    cv::Mat post_state = kf.predict();
    cv::Rect2d kcf_rect = last_rect;

    m_age += 1;

    if (since_update_age > 0)
        m_hit_streak = 0;

    //std::cout << "1.1" << std::endl;
    if (kcf_rect.height == 0 || kcf_rect == cv::Rect2d())
        return cv::Rect2d();

    // kcf->update(frame, kcf_rect);
    //std::cout << "1.2" << std::endl;
    cv::Mat measurement = cv::Mat::zeros(4, 1, CV_32F);
    // measurement
    measurement.at<float>(0, 0) = kcf_rect.x + kcf_rect.width / 2;
    measurement.at<float>(1, 0) = kcf_rect.y + kcf_rect.height / 2;
    measurement.at<float>(2, 0) = kcf_rect.area();
    measurement.at<float>(3, 0) = kcf_rect.width / kcf_rect.height;
    //std::cout << "1.3" << std::endl;
    // post_state = kf.correct(measurement);
    //std::cout << "1.4" << std::endl;
    cv::Rect2d predict_box = getRect(post_state.at<float>(0, 0), post_state.at<float>(1, 0), post_state.at<float>(2, 0), post_state.at<float>(3, 0));
    last_rect = predict_box;
    //std::cout << "1.5" << std::endl;
    return predict_box;
}

cv::Rect2d BatchTracker::getRect(float cx, float cy, float s, float r)
{
    float w = sqrt(s * r);
    float h = s / w;
    float x = (cx - w / 2);
    float y = (cy - h / 2);

    if (x < 0 && cx > 0)
        x = 0;
    if (y < 0 && cy > 0)
        y = 0;
    return cv::Rect2d(x, y, w, h);
}

cv::Rect2d BatchTracker::update(cv::Mat &frame, cv::Rect2d &rect)
{
    since_update_age = 0;
    m_hits += 1;
    m_hit_streak += 1;
    // kf.predict();
    // kcf->init(frame, rect);
    if (rect.height == 0 || rect == cv::Rect2d())
        return cv::Rect2d();
    cv::Mat measurement = cv::Mat::zeros(4, 1, CV_32F);
    measurement.at<float>(0, 0) = rect.x + rect.width / 2;
    measurement.at<float>(1, 0) = rect.y + rect.height / 2;
    measurement.at<float>(2, 0) = rect.area();
    measurement.at<float>(3, 0) = rect.width / rect.height;
    cv::Mat post_state = kf.correct(measurement);
    cv::Rect2d predict_box = getRect(post_state.at<float>(0, 0), post_state.at<float>(1, 0), post_state.at<float>(2, 0), post_state.at<float>(3, 0));
    last_rect = predict_box;
    return last_rect;
}

double Tracking::GetIOU(cv::Rect2d &bb_test, cv::Rect2d &bb_gt)
{
    float in = (bb_test & bb_gt).area();
    float un = bb_test.area() + bb_gt.area() - in;

    if (un < DBL_EPSILON)
        return 0;

    return (double)(in / un);
}

Tracking::Tracking()
{
}

bool Tracking::track(cv::Mat &frame, std::vector<cv::Rect2d> &detect_boxs)
{
    frameTrackingResult.clear();
    if (trackers.empty())
    {
        for (auto box : detect_boxs)
        {
            BatchTracker tracker = BatchTracker(frame, box);
            trackers.push_back(tracker);
        }
        return true;
    }

    predict_boxs.clear();
    for (auto it = trackers.begin(); it != trackers.end();)
    {
        cv::Rect2d pBox = (*it).predict(frame);
        // //std::cout << "2" << std::endl;
        if (pBox.x >= 0 && pBox.y >= 0 && pBox.height >= 0 && pBox.width >= 0)
        {
            predict_boxs.push_back(pBox);
            it++;
        }
        else
        {
            it = trackers.erase(it);
        }
    }
    unsigned int tracker_num = trackers.size();
    unsigned int detect_num = detect_boxs.size();
    // //std::cout << "3" << std::endl;
    std::vector<std::vector<double>> iouMatrix;
    iouMatrix.resize(tracker_num, std::vector<double>(detect_num, 0));

    for (unsigned int i = 0; i < tracker_num; i++) // compute iou matrix as a distance matrix
    {
        for (unsigned int j = 0; j < detect_num; j++)
        {
            // use 1-iou because the hungarian algorithm computes a minimum-cost assignment.
            iouMatrix[i][j] = 1 - GetIOU(predict_boxs[i], detect_boxs[j]);
        }
    }
    std::vector<int> assignment;
    std::set<int> unmatchedDetections;
    std::set<int> unmatchedTrajectories;
    std::set<int> allItems;
    std::set<int> matchedItems;
    std::vector<cv::Point> matchedPairs;
    HungarianAlgorithm HungAlgo;

    HungAlgo.Solve(iouMatrix, assignment);

    if (detect_num > tracker_num) //	there are unmatched detections
    {
        for (unsigned int n = 0; n < detect_num; n++)
            allItems.insert(n);

        for (unsigned int i = 0; i < tracker_num; ++i)
            matchedItems.insert(assignment[i]);

        set_difference(allItems.begin(), allItems.end(),
                       matchedItems.begin(), matchedItems.end(),
                       std::insert_iterator<std::set<int>>(unmatchedDetections, unmatchedDetections.begin()));
    }
    else if (detect_num < tracker_num) // there are unmatched trajectory/predictions
    {
        for (unsigned int i = 0; i < tracker_num; ++i)
            if (assignment[i] == -1) // unassigned label will be set as -1 in the assignment algorithm
                unmatchedTrajectories.insert(i);
    }

    
    for (unsigned int i = 0; i < tracker_num; ++i)
    {
        if (assignment[i] == -1) // pass over invalid values
            continue;
        if (1 - iouMatrix[i][assignment[i]] < IOU_THRESHOLD)
        {
            unmatchedTrajectories.insert(i);
            unmatchedDetections.insert(assignment[i]);
        }
        else
            matchedPairs.push_back(cv::Point(i, assignment[i]));
    }

    int detIdx, trkIdx;
    for (unsigned int i = 0; i < matchedPairs.size(); i++)
    {
        trkIdx = matchedPairs[i].x;
        detIdx = matchedPairs[i].y;
        trackers[trkIdx].update(frame, detect_boxs[detIdx]);
    }
    for (auto umd : unmatchedDetections)
    {
        BatchTracker tracker = BatchTracker(frame, detect_boxs[umd]);
        trackers.push_back(tracker);
    }

    // get output

    for (auto it = trackers.begin(); it != trackers.end();)
    {
        // if (((*it).since_update_age < MAX_AGE) &&
        //     ((*it).m_hit_streak >= MIN_HITS))
        if(1)
        {
            TrackingBox res;
            res.box = (*it).last_rect;
            res.id = (*it).id + 1;
            frameTrackingResult.push_back(res);
            it++;
        }
        else
        {
            it++;
        }
        // remove dead tracklet
        if (it != trackers.end() && (*it).since_update_age > 6)
            it = trackers.erase(it);
    }

    return true;
}
