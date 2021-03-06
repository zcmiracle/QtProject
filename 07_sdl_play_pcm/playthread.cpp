#include "playthread.h"
#include <QDebug>
#include <QFile>
#include <SDL2/SDL.h>

// in.pcm 的采样率 采样大小 声道数 要和下面一样
#define FILENAME "/Users/xfb/Desktop/QT/QtProject/07_sdl_play_pcm/in.pcm"
// 采样率
#define SAMPLE_RATE 44100
// 采样大小
#define SAMPLE_SIZE 16
// 声道数
#define CHANNELS 2


// 音频缓冲区的样本数量
#define SAMPLES 1024
// 每个样本占用多少个字节
#define BYTES_PER_SAMPLE ((SAMPLE_SIZE * CHANNELS) / 8)
// 文件缓冲区的大小
//#define BUFFER_SIZE (SAMPLES * BYTES_PER_SAMPLE)
#define BUFFER_SIZE 4096

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


int bufferLen;
char *bufferData;


// 等待音频设备回调（会回调多次）
// Uint8 *stream：需要往stream中填充PCM数据
// int len：希望填充的大小 samples * formate * channels / 8
void pull_audio_data(void *userdata, Uint8 *stream, int len) {
    // 清空stream(静音处理)
    SDL_memset(stream, 0, len);

    // 文件数据还没准备好
    if (bufferLen <= 0) return;

    // 取len 和 bufferLen的最小值 （为了保证数据安全，防止指针越界）
    len = (len > bufferLen) ? bufferLen : len;

    // 填充数据 stream指针：往哪里填充数据
    // 从bufferData这个指针开始，读取len长度的数据填充到stream中
    SDL_MixAudio(stream, (Uint8 *)bufferData, len, SDL_MIX_MAXVOLUME);
    // += len指针会往右挪动len长度
    bufferData += len;
    bufferLen -= len;
}

/**
  SDL播放音频有2种模式：
  Push(推)：【程序】主动推送数据给【音频设备】
  Pull(拉)：【音频设备】主动向【程序】拉取数据
 */
void PlayThread::run() {
    // 初始化子系统
    if (SDL_Init(SDL_INIT_AUDIO)) { // SDL_Init(SDL_INIT_AUDIO) == 0 成功
        qDebug() << "SDL_Init error" << SDL_GetError();
        return;
    }

    // 音频参数 SAMPLE_RATE + CHANNELS + AUDIO_S16LSB 这三个参数要和pcm格式一样
    SDL_AudioSpec spec;
    spec.freq = SAMPLE_RATE;            // 采样率
    spec.channels = CHANNELS;           // 声道数
    spec.format = AUDIO_S16LSB;         // 采样格式 s16le
    spec.samples = 1024;                // 音频缓冲区的样本数量（必须是2的幂次）
    spec.callback = pull_audio_data;    // 回调
//    spec.userdata = 100;

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
    char data[BUFFER_SIZE];
    while (!isInterruptionRequested()) {

        // 只要从文件中读取的音频数据，还没有填充完毕，就跳过
        if (bufferLen > 0) continue;

        bufferLen = file.read(data, BUFFER_SIZE);

        // 文件数据已经读取完毕
        if (bufferLen <= 0) break;

        // 读取到了文件数据
        bufferData = data;

//        // 等待音频数据填充完毕
//        // 只要音频数据还没有填充完毕，就Delay(sleep)
//        while (bufferLen > 0) { // 只要 bufferLen <= 0 重新从文件中读取数据 file.read(data, BUFFER_SIZE);
//            SDL_Delay(1);
//        }
    }

    // 关闭文件
    file.close();

    // 关闭设备
    SDL_CloseAudio();

    // 清除所有的子系统
    SDL_Quit();
}
