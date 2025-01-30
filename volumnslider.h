#ifndef VOLUMNSLIDER_H
#define VOLUMNSLIDER_H

#include <QObject>
#include <QSlider>
#include <QtCore>
#include <QStylePainter>
#include <QStyleOptionSlider>
#include <QMouseEvent>
#include "button.h"

class VolumnSlider : public QSlider
{
    Q_OBJECT
public:
    VolumnSlider(QWidget* parent = nullptr);

signals:
    void sliderValue(float);

private:
    void keyPressEvent(QKeyEvent* event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);
};

#endif // VOLUMNSLIDER_H
