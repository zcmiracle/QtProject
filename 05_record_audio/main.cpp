#include "mainwindow.h"

#include <QApplication>
#include <iostream>

extern "C" {
// 设备相关API
#include <libavdevice/avdevice.h>
}

int main(int argc, char *argv[])
{
    // 1、注册设备 - 只执行一次
    avdevice_register_all();

    // 打印方式
    // C语言
    printf("printf------\n");

    // C++
    std::cout << "std::cout-----" << std::endl;

    // FFmpeg
    // 这句会影响下面三句打印
    av_log_set_level(AV_LOG_DEBUG);

    av_log(nullptr, AV_LOG_ERROR, "av_log_error-----\n");
    av_log(nullptr, AV_LOG_WARNING, "av_log_warning-----\n");
    av_log(nullptr, AV_LOG_INFO, "av_log_info-----\n");

    // 日志级别大小
    // TRACE < DEBUG < INFO < WARNING < ERROR < FATAL

    // Qt qDebug 能自动换行
    qDebug() << "qDebug-----";

    // 刷新标准输出流
    fflush(stdout);
    fflush(stderr);

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
