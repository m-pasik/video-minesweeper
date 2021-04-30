#ifndef MATRIX_H
#define MATRIX_H

#include "../Headers/matrix.h"

Matrix::Matrix(QWidget *parent, QPixmap *pixmaps, int w, int h, int c) : QWidget(parent)
{
    this->pixmaps = pixmaps;
    this->w = w;
    this->h = h;
    count = c;
    marked = 0;

    started = false;
    playing = true;

    genButtons(w, h);
    setMouseTracking(true);

    player = new QMediaPlayer(this);
    videoTimer = new QTimer(this);
    connect(videoTimer, SIGNAL(timeout()), this, SLOT(videoTick()));
}

void Matrix::mouseMoveEvent(QMouseEvent *e)
{
    if (!playing)
        return;
    if (e->buttons() == Qt::LeftButton && e->x() > 0 && e->x() < 16 * w && e->y() > 0 && e->y() < 16 * h)
    {
        mouseOff();

        buttons[(int)(e->y() / 16)][(int)(e->x() / 16)]->mouseOn = true;

        if (buttons[(int)(e->y() / 16)][(int)(e->x() / 16)]->state == 0)
            buttons[(int)(e->y() / 16)][(int)(e->x() / 16)]->setPixmap(pixmaps[0]);
        else if (buttons[(int)(e->y() / 16)][(int)(e->x() / 16)]->state == 1)
            buttons[(int)(e->y() / 16)][(int)(e->x() / 16)]->setPixmap(pixmaps[12]);
    }
}

void Matrix::mousePressEvent(QMouseEvent *e)
{
    if (playing && e->button() == Qt::LeftButton)
        emit pressed();
    if (!playing)
        return;
    if (e->button() == Qt::LeftButton && e->x() > 0 && e->x() < 16 * w && e->y() > 0 && e->y() < 16 * h)
    {
        if (buttons[(int)(e->y() / 16)][(int)(e->x() / 16)]->state == 0)
            buttons[(int)(e->y() / 16)][(int)(e->x() / 16)]->setPixmap(pixmaps[0]);
        else if (buttons[(int)(e->y() / 16)][(int)(e->x() / 16)]->state == 1)
            buttons[(int)(e->y() / 16)][(int)(e->x() / 16)]->setPixmap(pixmaps[12]);
    }
}

void Matrix::mouseReleaseEvent(QMouseEvent *e)
{
    if (playing)
        emit released();
    mouseOff();
    if (e->x() > 0 && e->x() < 16 * w && e->y() > 0 && e->y() < 16 * h)
    {
        switch (e->button())
        {
        case Qt::LeftButton:
            leftClicked((int)(e->x() / 16), (int)(e->y() / 16));
            break;
        case Qt::RightButton:
            rightClicked((int)(e->x() / 16), (int)(e->y() / 16));
            break;
        default:
            break;
        }
    }
}

void Matrix::mouseOff()
{
    for (int y = 0; y < h; y++)
        for (int x = 0; x < w; x++)
            if (buttons[y][x]->mouseOn)
            {
                buttons[y][x]->mouseOn = false;
                if (buttons[y][x]->state == 0)
                    buttons[y][x]->setPixmap(pixmaps[13]);
                else if (buttons[y][(x)]->state == 1)
                    buttons[y][x]->setPixmap(pixmaps[15]);
            }
}

void Matrix::leftClicked(int x, int y)
{
    if (!playing)
        return;

    if (!started)
    {
        emit start();
        started = true;
        genField(x, y, w, h, count);
    }

    uncover(x, y);
}

void Matrix::rightClicked(int x, int y)
{
    if (!playing)
        return;

    switch (buttons[y][x]->state)
    {
    case 0:
        buttons[y][x]->state = 3;
        buttons[y][x]->setPixmap(pixmaps[14]);
        marked++;
        break;
    case 3:
        if (marks)
        {
            buttons[y][x]->state = 1;
            buttons[y][x]->setPixmap(pixmaps[15]);
        }
        else
        {
            buttons[y][x]->state = 0;
            buttons[y][x]->setPixmap(pixmaps[13]);
        }
        marked--;
        break;
    case 1:
        buttons[y][x]->state = 0;
        buttons[y][x]->setPixmap(pixmaps[13]);
        break;
    default:

        break;
    }
    emit mineUpdate();
}

void Matrix::uncover(int tx, int ty, bool isPlayer)
{
    if (buttons[ty][tx]->state > 1 && isPlayer)
        return;
    if (buttons[ty][tx]->state == 2)
        return;
    buttons[ty][tx]->state = 2;

    if (mines[ty][tx])
    {
        buttons[ty][tx]->setPixmap(pixmaps[9]);
        finish(false);
    }
    else
    {
        int c = 0;

        for (int y = ty - 1; y <= ty + 1; y++)
            for (int x = tx - 1; x <= tx + 1; x++)
                if (y >= 0 && y < h && x >= 0 && x < w && (x != tx || y != ty) && mines[y][x])
                    c++;

        buttons[ty][tx]->setPixmap(pixmaps[c]);

        uncovered++;
        if (uncovered >= w * h - count)
        {
            finish(true);
        }

        if (c == 0)
            for (int y = ty - 1; y <= ty + 1; y++)
                for (int x = tx - 1; x <= tx + 1; x++)
                    if (y >= 0 && y < h && x >= 0 && x < w && !(x == tx && y == ty))
                        uncover(x, y, false);
    }
}

