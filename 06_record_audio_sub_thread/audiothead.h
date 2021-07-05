#ifndef AUDIOTHEAD_H
#define AUDIOTHEAD_H

#include <QThread>

// Audio 继承 QThread
class AudioThead : public QThread {

public:
    explicit AudioThead(QObject *parent = nullptr);
    ~AudioThead();
    void setStop(bool stop);

private:
    void run();
    bool _stop = false;

signals:

};

#endif // AUDIOTHEAD_H
