#include "mainwindow.h"
#include "ui_mainwindow.h"
// SDL跨平台C语言多媒体开发库
#include <SDL2/SDL.h>
#include <playthread.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void showVersion() {
    SDL_version version;
    SDL_VERSION(&version);
    // 打印版本号
    qDebug() << version.major << version.minor << version.patch;
}

void MainWindow::on_playButton_clicked()
{
    PlayThread *playThread = new PlayThread(this);
    playThread->start();
}

