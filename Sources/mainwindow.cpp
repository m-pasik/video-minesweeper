#include "../Headers/mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    pixmaps[0] = QPixmap(":/Resources/Textures/uncovered0.png");
    pixmaps[1] = QPixmap(":/Resources/Textures/uncovered1.png");
    pixmaps[2] = QPixmap(":/Resources/Textures/uncovered2.png");
    pixmaps[3] = QPixmap(":/Resources/Textures/uncovered3.png");
    pixmaps[4] = QPixmap(":/Resources/Textures/uncovered4.png");
    pixmaps[5] = QPixmap(":/Resources/Textures/uncovered5.png");
    pixmaps[6] = QPixmap(":/Resources/Textures/uncovered6.png");
    pixmaps[7] = QPixmap(":/Resources/Textures/uncovered7.png");
    pixmaps[8] = QPixmap(":/Resources/Textures/uncovered8.png");
    pixmaps[9] = QPixmap(":/Resources/Textures/uncoveredA.png");
    pixmaps[10] = QPixmap(":/Resources/Textures/uncoveredB.png");
    pixmaps[11] = QPixmap(":/Resources/Textures/uncoveredC.png");
    pixmaps[12] = QPixmap(":/Resources/Textures/uncoveredD.png");
    pixmaps[13] = QPixmap(":/Resources/Textures/coveredA.png");
    pixmaps[14] = QPixmap(":/Resources/Textures/coveredB.png");
    pixmaps[15] = QPixmap(":/Resources/Textures/coveredC.png");

    textures[0] = QPixmap(":/Resources/Textures/leftBorderA.png");
    textures[1] = QPixmap(":/Resources/Textures/rightBorderA.png");
    textures[2] = QPixmap(":/Resources/Textures/leftCorner.png");
    textures[3] = QPixmap(":/Resources/Textures/rightCorner.png");
    textures[4] = QPixmap(":/Resources/Textures/upMiddle.png");
    textures[5] = QPixmap(":/Resources/Textures/bottomBorder.png");
    textures[6] = QPixmap(":/Resources/Textures/leftBorderB.png");
    textures[7] = QPixmap(":/Resources/Textures/rightBorderB.png");
    textures[8] = QPixmap(":/Resources/Textures/frameA.png");
    textures[9] = QPixmap(":/Resources/Textures/frameA.png");

    numbers[0] = QPixmap(":/Resources/Textures/number0.png");
    numbers[1] = QPixmap(":/Resources/Textures/number1.png");
    numbers[2] = QPixmap(":/Resources/Textures/number2.png");
    numbers[3] = QPixmap(":/Resources/Textures/number3.png");
    numbers[4] = QPixmap(":/Resources/Textures/number4.png");
    numbers[5] = QPixmap(":/Resources/Textures/number5.png");
    numbers[6] = QPixmap(":/Resources/Textures/number6.png");
    numbers[7] = QPixmap(":/Resources/Textures/number7.png");
    numbers[8] = QPixmap(":/Resources/Textures/number8.png");
    numbers[9] = QPixmap(":/Resources/Textures/number9.png");
    numbers[10] = QPixmap(":/Resources/Textures/negativeSign.png");

    buttonIcons[0] = QIcon(":/Resources/Textures/button.png");
    buttonIcons[1] = QIcon(":/Resources/Textures/buttonPressed.png");
    buttonIcons[2] = QIcon(":/Resources/Textures/buttonScared.png");
    buttonIcons[3] = QIcon(":/Resources/Textures/buttonWin.png");
    buttonIcons[4] = QIcon(":/Resources/Textures/buttonDead.png");

    soundsList[0] = new QSound(":/Resources/Sounds/beep.wav");
    soundsList[1] = new QSound(":/Resources/Sounds/win.wav");
    soundsList[2] = new QSound(":/Resources/Sounds/loss.wav");

    icon = QIcon(":/Resources/Textures/icon.png");
    setWindowIcon(icon);

    cw = new QWidget(this);
    setCentralWidget(cw);
    cw->setStyleSheet("background-color: #ffffff");
    cw->show();

    QMenu *gameMenu = this->menuBar()->addMenu("Game");
    QAction *newAction = gameMenu->addAction((tr("&New")));
    newAction->setShortcuts(QKeySequence::New);
    connect(newAction, SIGNAL(triggered()), this, SLOT(restart()));
    gameMenu->addSeparator();
    begginer = gameMenu->addAction("Begginer");
    begginer->setCheckable(true);
    connect(begginer, SIGNAL(triggered()), this, SLOT(begginerSlot()));
    intermediate = gameMenu->addAction("Intermediate");
    intermediate->setCheckable(true);
    connect(intermediate, SIGNAL(triggered()), this, SLOT(intermediateSlot()));
    expert = gameMenu->addAction("Expert");
    expert->setCheckable(true);
    connect(expert, SIGNAL(triggered()), this, SLOT(expertSlot()));
    custom = gameMenu->addAction("Custom");
    custom->setCheckable(true);
    connect(custom, SIGNAL(triggered()), this, SLOT(customSlot()));
    gameMenu->addSeparator();
    marks = gameMenu->addAction("Marks (?)");
    marks->setCheckable(true);
    marks->setChecked(true);
    connect(marks, SIGNAL(triggered()), this, SLOT(marksSlot()));
    sound = gameMenu->addAction("Sound");
    sound->setCheckable(true);
    connect(sound, SIGNAL(triggered()), this, SLOT(soundSlot()));
    gameMenu->addSeparator();
    bestTimes = gameMenu->addAction("Best Times");
    connect(bestTimes, SIGNAL(triggered()), this, SLOT(bestTimesSlot()));
    gameMenu->addSeparator();
    exit = gameMenu->addAction("Exit");
    connect(exit, SIGNAL(triggered()), this, SLOT(close()));

    QMenu *videoMenu = this->menuBar()->addMenu("Video");
    QAction *openAction = videoMenu->addAction((tr("&Open")));
    openAction->setShortcuts(QKeySequence::Open);
    connect(openAction, SIGNAL(triggered()), this, SLOT(openVideo()));
    videoMenu->addSeparator();
    videoOnWin = videoMenu->addAction("Play on win");
    videoOnWin->setCheckable(true);
    videoOnLoss = videoMenu->addAction("Play on loss");
    videoOnLoss->setCheckable(true);
    videoMenu->addSeparator();
    QAction *playNow = videoMenu->addAction("Play now");
    connect(playNow, SIGNAL(triggered()), this, SLOT(playVideo()));

    customField = new QDialog(this);
    customField->setWindowTitle("Custom Field");
    customField->setFixedSize(QSize(195, 138));
    customField->setWindowIcon(icon);
    QLabel *heightLabel = new QLabel(customField);
    heightLabel->setText("Height:");
    heightLabel->move(15, 33);
    QLabel *widthLabel = new QLabel(customField);
    widthLabel->setText("Width:");
    widthLabel->move(20, 57);
    QLabel *minesLabel = new QLabel(customField);
    minesLabel->setText("Mines:");
    minesLabel->move(20, 82);
    heightText = new QLineEdit(customField);
    heightText->move(65, 33);
    heightText->setFixedSize(QSize(38, 20));
    widthText = new QLineEdit(customField);
    widthText->move(65, 57);
    widthText->setFixedSize(QSize(38, 20));
    minesText = new QLineEdit(customField);
    minesText->move(65, 81);
    minesText->setFixedSize(QSize(38, 20));
    QPushButton *okButton = new QPushButton(customField);
    okButton->move(120, 33);
    okButton->setFixedSize(QSize(60, 25));
    okButton->setText("OK");
    connect(okButton, SIGNAL(clicked()), this, SLOT(setCustom()));
    QPushButton *cancelButton = new QPushButton(customField);
    cancelButton->move(120, 76);
    cancelButton->setFixedSize(QSize(60, 25));
    cancelButton->setText("Cancel");
    connect(cancelButton, SIGNAL(clicked()), customField, SLOT(close()));

    fastestMineSweepers = new QDialog(this);
    fastestMineSweepers->setWindowTitle("Fastest Mine Sweepers");
    fastestMineSweepers->setFixedSize(QSize(290, 122));
    QLabel *begginerLabel = new QLabel(fastestMineSweepers);
    begginerLabel->setText("Begginer:");
    begginerLabel->move(16, 21);
    QLabel *intermediateLabel = new QLabel(fastestMineSweepers);
    intermediateLabel->setText("Intermediate:");
    intermediateLabel->move(16, 38);
    QLabel *expertLabel = new QLabel(fastestMineSweepers);
    expertLabel->setText("Expert:");
    expertLabel->move(16, 54);
    begginerTimeLabel = new QLabel(fastestMineSweepers);
    begginerTimeLabel->move(110, 21);
    begginerTimeLabel->setFixedWidth(75);
    intermediateTimeLabel = new QLabel(fastestMineSweepers);
    intermediateTimeLabel->move(110, 38);
    intermediateTimeLabel->setFixedWidth(75);
    expertTimeLabel = new QLabel(fastestMineSweepers);
    expertTimeLabel->move(110, 54);
    expertTimeLabel->setFixedWidth(75);
    begginerNameLabel = new QLabel(fastestMineSweepers);
    begginerNameLabel->move(200, 21);
    begginerNameLabel->setFixedWidth(75);
    intermediateNameLabel = new QLabel(fastestMineSweepers);
    intermediateNameLabel->move(200, 38);
    intermediateNameLabel->setFixedWidth(75);
    expertNameLabel = new QLabel(fastestMineSweepers);
    expertNameLabel->move(200, 54);
    expertNameLabel->setFixedWidth(75);
    QPushButton *resetScoresButton = new QPushButton(fastestMineSweepers);
    resetScoresButton->move(40, 90);
    resetScoresButton->setFixedSize(85, 25);
    resetScoresButton->setText("Reset Scores");
    connect(resetScoresButton, SIGNAL(clicked()), this, SLOT(resetScores()));
    QPushButton *okScoresButton = new QPushButton(fastestMineSweepers);
    okScoresButton->move(205, 90);
    okScoresButton->setFixedSize(QSize(50, 25));
    okScoresButton->setText("OK");
    connect(okScoresButton, SIGNAL(clicked()), fastestMineSweepers, SLOT(close()));

    highScoreWindow = new QDialog(this);
    highScoreWindow->setWindowTitle("High Score");
    highScoreWindow->setFixedSize(QSize(174, 200));
    highScoreWindow->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    highScoreText = new QLabel(highScoreWindow);
    highScoreText->move(10, 10);
    highScoreText->setFixedSize(QSize(154, 60));
    highScoreText->setAlignment(Qt::AlignCenter);
    playerName = new QLineEdit(highScoreWindow);
    playerName->move(20, 130);
    playerName->setFixedSize(QSize(134, 20));
    QPushButton *highScoreOkButton = new QPushButton(highScoreWindow);
    highScoreOkButton->move(62, 160);
    highScoreOkButton->setFixedSize(QSize(50, 25));
    highScoreOkButton->setText("OK");
    connect(highScoreOkButton, SIGNAL(clicked()), this, SLOT(updateScores()));

    loadSettings();

    count = 0;
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(tick()));
    play();
}

