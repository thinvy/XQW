#ifndef MAPCAM_HPP
#define MAPCAM_HPP

#include <opencv2/opencv.hpp>
#include <vector>
#include <iostream>

#define D0 5.0
#define P0 38.0
#define W0 0.5
#define REAL2MAP1 90.0/20.0
#define REAL2MAP2 90.0/15.0

#define DEEP_BASE 1

#define FRAME_WIDTH 224
#define FRAME_HEIGTH 224
#define BASE_DEEP 90
#define GAIN_LEVEL (5.0/200.0)
#define GAIN_DEEPTH (90.0/55.0)

// 60,0->5,90

class MapCamera
{
public:
    MapCamera(){}
    MapCamera(float coordinate_x, float coordinate_y, std::string direction) :
        coordinate_x_(coordinate_x), coordinate_y_(coordinate_y), direction_(direction) {}
    cv::Point2f CalcPoint(cv::Point2f position, cv::Size size)
    {

        float dealta_deepth = D0 * P0 / size.width * REAL2MAP1;
        float dealta_level = W0 / size.width * (position.x - FRAME_WIDTH/2) * REAL2MAP2;

        // 90,30; 135,30; 135,120; 90,120;
        cv::Point2f aim_location;

        if (direction_ == "left") {
            aim_location.x = coordinate_x_ - dealta_deepth;
            aim_location.y = coordinate_y_ - dealta_level;
        }
        else if (direction_ == "right") {
            aim_location.x = coordinate_x_ + dealta_deepth;
            aim_location.y = coordinate_y_ + dealta_level;
        }
        else if (direction_ == "front") {
            aim_location.x = coordinate_x_ + dealta_level;
            aim_location.y = coordinate_y_ - dealta_deepth;
        }
        else if (direction_ == "back") {
            aim_location.x = coordinate_x_ - dealta_level;
            aim_location.y = coordinate_y_ + dealta_deepth;
        }

        return aim_location;
    }
    cv::Point2f get_position() {
        return cv::Point2f(coordinate_x_, coordinate_y_);
    }
    std::string get_direction() {
        return direction_;
    }


private:
    float coordinate_x_;
    float coordinate_y_;
    std::string direction_;
};






#endif // MAPCAM_HPP
