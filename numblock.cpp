#include "numblock.h"
#include "ui_numblock.h"

NumBlock::NumBlock(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::NumBlock)
    , num(0)
    , theme(0)
{
    ui->setupUi(this);
    setFixedSize(100, 100);
}

NumBlock::~NumBlock()
{
    delete ui;
}

void NumBlock::setNum(const int n)
{
    if (n == 0){

    }
    else{
        num = n;
        ui->number->setText(QString::number(num));
    }
    update();
}

void NumBlock::setTheme(const int t)
{
    if (t < 6)
        theme = t;
    switch (t) {
    case 0:
        break;
    case 1:
        break;
    case 2:
        break;
    case 3:
        break;
    case 4:
        break;
    case 5:
        break;
    default:
        break;
    }
    update();
}
