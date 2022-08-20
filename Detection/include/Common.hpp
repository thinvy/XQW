#ifndef COMMON_HPP_
#define COMMON_HPP_

///////////////////////////////////////////////////////////////////////////////
// Hungarian.h: Header file for Class HungarianAlgorithm.
//
// This is a C++ wrapper with slight modification of a hungarian algorithm implementation by Markus Buehren.
// The original implementation is a few mex-functions for use in MATLAB, found here:
// http://www.mathworks.com/matlabcentral/fileexchange/6543-functions-for-the-rectangular-assignment-problem
//
// Both this code and the orignal code are published under the BSD license.
// by Cong Ma, 2016
//

#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#include <opencv2/video/tracking.hpp>
#include <opencv2/highgui/highgui.hpp>


// 匈牙利算法
class HungarianAlgorithm
{
public:
    HungarianAlgorithm() {}
    ~HungarianAlgorithm() {}
    double Solve(std::vector<std::vector<double>> &DistMatrix, std::vector<int> &Assignment);

private:
    void assignmentoptimal(int *assignment, double *cost, double *distMatrix, int nOfRows, int nOfColumns);
    void buildassignmentvector(int *assignment, bool *starMatrix, int nOfRows, int nOfColumns);
    void computeassignmentcost(int *assignment, double *cost, double *distMatrix, int nOfRows);
    void step2a(int *assignment, double *distMatrix, bool *starMatrix, bool *newStarMatrix, bool *primeMatrix, bool *coveredColumns, bool *coveredRows, int nOfRows, int nOfColumns, int minDim);
    void step2b(int *assignment, double *distMatrix, bool *starMatrix, bool *newStarMatrix, bool *primeMatrix, bool *coveredColumns, bool *coveredRows, int nOfRows, int nOfColumns, int minDim);
    void step3(int *assignment, double *distMatrix, bool *starMatrix, bool *newStarMatrix, bool *primeMatrix, bool *coveredColumns, bool *coveredRows, int nOfRows, int nOfColumns, int minDim);
    void step4(int *assignment, double *distMatrix, bool *starMatrix, bool *newStarMatrix, bool *primeMatrix, bool *coveredColumns, bool *coveredRows, int nOfRows, int nOfColumns, int minDim, int row, int col);
    void step5(int *assignment, double *distMatrix, bool *starMatrix, bool *newStarMatrix, bool *primeMatrix, bool *coveredColumns, bool *coveredRows, int nOfRows, int nOfColumns, int minDim);
};

// This class represents the internel state of individual tracked objects observed as bounding box.
class KalmanTracker
{
public:
    KalmanTracker()
    {
        init_kf(cv::Rect2f());
        m_time_since_update = 0;
        m_hits = 0;
        m_hit_streak = 0;
        m_age = 0;
        m_id = kf_count;
        // kf_count++;
    }
    KalmanTracker(cv::Rect2f initRect)
    {
        init_kf(initRect);
        m_time_since_update = 0;
        m_hits = 0;
        m_hit_streak = 0;
        m_age = 0;
        m_id = kf_count;
        kf_count++;
    }

    ~KalmanTracker()
    {
        m_history.clear();
    }

    cv::Rect2f predict();
    void update(cv::Rect2f stateMat);

    cv::Rect2f get_state();
    cv::Rect2f get_rect_xysr(float cx, float cy, float s, float r);

    static int kf_count;

    int m_time_since_update;
    int m_hits;
    int m_hit_streak;
    int m_age;
    int m_id;

private:
    void init_kf(cv::Rect2f stateMat);

    cv::KalmanFilter kf;
    cv::Mat measurement;

    std::vector<cv::Rect2f> m_history;
};

#endif