#include "button.h"

Button::Button(QString str, QWidget *parent)
    : QWidget{parent}
    , text(str)
    , title(new QLabel(this))
{
    setFixedSize(78, 51);
    setStyleSheet("background-color:rgba(0,0,0,0)");
    title->setStyleSheet("color:white;font-size:20px;font-weight:bold;font-family:'华文宋体';");
    title->setAlignment(Qt::AlignCenter);
    title->setText(text);
    title->setGeometry(0, 0, 73, 46);
    buttonColor.setRgb(92, 213, 222);
    originColor.setRgb(92, 213, 222);
    enterColor.setRgb(0,217,217);
    pressColor.setRgb(0,133,178);
    shadowColor.setRgb(5, 132, 137);
}

void Button::enterEvent(QEnterEvent *event)
{
    buttonColor = enterColor;
    update();
}

void Button::leaveEvent(QEvent *event)
{
    buttonColor = originColor;
    update();
}

void Button::mousePressEvent(QMouseEvent *event)
{
    buttonColor = pressColor;
    update();
}

void Button::mouseReleaseEvent(QMouseEvent *event)
{
    buttonColor = enterColor;
    update();
    emit clicked();
}

void Button::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setPen(Qt::NoPen);

    QBrush brush(shadowColor);
    painter.setBrush(brush);
    painter.drawRect(5, 5, 73, 46);

    brush.setColor(buttonColor);
    painter.setBrush(brush);
    painter.drawRect(0, 0, 73, 46);

}
