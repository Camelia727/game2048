#include "numblock.h"
#include "ui_numblock.h"

NumBlock::NumBlock(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::NumBlock)
    , num(0)
    , theme(0)
{
    ui->setupUi(this);
    setFixedSize(80, 80);
    ui->number->setStyleSheet("color:rgb(255,255,255);");
    ui->shadow->setStyleSheet("color:rgb(0, 178, 178);");
    ui->number->raise();
}

NumBlock::~NumBlock()
{
    delete ui;
}

void NumBlock::setNum(const int n)
{
    num = n;
    QString text = QString::number(num);
    ui->number->setText(text);
    ui->shadow->setText(text);
    update();
}

void NumBlock::setTheme(const QColor grid, const QColor shadow)
{
    gridColor = grid;
    shadowColor = shadow;
    update();
}

void NumBlock::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setPen(Qt::NoPen);

    QBrush brush(shadowColor);
    painter.setBrush(brush);
    painter.drawRect(4, 4, 76, 76);

    brush.setColor(gridColor);
    painter.setBrush(brush);
    painter.drawRect(0, 0, 76, 76);
}
