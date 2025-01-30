#ifndef BUTTON_H
#define BUTTON_H

#include "qlabel.h"
#include <QWidget>
#include <QPainter>

class Button : public QWidget
{
    Q_OBJECT
protected:
    QString text;
    QLabel* title;
    QColor buttonColor;
    QColor originColor;
    QColor enterColor;
    QColor pressColor;
    QColor shadowColor;
public:
    explicit Button(QString str, QWidget *parent = nullptr);

protected:
    void enterEvent(QEnterEvent* event) override;
    void leaveEvent(QEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void paintEvent(QPaintEvent* event) override;

signals:
    void clicked();
};

#endif // BUTTON_H