void Matrix::genField(int x, int y, int w, int h, int c)
{
    uncovered = 0;
    srand((unsigned)time(NULL));
    mines = new bool *[h];
    for (int i = 0; i < h; ++i)
    {
        mines[i] = new bool[w];
        for (int j = 0; j < w; j++)
            mines[i][j] = 0;
    }
    int i = 0;
    while (i < c)
    {
        int randx = rand() % w;
        int randy = rand() % h;
        if (!mines[randy][randx] && (randx > x + 1 || randx < x - 1 || randy > y + 1 || randy < y - 1))
        {
            mines[randy][randx] = 1;
            i++;
        }
    }
}

void Matrix::genButtons(int w, int h)
{
    int size = 16;
    resize(size * w, size * h);

    buttons = new Tile **[h];
    for (int y = 0; y < h; y++)
    {
        buttons[y] = new Tile *[w];
        for (int x = 0; x < w; x++)
        {
            Tile *btn = new Tile(this, x, y);
            btn->setPixmap(pixmaps[13]);
            btn->setFixedSize(size, size);
            btn->move(size * x, size * y);
            btn->state = 0;
            buttons[y][x] = btn;
        }
    }
}

void Matrix::finish(bool win)
{
    playing = false;
    if (win)
    {
        emit won();
    }
    else
    {
        for (int y = 0; y < h; y++)
            for (int x = 0; x < w; x++)
                if (mines[y][x])
                {
                    if (buttons[y][x]->state == 0)
                        buttons[y][x]->setPixmap(pixmaps[11]);
                }
                else if (buttons[y][x]->state == 3)
                {
                    buttons[y][x]->setPixmap(pixmaps[10]);
                }
        emit lost();
    }
}

void Matrix::playVideo()
{
    videoTimer->stop();
    player->stop();
    playing = false;
    cap = cv::VideoCapture(videoFile.toStdString());
    if (!cap.isOpened())
        return;

    mines = new bool *[h];
    for (int i = 0; i < h; ++i)
    {
        mines[i] = new bool[w];
        for (int j = 0; j < w; j++)
            mines[i][j] = 0;
    }
    player->setMedia(QUrl::fromLocalFile(videoFile));
    player->play();
    delay = 1 / cap.get(cv::CAP_PROP_FPS) * 1000;
    videoTimer->start(delay);
    framesCount = 0;
    marked = 0;
    begin = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

void Matrix::getFrame()
{
    cap >> frame;
    framesCount++;
}

void Matrix::videoTick()
{
    unsigned long int now = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    if (now - begin > (long unsigned int)(delay * framesCount))
    {
        for(int i = framesCount; i <= (now - begin) / delay; i++)
            getFrame();
    }
    else if (now - begin < (long unsigned int)(delay * framesCount))
    {
        return;
    }
    getFrame();

    if (frame.empty())
    {
        videoTimer->stop();
        cap.release();
        for (int y = 0; y < h; y++)
            for (int x = 0; x < w; x++)
                buttons[y][x]->setPixmap(pixmaps[13]);
        return;
    }
    cv::resize(frame, frame, cv::Size(w, h));
    count = 0;
    int p = 0;
    for (int y = 0; y < h; y++)
        for (int x = 0; x < w; x++)
        {
            int RGB[3] = {frame.at<cv::Vec3b>(y, x)[0], frame.at<cv::Vec3b>(y, x)[1], frame.at<cv::Vec3b>(y, x)[2]};
            int lightness = (RGB[0] + RGB[1] + RGB[2]) / 3;
            p++;
            if (lightness > 127)
            {
                mines[y][x] = true;
                count++;
            }
            else
                mines[y][x] = false;
        }
    for (int y = 0; y < h; y++)
        for (int x = 0; x < w; x++)
            videoUncover(x, y);
    emit mineUpdate();
}

void Matrix::videoUncover(int tx, int ty)
{
    if (mines[ty][tx])
    {
        buttons[ty][tx]->setPixmap(pixmaps[13]);
    }
    else
    {
        int c = 0;

        for (int y = ty - 1; y <= ty + 1; y++)
            for (int x = tx - 1; x <= tx + 1; x++)
                if (y >= 0 && y < h && x >= 0 && x < w && (x != tx || y != ty) && mines[y][x])
                    c++;

        buttons[ty][tx]->setPixmap(pixmaps[c]);
    }
}
#endif
