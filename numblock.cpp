#include "numblock.h"
#include "ui_numblock.h"

NumBlock::NumBlock(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::NumBlock)
    , num(1)
    , theme(0)
{
    ui->setupUi(this);
    setFixedSize(80, 80);
    colors = {QColor(115,255,255), QColor(153,229,255),
        QColor(77,210,255), QColor(0,191,255),
        QColor(115,185,255), QColor(38,147,255),
        QColor(153,179,255), QColor(115,150,255),
        QColor(38,92,255), QColor(153,153,255),
        QColor(115,115,255), QColor(77,77,255),
        QColor(38,38,255), QColor(0,0,217),
        QColor(0,0,178), QColor(0,35,140)
    };
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
    QString text = QString::number(pow(2, num));
    ui->number->setText(text);
    ui->shadow->setText(text);
    gridColor = colors[n-1];
    update();
}

void NumBlock::setTheme(const QColor shadow)
{
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
