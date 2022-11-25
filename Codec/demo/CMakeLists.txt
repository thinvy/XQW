cmake_minimum_required(VERSION 3.6)
PROJECT(sample)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ./bin/)
find_package(OpenCV REQUIRED)

# 添加reader的demo
add_executable(VideoReaderDemo ./ReaderDemo.cpp ../src/VideoReader.cpp ../include/VideoReader.hpp)
target_link_libraries(VideoReaderDemo PUBLIC ${OpenCV_LIBS})
target_link_libraries(VideoReaderDemo PUBLIC "-lgstreamer-1.0 -lgobject-2.0 -lglib-2.0")
target_include_directories(VideoReaderDemo PUBLIC /usr/include/gstreamer-1.0)
target_include_directories(VideoReaderDemo PUBLIC /usr/include/gobject-2.0)
target_include_directories(VideoReaderDemo PUBLIC /usr/include/glib-2.0)
target_include_directories(VideoReaderDemo PUBLIC /usr/lib/x86_64-linux-gnu/glib-2.0/include)
target_include_directories(VideoReaderDemo PUBLIC ${OpenCV_INCLUDE_DIRS})

# 添加writer的demo
add_executable(VideoWriterDemo ./WriterDemo.cpp ../src/VideoWriter.cpp ../include/VideoWriter.hpp ../src/VideoReader.cpp ../include/VideoReader.hpp)
target_link_libraries(VideoWriterDemo PUBLIC ${OpenCV_LIBS})
target_link_libraries(VideoWriterDemo PUBLIC "-lgstreamer-1.0 -lgobject-2.0 -lglib-2.0")
target_include_directories(VideoWriterDemo PUBLIC /usr/include/gstreamer-1.0)
target_include_directories(VideoWriterDemo PUBLIC /usr/include/gobject-2.0)
target_include_directories(VideoWriterDemo PUBLIC /usr/include/glib-2.0)
target_include_directories(VideoWriterDemo PUBLIC /usr/lib/x86_64-linux-gnu/glib-2.0/include)
target_include_directories(VideoWriterDemo PUBLIC ${OpenCV_INCLUDE_DIRS})

# 添加camera的demo
add_executable(CameraDemo  ./CameraDemo.cpp ../src/VideoWriter.cpp ../include/VideoWriter.hpp)
target_link_libraries(CameraDemo PUBLIC ${OpenCV_LIBS})
target_link_libraries(CameraDemo PUBLIC "-lgstreamer-1.0 -lgobject-2.0 -lglib-2.0")
target_include_directories(CameraDemo PUBLIC /usr/include/gstreamer-1.0)
target_include_directories(CameraDemo PUBLIC /usr/include/gobject-2.0)
target_include_directories(CameraDemo PUBLIC /usr/include/glib-2.0)
target_include_directories(CameraDemo PUBLIC /usr/lib/x86_64-linux-gnu/glib-2.0/include)
target_include_directories(CameraDemo PUBLIC ${OpenCV_INCLUDE_DIRS})


