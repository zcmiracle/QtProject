#include "playthread.h"
#include <QDebug>
#include <QFile>
#include <SDL2/SDL.h>

#define FILENAME "/Users/xfb/Desktop/QT/QtProject/07_sdl_play_pcm/in.pcm"
// 采样率
#define SAMPLE_RATE 44100
//
#define SAMPLE_FORMAT AUDIO_S16LSB
// 采样大小
#define SAMPLE_SIZE SDL_AUDIO_BITSIZE(SAMPLE_FORMAT)
//#define SAMPLE_SIZE (SAMPLE_FORMAT & SDL_AUDIO_MASK_BITSIZE)
//#define SAMPLE_SIZE (SAMPLE_FORMAT & 0xFF)
//#define SAMPLE_SIZE 16
// 声道数
#define CHANNELS


// 音频缓冲区的样本数量
#define SAMPLES 1024
// 每个样本占用多少个字节
#define BYTES_PER_SAMPLE ((SAMPLE_SIZE * CHANNELS) / 8)
// 文件缓冲区的大小
#define BUFFER_SIZE (SAMPLES * BYTES_PER_SAMPLE)
//#define BUFFER_SIZE 4096

// 字节率
//#define



PlayThread::PlayThread(QObject *parent) : QThread(parent) {
    connect(this, &PlayThread::finished,
            this, &PlayThread::deleteLater);
}

PlayThread::~PlayThread() {

    disconnect();
    requestInterruption();
    quit();
    wait();

    qDebug() << this << "析构了";
}


 //int bufferLen;
//char *bufferData;

// 利用结构体，取代上面的bufferLen和bufferData
typedef struct {
    int len;
    int pullLen = 0; // 缓冲区每次拉取的数据
    char *data = nullptr;
} AudioBuffer;


// 等待音频设备回调（会回调多次）
// Uint8 *stream：需要往stream中填充PCM数据
// int len：希望填充的大小 samples * formate * channels / 8
void pull_audio_data(void *userdata, Uint8 *stream, int len) {
    // 清空stream(静音处理)
    SDL_memset(stream, 0, len);

    // 取出AudiopBuffer
    AudioBuffer *buffer = (AudioBuffer *)userdata;

    // 文件数据还没准备好
    if (buffer->len <= 0) return;

    // 取len 和 bufferLen的最小值 （为了保证数据安全，防止指针越界）
    buffer->pullLen = (len > buffer->len) ? buffer->len : len;

    // 填充数据 unsigned char == Uint8保证一个字节
    SDL_MixAudio(stream,
                 (Uint8 *)buffer->data,
                 buffer->pullLen, // 缓冲区每次拉取的数据 pullLen
                 SDL_MIX_MAXVOLUME);
    buffer->data += buffer->pullLen;
    buffer->len -= buffer->pullLen;
}

/**
  SDL播放音频有2中模式：
  Push(推)：【程序】主动推送数据给【音频设备】
  Pull(拉)：【音频设备】主动向【程序】拉取数据
 */
void PlayThread::run() {
    // 初始化子系统
    if (SDL_Init(SDL_INIT_AUDIO)) { // SDL_Init(SDL_INIT_AUDIO) == 0 成功
        qDebug() << "SDL_Init error" << SDL_GetError();
        return;
    }

    // 音频参数
    SDL_AudioSpec spec;
    spec.freq = SAMPLE_RATE;            // 采样率
    spec.channels = CHANNELS;           // 声道数
    spec.format = SAMPLE_FORMAT;        // 采样格式 s16le
    spec.samples = SAMPLES;             // 音频缓冲区的样本数量（必须是2的幂次）
    spec.callback = pull_audio_data;    // 回调
    // 传递给回调的参数
    AudioBuffer buffer;
    spec.userdata = &buffer;

    // 打开设备
    if (SDL_OpenAudio(&spec, nullptr)) {
        qDebug() << "SDL_OpenAudio error" << SDL_GetError();
        // 清除所有的子系统
        SDL_Quit();
        return;
    }

    // 打开文件
    QFile file(FILENAME);
    if (!file.open(QFile::ReadOnly)) {
        qDebug() << "file open error" << SDL_GetError();
        // 关闭设备
        SDL_CloseAudio();
        // 清除所有的子系统
        SDL_Quit();
    }

    // 开始播放(0取消暂停)
    SDL_PauseAudio(0);

    // 存放从文件中读取的数据 数组
//    char data[BUFFER_SIZE];
    Uint8 data[BUFFER_SIZE];
    while (!isInterruptionRequested()) {

        // 只要从文件中读取的音频数据，还没有填充完毕，就跳过
        if (buffer.len > 0) continue;

//        buffer.len = file.read(data, BUFFER_SIZE);
        buffer.len = file.read((char *)data, BUFFER_SIZE);

        // 文件数据已经读取完毕
        if (buffer.len <= 0) {
            // 样本的数量 = 剩余字节数 / 每个样本的字节数
            int samples = buffer.pullLen / BYTES_PER_SAMPLE;
            // 样本数量/每秒处理的样本数
            int ms = samples * 1000 / SAMPLE_RATE;
            SDL_Delay(ms);
            qDebug() << ms;
            break;
        };

        // 读取到了文件数据
        buffer.data = (char *)data;
    }

    // 关闭文件
    file.close();

    // 关闭设备
    SDL_CloseAudio();

    // 清除所有的子系统
    SDL_Quit();
}
