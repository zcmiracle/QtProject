#include "mainwindow.h"

#include <QApplication>
#include <iostream>

extern "C" {
// 设备相关API
#include <libavdevice/avdevice.h>
}

int main(int argc, char *argv[]) {

    // 注册设备 - 只执行一次
    avdevice_register_all();

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
