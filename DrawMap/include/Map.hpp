#ifndef MAP_HPP_
#define MAP_HPP_

#include <opencv2/opencv.hpp>
#include <vector>

#include "MapCam.hpp"
#include <memory>

#include <boost/circular_buffer.hpp>

class Map
{
    std::vector<cv::Point2f> map_point;
    cv::Mat map;
    cv::Point2f offset = cv::Point2f(5, 10);

    std::vector<std::vector<cv::Point2f>> person_point;

    std::shared_ptr<MapCamera> mapcam_0;

    std::shared_ptr<boost::circular_buffer<cv::Point2f>> trail;


public:
    void initMapCam()
    {
        mapcam_0 = std::make_shared<MapCamera>(135, 128, "left");
//        mapcam_0 = std::make_shared<MapCamera>(135, 75, "left");
    }

    void drawMapCam(cv::Mat &map_img, int cam_id)
    {
        if (cam_id == 0)
        {
            cv::Point2f point = mapcam_0->get_position();
            cv::circle(map_img, point, 2, cv::Scalar(0, 0, 255), 3);
            if (mapcam_0->get_direction() == "front")
            {
                cv::line(map_img, point, cv::Point(point.x+10, point.y-10), cv::Scalar(0, 0, 255), 1);
                cv::line(map_img, point, cv::Point(point.x-10, point.y-10), cv::Scalar(0, 0, 255), 1);
            }
            else if (mapcam_0->get_direction() == "back")
            {
                cv::line(map_img, point, cv::Point(point.x+10, point.y+10), cv::Scalar(0, 0, 255), 1);
                cv::line(map_img, point, cv::Point(point.x-10, point.y+10), cv::Scalar(0, 0, 255), 1);
            }
            else if (mapcam_0->get_direction() == "left")
            {
                cv::line(map_img, point, cv::Point(point.x-10, point.y+10), cv::Scalar(0, 0, 255), 1);
                cv::line(map_img, point, cv::Point(point.x-10, point.y-10), cv::Scalar(0, 0, 255), 1);
            }
            else if (mapcam_0->get_direction() == "right")
            {
                cv::line(map_img, point, cv::Point(point.x+10, point.y+10), cv::Scalar(0, 0, 255), 1);
                cv::line(map_img, point, cv::Point(point.x+10, point.y-10), cv::Scalar(0, 0, 255), 1);
            }
        }
    }

    cv::Mat getMap()
    {
//        cv::Point2f  point=person_point.at(0).front();
//        cv::circle(map, (point + offset) * 3, 1, cv::Scalar(0, 100, 0), 1);
//        person_point.at(0).erase(person_point.at(0).begin());
        return map.clone();
    }

    void showMap()
    {
        cv::namedWindow("map", cv::WINDOW_NORMAL);
        cv::imshow("map", map);
        cv::waitKey(0);
    }

    void drawPoint(cv::Mat &map_img, int cam_id, cv::Point pos, cv::Size size)
    {
        if (cam_id == 0)
        {
            cv::Point2f point = mapcam_0->CalcPoint(pos, size);
            trail->push_back(point);
            for (int i = 0; i < trail->size(); i++) {
                if (i == 0) continue;
                cv::line(map_img, trail->at(i-1), trail->at(i), cv::Scalar(0, 100, 0), 2);
//                cv::circle(map_img, trail->at(i), 1, cv::Scalar(0, 100, 0), 1);
            }
//            std::cout << "aim pos : " << point << std::endl;

        }
    }

