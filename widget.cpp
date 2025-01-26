#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
    , moving(false)
    , curScore(0)
    , topScore(0)
    , curscoreLabel(new QLabel(this))
    , topscoreLabel(new QLabel(this))
    , player(new QMediaPlayer(this))
    , audio(new QAudioOutput(this))
    , durationTimer(new QTimer(this))
{
    ui->setupUi(this);
    setFixedSize(500,750);
    backgroundColor.setRgb(0, 153, 153);
    mainbackColor.setRgb(51, 204, 204);
    mainbtnColor.setRgb(92, 213, 222);
    gridColor.setRgb(224, 224, 224, 80);
    gridblockColor.setRgb(117, 249, 253);
    gridbackColor.setRgb(185, 251, 255);
    backshadowColor.setRgb(0, 101, 108);
    mainshadowColor.setRgb(10, 171, 182);
    gridshadowColor.setRgb(5, 132, 137);
    durationTimer->setInterval(200);
    loadArchive();
    curscoreLabel->setGeometry(66, 116, 176, 118);
    topscoreLabel->setGeometry(258, 116, 176, 56);
    curscoreLabel->setStyleSheet("color:white;font-size:50px;font-weight:bold;font-family:'Segoe UI Black';");
    topscoreLabel->setStyleSheet("color:white;font-size:28px;font-weight:bold;font-family:'Segoe UI Black';");
    curscoreLabel->setAlignment(Qt::AlignCenter);
    topscoreLabel->setAlignment(Qt::AlignCenter);
    curscoreLabel->setText(QString::number(curScore));
    topscoreLabel->setText("Top：" + QString::number(topScore));

    bgms = {QUrl("qrc:/bgms/bgm/Alone.mp3"),
            QUrl("qrc:/bgms/bgm/April 11th.mp3"),
            QUrl("qrc:/bgms/bgm/autumn.mp3"),
            QUrl("qrc:/bgms/bgm/Classroom at dusk.mp3"),
            QUrl("qrc:/bgms/bgm/Night town.mp3"),
            QUrl("qrc:/bgms/bgm/Savage Love.mp3"),
            QUrl("qrc:/bgms/bgm/Shelter.mp3")
    };
    grids = QList<QList<NumBlock*>>(4, QList<NumBlock*>(4, nullptr));
    numbers = QList<QList<int>>(4, QList<int>(4, 0));

    int index = QRandomGenerator::global()->bounded(bgms.size());
    player->setSource(bgms[index]);
    player->setAudioOutput(audio);
    audio->setVolume(30);
    player->play();
    connect(player, &QMediaPlayer::mediaStatusChanged, this, &Widget::playBgm);
    connect(durationTimer, &QTimer::timeout, this, &Widget::acceptMove);
    createGrid();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::moveUp()
{
    QList<QList<QPoint>> moves;
    for (int x = 0; x < 4; x++){
        QList<QPoint> move;
        for (int y = 1; y < 4; y++){
            if (numbers[x][y] != 0){
                for (int y_ = y-1; y_ >= 0; y_--){
                    if (numbers[x][y_] != 0){
                        if (numbers[x][y_] == numbers[x][y]) {
                            moveGrid(x, y, x, y_);
                            move.append(QPoint(y, y_));
                            break;
                        }
                        else {
                            moveGrid(x, y, x, y_+1);
                            move.append(QPoint(y, y_+1));
                            break;
                        }
                    }
                    else{
                        if (y_ == 0){
                            moveGrid(x, y, x, 0);
                            move.append(QPoint(y, 0));
                            break;
                        }
                    }
                }
            }
        }
        moves.append(move);
    }
    if (moveAnimationY(moves))
        QTimer::singleShot(300, this, &Widget::createGrid);
    else
        moving = false;
}

void Widget::moveDown()
{
    QList<QList<QPoint>> moves;
    for (int x = 0; x < 4; x++){
        QList<QPoint> move;
        for (int y = 2; y >= 0; y--){
            if (numbers[x][y] != 0){
                for (int y_ = y+1; y_ < 4; y_++){
                    if (numbers[x][y_] != 0){
                        if (numbers[x][y_] == numbers[x][y]) {
                            moveGrid(x, y, x, y_);
                            move.append(QPoint(y, y_));
                            break;
                        }
                        else {
                            moveGrid(x, y, x, y_-1);
                            move.append(QPoint(y, y_-1));
                            break;
                        }
                    }
                    else{
                        if (y_ == 3){
                            moveGrid(x, y, x, 3);
                            move.append(QPoint(y, 3));
                            break;
                        }
                    }
                }
            }
        }
        moves.append(move);
    }
    if (moveAnimationY(moves))
        QTimer::singleShot(300, this, &Widget::createGrid);
    else
        moving = false;
}

void Widget::moveRight()
{
    QList<QList<QPoint>> moves;
    for (int y = 0; y < 4; y++){
        QList<QPoint> move;
        for (int x = 2; x >= 0; x--){
            if (numbers[x][y] != 0){
                for (int x_ = x+1; x_ < 4; x_++){
                    if (numbers[x_][y] != 0){
                        if (numbers[x_][y] == numbers[x][y]) {
                            moveGrid(x, y, x_, y);
                            move.append(QPoint(x, x_));
                            break;
                        }
                        else {
                            moveGrid(x, y, x_-1, y);
                            move.append(QPoint(x, x_-1));
                            break;
                        }
                    }
                    else{
                        if (x_ == 3){
                            moveGrid(x, y, 3, y);
                            move.append(QPoint(x, 3));
                            break;
                        }
                    }
                }
            }
        }
        moves.append(move);
    }
    if (moveAnimationX(moves))
        QTimer::singleShot(300, this, &Widget::createGrid);
    else
        moving = false;
}

void Widget::moveLeft()
{
    QList<QList<QPoint>> moves;
    for (int y = 0; y < 4; y++){
        QList<QPoint> move;
        for (int x = 1; x < 4; x++){
            if (numbers[x][y] != 0){
                for (int x_ = x-1; x_ >= 0; x_--){
                    if (numbers[x_][y] != 0){
                        if (numbers[x_][y] == numbers[x][y]) {
                            moveGrid(x, y, x_, y);
                            move.append(QPoint(x, x_));
                            break;
                        }
                        else {
                            moveGrid(x, y, x_+1, y);
                            move.append(QPoint(x, x_+1));
                            break;
                        }
                    }
                    else{
                        if (x_ == 0){
                            moveGrid(x, y, 0, y);
                            move.append(QPoint(x, 0));
                            break;
                        }
                    }
                }
            }
        }
        moves.append(move);
    }
    if (moveAnimationX(moves))
        QTimer::singleShot(300, this, &Widget::createGrid);
    else
        moving = false;
}

void Widget::gamePause()
{

}

void Widget::gameEnd()
{
    qDebug() << "gameEnd";
}

void Widget::saveArchive()
{

}

void Widget::loadArchive()
{

}

void Widget::newGame()
{
    saveArchive();
    updateTopScore();
    updateCurScore(0);
}

void Widget::playBgm(QMediaPlayer::MediaStatus status)
{
    if (status == QMediaPlayer::EndOfMedia || QMediaPlayer::NoMedia){
        qDebug() << "playbgm";
        int bgm_sum = bgms.size();
        int index = QRandomGenerator::global()->bounded(bgm_sum);
        player->setSource(bgms[index]);
        player->setAudioOutput(audio);
        audio->setVolume(30);
        player->play();
    }
}

void Widget::acceptMove()
{

}



void Widget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setPen(Qt::NoPen);

    QBrush brush(backgroundColor);
    painter.setBrush(brush);
    painter.drawRect(this->rect());

    brush.setColor(backshadowColor);
    painter.setBrush(brush);
    painter.drawRect(60,110,400,550);

    brush.setColor(mainbackColor);
    painter.setBrush(brush);
    painter.drawRect(50,100,400,150);

    brush.setColor(gridbackColor);
    painter.setBrush(brush);
    painter.drawRect(50,250,400,400);

    brush.setColor(mainshadowColor);
    painter.setBrush(brush);
    painter.drawRect(263, 188, 73, 46);
    painter.drawRect(361, 188, 73, 46);

    brush.setColor(mainbtnColor);
    painter.setBrush(brush);
    painter.drawRect(66, 116, 176, 118);
    painter.drawRect(258, 116, 176, 56);
    painter.drawRect(258, 183, 73, 46);
    painter.drawRect(356, 183, 73, 46);

    brush.setColor(gridColor);
    painter.setBrush(brush);
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            painter.drawRect(66+96*i, 266+96*j, 80, 80);

}

