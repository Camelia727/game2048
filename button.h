#ifndef BUTTON_H
#define BUTTON_H

#include <QWidget>

class Button : public QWidget
{
    Q_OBJECT
protected:
    QSize size;
    QRect rect;
    QPixmap pic;
    QColor shadowColor;
public:
    explicit Button(QWidget *parent = nullptr);

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
