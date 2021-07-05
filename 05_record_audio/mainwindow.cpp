#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFile>
#include <QThread>

extern "C" {
// 设备相关API
#include <libavdevice/avdevice.h>
// 格式相关API
#include <libavformat/avformat.h>
// 工具相关API（比如错误处理）
#include <libavutil/avutil.h>
}

// 宏定义
#ifdef Q_OS_MAC
    // 格式的名称
    #define FMT_NAME "avfoundation"
    // 设备名称
    #define DEVICE_NAME ":0"
    // PCM文件的文件名
    #define FILENAME "Users/xfb/Desktop/QT/QtProject/out.pcm"
//    #define FILENAME "/Users/zhoucheng/Desktop/qt/out.pcm"
#else
    // Windows
    #define FMT_NAME "dshow"
    #define DEVICE_NAME "audio=xxx"
    #define FINENAME "E:/out.pcm"
#endif


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {

    ui->setupUi(this);

    // 打印线程
    qDebug() << QThread::currentThread();
}

MainWindow::~MainWindow() {
    delete ui;
}

// 开始录音 button 点击
void MainWindow::on_audioButton_clicked() {
    // 1、注册设备，在main.cpp中，只注册一次

    // 2、指定获取输入格式对象
    // window平台：fmtName = dshow
    // mac平台：fmtName = avfoundation
    const char *fmtName = FMT_NAME;
    AVInputFormat *fmt = av_find_input_format("avfoundation");
    if (!fmt) {
        qDebug() << "获取输入格式对象失败" << fmtName;
        return;
    };

    /**
      mac录制     ffmpeg -f avfoundation -i :2 out.wav
      window录制  ffmpeg -f dshow -i audio="xxx" out.wav
      */

    // 3、打开设备
    // 格式上下文（将来可以利用上下文操作设备）
    AVFormatContext *context = nullptr;
    // 设备名称
    const char *deviceName = DEVICE_NAME;
    // 选项
    AVDictionary *options = {0};
    // 打开设备
    // int avformat_open_input(AVFormatContext **ps, const char *url, ff_const59 AVInputFormat *fmt, AVDictionary **options);
//    int ret = avformat_open_input(&context, deviceName, fmt, &options);
    int ret = avformat_open_input(&context, deviceName, fmt, nullptr);
    if (ret < 0) {
        // int av_strerror(int errnum, char *errbuf, size_t errbuf_size);
        char errbuf[1024]; // 字符数组
        // 根据函数返回的错误码获取错误信息
        av_strerror(ret, errbuf, sizeof(errbuf));
        qDebug() << "打开设备失败" << errbuf;
        return;
    }

    // 文件名
    const char *filename = FILENAME;
    QFile file(filename);


    // 打开文件
    // WriteOnly：只写模式，如果文件不存在，创建文件。如果文件存在，清空文件内容
    if (!file.open(QFile::WriteOnly)) {
        qDebug() << "文件打开失败" << filename;

        // 关闭设备
        avformat_close_input(&context);
        return;
    }


    // 采集次数
    int count = 50;

    // 数据包
    AVPacket *pkt = av_packet_alloc();
    // 不断采集数据
    // int av_read_frame(AVFormatContext *s, AVPacket *pkt);
    while ((count-- > 0)) {

        int ret = av_read_frame(context, pkt);
        if (ret == 0) { // 读取成功

            qDebug() << "写入成功";
            // 将数据写入文件
            file.write((const char *) pkt->data, pkt->size);
            // 释放资源
            av_packet_unref(pkt);
        } else if (ret == AVERROR(EAGAIN)) {
            qDebug() << "EAGAIN";
            continue;
        } else {
            char errbuf[1024];
            // int av_strerror(int errnum, char *errbuf, size_t errbuf_size);
            av_strerror(ret, errbuf, sizeof(errbuf));
            qDebug() << "av_read_frame error" << errbuf << ret;
            break;
        }

    }

    // 关闭文件
    file.close();

    // 释放资源
    av_packet_free(&pkt);

    // 关闭设备
    avformat_close_input(&context);

}