MainWindow::~MainWindow()
{
    QSettings settings("video-minesweeper", "settings");
    settings.setValue("position", pos());
    QSettings video("video-minesweeper", "video");
    video.setValue("file", file);
    video.setValue("onWin", videoOnWin->isChecked());
    video.setValue("onLoss", videoOnLoss->isChecked());
}

void MainWindow::loadSettings()
{
    QSettings settings("video-minesweeper", "settings");
    if (!settings.contains("marks"))
        settings.setValue("marks", true);
    if (!settings.contains("sounds"))
        settings.setValue("sounds", false);
    if (!settings.contains("sounds"))
        settings.setValue("sounds", false);
    if (!settings.contains("position"))
        settings.setValue("position", QPoint(0, 0));
    marks->setChecked(settings.value("marks").toBool());
    sound->setChecked(settings.value("sounds").toBool());
    move(settings.value("position").toPoint());
    QSettings game("video-minesweeper", "game");
    if (!game.contains("mode") || !(game.value("mode").toInt() >= 0) || !(game.value("mode").toInt() <= 3))
        game.setValue("mode", 0);
    switch (game.value("mode").toInt())
    {
    case 0:
        setBegginer();
        break;
    case 1:
        setIntermediate();
        break;
    case 2:
        setExpert();
        break;
    case 3:
        if (!game.contains("width"))
            game.setValue("width", 9);
        if (!game.contains("height"))
            game.setValue("height", 9);
        if (!game.contains("mines"))
            game.setValue("mines", 10);
        gameSettings[0] = game.value("width").toInt();
        gameSettings[1] = game.value("height").toInt();
        gameSettings[2] = game.value("mines").toInt();
        custom->setChecked(true);
        begginer->setChecked(false);
        intermediate->setChecked(false);
        expert->setChecked(false);
        break;
    default:
        gameMode = 0;
        gameSettings[0] = 9;
        gameSettings[1] = 9;
        gameSettings[2] = 10;
        break;
    }
    QSettings video("video-minesweeper", "video");
    if(video.contains("file"))
       file = video.value("file").toString();
    if(!video.contains("onWin"))
        video.setValue("onWin", false);
    if(!video.contains("onLoss"))
        video.setValue("onLoss", false);
    videoOnWin->setChecked(video.value("onWin").toBool());
    videoOnLoss->setChecked(video.value("onLoss").toBool());
}

