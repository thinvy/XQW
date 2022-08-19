QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QT       += opengl

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    display.cpp \
    loginWin.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    display.hpp \
    loginWin.hpp \
    mainwindow.hpp

FORMS += \
    #logineWindow.ui \
    loginWin.ui \
    mainwindow.ui

TRANSLATIONS += \
    MainCom_zh_CN.ts\
    img/1.png \
    ../../Camera/ \
    Detection/include/Detection.hpp \
    Detection/include/ReDetect.hpp \
    Detection/include/TfliteWorker.hpp \
    Detection/include/Tracking.hpp \
    Detection/src/Detection.cpp \
    Detection/src/ReDetect.cpp \
    Detection/src/TfliteWorker.cpp \
    Detection/src/Tracking.cpp \
    Detection/demo/** \
    Codec/include/VideoReader.hpp \
    Codec/include/VideoWriter.hpp \
    Codec/src/VideoReader.cpp \
    Codec/src/VideoWriter.cpp \
    Codec/ReadMe.md \
    Codec/demo/** \


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target



INCLUDEPATH += \
   # $$(SDKTARGETSYSROOT)/usr/include/opencv4 \
   # $$(SDKTARGETSYSROOT)/usr/include/tensorflow/lite/tools/make/downloads/flatbuffers/include \
   # $$(SDKTARGETSYSROOT)/usr/include/armnn \
   /usr/include/opencv4 \

LIBS += \
    #-L $$(SDKTARGETSYSROOT)/usr/lib64 \
    #-larmnn \
    #-larmnnDelegate \
    #-larmnnUtils \
    -lopencv_core \
    -lopencv_imgproc \
    -lopencv_imgcodecs \
    -lopencv_videoio \
    #-ltensorflow-lite \
    #-ldl \
    #-lutil

#contains(DEFINES, DUNFELL) {
#LIBS += \
    #-lflatbuffers \
    #-lfft2d_fftsg2d \
    #-lruy \
    #-lXNNPACK \
    #-lpthreadpool \
    #-lcpuinfo \
    #-lclog \
    #-lfft2d_fftsg \
    #-lfarmhash
#}
