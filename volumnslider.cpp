#include "volumnslider.h"

int nMin = 0;
int nMax = 100;
int nSingleStep = 10;
int nTick = 10;
int nWidth = 370;
int nHeight = 50;

VolumnSlider::VolumnSlider(QWidget* parent)
    : QSlider{parent}
{
    setStyleSheet("");
    setOrientation(Qt::Horizontal);
    setFixedSize(nWidth,nHeight);
    setMinimum(nMin);
    setMaximum(nMax);
    setTickInterval(nTick);
    setValue(nMax);
    setStyleSheet("QSlider::groove:horizontal{height:12px; left:0px; right:0px; border:0px; border-radius:6px; background:rgb(0,0,0);}    \
                   QSlider::handle:horizontal{width:24px; background:#73FFFF; border-radius:12px; margin:-6px 0px;}  \
                   QSlider::sub-page:horizontal{background:#99FFFF; border:0px; border-radius:6px;}");

}

void VolumnSlider::keyPressEvent(QKeyEvent *event)
{
    event->ignore();
}

void VolumnSlider::mousePressEvent(QMouseEvent *event)
{
    int pointPos = ((double)event->pos().x()) / (this->width() * (nMax - nMin) + nMin);
    if(pointPos != 0){
        if(abs(pointPos - this->value()) > nTick){
            this->setValue(pointPos);
        }
    }
    else{
        QSlider::mousePressEvent(event);
    }
}

void VolumnSlider::mouseReleaseEvent(QMouseEvent *event)
{
    int currentX = event->pos().x();
    float per = currentX *1.0 /this->width();
    if(per > 1) per = 1;
    else if(per < 0) per = 0;
    int value = per*(this->maximum() - this->minimum()) + this->minimum();
    this->setValue(value);
    QSlider::mousePressEvent(event);

}

void VolumnSlider::paintEvent(QPaintEvent *event)
{
    QStylePainter p(this);
    QStyleOptionSlider opt;
    initStyleOption(&opt);

    // 获取滑块的大小
    QRect handle = style()->subControlRect(QStyle::CC_Slider, &opt, QStyle::SC_SliderHandle, this);

    // draw the slider (this is basically copy/pasted from QSlider::paintEvent)
    opt.subControls = QStyle::SC_SliderGroove;
    p.drawComplexControl(QStyle::CC_Slider, opt);
    // draw the slider handle
    opt.subControls = QStyle::SC_SliderHandle;
    p.drawComplexControl(QStyle::CC_Slider, opt);
}