void MainWindow::setBegginer()
{
    begginer->setChecked(true);
    intermediate->setChecked(false);
    expert->setChecked(false);
    custom->setChecked(false);
    gameMode = 0;
    gameSettings[0] = 9;
    gameSettings[1] = 9;
    gameSettings[2] = 10;
}

void MainWindow::setIntermediate()
{
    intermediate->setChecked(true);
    begginer->setChecked(false);
    expert->setChecked(false);
    custom->setChecked(false);
    gameMode = 1;
    gameSettings[0] = 16;
    gameSettings[1] = 16;
    gameSettings[2] = 40;
}

void MainWindow::setExpert()
{
    expert->setChecked(true);
    begginer->setChecked(false);
    intermediate->setChecked(false);
    custom->setChecked(false);
    gameMode = 2;
    gameSettings[0] = 30;
    gameSettings[1] = 16;
    gameSettings[2] = 99;
}

void MainWindow::begginerSlot()
{
    setBegginer();
    QSettings game("video-minesweeper", "game");
    game.setValue("mode", 0);
    game.setValue("width", 9);
    game.setValue("height", 9);
    game.setValue("mines", 10);
    restart();
}

void MainWindow::intermediateSlot()
{
    setIntermediate();
    QSettings game("video-minesweeper", "game");
    game.setValue("mode", 1);
    game.setValue("width", 16);
    game.setValue("height", 16);
    game.setValue("mines", 40);
    restart();
}

