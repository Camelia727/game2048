#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
    , curScore(0)
    , topScore(0)
    , player(new QMediaPlayer(this))
    , audio(new QAudioOutput(this))
{
    ui->setupUi(this);
    setFixedSize(500,750);
    backgroundColor.setRgb(0, 153, 153);
    mainbackColor.setRgb(51, 204, 204);
    mainbtnColor.setRgb(92, 213, 222);
    gridColor.setRgb(224, 224, 224, 80);
    gridbackColor.setRgb(185, 251, 255);
    backshadowColor.setRgb(0, 101, 108);
    mainshadowColor.setRgb(10, 171, 182);
}

Widget::~Widget()
{
    delete ui;
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

}
