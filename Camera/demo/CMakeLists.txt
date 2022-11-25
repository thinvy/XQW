cmake_minimum_required(VERSION 2.8)
 
project(camera_demo)
 
find_package(OpenCV REQUIRED)
 
include_directories( 
    ${OpenCV_INCLUDE_DIRS} 
    ../include/
)
 
add_executable(camera_demo CameraDemo.cpp ../src/Camera.cpp)
 
target_link_libraries(camera_demo ${OpenCV_LIBS})