void Widget::keyPressEvent(QKeyEvent *event)
{
    if (moving || pausing){
        event->ignore();
        return;
    }
    switch (event->key()){
    case Qt::Key_Up:
        moving = true;
        moveUp();
        break;
    case Qt::Key_Down:
        moving = true;
        moveDown();
        break;
    case Qt::Key_Left:
        moving = true;
        moveLeft();
        break;
    case Qt::Key_Right:
        moving = true;
        moveRight();
        break;
    case Qt::Key_Escape:
        pausing = true;
        gamePause();
        break;
    default:
        break;
    }
    update();
}

void Widget::moveGrid(int x1, int y1, int x2, int y2)
{
    qDebug() << "movegrid";
    if (numbers[x1][y1] == 0)
        return;
    if (x1 == x2 && y1 == y2)
        return;
    if (numbers[x2][y2] == 0) {
        numbers[x2][y2] = numbers[x1][y1];
        numbers[x1][y1] = 0;
    }
    else if (numbers[x1][y1] == numbers[x2][y2]) {
        numbers[x2][y2]++;
        numbers[x1][y1] = 0;
    }
}

bool Widget::moveAnimationX(QList<QList<QPoint>> moves)
{
    qDebug() << "moveanimationx";
    bool haveMove = false;
    moving = true;
    for (int y = 0; y < 4; y++){
        for (QPoint move : moves[y]){
            int x = move.x(), x_ = move.y();
            if (x == x_)
                continue;
            qDebug() << "have move";
            haveMove = true;
            QPropertyAnimation* moveAnimation = new QPropertyAnimation(grids[x][y], "geometry", this);
            moveAnimation->setDuration(200);
            moveAnimation->setStartValue(QRect(66+96*x, 266+96*y, 80, 80));
            moveAnimation->setEndValue(QRect(66+96*x_, 266+96*y, 80, 80));
            moveAnimation->start();
            if (grids[x_][y] == nullptr) {
                grids[x_][y] = grids[x][y];
                grids[x][y] = nullptr;
            }
            else if (grids[x][y]->getNum() == grids[x_][y]->getNum()) {
                int num = grids[x][y]->getNum();
                int score = 2*pow(2, num);
                updateCurScore(score);
                grids[x_][y]->setNum(num+1);
                // QTimer::singleShot(200, this, [&](){grids[x][y]->hide();});
                grids[x][y]->hide();
                grids[x][y] = nullptr;
            }
        }
    }
    return haveMove;
}

