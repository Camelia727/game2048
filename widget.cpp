#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
    , changed(false)
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
    setWindowTitle("2048!!!!!");
    setWindowIcon(QIcon(":/pics/pics/icon.png"));
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

    menu = new QWidget(this);
    menu->setFixedSize(400, 150);
    menu->setGeometry(50, 100, 400, 150);
    menu->setStyleSheet(QString("background-color:%1").arg(mainbackColor.name()));
    menu->hide();

    recallBtn = new Button("撤回", this);
    menuBtn = new Button("菜单", this);
    themeBtn = new Button("主题", menu);
    resetBtn = new Button("重置", menu);
    returnBtn = new Button("返回", menu);
    exitBtn = new Button("退出", menu);
    volumnSlider = new VolumnSlider(menu);

    recallBtn->setGeometry(258, 183, 78, 51);
    menuBtn->setGeometry(356, 183, 78, 51);
    themeBtn->setGeometry(17, 83, 78, 51);
    resetBtn->setGeometry(113, 83, 78, 51);
    returnBtn->setGeometry(209, 83, 78, 51);
    exitBtn->setGeometry(305, 83, 78, 51);
    volumnSlider->setGeometry(16, 16, 400, 50);

    bgms = {QUrl("qrc:/bgms/bgm/Alone.mp3"),
            QUrl("qrc:/bgms/bgm/April 11th.mp3"),
            QUrl("qrc:/bgms/bgm/autumn.mp3"),
            QUrl("qrc:/bgms/bgm/Classroom at dusk.mp3"),
            QUrl("qrc:/bgms/bgm/Night town.mp3"),
            QUrl("qrc:/bgms/bgm/Savage Love.mp3"),
            QUrl("qrc:/bgms/bgm/Shelter.mp3")
    };
    grids = QList<QList<NumBlock*>>(4, QList<NumBlock*>(4, nullptr));
    pregrids = QList<QList<NumBlock*>>(4, QList<NumBlock*>(4, nullptr));
    numbers = QList<QList<int>>(4, QList<int>(4, 0));
    prenumbers = QList<QList<int>>(4, QList<int>(4, 0));

    int index = QRandomGenerator::global()->bounded(bgms.size());
    player->setSource(bgms[index]);
    player->setAudioOutput(audio);
    audio->setVolume(1);
    player->play();
    connect(player, &QMediaPlayer::mediaStatusChanged, this, &Widget::playBgm);
    connect(durationTimer, &QTimer::timeout, this, &Widget::acceptMove);
    connect(recallBtn, &Button::clicked, this, &Widget::recall);
    connect(menuBtn, &Button::clicked, this, &Widget::openMenu);
    connect(themeBtn, &Button::clicked, this, &Widget::changeTheme);
    connect(resetBtn, &Button::clicked, this, &Widget::reset);
    connect(returnBtn, &Button::clicked, this, &Widget::closeMenu);
    connect(exitBtn, &Button::clicked, this, &Widget::exit);
    connect(volumnSlider, &VolumnSlider::valueChanged, this, &Widget::changeVolumn);
    createGrid();
    createGrid();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::moveUp()
{
    changed = true;
    QList<QList<QPoint>> moves;
    for (int x = 0; x < 4; x++){
        QList<QPoint> move;
        for (int y = 1; y < 4; y++){
            if (numbers[x][y] != 0){
                for (int y_ = y-1; y_ >= 0; y_--){
                    if (numbers[x][y_] != 0){
                        if (numbers[x][y_] == numbers[x][y] && !merge[x][y_]) {
                            moveGrid(x, y, x, y_);
                            merge[x][y_] = true;
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
    changed = true;
    QList<QList<QPoint>> moves;
    for (int x = 0; x < 4; x++){
        QList<QPoint> move;
        for (int y = 2; y >= 0; y--){
            if (numbers[x][y] != 0){
                for (int y_ = y+1; y_ < 4; y_++){
                    if (numbers[x][y_] != 0){
                        if (numbers[x][y_] == numbers[x][y] && !merge[x][y_]) {
                            moveGrid(x, y, x, y_);
                            merge[x][y_] = true;
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
    changed = true;
    QList<QList<QPoint>> moves;
    for (int y = 0; y < 4; y++){
        QList<QPoint> move;
        for (int x = 2; x >= 0; x--){
            if (numbers[x][y] != 0){
                for (int x_ = x+1; x_ < 4; x_++){
                    if (numbers[x_][y] != 0){
                        if (numbers[x_][y] == numbers[x][y] && !merge[x_][y]) {
                            moveGrid(x, y, x_, y);
                            merge[x_][y] = true;
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
    changed = true;
    QList<QList<QPoint>> moves;
    for (int y = 0; y < 4; y++){
        QList<QPoint> move;
        for (int x = 1; x < 4; x++){
            if (numbers[x][y] != 0){
                for (int x_ = x-1; x_ >= 0; x_--){
                    if (numbers[x_][y] != 0){
                        if (numbers[x_][y] == numbers[x][y] && !merge[x_][y]) {
                            moveGrid(x, y, x_, y);
                            merge[x_][y] = true;
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

void Widget::gamePauseOn()
{

}

void Widget::gamePauseOff()
{

}

void Widget::gameEnd()
{
    qDebug() << "gameEnd";
    saveArchive();
}

void Widget::saveArchive()
{
    QDir currentDir = QDir::current();
    // 构建文件名
    QString fileName = currentDir.filePath("historyfile.txt");

    // 创建QFile对象
    QFile file(fileName);

    // 检查文件是否存在
    if (!file.exists()) {
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            qWarning() << "Could not open file for writing:" << file.errorString();
            return;
        }
        QTextStream out(&file);
        // TO DO
    } else {
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
            qWarning() << "Could not open file for writing:" << file.errorString();
            return;
        }
        QTextStream out(&file);

    }

    // 关闭文件
    file.close();
}

void Widget::loadArchive()
{
    // 获取当前工作目录
    QDir currentDir = QDir::current();
    // 构建文件名
    QString fileName = currentDir.filePath("historyfile.txt");


    // 创建QFile对象并打开文件
    QFile file(fileName);
    if (!file.exists()){
        return;
    }

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        // 如果文件打开失败，打印错误信息
        qDebug() << "Cannot open file:" << fileName << "Error:" << file.errorString();
        return;
    }

    // 创建QTextStream对象，与QFile对象关联
    QTextStream in(&file);

    // TO DO


    // 关闭文件
    file.close();
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

void Widget::recall()
{
    if (!changed)
        return;
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            if (grids[i][j])
                grids[i][j]->hide();
        }
    }
    grids = pregrids;
    numbers = prenumbers;
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            if (numbers[i][j] != 0 && grids[i][j]){
                grids[i][j]->show();
                grids[i][j]->setNum(numbers[i][j]);
                grids[i][j]->setGeometry(66+96*i, 266+96*j, 80, 80);
            }
            else {
                if (grids[i][j] != nullptr){
                    grids[i][j]->hide();
                }
            }
        }
    }
    update();
}

void Widget::openMenu()
{
    menu->show();
    menu->raise();
}

void Widget::changeTheme()
{

}

void Widget::reset()
{
    for (NumBlock* grid : allgrids){
        grid->hide();
        grid->setParent(nullptr);
        delete grid;
        grid = nullptr;
    }
    updateCurScore(0);
    changed = false;
    allgrids.clear();
    grids = QList<QList<NumBlock*>>(4, QList<NumBlock*>(4, nullptr));
    pregrids = QList<QList<NumBlock*>>(4, QList<NumBlock*>(4, nullptr));
    numbers = QList<QList<int>>(4, QList<int>(4, 0));
    prenumbers = QList<QList<int>>(4, QList<int>(4, 0));
    createGrid();
}

void Widget::closeMenu()
{
    menu->hide();
}

void Widget::exit()
{
    saveArchive();
    close();
}

void Widget::changeVolumn(int volumn)
{
    double v = static_cast<double>(volumn) / 100.0;
    qDebug() << v;
    audio->setVolume(v);
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

    brush.setColor(mainbtnColor);
    painter.setBrush(brush);
    painter.drawRect(66, 116, 176, 118);
    painter.drawRect(258, 116, 176, 56);

    brush.setColor(gridColor);
    painter.setBrush(brush);
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            painter.drawRect(66+96*i, 266+96*j, 80, 80);

}

void Widget::keyPressEvent(QKeyEvent *event)
{
    if (moving){
        event->ignore();
        return;
    }
    switch (event->key()){
    case Qt::Key_Up:
        moving = true;
        updatePre();
        moveUp();
        break;
    case Qt::Key_Down:
        moving = true;
        updatePre();
        moveDown();
        break;
    case Qt::Key_Left:
        moving = true;
        updatePre();
        moveLeft();
        break;
    case Qt::Key_Right:
        moving = true;
        updatePre();
        moveRight();
        break;
    case Qt::Key_Escape:
        if (menuOpen){
            menuOpen = false;
            openMenu();
        }
        else {
            menuOpen = true;
            closeMenu();
        }
        break;
    default:
        break;
    }
    update();
}

void Widget::moveGrid(int x1, int y1, int x2, int y2)
{
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
    bool haveMove = false;
    moving = true;
    for (int y = 0; y < 4; y++){
        for (QPoint move : moves[y]){
            int x = move.x(), x_ = move.y();
            if (x == x_)
                continue;
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
                NumBlock* block = grids[x][y];
                updateCurScore(score);
                grids[x_][y]->setNum(num+1);
                QTimer::singleShot(180, this, [=](){block->hide();});
                grids[x][y] = nullptr;
            }
        }
    }
    return haveMove;
}

bool Widget::moveAnimationY(QList<QList<QPoint>> moves)
{
    bool haveMove = false;
    moving = true;
    for (int x = 0; x < 4; x++){
        for (QPoint move : moves[x]){
            int y = move.x(), y_ = move.y();
            if (y == y_)
                continue;
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
                NumBlock* block = grids[x][y];
                updateCurScore(score);
                grids[x][y_]->setNum(num+1);
                QTimer::singleShot(180, this, [=](){block->hide();});
                grids[x][y] = nullptr;
            }
        }
    }
    return haveMove;
}

void Widget::createGrid()
{
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
            QPropertyAnimation* createAnimation = new QPropertyAnimation(newBlock, "geometry", this);
            createAnimation->setDuration(80);
            createAnimation->setStartValue(QRect(81+96*x, 281+96*y, 50, 50));
            createAnimation->setEndValue(QRect(66+96*x, 266+96*y, 80, 80));
            createAnimation->start();
            numbers[x][y] = num;
            grids[x][y] = newBlock;
            allgrids.append(newBlock);
            break;
        }
    }
    merge = QList<QList<bool>>(4, QList<bool>(4, false));
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
    if (curScore > topScore){
        topScore = curScore;
        topscoreLabel->setText("Top：" + QString::number(topScore));
        update();
    }
}

void Widget::updatePre()
{
    QList<NumBlock*> pres;
    QList<NumBlock*> curs;
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            if (grids[i][j] != nullptr){
                curs.append(grids[i][j]);
            }
            if (pregrids[i][j] != nullptr){
                pres.append(pregrids[i][j]);
            }
        }
    }
    for (NumBlock* grid : pres){
        if (!curs.contains(grid)){
            grid->setParent(nullptr);
            allgrids.removeAll(grid);
            delete grid;
            grid = nullptr;
        }
    }
    pregrids = grids;
    prenumbers = numbers;
}

bool Widget::isEnd() const
{
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            if (i < 3){
                if (numbers[i][j] == numbers[i+1][j]){
                    return false;
                }
            }
            if (j < 3){
                if (numbers[i][j] == numbers[i][j+1]){
                    return false;
                }
            }
        }
    }
    return true;
}
