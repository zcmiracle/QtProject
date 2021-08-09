#include "ffmpegutil.h"
#include <QFile>
#include <QDebug>

FFmpegUtil::FFmpegUtil()
{

}

void FFmpegUtil::pcm2wav(WAVHeader &header,
                         const char *pcmFilename,
                         const char *wavFilename) {

    // 打开pcm文件
    QFile pcmFile(pcmFilename);

    // 打开文件
    // WriteOnly：只写模式，如果文件不存在，创建文件。如果文件存在，清空文件内容
    if (!pcmFile.open(QFile::ReadOnly)) {
        qDebug() << "文件打开失败" << pcmFilename;
        return;
    }

    header.dataChunkDataSize = pcmFile.size();
    header.riffChunkDataSize = header.dataChunkDataSize + sizeof(WAVHeader) - 8;

    // 打开wav文件
    QFile wavFile(wavFilename);

    // 打开文件
    // WriteOnly：只写模式，如果文件不存在，创建文件。如果文件存在，清空文件内容
    if (!wavFile.open(QFile::WriteOnly)) {
        qDebug() << "文件打开失败" << wavFilename;

        pcmFile.close();
        return;
    }

    // 写入头部
    wavFile.write((const char *) &header, sizeof(WAVHeader));

    // 写入pcm数据
    char buff[1024];
    int size;
    while ((size = pcmFile.read(buff, sizeof (buff))) > 0) {
        wavFile.write(buff, size);
    }

    // 关闭文件
    pcmFile.close();
    wavFile.close();
}
