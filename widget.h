#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPainter>
#include <QMediaPlayer>
#include <QAudioOutput>

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

protected:
    void paintEvent(QPaintEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;

private:
    Ui::Widget *ui;

    int curScore;
    int topScore;
    QMediaPlayer* player;
    QAudioOutput* audio;
    QColor backgroundColor;
    QColor mainbackColor;
    QColor mainbtnColor;
    QColor gridColor;
    QColor gridbackColor;
    QColor backshadowColor;
    QColor mainshadowColor;
};
#endif // WIDGET_H
