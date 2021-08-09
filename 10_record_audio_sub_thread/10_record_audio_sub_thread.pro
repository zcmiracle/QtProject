QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    audiothead.cpp \
    ffmpegutil.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    audiothead.h \
    ffmpegutil.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


macx {

    # 添加plist
    QMAKE_INFO_PLIST = mac/Info.plist
    # 抽离
    FFMPEG_HOME = /usr/local/Cellar/ffmpeg/4.4_1
    # 打印路径
    message($${FFMPEG_HOME});

    # 设置头文件路径
    INCLUDEPATH += $${FFMPEG_HOME}/include
    # 设置库文件路径
    LIBS += -L $${FFMPEG_HOME}/lib \
            -lavdevice \
            -lavformat \
            -lavcodec \
            -lavutil \
}
