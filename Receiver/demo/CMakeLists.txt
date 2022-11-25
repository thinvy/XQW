cmake_minimum_required(VERSION 3.6)
PROJECT(sample)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ./bin/)
find_package(OpenCV REQUIRED)


# 添加receiver的demo
add_executable(ReceiverDemo ./ReceiverDemo.cpp ../include/VideoReceiver.hpp ../src/VideoReceiver.cpp)
target_link_libraries(ReceiverDemo PUBLIC ${OpenCV_LIBS})
target_link_libraries(ReceiverDemo PUBLIC "-lgstreamer-1.0 -lgobject-2.0 -lglib-2.0")
target_include_directories(ReceiverDemo PUBLIC /usr/include/gstreamer-1.0)
target_include_directories(ReceiverDemo PUBLIC /usr/include/gobject-2.0)
target_include_directories(ReceiverDemo PUBLIC /usr/include/glib-2.0)
target_include_directories(ReceiverDemo PUBLIC /usr/lib/x86_64-linux-gnu/glib-2.0/include)
target_include_directories(ReceiverDemo PUBLIC ${OpenCV_INCLUDE_DIRS})
