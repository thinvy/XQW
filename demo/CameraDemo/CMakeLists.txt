cmake_minimum_required(VERSION 2.8)
 
project(camera_demo)
 
find_package(OpenCV REQUIRED)
 
include_directories( 
    ${OpenCV_INCLUDE_DIRS} 
    ../../Camera.hpp
)
 
add_executable(camera_demo CameraDemo.cpp ../../Camera.cpp)
 
target_link_libraries(camera_demo ${OpenCV_LIBS})