void MainWindow::expertSlot()
{
    setExpert();
    QSettings game("video-minesweeper", "game");
    game.setValue("mode", 2);
    game.setValue("width", 30);
    game.setValue("height", 16);
    game.setValue("mines", 99);
    restart();
}

void MainWindow::customSlot()
{
    heightText->setText(QString::number(gameSettings[1]));
    widthText->setText(QString::number(gameSettings[0]));
    minesText->setText(QString::number(gameSettings[2]));
    custom->setChecked(false);

    customField->exec();
}

void MainWindow::setCustom()
{
    custom->setChecked(true);
    begginer->setChecked(false);
    intermediate->setChecked(false);
    expert->setChecked(false);

    int h = heightText->text().toInt();
    int w = widthText->text().toInt();
    int m = minesText->text().toInt();

    if (w < 9)
        w = 9;
    else if (w > 50)
        w = 50;
    if (h < 9)
        h = 9;
    else if (h > 50)
        h = 50;
    if (m < 10)
        m = 10;
    else if (m > (int)(3.0 / 4.0 * h * w))
        m = (int)(3.0 / 4.0 * h * w);

    gameSettings[0] = w;
    gameSettings[1] = h;
    gameSettings[2] = m;

    gameMode = 3;
    QSettings game("video-minesweeper", "game");
    game.setValue("mode", 3);
    game.setValue("width", w);
    game.setValue("height", h);
    game.setValue("mines", m);

    customField->close();
    restart();
}