bool Widget::moveAnimationY(QList<QList<QPoint>> moves)
{
    qDebug() << "moveanimationy";
    bool haveMove = false;
    moving = true;
    for (int x = 0; x < 4; x++){
        for (QPoint move : moves[x]){
            int y = move.x(), y_ = move.y();
            if (y == y_)
                continue;
            qDebug() << "have move";
            haveMove = true;
            QPropertyAnimation* moveAnimation = new QPropertyAnimation(grids[x][y], "geometry", this);
            moveAnimation->setDuration(200);
            moveAnimation->setStartValue(QRect(66+96*x, 266+96*y, 80, 80));
            moveAnimation->setEndValue(QRect(66+96*x, 266+96*y_, 80, 80));
            moveAnimation->start();
            if (grids[x][y_] == nullptr) {
                grids[x][y_] = grids[x][y];
                grids[x][y] = nullptr;
            }
            else if (grids[x][y]->getNum() == grids[x][y_]->getNum()) {
                int num = grids[x][y]->getNum();
                int score = 2*pow(2, num);
                updateCurScore(score);
                grids[x][y_]->setNum(num+1);
                grids[x][y]->hide();
                grids[x][y] = nullptr;
            }
        }
    }
    return haveMove;
}

void Widget::createGrid()
{
    qDebug() << "gridCreate";
    while (true){
        int pos = QRandomGenerator::global()->bounded(16);
        int x = pos / 4;
        int y = pos % 4;
        if (grids[x][y] == nullptr) {
            qDebug() << "x:" << x << "y:" << y << "\n*****";
            int num = QRandomGenerator::global()->bounded(10) < 9 ? 1 : 2;
            NumBlock* newBlock = new NumBlock(this);
            newBlock->setNum(num);
            newBlock->setTheme(gridshadowColor);
            newBlock->setGeometry(66+96*x, 266+96*y, 80, 80);
            newBlock->show();
            numbers[x][y] = num;
            grids[x][y] = newBlock;
            break;
        }
    }
    for (int i = 0; i < 4; i++){
        QList<int> line;
        for (int j = 0; j < 4; j++){
            if (grids[j][i] == nullptr)
                line.append(0);
            else
                line.append(grids[j][i]->getNum());
        }
        qDebug() << pow(2, line[0]) << " " << pow(2, line[1]) << " " << pow(2, line[2]) << " " << pow(2, line[3]);
    }
    bool full = true;
    for (int i = 0; i < 4; i++){
        if (!full)
            break;
        for (int j = 0; j < 4; j++){
            if (grids[i][j] == nullptr){
                full = false;
                break;
            }
        }
    }
    if (full && isEnd())
        gameEnd();
    else
        moving = false;
}

void Widget::updateCurScore(int score)
{
    qDebug() << "update curscore";
    if (score == 0){
        curScore = 0;
        curscoreLabel->setText("0");
    }
    else{
        curScore += score;
        curscoreLabel->setText(QString::number(curScore));
        updateTopScore();
    }
    update();
}

void Widget::updateTopScore()
{
    qDebug() << "update topscore";
    if (curScore > topScore){
        topScore = curScore;
        topscoreLabel->setText("Top：" + QString::number(topScore));
        update();
    }
}

bool Widget::isEnd() const
{
    return false;
}
