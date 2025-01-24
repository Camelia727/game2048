#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTimer>
#include <QPainter>
#include <QKeyEvent>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QRandomGenerator>
#include <QPropertyAnimation>
#include "numblock.h"

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
    QColor getGridColor() const {return gridColor;}
    QColor getGridshadowColor() const {return gridshadowColor;}

protected:
    void paintEvent(QPaintEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;

private:
    Ui::Widget *ui;

    bool moving;
    bool pausing;
    int curScore;
    int topScore;
    QMediaPlayer* player;
    QAudioOutput* audio;
    QTimer* durationTimer;
    QColor backgroundColor;
    QColor mainbackColor;
    QColor mainbtnColor;
    QColor gridColor;
    QColor gridbackColor;
    QColor gridblockColor;
    QColor backshadowColor;
    QColor mainshadowColor;
    QColor gridshadowColor;
    QList<QUrl> bgms;
    QList<QList<int>> numbers;
    QList<QList<NumBlock*>> grids;

    void moveGrid(int x1, int y1, int x2, int y2);
    void moveUp();
    void moveDown();
    void moveRight();
    void moveLeft();
    void createGrid();
    bool isEnd() const;
    void gamePause();
    void gameEnd();

public slots:
    void playBgm();
    void acceptMove();

};
#endif // WIDGET_H