void MainWindow::marksSlot()
{
    QSettings settings("video-minesweeper", "settings");
    settings.setValue("marks", marks->isChecked());
    mtx->marks = marks->isChecked();
}

void MainWindow::soundSlot()
{
    QSettings settings("video-minesweeper", "settings");
    settings.setValue("sounds", sound->isChecked());
    sounds = sound->isChecked();
}

void MainWindow::resetScores()
{
    QSettings scores("video-minesweeper", "scores");
    scores.setValue("begginerTime", 999);
    scores.setValue("begginerName", "Anonymous");
    scores.setValue("intermediateTime", 999);
    scores.setValue("intermediateName", "Anonymous");
    scores.setValue("expertTime", 999);
    scores.setValue("expertName", "Anonymous");
    loadScores();
}

void MainWindow::loadScores()
{
    QSettings scores("video-minesweeper", "scores");
    if (!scores.contains("begginerTime"))
        scores.setValue("begginerTime", 999);
    if (!scores.contains("begginerName"))
        scores.setValue("begginerName", "Anonymous");
    if (!scores.contains("intermediateTime"))
        scores.setValue("intermediateTime", 999);
    if (!scores.contains("intermediateName"))
        scores.setValue("intermediateName", "Anonymous");
    if (!scores.contains("expertTime"))
        scores.setValue("expertTime", 999);
    if (!scores.contains("expertName"))
        scores.setValue("expertName", "Anonymous");
    begginerTimeLabel->setText(scores.value("begginerTime").toString() + " seconds");
    begginerNameLabel->setText(scores.value("begginerName").toString());
    intermediateTimeLabel->setText(scores.value("intermediateTime").toString() + " seconds");
    intermediateNameLabel->setText(scores.value("intermediateName").toString());
    expertTimeLabel->setText(scores.value("expertTime").toString() + " seconds");
    expertNameLabel->setText(scores.value("expertName").toString());
}

void MainWindow::updateScores()
{
    QSettings scores("video-minesweeper", "scores");
    switch (gameMode)
    {
    case 0:
        scores.setValue("begginerTime", time);
        scores.setValue("begginerName", playerName->text());
        break;
    case 1:
        scores.setValue("intermediateTime", time);
        scores.setValue("intermediateName", playerName->text());
        break;
    case 2:
        scores.setValue("expertTime", time);
        scores.setValue("expertName", playerName->text());
    default:
        break;
    }
    highScoreWindow->close();
}

void MainWindow::bestTimesSlot()
{
    loadScores();
    fastestMineSweepers->exec();
}

void MainWindow::openVideo()
{
    file = QFileDialog::getOpenFileName(this, tr("Open Video"), QDir::homePath(), "");
    if (file != "")
    {
        restart();
    }
}

void MainWindow::playVideo()
{
    mtx->videoFile = file;
    mtx->playVideo();
}

