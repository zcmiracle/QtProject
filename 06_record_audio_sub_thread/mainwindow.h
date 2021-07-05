#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <audiothead.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {

    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // 转为槽
    void on_audioButton_clicked();

private:
    Ui::MainWindow *ui;
    AudioThead *_audioThread;

};
#endif // MAINWINDOW_H
