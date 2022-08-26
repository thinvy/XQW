cmake_minimum_required(VERSION 3.6)
PROJECT(data_transporter_demo)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ./bin/)
find_package(OpenCV REQUIRED)

add_executable(UdpBroadcastDemo UdpBroadcastDemo.cpp udpbd_transporter.cpp udpbd_transporter.hpp transporter.hpp)
target_link_libraries(UdpBroadcastDemo PUBLIC ${OpenCV_LIBS})
target_include_directories(UdpBroadcastDemo PUBLIC ${OpenCV_INCLUDE_DIRS})

add_executable(ResultTransporterDemo ResultTransporterDemo.cpp ResultTransporter.hpp udpbd_transporter.cpp udpbd_transporter.hpp transporter.hpp)
target_link_libraries(ResultTransporterDemo PUBLIC ${OpenCV_LIBS})
target_include_directories(ResultTransporterDemo PUBLIC ${OpenCV_INCLUDE_DIRS})