void MainWindow::play()
{
    int w = gameSettings[0];
    int h = gameSettings[1];
    int c = gameSettings[2];
    sounds = sound->isChecked();
    count = 6 + 2 * w + 2 * h;
    elements = new QLabel *[count];
    for (int i = 0; i < count; i++)
        elements[i] = NULL;
    mtx = new Matrix(cw, pixmaps, w, h, c);
    mtx->marks = marks->isChecked();
    mtx->videoFile = file;
    connect(mtx, SIGNAL(won()), this, SLOT(won()));
    connect(mtx, SIGNAL(lost()), this, SLOT(lost()));
    connect(mtx, SIGNAL(start()), this, SLOT(start()));
    connect(mtx, SIGNAL(pressed()), this, SLOT(mtxPressed()));
    connect(mtx, SIGNAL(released()), this, SLOT(mtxReleased()));
    connect(mtx, SIGNAL(mineUpdate()), this, SLOT(mineUpdate()));
    mtx->move(12, 56);
    mtx->show();
    setFixedSize(16 * w + 20, 16 * h + 64 + this->menuBar()->height());
    QLabel *leftBorderA = new QLabel(cw);
    leftBorderA->setPixmap(textures[0]);
    leftBorderA->setFixedSize(9, 52);
    leftBorderA->move(3, 4);
    leftBorderA->show();
    elements[0] = leftBorderA;
    QLabel *rightBorderA = new QLabel(cw);
    rightBorderA->setPixmap(textures[1]);
    rightBorderA->setFixedSize(9, 52);
    rightBorderA->move(width() - 8, 4);
    rightBorderA->show();
    elements[1] = rightBorderA;
    QLabel *leftCorner = new QLabel(cw);
    leftCorner->setPixmap(textures[2]);
    leftCorner->setFixedSize(9, 9);
    leftCorner->move(3, height() - 8 - this->menuBar()->height());
    leftCorner->show();
    elements[2] = leftCorner;
    QLabel *rightCorner = new QLabel(cw);
    rightCorner->setPixmap(textures[3]);
    rightCorner->setFixedSize(9, 9);
    rightCorner->move(width() - 8, height() - 8 - this->menuBar()->height());
    rightCorner->show();
    elements[3] = rightCorner;
    for (int i = 0; i < w; i++)
    {
        QLabel *upMiddle = new QLabel(cw);
        upMiddle->setPixmap(textures[4]);
        upMiddle->setFixedSize(16, 52);
        upMiddle->move(i * 16 + 12, 4);
        upMiddle->show();
        elements[4 + i * 2] = upMiddle;
        QLabel *bottomBorder = new QLabel(cw);
        bottomBorder->setPixmap(textures[5]);
        bottomBorder->setFixedSize(16, 9);
        bottomBorder->move(i * 16 + 12, height() - 8 - this->menuBar()->height());
        bottomBorder->show();
        elements[5 + i * 2] = bottomBorder;
    }
    for (int i = 0; i < h; i++)
    {
        QLabel *leftBorderB = new QLabel(cw);
        leftBorderB->setPixmap(textures[6]);
        leftBorderB->setFixedSize(9, 16);
        leftBorderB->move(3, i * 16 + 56);
        leftBorderB->show();
        elements[4 + w * 2 + i * 2] = leftBorderB;
        QLabel *rightBorderB = new QLabel(cw);
        rightBorderB->setPixmap(textures[7]);
        rightBorderB->setFixedSize(9, 16);
        rightBorderB->move(width() - 8, i * 16 + 56);
        rightBorderB->show();
        elements[5 + w * 2 + i * 2] = rightBorderB;
    }
    QLabel *frameA0 = new QLabel(cw);
    frameA0->setPixmap(textures[8]);
    frameA0->setFixedSize(41, 25);
    frameA0->move(16, 16);
    frameA0->show();
    elements[count - 2] = frameA0;
    QLabel *frameA1 = new QLabel(cw);
    frameA1->setPixmap(textures[9]);
    frameA1->setFixedSize(41, 25);
    frameA1->move(width() - 55, 16);
    frameA1->show();
    elements[count - 1] = frameA1;
    for (int i = 0; i < 3; i++)
    {
        QLabel *numberA = new QLabel(cw);
        numberA->setPixmap(numbers[0]);
        numberA->setFixedSize(13, 23);
        numberA->move(17 + 13 * i, 17);
        numberA->show();
        numberLabels[i] = numberA;
        QLabel *numberB = new QLabel(cw);
        numberB->setPixmap(numbers[0]);
        numberB->setFixedSize(13, 23);
        numberB->move(width() - 54 + 13 * i, 17);
        numberB->show();
        numberLabels[i + 3] = numberB;
    }
    time = 0;
    timer->stop();
    mineUpdate();
    button = new QPushButton(cw);
    button->setIcon(buttonIcons[0]);
    button->setIconSize(QSize(26, 26));
    button->setFixedSize(26, 26);
    button->setStyleSheet("QPushButton:focus {border: none; outline: none;}");
    button->move(width() / 2 - 13, 16);
    button->show();
    buttonState = 0;
    connect(button, SIGNAL(pressed()), this, SLOT(btnPressed()));
    connect(button, SIGNAL(clicked()), this, SLOT(restart()));
    connect(button, SIGNAL(released()), this, SLOT(btnReleased()));
}

