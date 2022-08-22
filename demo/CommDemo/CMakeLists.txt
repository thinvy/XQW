cmake_minimum_required(VERSION 3.6)
PROJECT(data_transporter_demo)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ./bin/)

# 添加reader的demo
add_executable(UdpBroadcastDemo UdpBroadcastDemo.cpp udpbd_transporter.cpp udpbd_transporter.hpp transporter.hpp)
