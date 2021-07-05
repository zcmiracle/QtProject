#include "audiothead.h"
#include <QFile>
#include <QDebug>
#include <QDateTime>

extern "C" {
// 设备相关API
#include <libavdevice/avdevice.h>
// 格式相关API
#include <libavformat/avformat.h>
// 工具相关API（比如错误处理）
#include <libavutil/avutil.h>
#include <libavcodec/avcodec.h>
}

// 宏定义
#ifdef Q_OS_MAC
    // 格式的名称
    #define FMT_NAME "avfoundation"
    // 设备名称
    #define DEVICE_NAME ":0"
    // PCM文件的文件名
//    #define FILEPATH "Users/xfb/Desktop/QT/QtProject/"
    #define FILEPATH "/Users/zhoucheng/Desktop/qt/"
#else
    // Windows
    #define FMT_NAME "dshow"
    #define DEVICE_NAME "audio=xxx"
    #define FILEPATH "E:/"
#endif


AudioThead::AudioThead(QObject *parent) : QThread(parent) {
    // 当监听到线程结束时 finished，就调用线程自己的deleteLater回收内存
    connect(this, &AudioThead::finished,
            this, &AudioThead::deleteLater);
}


// 析构函数
AudioThead::~AudioThead() {
    // 断开所有的连接
    disconnect();
    // 内存回收之前，正常结束线程
    requestInterruption();
    // 安全退出
    quit();
    wait();

    qDebug() << this << "析构（内存被回收）";
}


void display(AVFormatContext *contxt) {
    // 获取输入流
    AVStream *stream = contxt->streams[0];
    // 获取音频参数
    AVCodecParameters *parameter = stream->codecpar;
    // 声道数
    qDebug() << parameter->channels;
    // 采样率
    qDebug() << parameter->sample_rate;
    // 采样格式
    qDebug() << parameter->format;
    // 每一个样本的一个声道占用多少个字节
    qDebug() << av_get_bytes_per_sample((AVSampleFormat) parameter->format);
}


// 当线程启动的时候 start ，会自动调用run函数
// run函数中的代码在子线程中执行的
// 耗时操作应该在子线程中执行
void AudioThead::run() {

    qDebug() << this << "------开始执行------";

    // 获取输入格式对象
    AVInputFormat *fmt = av_find_input_format(FMT_NAME);
    if (!fmt) {
        qDebug() << "获取输入格式对象失败" << FMT_NAME;
        return;
    };

    // 格式上下文（将来可以利用上下文操作设备）
    AVFormatContext *contxt = nullptr;
    // 打开设备
    int ret = avformat_open_input(&contxt, DEVICE_NAME, fmt, nullptr);
    if (ret < 0) {
        char errbuf[1024]; // 字符数组
        // 根据函数返回的错误码获取错误信息
        av_strerror(ret, errbuf, sizeof(errbuf));
        qDebug() << "打开设备失败" << errbuf;
        return;
    }

    // 打印录音设备的参数信息
    display(contxt);

    // 文件名
    QString filename = FILEPATH;
    filename += QDateTime::currentDateTime().toString("MM_dd_HH_mm_ss");
    filename += ".pcm";
    QFile file(filename);

    // 打开文件
    // WriteOnly：只写模式，如果文件不存在，创建文件。如果文件存在，清空文件内容
    if (!file.open(QFile::WriteOnly)) {
        qDebug() << "文件打开失败" << filename;

        // 关闭设备
        avformat_close_input(&contxt);
        return;
    }

    // 数据包
    AVPacket *pkt = av_packet_alloc();
    // 不断采集数据
    while (isInterruptionRequested()) {
        // 不断采集数据
        ret = av_read_frame(contxt, pkt);

        if (ret== 0) {
            file.write((const char *) pkt->data, pkt->size);
        } else if (ret == AVERROR(EAGAIN)) {
            continue;
        } else {
            char errbuf[1024];
            av_strerror(ret, errbuf, sizeof(errbuf));
            qDebug() << "av_read_frame error" << errbuf << ret;
            break;
        }

        // 必须要加，释放pkt内部的资源
        av_packet_unref(pkt);
    }

    // 关闭文件
    file.close();

    // 释放资源
    av_packet_free(&pkt);

    // 关闭设备
    avformat_close_input(&contxt);

    qDebug() << this << "------正常结束------";
}


void AudioThead::setStop(bool stop) {
    _stop = stop;
}


