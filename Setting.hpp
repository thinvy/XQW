#ifndef SETTING_HPP_
#define SETTING_HPP_


const std::string camera_path = "/dev/video0";

const int CAMERA_WIDTH = 640;
const int CAMERA_HEIGHT = 480;

const int REQURIED_WIDTH =224;
const int REQURIED_HEGIHT =224;

const int DISPLAY_WIGTH=512;
const int DISPLAY_HEIGHT=512    ;

const int CAMERA_EXPORSURE = 100;
const int CAMERA_FPS = 30;
const std::string OUTURL = "192.168.0.88";
const std::string OUTPORT = "5004";
#define THRESHOLD 0.55

#define ANCHOR_SIZE 3087
#define OUTPUT_SIZE 6
#define INPUT_TESONR_SIZE 1 * REQURIED_WIDTH* REQURIED_HEGIHT * 3
#define OUTPUT_TESONR_SIZE  1 * ANCHOR_SIZE * OUTPUT_SIZE



#endif