void MainWindow::btnPressed()
{
    button->setIcon(buttonIcons[1]);
}

void MainWindow::btnReleased()
{
    button->setIcon(buttonIcons[0]);
    switch (buttonState)
    {
    case 0:
        button->setIcon(buttonIcons[0]);
        break;
    case 1:
        button->setIcon(buttonIcons[3]);
        break;
    case 2:
        button->setIcon(buttonIcons[4]);
        break;
    default:
        break;
    }
}

void MainWindow::restart()
{
    delete mtx;
    for (int i = 0; i < count; i++)
    {
        if (elements[i])
        {
            delete elements[i];
        }
    }
    for (int i = 0; i < 6; i++)
        if (numberLabels[i])
            delete numberLabels[i];
    delete elements;
    delete button;
    play();
}

void MainWindow::mineUpdate()
{
    int num = mtx->count - mtx->marked;
    if (num > 999)
        num = 999;
    int count = 0;
    int n = num;
    while (n != 0)
    {
        n = n / 10;
        ++count;
    }
    if (num < 0)
        count++;
    if (num == 0)
        count = 1;
    char text[count];
    sprintf(text, "%d", num);
    for (int i = 0; i < 3 && i < 3; i++)
    {
        numberLabels[i]->setPixmap(numbers[0]);
    }
    for (int i = 0; i < count; i++)
    {
        char str = text[count - i - 1];
        numberLabels[2 - i]->setPixmap(numbers[atoi(&str)]);
    }
    if (num < 0)
        numberLabels[0]->setPixmap(numbers[10]);
}

void MainWindow::start()
{
    timer->start(1000);
}

void MainWindow::tick()
{
    if (sounds)
        soundsList[0]->play();

    if (time < 999)
        time++;
    int num = time;
    int count = 0;
    int n = num;
    while (n != 0)
    {
        n = n / 10;
        ++count;
    }
    if (num == 0)
        count = 1;
    char text[count];
    sprintf(text, "%d", num);
    for (int i = 3; i < 6; i++)
    {
        numberLabels[i]->setPixmap(numbers[0]);
    }
    for (int i = 0; i < count; i++)
    {
        char str = text[count - i - 1];
        numberLabels[3 + 2 - i]->setPixmap(numbers[atoi(&str)]);
    }
}

void MainWindow::won()
{
    if (sounds)
        soundsList[1]->play();
    timer->stop();
    buttonState = 1;
    button->setIcon(buttonIcons[3]);
    QSettings scores("video-minesweeper", "scores");
    loadScores();
    playerName->setText("Anonymous");
    switch (gameMode)
    {
    case 0:
        if (time < scores.value("begginerTime").toInt())
        {
            highScoreText->setText("You have the fastest time\n for begginer level.\nPlease enter your name.");
            highScoreWindow->exec();
        }
        break;
    case 1:
        if (time < scores.value("intermediateTime").toInt())
        {
            highScoreText->setText("You have the fastest time\n for intermediate level.\nPlease enter your name.");
            highScoreWindow->exec();
        }
        break;
    case 2:
        if (time < scores.value("expertTime").toInt())
        {
            highScoreText->setText("You have the fastest time\n for expert level.\nPlease enter your name.");
            highScoreWindow->exec();
        }
    default:
        break;
    }
    if (videoOnWin->isChecked())
        playVideo();
}

void MainWindow::lost()
{
    if (sounds)
        soundsList[2]->play();
    timer->stop();
    buttonState = 2;
    button->setIcon(buttonIcons[4]);
    if (videoOnLoss->isChecked())
        playVideo();
}

void MainWindow::mtxPressed()
{
    button->setIcon(buttonIcons[2]);
}

void MainWindow::mtxReleased()
{
    button->setIcon(buttonIcons[0]);
}
