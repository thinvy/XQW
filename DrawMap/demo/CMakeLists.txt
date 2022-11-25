cmake_minimum_required(VERSION 3.6)
PROJECT(sample)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ./bin/)
find_package(OpenCV REQUIRED)


# 添加receiver的demo
add_executable(DrawMapDemo ./DrawMapDemo.cpp ../include/Map.hpp)
target_link_libraries(DrawMapDemo PUBLIC ${OpenCV_LIBS})
target_include_directories(DrawMapDemo PUBLIC ${OpenCV_INCLUDE_DIRS})
