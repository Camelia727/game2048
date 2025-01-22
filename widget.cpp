#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
    , curScore(0)
    , topScore(0)
    , moving(false)
    , player(new QMediaPlayer(this))
    , audio(new QAudioOutput(this))
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

    grids = QList<QList<NumBlock*>>(4, QList<NumBlock*>(4, nullptr));
    createGrid();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::moveUp()
{
    for (int x = 0; x < 4; x++){
        for (int y = 1; y < 4; y++){
            if (grids[x][y] != nullptr){
                for (int y_ = y-1; y_ >= 0; y_--){
                    if (grids[x][y_] != nullptr){
                        if (grids[x][y_]->getNum() == grids[x][y]->getNum()) {
                            moveGrid(x, y, x, y_);
                            break;
                        }
                        else {
                            moveGrid(x, y, x, y_+1);
                            break;
                        }
                    }
                    else{
                        if (y_ == 0){
                            moveGrid(x, y, x, 0);
                            break;
                        }
                    }
                }
            }
        }
    }
}

void Widget::moveDown()
{
    for (int x = 0; x < 4; x++){
        for (int y = 2; y >= 0; y--){
            if (grids[x][y] != nullptr){
                for (int y_ = y+1; y_ < 4; y_++){
                    if (grids[x][y_] != nullptr){
                        if (grids[x][y_]->getNum() == grids[x][y]->getNum()) {
                            moveGrid(x, y, x, y_);
                            break;
                        }
                        else {
                            moveGrid(x, y, x, y_-1);
                            break;
                        }
                    }
                    else{
                        if (y_ == 3){
                            moveGrid(x, y, x, 3);
                            break;
                        }
                    }
                }
            }
        }
    }
}

void Widget::moveRight()
{
    for (int y = 0; y < 4; y++){
        for (int x = 2; x >= 0; x--){
            if (grids[x][y] != nullptr){
                for (int x_ = x+1; x_ < 4; x_++){
                    if (grids[x_][y] != nullptr){
                        if (grids[x_][y]->getNum() == grids[x][y]->getNum()) {
                            moveGrid(x, y, x_, y);
                            break;
                        }
                        else {
                            moveGrid(x, y, x_-1, y);
                            break;
                        }
                    }
                    else{
                        if (x_ == 3){
                            moveGrid(x, y, 3, y);
                            break;
                        }
                    }
                }
            }
        }
    }
}

void Widget::moveLeft()
{
    for (int y = 0; y < 4; y++){
        for (int x = 1; x < 4; x++){
            if (grids[x][y] != nullptr){
                for (int x_ = x-1; x_ >= 0; x_--){
                    if (grids[x_][y] != nullptr){
                        if (grids[x_][y]->getNum() == grids[x][y]->getNum()) {
                            moveGrid(x, y, x_, y);
                            break;
                        }
                        else {
                            moveGrid(x, y, x_+1, y);
                            break;
                        }
                    }
                    else{
                        if (x_ == 0){
                            moveGrid(x, y, 0, y);
                            break;
                        }
                    }
                }
            }
        }
    }
}

void Widget::gamePause()
{

}

void Widget::gameEnd()
{
    qDebug() << "gameEnd";
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
    if (moving){
        event->ignore();
        return;
    }
    switch (event->key()){
    case Qt::Key_Up:
        moving = true;
        moveUp();
        createGrid();
        break;
    case Qt::Key_Down:
        moving = true;
        moveDown();
        createGrid();
        break;
    case Qt::Key_Left:
        moving = true;
        moveLeft();
        createGrid();
        break;
    case Qt::Key_Right:
        moving = true;
        moveRight();
        createGrid();
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
    if (grids[x1][y1] == nullptr)
        return;
    if (x1 == x2 && y1 == y2)
        return;
    QPropertyAnimation* move = new QPropertyAnimation(grids[x1][y1], "geometry", this);
    move->setDuration(200);
    move->setStartValue(QRect(66+96*x1, 266+96*y1, 80, 80));
    move->setEndValue(QRect(66+96*x2, 266+96*y2, 80, 80));
    move->start();
    moving = true;
    QTimer::singleShot(200, this, [this, x1, y1, x2, y2]() {
        if (grids[x2][y2] == nullptr) {
            grids[x2][y2] = grids[x1][y1];
            grids[x1][y1] = nullptr;
        }
        else if (grids[x1][y1]->getNum() == grids[x2][y2]->getNum()) {
            grids[x2][y2]->setNum(2*grids[x2][y2]->getNum());
            grids[x1][y1]->hide();
            grids[x1][y1] = nullptr;
        }
        moving = false;
    });
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
            NumBlock* newBlock = new NumBlock(this);
            newBlock->setNum(2);
            newBlock->setTheme(gridblockColor, gridshadowColor);
            newBlock->setGeometry(66+96*x, 266+96*y, 80, 80);
            newBlock->show();
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
        qDebug() << line[0] << " " << line[1] << " " << line[2] << " " << line[3];
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
}

bool Widget::isEnd() const
{
    return false;
}
