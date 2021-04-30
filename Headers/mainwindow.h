#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QMenuBar>
#include <QTimer>
#include <QSound>
#include <QLineEdit>
#include <QSettings>
#include <QDialog>
#include <QDebug>
#include <QFileDialog>
#include "matrix.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    QPixmap pixmaps[16];
    QPixmap textures[10];
    QPixmap numbers[11];
    QIcon buttonIcons[5];
    QSound *soundsList[3];
    bool sounds;
    QLabel *numberLabels[6];
    QLabel **elements;
    QPushButton *button;
    QIcon icon;
    QWidget *cw;
    Matrix *mtx;
    QTimer *timer;
    QMenu *gameMenu;
    QAction *newAction;
    QAction *begginer;
    QAction *intermediate;
    QAction *expert;
    QAction *custom;
    QAction *marks;
    QAction *sound;
    QAction *bestTimes;
    QAction *exit;
    QAction *videoOnWin;
    QAction *videoOnLoss;
    QDialog *customField;
    QDialog *fastestMineSweepers;
    QLineEdit *heightText;
    QLineEdit *widthText;
    QLineEdit *minesText;
    QLabel *begginerTimeLabel;
    QLabel *intermediateTimeLabel;
    QLabel *expertTimeLabel;
    QLabel *begginerNameLabel;
    QLabel *intermediateNameLabel;
    QLabel *expertNameLabel;
    QDialog *highScoreWindow;
    QLabel *highScoreText;
    QLineEdit *playerName;
    QString file;
    void loadScores();
    void loadSettings();
    int gameMode;
    int gameSettings[3];
    int buttonState;
    int time;
    int count;
    void play();
    void setBegginer();
    void setIntermediate();
    void setExpert();

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void btnPressed();
    void restart();
    void btnReleased();
    void mtxPressed();
    void mtxReleased();
    void mineUpdate();
    void begginerSlot();
    void intermediateSlot();
    void expertSlot();
    void customSlot();
    void bestTimesSlot();
    void setCustom();
    void marksSlot();
    void soundSlot();
    void updateScores();
    void resetScores();
    void openVideo();
    void playVideo();
    void start();
    void tick();
    void lost();
    void won();
};

#endif