    void readMap()
    {
        int x_sc = 1.0;
        int y_sc = 1.0;
//        map_point.push_back(cv::Point2f(0 * x_sc, 10 * y_sc));
//        map_point.push_back(cv::Point2f(0 * x_sc, 30 * y_sc));
//        map_point.push_back(cv::Point2f(5 * x_sc, 30 * y_sc));
//        map_point.push_back(cv::Point2f(5 * x_sc, 20 * y_sc));
//        map_point.push_back(cv::Point2f(20 * x_sc, 20 * y_sc));
//        map_point.push_back(cv::Point2f(20 * x_sc, 30 * y_sc));
//        map_point.push_back(cv::Point2f(25 * x_sc, 30 * y_sc));
//        map_point.push_back(cv::Point2f(40 * x_sc, 30 * y_sc));

//        map_point.push_back(cv::Point2f(40 * x_sc, 0 * y_sc));
//        map_point.push_back(cv::Point2f(25 * x_sc, 0 * y_sc));
//        map_point.push_back(cv::Point2f(25 * x_sc, 15 * y_sc));
//        map_point.push_back(cv::Point2f(5 * x_sc, 15 * y_sc));
//        map_point.push_back(cv::Point2f(5 * x_sc, 10 * y_sc));
        map_point.push_back(cv::Point2f(10 * x_sc, 10 * y_sc));
        map_point.push_back(cv::Point2f(10 * x_sc, 38 * y_sc));
        map_point.push_back(cv::Point2f(40 * x_sc, 38 * y_sc));
        map_point.push_back(cv::Point2f(40 * x_sc, -8 * y_sc));
        map_point.push_back(cv::Point2f(-2 * x_sc, -8 * y_sc));
        map_point.push_back(cv::Point2f(-2 * x_sc, 10 * y_sc));
        map = cv::Mat(150, 150, CV_8UC3, cv::Scalar(255, 255, 255));
        for (int i = 0; i < map_point.size(); i++)
        {
            cv::line(map, (map_point.at(i) + offset) * 3, (map_point.at((i + 1) % map_point.size()) + offset) * 3, cv::Scalar(200, 0, 0), 1);
            cv::circle(map, (map_point.at(i) + offset) * 3, 1, cv::Scalar(200, 0, 0), 1);
        }
        map_point.clear();

        map_point.push_back(cv::Point2f(40 * x_sc, 38 * y_sc));
        map_point.push_back(cv::Point2f(40 * x_sc, 10 * y_sc));
        map_point.push_back(cv::Point2f(20 * x_sc, 10 * y_sc));
        map_point.push_back(cv::Point2f(20 * x_sc, 38 * y_sc));
        for (int i = 0; i < map_point.size(); i++)
        {
            cv::line(map, (map_point.at(i) + offset) * 3, (map_point.at((i + 1) % map_point.size()) + offset) * 3, cv::Scalar(200, 0, 0), 1);
            cv::circle(map, (map_point.at(i) + offset) * 3, 1, cv::Scalar(200, 0, 0), 1);
        }
        map_point.clear();

        map_point.push_back(cv::Point2f(20 * x_sc, 34 * y_sc));
        map_point.push_back(cv::Point2f(20 * x_sc, 37.5 * y_sc));
        for (int i = 0; i < map_point.size(); i++)
        {
            cv::line(map, (map_point.at(i) + offset) * 3, (map_point.at((i + 1) % map_point.size()) + offset) * 3, cv::Scalar(255, 255, 255), 2);
//            cv::circle(map, (map_point.at(i) + offset) * 3, 2, cv::Scalar(255, 255, 255), 1);
        }
        map_point.clear();

        map_point.push_back(cv::Point2f(3 * x_sc, -8 * y_sc));
        map_point.push_back(cv::Point2f(6.5 * x_sc, -8 * y_sc));
        for (int i = 0; i < map_point.size(); i++)
        {
            cv::line(map, (map_point.at(i) + offset) * 3, (map_point.at((i + 1) % map_point.size()) + offset) * 3, cv::Scalar(255, 255, 255), 2);
//            cv::circle(map, (map_point.at(i) + offset) * 3, 2, cv::Scalar(255, 255, 255), 1);
        }
        map_point.clear();

        map_point.push_back(cv::Point2f(11 * x_sc, -8 * y_sc));
        map_point.push_back(cv::Point2f(19 * x_sc, -8 * y_sc));
        for (int i = 0; i < map_point.size(); i++)
        {
            cv::line(map, (map_point.at(i) + offset) * 3, (map_point.at((i + 1) % map_point.size()) + offset) * 3, cv::Scalar(255, 255, 255), 2);
//            cv::circle(map, (map_point.at(i) + offset) * 3, 2, cv::Scalar(255, 255, 255), 1);
        }
        map_point.clear();


//        cv::line(map, (cv::Point2f(25 * x_sc, 25 * y_sc) + offset) * 3, (cv::Point2f(25, 15 * y_sc) + offset) * 3, cv::Scalar(100, 0, 0), 1);
//        cv::circle(map, (cv::Point2f(25 * x_sc, 25 * y_sc) + offset) * 3, 1, cv::Scalar(100, 0, 0), 1);
//        cv::circle(map, (cv::Point2f(25 * x_sc, 15 * y_sc) + offset) * 3, 1, cv::Scalar(100, 0, 0), 1);
//        cv::line(map,(cv::Point2f(3,13))*3,(cv::Point2f(9,13))*3,cv::Scalar(0, 100, 0),1);
//        cv::putText(map,"2",(cv::Point2f(10,13))*3,1,1,cv::Scalar(0, 100, 0));
    }

    void readPersonPoint()
    {
        std::vector<cv::Point2f> person2 = { cv::Point2f(1, 27),
                                             cv::Point2f(1, 20),
                                             cv::Point2f(5, 17),
                                             cv::Point2f(10, 17),
                                             cv::Point2f(15, 17),
                                             cv::Point2f(22, 17),
                                            // cv::Point2f(22, 25),
                                             cv::Point2f(22, 29),
                                             //cv::Point2f(30, 29),
                                             cv::Point2f(32, 29),
                                             cv::Point2f(32, 15),
                                             cv::Point2f(32, 5),
        };
        person_point.push_back(person2);
    }

    Map()
    {
        readMap();
        readPersonPoint();
        trail = std::make_shared<boost::circular_buffer<cv::Point2f>>(12);
    }
};
#endif
