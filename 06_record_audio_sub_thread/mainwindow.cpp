#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {

    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui;
}

// 开始录音 button 点击
void MainWindow::on_audioButton_clicked() {

    if (!_audioThread) { // 如果点击了开始录音
        // 开启线程
        _audioThread = new AudioThead(this);
        _audioThread->start();

        connect(_audioThread, &AudioThead::finished, [this]() {
            _audioThread = nullptr;
            ui->audioButton->setText("开始录音");
        });

        ui->audioButton->setText("结束录音");
    } else { // 点击了结束录音
        // 结束线程

//        _audioThread->setStop(true);
        _audioThread->requestInterruption();
        _audioThread = nullptr;

        ui->audioButton->setText("开始录音");
    }

}

