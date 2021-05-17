QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


# 设置头文件路径
#mac:INCLUDEPATH += /usr/local/Cellar/ffmpeg/4.4_1/include
#mac:INCLUDEPATH += $${FFMPEG_HOME}/include
#win32: 如果是window

# 设置库文件路径
# 需要链接哪些库，默认是链接动态库
#mac:LIBS += -L $${FFMPEG_HOME}/lib \
#        -lavcodec \
#        -lavdevice \
#        -lavfilter \
#        -lavformat \
#        -lavresample \
#        -lavutil \
#        -lpostproc \
#        -lswresample \
#        -lswscale \

win32: {
    FFMPEG_HOME = ..
    # 设置头文件路径
    INCLUDEPATH += $${FFMPEG_HOME}/include
    # 设置库文件路径
    LIBS += -L $${FFMPEG_HOME}/lib \
            -lavcodec \
            -lavdevice \
            -lavfilter \
            -lavformat \
            -lavresample \
            -lavutil \
            -lpostproc \
            -lswresample \
            -lswscale \
}



mac: {
    # 抽离
    FFMPEG_HOME = /usr/local/Cellar/ffmpeg/4.4_1
    # 打印路径
    message($${FFMPEG_HOME});

    # 设置头文件路径
    INCLUDEPATH += $${FFMPEG_HOME}/include
    # 设置库文件路径
    LIBS += -L $${FFMPEG_HOME}/lib \
            -lavcodec \
            -lavdevice \
            -lavfilter \
            -lavformat \
            -lavresample \
            -lavutil \
            -lpostproc \
            -lswresample \
            -lswscale \
}

# message() 用来打印

# $${xxx} 可以用来取值, .pro中定义的变量

# ##() 可以用来取值：系统环境变量中的值
