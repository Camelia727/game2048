#include "menu.h"
#include "ui_menu.h"

Menu::Menu(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Menu)
{
    ui->setupUi(this);
    setFixedSize(400, 150);
    mainbackColor.setRgb(51, 204, 204);
    setStyleSheet(QString("background-color:%1").arg(mainbackColor.name()));
    themeBtn = new Button("主题", this);
    resetBtn = new Button("重置", this);
    returnBtn = new Button("返回", this);
    exitBtn = new Button("退出", this);
    volumnSlider = new VolumnSlider(this);

    themeBtn->setGeometry(17, 83, 78, 51);
    resetBtn->setGeometry(113, 83, 78, 51);
    returnBtn->setGeometry(209, 83, 78, 51);
    exitBtn->setGeometry(305, 83, 78, 51);
    volumnSlider->setGeometry(16, 16, 400, 50);
}

Menu::~Menu()
{
    delete ui;
}

void Menu::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QBrush brush(mainbackColor);
    painter.setBrush(brush);
    painter.setPen(Qt::NoPen);
    painter.drawRect(this->rect());
}
