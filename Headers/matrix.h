#include <QLabel>
#include <QMouseEvent>
#include <opencv2/opencv.hpp>
#include <QVideoWidget>
#include <QMediaPlayer>
#include <QDebug>
#include <QTimer>
#include <chrono>
#include <iostream>
#include <string>
#include "tile.h"

class Matrix : public QWidget
{
    Q_OBJECT

private:
    QPixmap *pixmaps;
    bool **mines;
    Tile ***buttons;
    int uncovered;
    int w;
    int h;
    bool started;
    bool playing;

    QMediaPlayer *player;
    QTimer *videoTimer;
    double delay;
    cv::VideoCapture cap;
    cv::Mat frame;
    unsigned long int begin;
    int framesCount;
    void videoUncover(int x, int y);
    void getFrame();

    void finish(bool won);
    void genField(int x, int y, int w = 9, int h = 9, int c = 10);
    void genButtons(int w = 9, int h = 9);
    void uncover(int x, int y, bool isPlayer = true);
    void leftClicked(int x, int y);
    void rightClicked(int x, int y);
    void mouseOff();

public:
    Matrix(QWidget *parent, QPixmap *pixmaps, int w = 9, int h = 9, int c = 10);
    int count;
    int marked;
    bool marks;
    QString videoFile;
    void playVideo();

private slots:
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void videoTick();

signals:
    void start();
    void lost();
    void won();
    void mineUpdate();
    void pressed();
    void released();
};
