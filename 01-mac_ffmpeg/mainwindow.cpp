#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    // 窗口标题设置
    setWindowTitle("主窗口");

    // 设置窗口大小
    resize(500, 500);

    // 设置窗口的固定大小
//    setFixedSize(600, 600);

    // 设置窗口的位置
    move(200, 200);

    ui->setupUi(this);


    /**

        1、【ffplay】 主要作用：播放音视频
        ffplay [options] input_file
            + options：参数
            + input_file：输入文件

        详细文档链接：https://ffmpeg.org/ffplay-all.html


        2、【ffmpeg】 主要作用：对音频进行编解码
        ffmpeg -i audio.mp3 audio2.wav

        输入命令ffmpeg时，可以看到ffmpeg命令的使用格式是：
        ffmpge arg1 arg2 -i arg3 arg4 arg5
            + arg1：全局参数
            + arg2：输入文件参数
            + arg3：输入文件
            + arg4：输出文件参数
            + arg5：输出文件


        3、【ffprobe】主要作用：查看音视频的参数信息
        ffprobe audio.mp3
        ffprobe [OPTIONS] [INPUT_FILE]
            + OPTIONS：参数
            + INPUT_FILE：输入文件


        4、【-hide_bannder】主要作用：参数可以隐藏一些冗余的描述信息
        ffprobe -hide_banner audio.mp3
        ffprobe audio.mp3


        5、【ffmpeg -devices】主要作用：查看当前平台的可用设备

        6、查看dshow支持的设备
            + dshow 是window平台
            + avfoundation 是mac平台

        mac 平台：ffmpeg -f avfoundation -list_devices true -i dummy
        window平台：ffmpeg -f dshow -list_devices true -i dummy

        -f dshow
            + dshow 支持的

        -list_devices true
            + 打印出所有的设备

        -i dummy 或 -i '' 或 -i ""
            + 立即退出

        【Mac打印】：ffmpeg -f avfoundation -list_devices true -i dummy
            [AVFoundation indev @ 0x7f99eee291c0] AVFoundation video devices:
            [AVFoundation indev @ 0x7f99eee291c0] [0] FaceTime高清摄像头（内建）
            [AVFoundation indev @ 0x7f99eee291c0] [1] Capture screen 0
            [AVFoundation indev @ 0x7f99eee291c0] [2] Capture screen 1
            [AVFoundation indev @ 0x7f99eee291c0] AVFoundation audio devices:
            [AVFoundation indev @ 0x7f99eee291c0] [0] Built-in Microphone

         7、【指定设备进行录音】
         使用外接的麦克风进行录音，最后生成一个wav文件
            ffmpeg -f dshow -i audio="xxx" out.wav

         在Mac上通过编号指定设备
            ffmpeg -f avfoundation -i :2 out.wav
                + :0表示使用0号音频设备
                + 0:2表示使用0号视频设备和2号音频设备

         8、【设置dshow参数】 或者 avfoundation的参数
         ffmpeg -h demuxer=dshow
         ffmpeg -h demuxer=avfoundation

         -sample_rate: 采样率
         -sample_size: 采样大小（位深度）
         -channels: 声道数
         -list_options: 列出特定设备支持的参数

         ffmpeg -f avfoundation -list_options true -i audio="麦克风阵列 (Realtek(R) Audio)"

      */

}

MainWindow::~MainWindow()
{
    delete ui;
}

