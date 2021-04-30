#include "../Headers/mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("Video Minesweeper");

    w.show();
    return a.exec();
}
