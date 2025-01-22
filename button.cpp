#include "button.h"

Button::Button(QWidget *parent)
    : QWidget{parent}
{}

void Button::enterEvent(QEnterEvent *event)
{

}

void Button::leaveEvent(QEvent *event)
{

}

void Button::mousePressEvent(QMouseEvent *event)
{

}

void Button::mouseReleaseEvent(QMouseEvent *event)
{
    emit clicked();
}

void Button::paintEvent(QPaintEvent *event)
{

}
